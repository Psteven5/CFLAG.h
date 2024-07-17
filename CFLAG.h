/*
BSD 3-Clause License

Copyright (c) 2024, Pieter Stevens

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CFLAG_H_c02b7d24a066adb747fdeb12deb21bfa
#define CFLAG_H_c02b7d24a066adb747fdeb12deb21bfa

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#undef CFLAG_STR
#undef CFLAG_STR_
#define CFLAG_STR_(flag) # flag
#define CFLAG_STR(flag) CFLAG_STR_(flag)

#undef CFLAG_FMT
#define CFLAG_FMT(flag) _Generic((flag) \
        , bool: "B" \
        , char: "%c" \
        , uint8_t: "%" SCNu8 \
        , uint16_t: "%" SCNu16 \
        , uint32_t: "%" SCNu32 \
        , uint64_t: "%" SCNu64 \
        , int8_t: "%" SCNi8 \
        , int16_t: "%" SCNi16 \
        , int32_t: "%" SCNi32 \
        , int64_t: "%" SCNi64 \
        , float: "%f" \
        , double: "%lf" \
        , default: "S" \
)

#undef CFLAG
#define CFLAG(flag) CFLAG_(CFLAG_STR(flag), sizeof(CFLAG_STR(flag)) - 1, CFLAG_FMT(flag), &argc, argv, &flag, sizeof(flag))
static inline void CFLAG_(char const *restrict const name, size_t name_len, char const *restrict const fmt, int *restrict const pargc, char **argv, void *data, size_t data_size) {
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
#define CFLAGS_3_(_0,...) CFLAG(_0);CFLAGS_2_(__VA_ARGS__)
#define CFLAGS_4_(_0,...) CFLAG(_0);CFLAGS_3_(__VA_ARGS__)
#define CFLAGS_5_(_0,...) CFLAG(_0);CFLAGS_4_(__VA_ARGS__)
#define CFLAGS_6_(_0,...) CFLAG(_0);CFLAGS_5_(__VA_ARGS__)
#define CFLAGS_7_(_0,...) CFLAG(_0);CFLAGS_6_(__VA_ARGS__)
#define CFLAGS_8_(_0,...) CFLAG(_0);CFLAGS_7_(__VA_ARGS__)
#define CFLAGS_9_(_0,...) CFLAG(_0);CFLAGS_8_(__VA_ARGS__)
#define CFLAGS_10_(_0,...) CFLAG(_0);CFLAGS_9_(__VA_ARGS__)
#define CFLAGS_11_(_0,...) CFLAG(_0);CFLAGS_10_(__VA_ARGS__)
#define CFLAGS_12_(_0,...) CFLAG(_0);CFLAGS_11_(__VA_ARGS__)
#define CFLAGS_13_(_0,...) CFLAG(_0);CFLAGS_12_(__VA_ARGS__)
#define CFLAGS_14_(_0,...) CFLAG(_0);CFLAGS_13_(__VA_ARGS__)
#define CFLAGS_15_(_0,...) CFLAG(_0);CFLAGS_14_(__VA_ARGS__)
#define CFLAGS_16_(_0,...) CFLAG(_0);CFLAGS_15_(__VA_ARGS__)
#define CFLAGS_C_(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,m,...) m
#define CFLAGS(...) do { \
  CFLAGS_C_(__VA_ARGS__,CFLAGS_16_,CFLAGS_15_,CFLAGS_14_,CFLAGS_13_,CFLAGS_12_,CFLAGS_11_,CFLAGS_10_,CFLAGS_9_,CFLAGS_8_,CFLAGS_7_,CFLAGS_6_,CFLAGS_5_,CFLAGS_4_,CFLAGS_3_,CFLAGS_2_,CFLAG)(__VA_ARGS__) \
} while (0)

#endif /* CFLAG_H_ */
