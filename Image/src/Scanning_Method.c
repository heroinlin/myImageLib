#include "scanning_method.h"
image_t* scanning_method(image_t* img, float* x0, float* y0, float* r, float GRAY_DIFF_THR)
{
	image_t* img_temp;
	int n_left;
	int n_right;
	int n_top;
	int n_bottom;

	float n_max;
	float n_min;

	//Looking for left tangent of fisheye image
	for (int i = 0; i < img->width; i++)
	{
		extreme_col(img, &n_max, &n_min, i);
		if ((n_max - n_min) > GRAY_DIFF_THR)
		{
			n_left = i;
			break;
		}
	}

	//Looking for right tangent of fisheye image
	for (int i = img->width - 1; i >= 0; i--)
	{

		extreme_col(img, &n_max, &n_min, i);
		if ((n_max - n_min) > GRAY_DIFF_THR)
		{
			n_right = i;
			break;
		}
	}

	//Looking for top tangent of fisheye image
	for (int i = 0; i < img->height; i++)
	{

		extreme_row(img, &n_max, &n_min, i);
		if ((n_max - n_min) > GRAY_DIFF_THR)
		{
			n_top = i;
			break;
		}
	}

	//Looking for bottom tangent of fisheye image
	for (int i = img->height - 1; i >= 0; i--)
	{

		extreme_row(img, &n_max, &n_min, i);
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

		img_temp = image_create(image_set_size(n_right - n_left, n_bottom - n_top), IPL_DEPTH_8U, 3);

		image_crop(img, img_temp, n_left , n_top, n_right - n_left, n_bottom - n_top);
		image_t* img_circle = standard_circle(img_temp);

		image_release(img_temp);

		//Calculate the fisheye image center coordinates and radius 
		*x0 = 1.0 * (n_left + n_right) / 2;
		*y0 = 1.0 * (n_top + n_bottom) / 2;
		float r1 = 1.0 * (n_right - n_left) / 2;
		float r2 = 1.0 * (n_bottom - n_top) / 2;
		*r = max(r1, r2);
		return img_circle;

	}
}

void extreme_row(image_t* img, float* max_row, float* min_row, int row)
{
	float max_temp;
	float min_temp;

	float n_temp;
	max_temp = rgb_to_gray(img, 0, row);
	min_temp = rgb_to_gray(img, 0, row);

	for (int i = 0; i < img->width; i++)
	{
		n_temp = rgb_to_gray(img, i, row);
		if (max_temp < n_temp)
			max_temp = n_temp;
		if (min_temp > n_temp)
			min_temp = n_temp;
	}

	*max_row = max_temp;
	*min_row = min_temp;

}

void extreme_col(image_t* img, float* max_col, float* min_col, int col)
{
	float max_temp;
	float min_temp;

	float n_temp;
	max_temp = rgb_to_gray(img, col, 0);
	min_temp = rgb_to_gray(img, col, 0);

	for (int i = 0; i < img->height; i++)
	{
		n_temp = rgb_to_gray(img, col, i);
		if (max_temp < n_temp)
			max_temp = n_temp;
		if (min_temp > n_temp)
			min_temp = n_temp;
	}

	*max_col = max_temp;
	*min_col = min_temp;

}

float rgb_to_gray(image_t* img, int x, int y)
{
	float value = 0;
	int channel = image_get_depth(img);
	float scale[] = { 0.587, 0.299, 0.114 };
	for (int k = 0; k < channel; k++)
	{
		value += scale[k] * (float)image_get_pixel_value(img, x, y, k);
	}

	return value;

}

image_t* standard_circle(image_t* img)
{
	float u = 1.0*img->width / 2;
	float v = 1.0*img->height / 2;
	float beta = 1.0 * img->width / img->height;
	image_t* img_out;
	if (img->width < img->height)

		img_out = image_create(image_set_size(min(img->width, img->height), min(img->width, img->height)), IPL_DEPTH_8U, 3);
	else
		img_out = image_create(image_set_size(max(img->width, img->height), max(img->width, img->height)), IPL_DEPTH_8U, 3);

	image_warp(img, img_out);

	return img_out;

}