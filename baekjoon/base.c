#include <stdio.h>

int main(void) {
#ifndef ONLINE_JUDGE  // 해당 문단 무시됨
  freopen("baekjoon/input.txt", "r", stdin);
  freopen("baekjoon/output.txt", "w", stdout);
#endif

  // input 방법
  int data, data2;
  scanf("%d %d", &data);

  // output 방법
  printf("%d", data);

  return 0;
}