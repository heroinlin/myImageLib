#ifndef SCANNING_METHOD_H
#define SCANNING_METHOD_H
#include "image.h"
#ifdef __cplusplus
extern "C" {
#endif

	/**
	* extreme_row - looking for extreme value of image of some row,including the maximum and the minimum.
	*
	* Parameters:
	* @img ------ the image itself.
	* @max_row -- the maximum of some row
	* @min_row -- the minimum of some row
	* @row -- the row want to find the extreme value
	* Return:
	* none
	*
	*/
	void extreme_row(image_t* img, float* max_row, float* min_row, int row);

	/**
	* extreme_col - looking for extreme value of image of some column,including the maximum and the minimum.
	*
	* Parameters:
	* @img ------ the image itself.
	* @max_col -- the maximum of some column
	* @min_col -- the minimum of some column
	* @col -- the column want to find the extreme value
	* Return:
	* none
	*
	*/
	void extreme_col(image_t* img, float* max_col, float* min_col, int col);

	/**
	* RGB_to_gray - Calculate the brightness of the pixel
	*
	* Parameters:
	* @img ------ the image itself.
	* @x -- the x-coordinate of image
	* @y -- the y-coordinate of image
	* Return:
	* the brightness of the pixel
	*
	*/
	float rgb_to_gray(image_t* img, int x, int y);

	/**
	* standard_circle - Oval transformation for the standard circle
	*
	* Parameters:
	* @img ------ the Oval image.
	* Return:
	* the standard circle image
	*
	*/
	image_t* standard_circle(image_t* img);

	/**
	* scanning_method - Calibration the center and radius of fisheye image 
	*
	* Parameters:
	* @img ------ the image itself.
	* @x0 - the x-coordinate of circle center
	* @y0 - the y-coordinate of circle center
	* @r - the radium of circle
	* @GRAY_DIFF_THR - the threshold that  different of extreme value
	* Return:
	* fisheye image after shearing as standard circle
	*
	*/
	image_t* scanning_method(image_t* img, float* x0, float* y0, float* r, float GRAY_DIFF_THR);

#ifdef __cplusplus
}
#endif
#endif
