//Write a C program that accepts a character between A to J and prints the next 6 characters.
#include <stdio.h>

int main() {
    char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l'};
    

    char choice;
    printf("Enter your alphabet choice: ");
    scanf(" %c", &choice); // Use a space before %c to consume any leftover newline

    // Check if the entered character is in the alphabet array
    for (int i = 0; i < 9; i++) {
        if (choice == alphabet[i]) {
            printf("Your selection is: %c\n", choice);
            printf("%c  ", ++choice);
            printf("%c  ", ++choice);
            printf("%c  ", ++choice);
            printf("%c  ", ++choice);
            printf("%c  ", ++choice);
            printf("%c  ", ++choice);

            break;
          
        }
        
    }

}


