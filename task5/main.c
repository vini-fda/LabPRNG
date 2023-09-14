#include <stdlib.h>
#include <stdio.h>

#define LEN 32 // 256 bits


int main() {
  unsigned char key[LEN];
  FILE* random = fopen("/dev/urandom", "r");
  fread(key, sizeof(unsigned char) * LEN, 1, random);
  fclose(random);
  printf("key = ");
  for (int i = 0; i < LEN; i++) {
    printf("%.2x", key[i]);
  }
  printf("\n");
}
