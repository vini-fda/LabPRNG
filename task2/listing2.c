#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <openssl/aes.h>
#include <openssl/crypto.h>

#define KEYSIZE 16
#define BUF_SIZE_BYTES 16
#define PLAINTEXT "255044462d312e350a25d0d4c5d80a34"
#define CIPHERTEXT "d06bf9d0dab8e8ef880660d2af65aa82" // desired ciphertext
#define IV "09080706050403020100A2B2C2D2E2F2"

long long seconds_ull(char* restrict str_time_since_epoch) {
  long long t = strtoull(str_time_since_epoch, NULL, 10);
  errno = 0;
  if (errno != 0) {
    fprintf(stderr, "Error while converting argument: %s\n", strerror(errno));
    exit(errno);
  }
  return t;
}

char perfect_match(unsigned char* ciphertext, unsigned char* desired_ciphertext) {
  for (int i = 0; i < BUF_SIZE_BYTES; i++) {
    if (ciphertext[i] != desired_ciphertext[i])
      return 1;
  }
  return 0;
}

void main(int argc, char** argv) {
  if (argc != 3) {
    return;
  }

  char* s1 = argv[1];
  char* s2 = argv[2];

  long long t1 = seconds_ull(s1);
  long long t2 = seconds_ull(s2);
  if (t2 < t1) {
    fprintf(stderr, "Second argument (t2) should be bigger than first argument (t1).\n");
  }

  unsigned char desired_ciphertext[BUF_SIZE_BYTES];
  if (!OPENSSL_hexstr2buf_ex(desired_ciphertext, BUF_SIZE_BYTES, NULL, CIPHERTEXT, '\0')) {
    fprintf(stderr, "Error converting hexadecimal ciphertext.\n");
    exit(1);
  }
  unsigned char plaintext[BUF_SIZE_BYTES];
  if (!OPENSSL_hexstr2buf_ex(plaintext, BUF_SIZE_BYTES, NULL, PLAINTEXT, '\0')) {
    fprintf(stderr, "Error converting hexadecimal plaintext.\n");
    exit(1);
  }
  printf("plaintext = ");
  for (int i = 0; i < BUF_SIZE_BYTES; i++) {
    printf("%.2x", plaintext[i]);
  }
  printf("\n");
  unsigned char iv[BUF_SIZE_BYTES];
  if (!OPENSSL_hexstr2buf_ex(iv, BUF_SIZE_BYTES, NULL, IV, '\0')) {
    fprintf(stderr, "Error converting hexadecimal initialization vector (IV).\n");
    exit(1);
  }
  printf("ivec = ");
  for (int i = 0; i < BUF_SIZE_BYTES; i++) {
    printf("%.2x", iv[i]);
  }
  printf("\n");

  printf("search size = %llu\n", t2 - t1 + 1);

  for (long long t = t1; t <= t2; t++) {
    srand(t);

    char key[KEYSIZE];
    for (int i = 0; i < KEYSIZE; i++) {
      key[i] = rand() % 256;
    }

    AES_KEY aes_key;
    if (AES_set_encrypt_key((unsigned char*)key, 8 * KEYSIZE, &aes_key) < 0) {
      fprintf(stderr, "Error setting AES encryption key.\n");
      exit(1);
    }
    unsigned char ciphertext[BUF_SIZE_BYTES];
    AES_cbc_encrypt(plaintext, ciphertext, BUF_SIZE_BYTES, &aes_key, iv, AES_ENCRYPT);
    if (perfect_match(ciphertext, desired_ciphertext)) {
      printf("found desired key: ");
      for (int i = 0; i < KEYSIZE; i++) {
        printf("%.2x", (unsigned char)key[i]);
      }
      printf("\n");
      printf("seed = %llu\n", t);
      return;
    }
  }
}
