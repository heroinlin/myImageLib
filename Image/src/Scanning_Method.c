#include "ScanningMethod.h"
Image* ScanningMethod(Image* img, float* x0, float* y0, float* r, float GRAY_DIFF_THR)
{
	Image* imgTemp;
	int n_left;
	int n_right;
	int n_top;
	int n_bottom;

	float n_max;
	float n_min;

	//Looking for left tangent of fisheye image
	for (int i = 0; i < img->width; i++)
	{
		ExtremeCol(img, &n_max, &n_min, i);
		if ((n_max - n_min) > GRAY_DIFF_THR)
		{
			n_left = i;
			break;
		}
	}

	//Looking for right tangent of fisheye image
	for (int i = img->width - 1; i >= 0; i--)
	{

		ExtremeCol(img, &n_max, &n_min, i);
		if ((n_max - n_min) > GRAY_DIFF_THR)
		{
			n_right = i;
			break;
		}
	}

	//Looking for top tangent of fisheye image
	for (int i = 0; i < img->height; i++)
	{

		ExtremeRow(img, &n_max, &n_min, i);
		if ((n_max - n_min) > GRAY_DIFF_THR)
		{
			n_top = i;
			break;
		}
	}

	//Looking for bottom tangent of fisheye image
	for (int i = img->height - 1; i >= 0; i--)
	{

		ExtremeRow(img, &n_max, &n_min, i);
		if ((n_max - n_min) > GRAY_DIFF_THR)
		{
			n_bottom = i;
			break;
		}
	}

	if (n_left >= n_right || n_top >= n_bottom)
	{
		return NULL;
	}
	else
	{

		imgTemp = CreateImage(set_img_size(n_right - n_left, n_bottom - n_top), IPL_DEPTH_8U, 3);

		Img_Crop(img, imgTemp, n_left , n_top, n_right - n_left, n_bottom - n_top);
		Image* imgCircle = Standard_circle(imgTemp);

		ReleaseImage(imgTemp);

		//Calculate the fisheye image center coordinates and radius 
		*x0 = 1.0 * (n_left + n_right) / 2;
		*y0 = 1.0 * (n_top + n_bottom) / 2;
		float r1 = 1.0 * (n_right - n_left) / 2;
		float r2 = 1.0 * (n_bottom - n_top) / 2;
		*r = max(r1, r2);
		return imgCircle;

	}
}

void ExtremeRow(Image* img, float* maxRow, float* minRow, int row)
{
	float maxTemp;
	float minTemp;

	float n_temp;
	maxTemp = RGB_to_gray(img, 0, row);
	minTemp = RGB_to_gray(img, 0, row);

	for (int i = 0; i < img->width; i++)
	{
		n_temp = RGB_to_gray(img, i, row);
		if (maxTemp < n_temp)
			maxTemp = n_temp;
		if (minTemp > n_temp)
			minTemp = n_temp;
	}

	*maxRow = maxTemp;
	*minRow = minTemp;

}

void ExtremeCol(Image* img, float* maxCol, float* minCol, int col)
{
	float maxTemp;
	float minTemp;

	float n_temp;
	maxTemp = RGB_to_gray(img, col, 0);
	minTemp = RGB_to_gray(img, col, 0);

	for (int i = 0; i < img->height; i++)
	{
		n_temp = RGB_to_gray(img, col, i);
		if (maxTemp < n_temp)
			maxTemp = n_temp;
		if (minTemp > n_temp)
			minTemp = n_temp;
	}

	*maxCol = maxTemp;
	*minCol = minTemp;

}

float RGB_to_gray(Image* img, int x, int y)
{
	float value = 0;
	int channel = get_img_channel(img);
	float scale[] = { 0.587, 0.299, 0.114 };
	for (int k = 0; k < channel; k++)
	{
		value += scale[k] * (float)get_pixel(img, x, y, k);
	}

	return value;

}

Image* Standard_circle(Image* img)
{
	float u = 1.0*img->width / 2;
	float v = 1.0*img->height / 2;
	float beta = 1.0 * img->width / img->height;
	Image* imgOut;
	if (img->width < img->height)

		imgOut = CreateImage(set_img_size(min(img->width, img->height), min(img->width, img->height)), IPL_DEPTH_8U, 3);
	else
		imgOut = CreateImage(set_img_size(max(img->width, img->height), max(img->width, img->height)), IPL_DEPTH_8U, 3);

	Img_Warp(img, imgOut);

	return imgOut;

}