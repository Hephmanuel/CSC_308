#include <stdio.h>


int main(){
printf("Welcome to the cafeteria. Choose a food item:\n");
    printf("P - Poundo Yam/Edinkinko Soup - N3,200\n");
    printf("F - Fried Rice and Chicken - N3,000\n");
    printf("A - Amala and Ewedu Soup - N2,500\n");
    printf("E - Eba and Egusi Soup - N2,000\n");
    printf("W - White Rice and Stew - N2,500\n");
    printf("\nChoice: ");
    
char choice;
scanf(" %c", &choice);
int priceTotal = 0;

switch(choice){
  case('P'):
    priceTotal = 3200;
    break;
  case('F'):
    priceTotal = 3000;
    break;
  case('A'):
    priceTotal = 2500;
    break;
  case('E'):
    priceTotal = 2000;
    break;
  case('W'):
    priceTotal = 2500;
    break;
  default:
    printf("No match found.\n");
    return 0;
}


printf("Your total charge = N%i\n", priceTotal);
}
