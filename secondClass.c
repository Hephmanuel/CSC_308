#include <stdio.h>

int main(){
  int age = 90;
  printf("Manuela is %d years old.\n", age);
  puts("Hello World"); //Does not take formatted printing
  puts("Hello World");

  char gender[] ="M";
  char name[20];
  
  //scanf("%s", &name);

      printf("Characters in the name:\n");
    for (int i = 0; name[i] != '\0'; i++) {
        printf("name[%d] = %c\n", i, name[i]);
    }
  return 0;
}

