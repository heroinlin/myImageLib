#include "rectangle.h"

/**
* rect_br - get the bottom right point of the rect
*
* Parameters:
* @rect - the rect itself
* @pt --- the output bottom right point
*
* Return:
* None
*/
static void rect_br(rect_pst rect, point2_pst pt)
{
	pt->x = rect->x + rect->width;
	pt->y = rect->y + rect->height;
}

u32_t rect_area(rect_pst rect)
{
	return rect->width * rect->height;
}

u32_t rect_overlap_area(rect_pst rect_a, rect_pst rect_b)
{
	point2_t br_pt_a, br_pt_b;
	u16_t x0, y0, x1, y1;
	u32_t s = 0;

	x0 = MAX(rect_a->x, rect_b->x);
	y0 = MAX(rect_a->y, rect_b->y);

	rect_br(rect_a, &br_pt_a);
	rect_br(rect_b, &br_pt_b);

	x1 = MIN(br_pt_a.x, br_pt_b.x);
	y1 = MIN(br_pt_a.y, br_pt_b.y);

	if (x0 < x1 && y0 < y1) {
		s = (x1 - x0) * (y1 - y0);
	}

	return s;
}

u32_t rect_overlap_rate(rect_pst rect_a, rect_pst rect_b)
{
	return rect_overlap_area(rect_a, rect_b) * 10000 / rect_area(rect_b);
}

int rect_contains(rect_pst  rect, point2_pst pt)
{
	return (rect->x <= pt->x &&
		pt->x < rect->x + rect->width &&
		rect->y <= pt->y &&
		pt->y < rect->y + rect->height);
}

int rect_contains_f32(rect_pst  rect, point2_f32_pst pt)
{
	return ((f32_t)rect->x <= pt->x &&
		pt->x < (f32_t)rect->x + (f32_t)rect->width &&
		(f32_t)rect->y <= pt->y &&
		pt->y < (f32_t)rect->y + (f32_t)rect->height);
}
