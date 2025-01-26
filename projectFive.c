#include <stdio.h>

int main() {
    printf("Select your input type:\n1 - Character\n2 - Float\n3 - Integer\nSelection: ");
    
    int inputType;
    scanf("%i", &inputType);  // Correctly read the inputType

    char charChoice;

    switch (inputType) {
        case 1:  // For character selection
            // Clear the buffer before reading character
            getchar();  // This handles the newline character left in the buffer by previous scanf

            printf("Select a character: ");
            scanf("%c", &charChoice);  // Now correctly read a character

            int ascii_value = (int) charChoice;  // Get ASCII value of the character
            printf("You selected '%c'\n", charChoice);  // Print the selected character
            printf("The ASCII equivalent is: %d\n", ascii_value);  // Print ASCII value

            printf("Next four characters (in multiples of three):\n");
            for (int i = 1; i <= 4; i++) {
                char newChar = (char)(ascii_value + i * 3);  // Calculate the next character in multiples of 3
                printf("%c ", newChar);  // Print the new character
            }
            printf("\n");

            // Print the size of the charChoice variable
            printf("The size of the operator is: %zu bytes\n", sizeof(charChoice));
            break;

        case 2:
            
            getchar();  // This handles the newline character left in the buffer by previous scanf
            float floatChoice;
            printf("Enter a decimal number: ");
            scanf("%f", &floatChoice);  // Now correctly read a character

            int ascii_value2 = (int) floatChoice;  // Get ASCII value of the character
            printf("You selected '%c'\n", floatChoice);  // Print the selected character
            printf("The ASCII equivalent is: %d\n", ascii_value2);  // Print ASCII value

            printf("Next four characters (in multiples of three):\n");
            for (int i = 1; i <= 4; i++) {
                float newFloat = (newFloat + i * 3);  // Calculate the next character in multiples of 3
                printf("%f ", newFloat);  // Print the new character
            }
            printf("\n");

            // Print the size of the charChoice variable
            printf("The size of the operator is: %zu bytes\n", sizeof(floatChoice));
            break;

        case 3:
           getchar();  // This handles the newline character left in the buffer by previous scanf

            printf("Enter an integer: ");
            int intChoice;
            scanf("%i", &intChoice);  // Now correctly read a character

            char charRepresentation = (char) intChoice;  // Get ASCII value of the character
            int ascii_value3 = (int)charRepresentation;
            printf("You selected '%c'\n", intChoice);  // Print the selected character
            printf("The ASCII equivalent is: %d\n", ascii_value3);  // Print ASCII value

            printf("Next four characters (in multiples of three):\n");
            for (int i = 1; i <= 4; i++) {
                int newInt = (newInt + i * 3);  // Calculate the next character in multiples of 3
                printf("%i ", newInt);  // Print the new character
            }
            printf("\n");

            // Print the size of the charChoice variable
            printf("The size of the operator is: %zu bytes\n", sizeof(intChoice));

            break;

        default:
            printf("Invalid selection.\n");
            break;
    }

    return 0;
}
