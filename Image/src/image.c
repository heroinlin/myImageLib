#include "image.h"

Image *CreateImage(Imagesize size, int depth, int channel)
{
	Image *out = 0;
	out = (Image *)malloc(sizeof(Image));
	(*out).width = size.width;
	(*out).height = size.height;
	(*out).depth = depth;
	(*out).nChannels = channel;
	(*out).imageData = (char*)malloc(size.width*size.height*channel*sizeof(char));
	//
	return out;
}

void ReleaseImage(Image *src)
{
	free((*src).imageData);
	free(src);
}

void CopyImage(Image *src, Image *dst)
{
	int channel = get_img_channel(src);
	int width = get_img_width(src);
	int height = get_img_height(src);
	assert(get_img_channel(dst) == channel&&get_img_width(dst) == width&&get_img_height(dst) == height);
	int value;
	int i, j, k;
	for (k = 0; k < channel; k++)
		for (j = 0; j < height; j++)
			for (i = 0; i < width; i++)
			{
				value = (int)get_pixel(src, i, j, k);
				set_pixel(dst, i, j, k, value);
			}
}

void Img_flip(Image *src, int flip_code)
{
	int width = src->width;
	int height = src->height;
	int channel = src->nChannels;
	int i, j, k;
	switch (flip_code)
	{
	case 0:
		for (k = 0; k < channel; ++k)
			for (j = 0; j < height; ++j)
				for (i = 0; i < width / 2; ++i)
				{
					int data = get_pixel(src, i, j, k);
					int swap = get_pixel(src, width - i - 1, j, k);
					set_pixel(src, i, j, k, swap);
					set_pixel(src, width - i - 1, j, k, data);
				}
		break;
	case 1:
		for (k = 0; k < channel; ++k)
			for (j = 0; j < height / 2; ++j)
				for (i = 0; i < width; ++i)
				{
					int data = get_pixel(src, i, j, k);
					int swap = get_pixel(src, i, height - j - 1, k);
					set_pixel(src, i, j, k, swap);
					set_pixel(src, i, height - j - 1, k, data);
				}
		break;
	case -1:
		for (k = 0; k < channel; ++k)
			for (j = 0; j < height / 2; ++j)
				for (i = 0; i < width; ++i)
				{
					int data = (int)get_pixel(src, i, j, k);
					int swap = (int)get_pixel(src, width - i - 1, height - j - 1, k);
					set_pixel(src, i, j, k, swap);
					set_pixel(src, width - i - 1, height - j - 1, k, data);
				}
		break;
	default:
		break;
	}


}

void Img_Grayscale(Image *src, Image *gray)
{
	assert(get_img_channel(src) == 3);
	int i, j, k;
//	Image gray = creatImage(get_img_size(src), get_img_depth(src), 1);
	float scale[] = { 0.587, 0.299, 0.114 };
	int channel = get_img_channel(src);
	int width = get_img_width(src);
	int height = get_img_height(src);
	for (j = 0; j < height; j++)
		for (i = 0; i < width; i++)
		{
			float value = 0;
			for (k = 0; k < channel; k++)
			{
				value += scale[k] * (float)get_pixel(src, i, j, k);
			}
			set_pixel(gray, i, j, 0, (int)value);
		}
//	return gray;
}

void Img_Abs_Diff(Image *src1, Image *src2, Image *dst)
{
	assert(get_img_channel(src1) == get_img_channel(src2)
			&& get_img_width(src1) == get_img_width(src2)
			&& get_img_height(src1) == get_img_height(src2));
	int i, j, k;
	//Image dst = CreateImage(get_img_size(src1), get_img_depth(src1), get_img_channel(src1));
	int channel = get_img_channel(dst);
	int width = get_img_width(dst);
	int height = get_img_height(dst);
	for (k = 0; k < channel; k++)
		for (j = 0; j < height; j++)
			for (i = 0; i < width; i++)
			{
				int val = (int)(abs)(get_pixel(src1, i, j, k) - get_pixel(src2, i, j, k));
				set_pixel(dst, i, j, k, val);
			}
	//return dst;
}

