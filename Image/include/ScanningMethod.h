#ifndef SCANNINGMETHOD_H
#define SCANNINGMETHOD_H
#include "image.h"
#ifdef __cplusplus
extern "C" {
#endif

	/**
	* ExtremeRow - looking for extreme value of image of some row,including the maximum and the minimum.
	*
	* Parameters:
	* @img ------ the image itself.
	* @maxRow -- the maximum of some row
	* @minRow -- the minimum of some row
	* @row -- the row want to find the extreme value
	* Return:
	* none
	*
	*/
	void ExtremeRow(Image* img, float* maxRow, float* minRow, int row);

	/**
	* ExtremeCol - looking for extreme value of image of some column,including the maximum and the minimum.
	*
	* Parameters:
	* @img ------ the image itself.
	* @maxCol -- the maximum of some column
	* @minCol -- the minimum of some column
	* @col -- the column want to find the extreme value
	* Return:
	* none
	*
	*/
	void ExtremeCol(Image* img, float* maxCol, float* minCol, int col);

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
	float RGB_to_gray(Image* img, int x, int y);

	/**
	* Standard_circle - Oval transformation for the standard circle
	*
	* Parameters:
	* @img ------ the Oval image.
	* Return:
	* the standard circle image
	*
	*/
	Image* Standard_circle(Image* img);

	/**
	* ScanningMethod - Calibration the center and radius of fisheye image 
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
	Image* ScanningMethod(Image* img, float* x0, float* y0, float* r, float GRAY_DIFF_THR);

#ifdef __cplusplus
}
#endif
#endif
