use core::{
  fmt::{self, Write},
  ptr,
};
use bootloader_api::info::{FrameBufferInfo, PixelFormat};
use crate::writer::constants::font_constants;
use crate::writer::constants::font_constants::{BACKUP_CHAR, CHAR_RASTER_HEIGHT, FONT_WEIGHT};
use noto_sans_mono_bitmap::{get_raster, RasterizedChar};

/// Additional vertical space between lines.
const LINE_SPACING: usize = 2;

/// Additional horizontal space between characters.
const LETTER_SPACING: usize = 0;

/// Padding from the border to prevent the font from being too close to the edge.
const BORDER_PADDING: usize = 1;

/// Returns the raster of the given char or the raster of [font_constants::BACKUP_CHAR].
fn get_char_raster(c: char) -> RasterizedChar {
  fn get(c: char) -> Option<RasterizedChar> {
      get_raster(c, FONT_WEIGHT, CHAR_RASTER_HEIGHT)
  }
  get(c).unwrap_or_else(|| get(BACKUP_CHAR).expect("Should get raster of backup char."))
}

/// Allows logging text to a pixel-based framebuffer.
pub struct FrameBufferWriter {
  framebuffer: &'static mut [u8],
  info: FrameBufferInfo,
  x_pos: usize,
  y_pos: usize,
}

impl FrameBufferWriter {
  /// Creates a new logger that uses the given framebuffer.
  pub fn new(framebuffer: &'static mut [u8], info: FrameBufferInfo) -> Self {
      let mut logger = Self {
          framebuffer,
          info,
          x_pos: 0,
          y_pos: 0,
      };
      logger.clear();
      logger
  }

  /// Moves to the next line and resets the x position.
  fn newline(&mut self) {
      self.y_pos += CHAR_RASTER_HEIGHT.val() + LINE_SPACING;
      self.carriage_return();
  }

  /// Resets the x position to the border padding.
  fn carriage_return(&mut self) {
      self.x_pos = BORDER_PADDING;
  }

  /// Erases all text on the screen and resets the cursor position.
  pub fn clear(&mut self) {
      self.x_pos = BORDER_PADDING;
      self.y_pos = BORDER_PADDING;
      self.framebuffer.fill(0);
  }

  /// Returns the width of the framebuffer.
  fn width(&self) -> usize {
      self.info.width
  }

  /// Returns the height of the framebuffer.
  fn height(&self) -> usize {
      self.info.height
  }

  /// Writes a single character to the framebuffer, handling special control characters.
  fn write_char(&mut self, c: char) {
      match c {
          '\n' => self.newline(),
          '\r' => self.carriage_return(),
          c => {
              let new_xpos = self.x_pos + font_constants::CHAR_RASTER_WIDTH;
              if new_xpos >= self.width() {
                  self.newline();
              }
              let new_ypos = self.y_pos + CHAR_RASTER_HEIGHT.val() + BORDER_PADDING;
              if new_ypos >= self.height() {
                  self.clear();
              }
              self.write_rendered_char(get_char_raster(c));
          }
      }
  }

  /// Prints a rendered character into the framebuffer and updates the x position.
  fn write_rendered_char(&mut self, rendered_char: RasterizedChar) {
      for (y, row) in rendered_char.raster().iter().enumerate() {
          for (x, byte) in row.iter().enumerate() {
              self.write_pixel(self.x_pos + x, self.y_pos + y, *byte);
          }
      }
      self.x_pos += rendered_char.width() + LETTER_SPACING;
  }

  /// Writes a single pixel to the framebuffer with the given intensity.
  fn write_pixel(&mut self, x: usize, y: usize, intensity: u8) {
      let pixel_offset = y * self.info.stride + x;
      let color = match self.info.pixel_format {
          PixelFormat::Rgb => [intensity, intensity, intensity / 2, 0],
          PixelFormat::Bgr => [intensity / 2, intensity, intensity, 0],
          PixelFormat::U8 => [if intensity > 200 { 0xf } else { 0 }, 0, 0, 0],
          other => {
              self.info.pixel_format = PixelFormat::Rgb;
              panic!("Pixel format {:?} not supported in logger", other);
          }
      };
      let bytes_per_pixel = self.info.bytes_per_pixel;
      let byte_offset = pixel_offset * bytes_per_pixel;
      self.framebuffer[byte_offset..(byte_offset + bytes_per_pixel)]
          .copy_from_slice(&color[..bytes_per_pixel]);
      let _ = unsafe { ptr::read_volatile(&self.framebuffer[byte_offset]) };
  }
}

unsafe impl Send for FrameBufferWriter {}
unsafe impl Sync for FrameBufferWriter {}

impl Write for FrameBufferWriter {
  fn write_str(&mut self, s: &str) -> fmt::Result {
      for c in s.chars() {
          self.write_char(c);
      }
    Ok(())}
}