void Img_Threshold_Binary(Image *src, Image *dst, double threshold)
{
	int i, j, k;
	//Image dst = CreateImage(get_img_size(src), get_img_depth(src), get_img_channel(src));
	int channel = get_img_channel(dst);
	int width = get_img_width(dst);
	int height = get_img_height(dst);
	for (k = 0; k < channel; k++)
		for (j = 0; j < height; j++)
			for (i = 0; i < width; i++)
			{
				int val = (int)(get_pixel(src, i, j, k));
				if (val < threshold)
					set_pixel(dst, i, j, k, 0);
				else
					set_pixel(dst, i, j, k, 255);
			}
	//return dst;
}

void Img_And(Image *src1, Image *src2, Image *dst)
{
	assert(get_img_channel(src1) == get_img_channel(src2)
		&& get_img_width(src1) == get_img_width(src2)
		&& get_img_height(src1) == get_img_height(src2));
	//Image dst = CreateImage(get_img_size(src1), get_img_depth(src1), get_img_channel(src1));
	int channel = get_img_channel(dst);
	int width = get_img_width(dst);
	int height = get_img_height(dst);
	int i, j, k;
	for (k = 0; k < channel; k++)
		for (j = 0; j < height; j++)
			for (i = 0; i < width; i++)
			{
				int val = (int)get_pixel(src1, i, j, k) & (int)get_pixel(src2, i, j, k);
				set_pixel(dst, i, j, k, val);
			}
	//return dst;
}

void Img_Add(Image *src1, Image *src2, Image *dst)
{
	assert(get_img_channel(src1) == get_img_channel(src2)
		&& get_img_width(src1) == get_img_width(src2)
		&& get_img_height(src1) == get_img_height(src2));
	//Image dst = CreateImage(get_img_size(src1), get_img_depth(src1), get_img_channel(src1));
	int channel = get_img_channel(dst);
	int width = get_img_width(dst);
	int height = get_img_height(dst);
	int i, j, k;
	for (k = 0; k < channel; k++)
		for (j = 0; j < height; j++)
			for (i = 0; i < width; i++)
			{
				int val = (int)get_pixel(src1, i, j, k) + (int)get_pixel(src2, i, j, k);
				if (val > 255)
					val = 255;
				set_pixel(dst, i, j, k, val);
			}
}

void Img_Crop(Image *src, Image *dst, int x, int y, int width, int height)
{
	//Image dst = CreateImage(set_img_size(width,height), get_img_depth(src), get_img_channel(src));
	assert(x >= 0 && y >= 0 && width >= 0 && height >= 0);
	assert(x <= get_img_width(src), y <= get_img_height(src), width <= get_img_width(src), height <= get_img_height(src));
	assert((x + width < get_img_width(src)) && (y + height < get_img_height(src)));
	int channel = get_img_channel(dst);
	int i, j, k;
	for (k = 0; k < channel; k++)
		for (j = 0; j < height; j++)
			for (i = 0; i < width; i++)
			{
				int dx = i + x;
				int dy = j + y;
				int val = 0;
				if (dx >= 0 && dx < get_img_width(src) && dy >= 0 && dy < get_img_height(src)) 
				{
					val = (int)get_pixel(src, dx, dy, k);
				}
				set_pixel(dst, i, j, k, val);
			}
	//return dst;
}

void Img_Warp(Image *src, Image *dst)
{
	assert(get_img_channel(src) == get_img_channel(dst));
	int channel = get_img_channel(dst);
	int width1 = get_img_width(src);
	int height1 = get_img_height(src);
	int width2 = get_img_width(dst);
	int height2 = get_img_height(dst);
	float w_rate = (float)width1 / (float)width2;
	float h_rate = (float)height1 / (float)height2;
	for (int c = 0; c < channel; c++)
		for (int j = 0; j < height2; j++)
			for (int i = 0; i < width2; i++)
			{
				int u = i*w_rate;
				int v = j*h_rate;
				float u_dec = i*w_rate - u;
				float v_dec = j*h_rate - v;
				int value1 = (int)get_pixel(src, u, v, c);
				if (u >= width1 - 1)
					u = width1 - 2;
				if (v >= height1 - 1)
					v = height1 - 2;
				int value2 = (int)get_pixel(src, u + 1, v, c);
				int value3 = (int)get_pixel(src, u, v + 1, c);
				int value4 = (int)get_pixel(src, u + 1, v + 1, c);
				int value = (int)((1 - u_dec)*(1 - v_dec)*value1+ u_dec*(1 - v_dec)*value2+ (1 - u_dec)*v_dec*value3+ u_dec*v_dec*value4);
				set_pixel(dst, i, j, c, value);
			}
}

