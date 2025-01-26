#include <stdio.h>
int main(){

  int isExperience;
  int age;

  printf("Enter your age: ");
  scanf("%i", &age);
  printf("Do you have experience?\nYes - 1\nNo - 0\n");
  scanf("%i", &isExperience);

  if (isExperience == 1 && age >=40){
    printf("Salary is N560,000");
  }
  else if(isExperience == 1 && age >=30 && age <=40){
    printf("Salary is N480,000");
  }
  else if(isExperience == 1 && age <=28){
    printf("Salary is N300,000");
  }
  else if(isExperience == 0){
    printf("Salary is N100,000");
  }
  else{
    printf("You have no salary!");
  }
}