#include "history.h"

History *CreateHistory(int bin, int ranges)
{
	History *hist = 0;
	hist = (History *)malloc(sizeof(History));
	(*hist).value = (float*)malloc(bin*sizeof(float));
	(*hist).bin = bin;
	(*hist).ranges = ranges;
	return hist;
}

void ReleaseHistory(History *hist)
{
	free((*hist).value);
	free(hist);
}

void NormalizeHist(History *hist, double factor)
{
	float pixel_num = 0;
	int bin = GetHistBin(hist);
	float value = 0;
	for (int i = 0; i < bin; i++)
	{
		pixel_num += GetHistValue(hist, i);
	}
	for (int i = 0; i < bin; i++)
	{
		value = GetHistValue(hist, i) / pixel_num;
		SetHistValue(hist, i, value);
	}
	/*for (int k = 0; k < bin; k++)
		printf("hist_value[%d]=%f\n", k, GetHistValue(hist, k));*/
}

void ThreshHist(History *hist, double threshold)
{
	int bin = GetHistBin(hist);
	float value = 0;
	for (int i = 0; i < bin; i++)
	{
		value = GetHistValue(hist, i);
		if (value < threshold)
			SetHistValue(hist, i, 0);
	}
}

void minmax_hist(History *hist, int *minval, int *maxval, float *minval_p, float *maxval_p)
{
	float pixel_num = 0;
	int bin = GetHistBin(hist);
	float value = 0, min_value = 0, max_value = 0;
	min_value = GetHistValue(hist, *minval);
	max_value = GetHistValue(hist, *maxval);
	for (int i = 0; i < bin; i++)
	{
		value = GetHistValue(hist, i);
		pixel_num += value;
		if (value < min_value)
		{
			*minval = i;
			min_value = GetHistValue(hist, *minval);
		}
		if (value > max_value)
		{
			*maxval = i;
			max_value = GetHistValue(hist, *maxval);
		}
	}
	*minval_p = min_value / pixel_num;
	*maxval_p = max_value / pixel_num;

}

double CompareHist(History *hist1, History *hist2, int method)
{
	assert(GetHistBin(hist1) == GetHistBin(hist2) && GetHistRange(hist1) == GetHistRange(hist2));
	assert(method == 1 || method == 2 || method == 3 || method == 4);
	int j;
	int len = GetHistBin(hist1);
	double result = 0;
	double s1 = 0, s2 = 0, s11 = 0, s12 = 0, s22 = 0;
	if (method == CHISQR)
	{
		for (j = 0; j < len; j++)
		{
			double a = GetHistValue(hist1, j) - GetHistValue(hist2, j);
			double b = GetHistValue(hist1, j);
			if (fabs(b) > DBL_EPSILON)
				result += a*a / b;
		}
	}
	else if (method == CORREL)
	{
		for (j = 0; j < len; j++)
		{
			double a = GetHistValue(hist1, j);
			double b = GetHistValue(hist2, j);

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
			result += min(GetHistValue(hist1, j), GetHistValue(hist2, j));
	}
	else if (method == BHATTACHARYYA)
	{
		for (j = 0; j < len; j++)
		{
			double a = GetHistValue(hist1, j);
			double b = GetHistValue(hist2, j);
			result += sqrt(a*b);
			s1 += a;
			s2 += b;
		}
	}
	/*else
	CV_Error(CV_StsBadArg, "Unknown comparison method");*/

	if (method == CORREL)
	{
		int  total = GetHistBin(hist1);
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
void clachist(Image *img, History *hist)
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
	int bin = GetHistBin(hist);
	int ranges = GetHistRange(hist);
	int height = get_img_height(img);
	int width = get_img_width(img);
	for (int k = 0; k < bin; k++)
		SetHistValue(hist, k, 0);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int n = (int)get_pixel(img, j, i, 0);
			n = n * bin / ranges;
			SetHistValue(hist, n, GetHistValue(hist, n) + 1);
		}
	}
	//for (int k = 0; k < bin; k++)
	//	printf("hist_value[%d]=%f\n", k, GetHistValue(hist, k));
}
#endif
