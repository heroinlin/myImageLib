#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "elem_type.h"
#include "point.h"
#ifdef __cplusplus
extern "C" {
#endif
#define  MAX(a,b) ((a)>(b)?(a):(b))
#define  MIN(a,b) ((a)<(b)?(a):(b))
	typedef struct Rect_s {
		/* the x-coordinate location of the left side of the rectangle */
		u16_t       x;

		/* the y-coordinate location of the top side of the rectangle */
		u16_t       y;

		/* the width of the rectangle */
		u16_t       width;

		/* the height of the rectangle */
		u16_t       height;
	} Rect_t,*Rect_pst;

	/**
	* rect_get_x - get the x-coordinate of the rectangle
	*
	* Parameters:
	* @rect - the rectangle itself
	*
	* Return:
	* The x-coordinate of rectangle.
	*/
	static __inline u16_t rect_get_x(Rect_pst rect)
	{
		return rect->x;
	}

	/**
	* rect_set_x - set the x-coordinate of the rectangle
	*
	* Parameters:
	* @rect -- the rectangle itself
	* @new_x - the new x-coordinate
	*
	* Return:
	* None
	*/
	static __inline void rect_set_x(Rect_pst rect, u16_t new_x)
	{
		rect->x = new_x;
	}

	/**
	* rect_get_y - get the y-coordinate of the rectangle
	*
	* Parameters:
	* @rect - the rectangle itself
	*
	* Return:
	* The y-coordinate of rectangle.
	*/
	static __inline u16_t rect_get_y(Rect_pst rect)
	{
		return rect->y;
	}

	/**
	* rect_set_y - set the y-coordinate of the rectangle
	*
	* Parameters:
	* @rect -- the rectangle itself
	* @new_y - the new y-coordinate
	*
	* Return:
	* None
	*/
	static __inline void rect_set_y(Rect_pst rect, u16_t new_y)
	{
		rect->y = new_y;
	}

	/**
	* rect_get_width - get the width of the rectangle
	*
	* Parameters:
	* @rect - the rectangle itself
	*
	* Return:
	* The width of rectangle.
	*/
	static __inline u16_t rect_get_width(Rect_pst rect)
	{
		return rect->width;
	}
	/**
	* rect_set_width - set the width of the rectangle
	*
	* Parameters:
	* @rect -- the rectangle itself
	* @new_width - the new width
	*
	* Return:
	* None
	*/
	static __inline void rect_set_width(Rect_pst rect, u16_t new_width)
	{
		rect->width = new_width;
	}

	/**
	* rect_get_height - get the height of the rectangle
	*
	* Parameters:
	* @rect - the rectangle itself
	*
	* Return:
	* The height of rectangle.
	*/
	static __inline u16_t rect_get_height(Rect_pst rect)
	{
		return rect->height;
	}

	/**
	* rect_set_height - set the height of the rectangle
	*
	* Parameters:
	* @rect -- the rectangle itself
	* @new_height - the new height
	*
	* Return:
	* None
	*/
	static __inline void rect_set_height(Rect_pst rect, u16_t new_height)
	{
		rect->height = new_height;
	}

	/**
	* rect_set - set all values of the rectangle
	*
	* Parameters:
	* @rect - the rectangle itself
	* @x -- the x-coordinate location of the left side of the rectangle
	* @y -- the y-coordinate location of the left side of the rectangle
	* @width -- The width of rectangle
	* @height -- The height of rectangle
	*
	* Return:
	* None
	*/
	static __inline rect_set(Rect_pst rect, u16_t x, u16_t y, u16_t width, u16_t height)
	{
		rect->x = x;
		rect->y = y;
		rect->width = width;
		rect->height = height;
	}

	/**
	* rect_area - get the area of the rect
	*
	* Parameters:
	* @rect - the rect itself
	*
	* Return:
	* The area of the rect.
	*/
	extern u32_t rect_area(Rect_pst rect);

	/**
	* rect_overlap_area - get the area of the overlap of two rects
	*
	* Parameters:
	* @rect_a - the first rect
	* @rect_b - the second rect
	*
	* Return:
	* The area of the overlap of two rects.
	*/
	extern u32_t rect_overlap_area(Rect_pst rect_a, Rect_pst rect_b);

	/**
	* rect_overlap_rate - get the overlap rate of two rect
	*
	* Parameters:
	* @rect_a - the first rect
	* @rect_b - the second rect
	*
	* Return:
	* The overlap rate of the overlap area over @rect_b.
	*/
	extern u32_t rect_overlap_rate(Rect_pst rect_a, Rect_pst rect_b);

	/**
	* rect_contains - detect whether the rectangle contains the point
	*
	* Parameters:
	* @rect - the rect itself
	* @pt --- the point
	*
	* Return:
	* 1 for contains, 0 for not.
	*/
	extern int rect_contains(Rect_pst  rect, Point2_pst pt);

	/**
	* rect_contains_f32 - detect whether the rectangle contains the point
	*
	* Parameters:
	* @rect - the rect itself
	* @pt --- the point
	*
	* Return:
	* 1 for contains, 0 for not.
	*/
	extern int rect_contains_f32(Rect_pst  rect, Point2_f32_pst pt);

#endif