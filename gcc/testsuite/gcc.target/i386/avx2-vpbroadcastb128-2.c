/* { dg-do run } */
/* { dg-options "-mavx2 -O2" } */
/* { dg-require-effective-target avx2 } */

#include "avx2-check.h"
#include <string.h>

#define NUM 10

static void
init_pbroadcastb128 (char *src, int seed)
{
  int i, sign = 1;

  for (i = 0; i < 16; i++)
    {
      src[i] = (i + seed) * (i + seed) * sign;
      sign = -sign;
    }
}

static void
calc_pbroadcastb128 (char *src, char *dst)
{
  int i;

  for (i = 0; i < 16; i++)
    dst[i] = src[0];
}

static void
avx2_test (void)
{
  union128i_b src, dst;
  char dst_ref[16];
  int i;

  for (i = 0; i < NUM; i++)
    {
      init_pbroadcastb128 (src.a, i);

      dst.x = _mm_broadcastb_epi8 (src.x);
      calc_pbroadcastb128 (src.a, dst_ref);

      if (check_union128i_b (dst, dst_ref))
	abort ();
    }
}
