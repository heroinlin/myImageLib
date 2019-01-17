#include "mysse.h"


__m128 _mm_floor(__m128 a)
{
	__m128 t = _mm_cvtepi32_ps(_mm_cvttps_epi32(a));
	__m128 b = _mm_and_ps(_mm_cmpgt_ps(t, a), _mm_set1_ps(1.0f));
	return _mm_sub_ps(t, b);
}


__m128 inv_sqrt_sse(__m128 x) {
	__m128 xhalf = _mm_mul_ps(x, _mm_set1_ps(0.5f));
	x = _mm_castsi128_ps(_mm_sub_epi32(_mm_set1_epi32(0x5f3759df), 
									   _mm_srai_epi32(_mm_castps_si128(x), 1)));
	return _mm_mul_ps(x, _mm_sub_ps(_mm_set1_ps(1.5f), 
									_mm_mul_ps(xhalf, _mm_mul_ps(x, x))));
}


float inv_sqrt_sse1(float x)
{
	float r[4];
	__m128 z = _mm_set1_ps(x);
	_mm_storeu_ps(r, inv_sqrt_sse(z));
	return r[0];
}


float *inv_sqrt_sse2(float x[4])
{
	float *r = (float *)malloc (4 * sizeof (float));
	__m128 z = _mm_set_ps(x[3], x[2], x[1], x[0]);
	_mm_storeu_ps(r, inv_sqrt_sse(z));
	return r;
}

