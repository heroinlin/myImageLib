#ifndef _MYSSE_H_
#define _MYSSE_H_

#include <xmmintrin.h>
#include <tmmintrin.h>
#include <intrin.h> 
#include <emmintrin.h>

#ifdef __cplusplus
extern "C" {
#endif

	__m128 _mm_floor(__m128 a);

	__m128 inv_sqrt_sse(__m128 x);

	extern float inv_sqrt_sse1(float x);
	
	float *inv_sqrt_sse2(float *x);
#ifdef __cplusplus
}
#endif


#endif 