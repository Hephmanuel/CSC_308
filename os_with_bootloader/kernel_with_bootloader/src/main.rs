#![no_std]
#![no_main]

mod writer;  // Declare the writer module

use writer::writer::FrameBufferWriter;  // Use FrameBufferWriter from the writer module
use writer::constants::font_constants;    // Access constants from the constants.rs file
use bootloader_api::config::Mapping;
use x86_64::instructions::hlt;
use core::fmt::Write; // Use the Write trait from core

/// Use the entry_point macro to register the entry point function.
pub static BOOTLOADER_CONFIG: bootloader_api::BootloaderConfig = {
    let mut config = bootloader_api::BootloaderConfig::new_default();
    config.mappings.physical_memory = Some(Mapping::Dynamic);
    config.kernel_stack_size = 100 * 1024; // 100 KiB
    config
};

bootloader_api::entry_point!(my_entry_point, config = &BOOTLOADER_CONFIG);

/// Entry point of the kernel.
fn my_entry_point(boot_info: &'static mut bootloader_api::BootInfo) -> ! {
    // Get framebuffer information and mutable buffer
    let frame_buffer_info = boot_info.framebuffer.as_mut().unwrap().info();
    let buffer = boot_info.framebuffer.as_mut().unwrap().buffer_mut();

    // Initialize the framebuffer writer
    let mut frame_buffer_writer = FrameBufferWriter::new(buffer, frame_buffer_info);

    // Write lines to test escape sequences
let test_string ="Hello, world!\nThis is a test.\n Blue Text\tIndented Text";
writeln!(frame_buffer_writer, "{}", test_string).unwrap();  // Pass the string to the framebuffer writer

    // Test multiple lines with newlines
    for i in 1..=10 {
        writeln!(frame_buffer_writer, "Line number: {}", i).unwrap();  // Write lines using writeln!
    }

    // Enter an infinite loop to halt the CPU
    loop {
        hlt(); // Stop x86_64 from being unnecessarily busy while looping
    }
}

/// Panic handler to handle kernel panics.
#[panic_handler]
fn panic(_info: &core::panic::PanicInfo) -> ! {
    loop {
        hlt(); // Halt the CPU to prevent unnecessary activity
    }
}
