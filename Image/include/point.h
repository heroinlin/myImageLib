#ifndef POINT_H
#define POINT_H
#include"elem_type.h"
#ifdef __cplusplus
extern "C" {
#endif

	typedef struct point2_s{
		/* the x-coordinate of point */
		u16_t x;
		/* the y-coordinate of point */
		u16_t y;
	}Point2_st,*Point2_pst;
	typedef struct point2_u32_s{
		/* the x-coordinate of point */
		u32_t x;
		/* the y-coordinate of point */
		u32_t y;
	}Point2_u32_st, *Point2_u32_pst;
	typedef struct point2_f32_s{
		/* the x-coordinate of point */
		f32_t x;
		/* the y-coordinate of point */
		f32_t y;
	}Point2_f32_st, *Point2_f32_pst;
	typedef struct point2_d64_s{
		/* the x-coordinate of point */
		d64_t x;
		/* the y-coordinate of point */
		d64_t y;
	}Point2_d64_st, *Point2_d64_pst;

	typedef struct point3_s{
		/* the x-coordinate of point */
		u16_t x;
		/* the y-coordinate of point */
		u16_t y;
		/* the z-coordinate of point */
		u16_t z;
	}Point3_st, *Point3_pst;
	typedef struct point3_u32_s{
		/* the x-coordinate of point */
		u32_t x;
		/* the y-coordinate of point */
		u32_t y;
		/* the z-coordinate of point */
		u32_t z;
	}Point3_u32_st, *Point3_u32_pst;
	typedef struct point3_f32_s{
		/* the x-coordinate of point */
		f32_t x;
		/* the y-coordinate of point */
		f32_t y;
		/* the z-coordinate of point */
		f32_t z;
	}Point3_f32_st, *Point3_f32_pst;
	typedef struct point3_d64_s{
		/* the x-coordinate of point */
		d64_t x;
		/* the y-coordinate of point */
		d64_t y;
		/* the z-coordinate of point */
		d64_t z;
	}Point3_d64_st, *Point3_d64_pst;

#ifdef __cplusplus
}
#endif
#endif
