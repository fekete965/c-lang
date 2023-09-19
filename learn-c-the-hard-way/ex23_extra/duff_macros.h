#ifndef __duff_macros_h__
#define __duff_macros_h__

#define dd_create_sixteen_cases(X) \
  dd_create_eight_cases((X))\
  dd_create_eight_cases(((X) - 8))\

#define dd_create_eight_cases(X) \
  dd_create_four_cases((X))\
  dd_create_four_cases(((X) - 4))\

#define dd_create_four_cases(X) \
  dd_create_two_cases((X))\
  dd_create_two_cases(((X) - 2))\

#define dd_create_two_cases(X) \
  dd_create_case(((X) - 1))\
  dd_create_case(((X) - 2))\

#define dd_create_case(N) case (N): *to++ = *from++;

#define dd_start_device(X, C) int n = ((C) + (X - 1)) / (X);\
switch ((C) % X) { case 0: do { *to++ = *from++;\

#define dd_end_device } while (--n > 0); }

#endif
