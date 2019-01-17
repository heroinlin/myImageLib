#include "history.h"


histogram_t *histogram_create(int bin, int ranges)
{
	histogram_t *hist = 0;
	hist = (histogram_t *)malloc(sizeof(histogram_t));
	if (!hist){
		return NULL;
	}
	hist->bin = bin;
	hist->ranges = ranges;
	hist->value = (float*)malloc(bin*sizeof(float));
	if (!hist->value) {
		free(hist);
		hist = NULL;
		return NULL;
	}
	return hist;
}


u8_t histogram_release(histogram_t *hist)
{
	if (!hist){
		return 1;
	}
	if (hist->value){
		free(hist->value);
		hist->value = NULL;
	}
	if (hist){
		free(hist);
		hist = NULL;
	}
	return 1;
}


void histogram_normalize(histogram_t *hist, double factor)
{
	float pixel_num = 0;
	int bin = histogram_get_bin(hist);
	float value = 0;
	for (int i = 0; i < bin; i++)
	{
		pixel_num += histogram_get_value(hist, i);
	}
	for (int i = 0; i < bin; i++)
	{
		value = histogram_get_value(hist, i) / pixel_num;
		histogram_set_value(hist, i, value);
	}
	/*for (int k = 0; k < bin; k++)
	printf("hist_value[%d]=%f\n", k, histogram_get_value(hist, k));*/
}


void histogram_threshold(histogram_t *hist, double threshold)
{
	int bin = histogram_get_bin(hist);
	float value = 0;
	for (int i = 0; i < bin; i++)
	{
		value = histogram_get_value(hist, i);
		if (value < threshold)
			histogram_set_value(hist, i, 0);
	}
}


void histogram_min_max(histogram_t *hist,
	int *minval,
	int *maxval,
	float *minval_p,
	float *maxval_p)
{
	float pixel_num = 0;
	int bin = histogram_get_bin(hist);
	float value = 0, min_value = 0, max_value = 0;
	min_value = histogram_get_value(hist, *minval);
	max_value = histogram_get_value(hist, *maxval);
	for (int i = 0; i < bin; i++)
	{
		value = histogram_get_value(hist, i);
		pixel_num += value;
		if (value < min_value)
		{
			*minval = i;
			min_value = histogram_get_value(hist, *minval);
		}
		if (value > max_value)
		{
			*maxval = i;
			max_value = histogram_get_value(hist, *maxval);
		}
	}
	*minval_p = min_value / pixel_num;
	*maxval_p = max_value / pixel_num;

}


double histogram_compare(histogram_t *hist1,
	histogram_t *hist2,
	int method)
{
	assert(histogram_get_bin(hist1) == histogram_get_bin(hist2) && histogram_get_range(hist1) == histogram_get_range(hist2));
	assert(method == 1 || method == 2 || method == 3 || method == 4);
	int j;
	int len = histogram_get_bin(hist1);
	double result = 0;
	double s1 = 0, s2 = 0, s11 = 0, s12 = 0, s22 = 0;
	if (method == CHISQR)
	{
		for (j = 0; j < len; j++)
		{
			double a = histogram_get_value(hist1, j) - histogram_get_value(hist2, j);
			double b = histogram_get_value(hist1, j);
			if (fabs(b) > DBL_EPSILON)
				result += a*a / b;
		}
	}
	else if (method == CORREL)
	{
		for (j = 0; j < len; j++)
		{
			double a = histogram_get_value(hist1, j);
			double b = histogram_get_value(hist2, j);

			s12 += a*b;
			s1 += a;
			s11 += a*a;
			s2 += b;
			s22 += b*b;
		}
	}
	else if (method == INTERSECT)
	{
		for (j = 0; j < len; j++)
			result += min(histogram_get_value(hist1, j), histogram_get_value(hist2, j));
	}
	else if (method == BHATTACHARYYA)
	{
		for (j = 0; j < len; j++)
		{
			double a = histogram_get_value(hist1, j);
			double b = histogram_get_value(hist2, j);
			result += sqrt(a*b);
			s1 += a;
			s2 += b;
		}
	}
	/*else
	CV_Error(CV_StsBadArg, "Unknown comparison method");*/

	if (method == CORREL)
	{
		int  total = histogram_get_bin(hist1);
		double scale = 1. / total;
		double num = s12 - s1*s2*scale;
		double denom2 = (s11 - s1*s1*scale)*(s22 - s2*s2*scale);
		result = fabs(denom2) > DBL_EPSILON ? num / sqrt(denom2) : 1.;
	}
	else if (method == BHATTACHARYYA)
	{
		s1 *= s2;
		s1 = fabs(s1) > FLT_EPSILON ? 1. / sqrt(s1) : 1.;
		result = sqrt(max(1. - result*s1, 0.));
	}
	return result;
}


#ifdef IMAGE


void histogram_calculate(image_t *img, histogram_t *hist)
{

	/*for (int k = 0; k < hist.bin; k++)
	hist.value[k] = 0;
	for (int i = 0; i < img->height; i++)
	{
	for (int j = 0; j < img->width; j++)
	{
	unsigned char *t = (unsigned char*)(img->imageData + i*img->widthStep + j);
	int n = int(*t);
	hist.value[n*hist.bin / hist.ranges] = hist.value[n*hist.bin / hist.ranges] + 1;
	}
	}

	for (int k = 0; k < hist.bin; k++)
	printf("hist_value[%d]=%f\n", k, hist.value[k]);*/
	int i, j, n;
	float value;
	int bin = histogram_get_bin(hist);
	int ranges = histogram_get_range(hist);
	assert(bin > 0 && ranges > 0);
	int height = image_get_height(img);
	int width = image_get_width(img);
	for (int k = 0; k < bin; k++)
		histogram_set_value(hist, k, 0);
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			n = (int)image_get_pixel_value(img, j, i, 0);
			n = n * (bin - 1) / ranges;
			value = histogram_get_value(hist, n) + 1;
			if (n<bin && n>-1)
			{
				histogram_set_value(hist, n, value);
			}
		}
	}
	/*for (int k = 0; k < bin; k++)
		printf("hist_value[%d]=%f\n", k, histogram_get_value(hist, k));*/
}
	

#endif