float Entropy(Image *img)
{
	float temp[256] = { 0.0 };
	/* Calculate the accumulative value of each pixel  */
	int height = get_img_height(img);
	int width = get_img_width(img);
	for (int m = 0; m < height; m++)
	{
		for (int n = 0; n < width; n++)
		{
			int i = (int)get_pixel(img, n, m, 0);
			temp[i] = temp[i] + 1;
		}
	}
	/* Calculate the probability of  each pixel  */
	for (int i = 0; i < 256; i++)
	{
		temp[i] = temp[i] / (height*width);
	}
	float result = 0;
	/* Calculate the entropy of image */
	for (int i = 0; i < 256; i++)
	{
		if (temp[i] == 0.0)
			result = result;
		else
			result = result - temp[i] * (log(temp[i]) / log(2.0));
	}
	return result;
}

void Mask_three_frame_diff(Image *src1, Image *src2, Image *src3, Image *Imask, float threshold)
{
	Image *Imask1 = CreateImage(get_img_size(src1), get_img_depth(src1), get_img_channel(src1));
	Image *Imask2 = CreateImage(get_img_size(src1), get_img_depth(src1), get_img_channel(src1));
	Img_Abs_Diff(src1, src2, Imask1);
	Img_Abs_Diff(src2, src3, Imask2);
	Img_Threshold_Binary(Imask1, Imask1, threshold);
	Img_Threshold_Binary(Imask2, Imask2, threshold);
	Img_And(Imask1, Imask2, Imask);
//	Image Imask = CreateImage(get_img_size(src1), get_img_depth(src1), get_img_channel(src1));
	//cvAnd(Imask1, Imask2, Imask);
	ReleaseImage(Imask1);
	ReleaseImage(Imask2);
//	return Imask;
}

void Mask_backgroung_diff(Image *background, Image *src, Image *Bmask, float threshold)
{
	Img_Abs_Diff(background, src, Bmask);
	Img_Threshold_Binary(Bmask, Bmask , threshold);
	//ReleaseImage(Bmask);
	//return Bmask;
}

#ifdef OPENCV
void ipltoImage(IplImage *src, Image *dst)
{
	//Image *dst = CreateImage(set_img_size(src->width, src->height),src->depth, src->nChannels);
	int step = src->widthStep;
	uchar value;
	int i, j, k;
	for (k = 0; k < src->nChannels; k++)
		for (j = 0; j < src->height; j++)
			for (i = 0; i < src->width; i++)
			{
				value = src->imageData[j*step + i*src->nChannels + k];
				set_pixel(dst, i, j, k, (int)value);
			}
	//return dst;
}

void Imagetoipl(Image *src, IplImage *dst)
{
	//IplImage *dst = cvCreateImage(cvSize(src->width, src->height), src->depth, src->nChannels);
	int step = dst->widthStep;
	uchar value;
	int i, j, k;
	for (k = 0; k < src->nChannels; k++)
		for (j = 0; j < src->height; j++)
			for (i = 0; i < src->width; i++)
			{
				value = get_pixel(src, i, j, k);
				dst->imageData[j*step + i*src->nChannels + k] = value;
			}
	//return dst;
}

void showimage(char *windowsname, Image *src,int t)
{
	IplImage *img = cvCreateImage(cvSize(src->width, src->height), src->depth, src->nChannels);
	Imagetoipl(src, img);
	cvShowImage(windowsname, img);
	cvWaitKey(t);
	cvReleaseImage(&img);
}

#endif
