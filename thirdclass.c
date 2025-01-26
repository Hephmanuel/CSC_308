#include <stdio.h>

int main(){
  int accountBalance = 10000;
  int credit = 50000;

  int newVariable = accountBalance + credit;
  //accountBalance+= credit;

  int isAdult = 1;
  int isPAUstudent = 0;

  if isAdult == 1||isPAUstudent == 0 {
    printf("You can get free lunch\n")
  }
  else{
    printf("No free lunch for you!\n")
  }

  printf("%i", newVariable);

int a  = 5;
int b = 3;
printf("%i", a & b);

  return 0;
}