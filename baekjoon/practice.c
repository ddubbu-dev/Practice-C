#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {
  printf("================ with str arr (correct) ================\n");

  char name1[3];
  printf("Enter the name: ");
  scanf("%s", name1);
  printf("%s\n", name1);
  printf("sizeof(name1)=%d\n", sizeof(name1));

  printf("================ with pointer + str arr (wrong) ================\n");
  char *name2[3];
  printf("Enter the name: \n");
  scanf("%s", &name2);
  printf("%s\n", name1);
  printf("sizeof(name2)=%d\n", sizeof(name2));

  return 0;
}