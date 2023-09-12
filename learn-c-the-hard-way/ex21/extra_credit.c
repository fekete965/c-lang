#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
  printf("\n-------------------------\n");
  printf("\tExercise 21\n");

  printf("-------------------------\n");
  printf("\tINT 8\n");
  printf("-------------------------\n");
  printf("INT8_MIN %i\n", INT8_MIN);               // -128
  printf("INT8_MAX %i\n", INT8_MAX);               // 127
  printf("UINT8_MAX %i\n", UINT8_MAX);             // 255
  printf("INT_LEAST8_MIN %i\n", INT_LEAST8_MIN);   // -128
  printf("INT_LEAST8_MAX %i\n", INT_LEAST8_MAX);   // 127
  printf("UINT_LEAST8_MAX %i\n", UINT_LEAST8_MAX); // 255
  printf("INT_FAST8_MIN %i\n", INT_FAST8_MIN);     // -128
  printf("INT_FAST8_MAX %i\n", INT_FAST8_MAX);     // 127
  printf("UINT_FAST8_MAX %i\n", UINT_FAST8_MAX);   // 255

  printf("\n-------------------------\n");
  printf("\tINT 16\n");
  printf("-------------------------\n");
  printf("INT16_MIN %i\n", INT16_MIN);               // -32768
  printf("INT16_MAX %i\n", INT16_MAX);               // 23767
  printf("UINT16_MAX %i\n", UINT16_MAX);             // 65535
  printf("INT_LEAST16_MIN %i\n", INT_LEAST16_MIN);   // -32768
  printf("INT_LEAST16_MAX %i\n", INT_LEAST16_MAX);   // 32767
  printf("UINT_LEAST16_MAX %i\n", UINT_LEAST16_MAX); // 65535
  printf("INT_FAST16_MIN %i\n", INT_FAST16_MIN);     // -32768
  printf("INT_FAST16_MAX %i\n", INT_FAST16_MAX);     // 32767
  printf("UINT_FAST16_MAX %i\n", UINT_FAST16_MAX);   // 65535

  printf("\n-------------------------\n");
  printf("\tINT 32\n");
  printf("-------------------------\n");
  printf("INT32_MIN %i\n", INT32_MIN);               // -2147483648
  printf("INT32_MAX %i\n", INT32_MAX);               // 2147483647
  printf("UINT32_MAX %u\n", UINT32_MAX);             // 4294967295
  printf("INT_LEAST32_MIN %i\n", INT_LEAST32_MIN);   // -2147483648
  printf("INT_LEAST32_MAX %i\n", INT_LEAST32_MAX);   // 2147483647
  printf("UINT_LEAST32_MAX %u\n", UINT_LEAST32_MAX); // 4294967295
  printf("INT_FAST32_MIN %i\n", INT_FAST32_MIN);     // -2147483648
  printf("INT_FAST32_MAX %i\n", INT_FAST32_MAX);     // 2147483647
  printf("UINT_FAST32_MAX %u\n", UINT_FAST32_MAX);   // 4294967295

  printf("\n-------------------------\n");
  printf("\tINT 64\n");
  printf("-------------------------\n");
  printf("INT64_MIN %lli\n", INT64_MIN);               // -9223372036854775808
  printf("INT64_MAX %lli\n", INT64_MAX);               // 9223372036854775807
  printf("UINT64_MAX %llu\n", UINT64_MAX);             // 18446744073709551615
  printf("INT_LEAST64_MIN %lli\n", INT_LEAST64_MIN);   // -9223372036854775808
  printf("INT_LEAST64_MAX %lli\n", INT_LEAST64_MAX);   // 9223372036854775807
  printf("UINT_LEAST64_MAX %llu\n", UINT_LEAST64_MAX); // 18446744073709551615
  printf("INT_FAST64_MIN %lli\n", INT_FAST64_MIN);     // -9223372036854775808
  printf("INT_FAST64_MAX %lli\n", INT_FAST64_MAX);     // 9223372036854775807
  printf("UINT_FAST64_MAX %llu\n", UINT_FAST64_MAX);   // 18446744073709551615

  printf("\n-------------------------\n");
  printf("\tINT PTR\n");
  printf("-------------------------\n");
  printf("INTPTR_MIN %li\n", INTPTR_MIN);   // -9223372036854775808
  printf("INTPTR_MAX %li\n", INTPTR_MAX);   // 9223372036854775807
  printf("UINTPTR_MAX %lu\n", UINTPTR_MAX); // 18446744073709551615

  return 0;
}
