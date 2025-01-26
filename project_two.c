#include <stdio.h>
//Grade calculator
int main(){

  int CSC201, CSC205, STA205;
  printf("Enter score for CSC201: ");
  scanf("%i", &CSC201);

  printf("Enter score for CSC205: ");
  scanf("%i", &CSC205);

  printf("Enter score for STA205: ");
  scanf("%i", &STA205);

  float total, average, percentage;
  total = CSC201 + CSC205 + STA205;
  printf("Total = %.2f\n", total);
  average = total/3;
  printf("Average = %.2f\n",average);
  percentage = total/ 300 * 100;
   printf("Percentage = %.2f%%\n", percentage); 
  

  }