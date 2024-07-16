#ifndef CFLAG_H_c02b7d24a066adb747fdeb12deb21bfa
#define CFLAG_H_c02b7d24a066adb747fdeb12deb21bfa

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef CFLAG_STR
#undef CFLAG_STR_
#define CFLAG_STR_(flag) # flag
#define CFLAG_STR(flag) CFLAG_STR_(flag)

#undef CFLAG_FMT
#define CFLAG_FMT(flag) _Generic((flag) \
        , bool: "B" \
        , char: "%c" \
        , uint8_t: "%" PRIu8 \
        , uint16_t: "%" PRIu16 \
        , uint32_t: "%" PRIu32 \
        , uint64_t: "%" PRIu64 \
        , int8_t: "%" PRIi8 \
        , int16_t: "%" PRIi16 \
        , int32_t: "%" PRIi32 \
        , int64_t: "%" PRIi64 \
        , float: "%f" \
        , double: "%lf" \
        , default: "S" \
)

#undef CFLAG
#define CFLAG(flag) CFLAG_(CFLAG_STR(flag), sizeof(CFLAG_STR(flag)) - 1, CFLAG_FMT(flag), &argc, argv, (void *restrict const) &flag, sizeof(flag))
static inline void CFLAG_(char const *restrict const name, size_t name_len, char const *restrict const fmt, int *restrict const pargc, char **argv, void *restrict const data, size_t data_size) {
  for (int i = 0; i < *pargc; ++i) {
    if ('-' == argv[i][0] && 0 == memcmp(name, argv[i] + 1, name_len)) {
      if ('=' == argv[i][name_len + 1]) {
        if ('\0' != argv[i][name_len + 2]) {
          if ('S' == fmt[0])
            *(char **)data = argv[i] + name_len + 2;
          else if ('B' == fmt[0])
            goto here;
          else
            sscanf(argv[i] + name_len + 2, fmt, data);
        } else {
          if ('B' == fmt[0])
            memset(data, 1, data_size);
          else
            memset(data, 0, data_size);
        }
        memmove(argv + i, argv + i + 1, ((*pargc)-- - (i + 1)) * sizeof(*argv));
        return;
      } else if ('\0' == argv[i][name_len + 1]) {
        if (i + 1 < *pargc && '-' != argv[i + 1][0]) {
          if ('S' == fmt[0])
            *(char **)data = argv[i + 1];
          else if ('B' == fmt[0])
            goto here;
          else
            sscanf(argv[i + 1], fmt, data);
          memmove(argv + i, argv + i + 2, (*pargc - (i + 2)) * sizeof(*argv));
          *pargc -= 2;
        } else {
          here: if ('B' == fmt[0])
            memset(data, 1, data_size);
          else
            memset(data, 0, data_size);
          memmove(argv + i, argv + i + 1, ((*pargc)-- - (i + 1)) * sizeof(*argv));
        }
        return;
      }
    }
  }
}

#define CFLAGS_2_(_0,_1) CFLAG(_0);CFLAG(_1)
#define CFLAGS_3_(_0,_1,_2) CFLAG(_0);CFLAGS_2_(_1,_2)
#define CFLAGS_4_(_0,_1,_2,_3) CFLAG(_0);CFLAGS_3_(_1,_2,_3)
#define CFLAGS_5_(_0,_1,_2,_3,_4) CFLAG(_0);CFLAGS_4_(_1,_2,_3,_4)
#define CFLAGS_6_(_0,_1,_2,_3,_4,_5) CFLAG(_0);CFLAGS_5_(_1,_2,_3,_4,_5)
#define CFLAGS_7_(_0,_1,_2,_3,_4,_5,_6) CFLAG(_0);CFLAGS_6_(_1,_2,_3,_4,_5,_6)
#define CFLAGS_8_(_0,_1,_2,_3,_4,_5,_6,_7) CFLAG(_0);CFLAGS_7_(_1,_2,_3,_4,_5,_6,_7)
#define CFLAGS_9_(_0,_1,_2,_3,_4,_5,_6,_7,_8) CFLAG(_0);CFLAGS_8_(_1,_2,_3,_4,_5,_6,_7,_8)
#define CFLAGS_10_(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9) CFLAG(_0);CFLAGS_9_(_1,_2,_3,_4,_5,_6,_7,_8,_9)
#define CFLAGS_11_(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10) CFLAG(_0);CFLAGS_10_(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10)
#define CFLAGS_12_(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11) CFLAG(_0);CFLAGS_11_(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11)
#define CFLAGS_13_(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12) CFLAG(_0);CFLAGS_12_(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12)
#define CFLAGS_14_(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13) CFLAG(_0);CFLAGS_13_(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13)
#define CFLAGS_15_(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14) CFLAG(_0);CFLAGS_14_(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14)
#define CFLAGS_16_(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15) CFLAG(_0);CFLAGS_15_(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15)
#define CFLAGS_C_(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,m,...) m
#define CFLAGS(...) CFLAGS_C_(__VA_ARGS__,CFLAGS_16_,CFLAGS_15_,CFLAGS_14_,CFLAGS_13_,CFLAGS_12_,CFLAGS_11_,CFLAGS_10_,CFLAGS_9_,CFLAGS_8_,CFLAGS_7_,CFLAGS_6_,CFLAGS_5_,CFLAGS_4_,CFLAGS_3_,CFLAGS_2_,CFLAG)(__VA_ARGS__)

#endif /* CFLAG_H_ */
