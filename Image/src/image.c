#include "image.h"


image_t *image_create(image_size_t size, int depth, int channel)
{
	image_t *out = 0;
	out = (image_t *)malloc(sizeof(image_t));
	if (!out){
		return NULL;
	}
	if (size.width & 15)
		size.width += 16 - (size.width & 15);
	if (size.height & 15)
		size.height += 16 - (size.height & 15);
	out->width = size.width;
	out->height = size.height;
	out->depth = depth;
	out->channel = channel;
	out->widthstep = size.width * channel;
	out->imagedata = (char*)malloc(out->widthstep*out->height*sizeof(char));
	if (!out->imagedata) {
		free(out);
		out = NULL;
		return NULL;
	}
	return out;
}


uchar image_release(image_t *src)
{
	if (!src){
		return 1;
	}
	if (src->imagedata){
		free(src->imagedata);
		src->imagedata = NULL;
	}
	if (src){
		free(src);
		src = NULL;
	}
	return 1;
}


void image_copy(image_t *src, image_t *dst)
{
	int i, j, k;
	int value;
	int width, height, channel;
	channel = image_get_channel(src);
	width = image_get_width(src);
	height = image_get_height(src);
	assert(image_get_channel(dst) == channel&&image_get_width(dst) == width&&image_get_height(dst) == height);
	for (k = 0; k < channel; k++)
		for (j = 0; j < height; j++)
			for (i = 0; i < width; i++){
				value = (int)image_get_pixel_value(src, i, j, k);
				image_set_pixel_value(dst, i, j, k, value);
			}
}


void image_flip(image_t *src, int flip_code)
{
	int i, j, k;
	int data, swap;
	int width, height, channel;
	channel = image_get_channel(src);
	width = image_get_width(src);
	height = image_get_height(src);
	switch (flip_code){
	case 0:
		for (k = 0; k < channel; ++k)
			for (j = 0; j < height; ++j)
				for (i = 0; i < width / 2; ++i){
					data = image_get_pixel_value(src, i, j, k);
					swap = image_get_pixel_value(src, width - i - 1, j, k);
					image_set_pixel_value(src, i, j, k, swap);
					image_set_pixel_value(src, width - i - 1, j, k, data);
				}
		break;
	case 1:
		for (k = 0; k < channel; ++k)
			for (j = 0; j < height / 2; ++j)
				for (i = 0; i < width; ++i){
					data = image_get_pixel_value(src, i, j, k);
					swap = image_get_pixel_value(src, i, height - j - 1, k);
					image_set_pixel_value(src, i, j, k, swap);
					image_set_pixel_value(src, i, height - j - 1, k, data);
				}
		break;
	case -1:
		for (k = 0; k < channel; ++k)
			for (j = 0; j < height / 2; ++j)
				for (i = 0; i < width; ++i){
					data = (int)image_get_pixel_value(src, i, j, k);
					swap = (int)image_get_pixel_value(src, width - i - 1, height - j - 1, k);
					image_set_pixel_value(src, i, j, k, swap);
					image_set_pixel_value(src, width - i - 1, height - j - 1, k, data);
				}
		break;
	default:
		break;
	}


}


void image_grayscale(image_t *src, image_t *gray)
{
	assert(image_get_channel(src) == 3);
	/*float scale[] = { 0.587, 0.299, 0.114 };*/
	int i, j, k;
	int value;
	int channel, width, height;
	int scale[] = { 38, 75, 18 };
	channel = image_get_channel(src);
	width = image_get_width(src);
	height = image_get_height(src);
	for (j = 0; j < height; j++)
		for (i = 0; i < width; i++){
			value = 0;
			for (k = 0; k < channel; k++){
				value += (scale[k] * (int)image_get_pixel_value(src, i, j, k)) >> 7;
			}
			image_set_pixel_value(gray, i, j, 0, (int)value);
		}
}


void image_abs_diff(image_t *src1, image_t *src2, image_t *dst)
{
	assert(image_get_channel(src1) == image_get_channel(src2)
		&& image_get_width(src1) == image_get_width(src2)
		&& image_get_height(src1) == image_get_height(src2));
	int i, j, k;
	int val;
	int channel, width, height;
	channel = image_get_channel(dst);
	width = image_get_width(dst);
	height = image_get_height(dst);
	for (k = 0; k < channel; k++)
		for (j = 0; j < height; j++)
			for (i = 0; i < width; i++){
				val = (int)(abs)(image_get_pixel_value(src1, i, j, k) - image_get_pixel_value(src2, i, j, k));
				image_set_pixel_value(dst, i, j, k, val);
			}
}


void image_threshold_binary(image_t *src, image_t *dst, double threshold)
{
	int i, j, k;
	int val;
	int channel, width, height;
	channel = image_get_channel(dst);
	width = image_get_width(dst);
	height = image_get_height(dst);
	for (k = 0; k < channel; k++)
		for (j = 0; j < height; j++)
			for (i = 0; i < width; i++){
				val = (int)(image_get_pixel_value(src, i, j, k));
				if (val < threshold)
					image_set_pixel_value(dst, i, j, k, 0);
				else
					image_set_pixel_value(dst, i, j, k, 255);
			}
}


void image_and(image_t *src1, image_t *src2, image_t *dst)
{
	assert(image_get_channel(src1) == image_get_channel(src2)
		&& image_get_width(src1) == image_get_width(src2)
		&& image_get_height(src1) == image_get_height(src2));
	int i, j, k;
	int val;
	int channel, width, height;
	channel = image_get_channel(dst);
	width = image_get_width(dst);
	height = image_get_height(dst);
	for (k = 0; k < channel; k++)
		for (j = 0; j < height; j++)
			for (i = 0; i < width; i++){
				val = (int)image_get_pixel_value(src1, i, j, k) & (int)image_get_pixel_value(src2, i, j, k);
				image_set_pixel_value(dst, i, j, k, val);
			}
}


void image_add(image_t *src1, image_t *src2, image_t *dst)
{
	assert(image_get_channel(src1) == image_get_channel(src2)
		&& image_get_width(src1) == image_get_width(src2)
		&& image_get_height(src1) == image_get_height(src2));
	int i, j, k;
	int val;
	int channel, width, height;
	channel = image_get_channel(dst);
	width = image_get_width(dst);
	height = image_get_height(dst);
	for (k = 0; k < channel; k++)
		for (j = 0; j < height; j++)
			for (i = 0; i < width; i++){
				val = (int)image_get_pixel_value(src1, i, j, k) + (int)image_get_pixel_value(src2, i, j, k);
				if (val > 255)
					val = 255;
				image_set_pixel_value(dst, i, j, k, val);
			}
}


void image_crop(image_t *src,
	image_t *dst,
	int left,
	int top,
	int width,
	int height)
{
	assert(left >= 0 && top >= 0 && width >= 0 && height >= 0);
	assert(left <= image_get_width(src) && top <= image_get_height(src) && width <= image_get_width(src) && height <= image_get_height(src));
	assert((left + width < image_get_width(src)) && (top + height < image_get_height(src)));
	int channel = image_get_channel(dst);
	int i, j, k;
	int dx, dy, val;
	for (k = 0; k < channel; k++)
		for (j = 0; j < height; j++)
			for (i = 0; i < width; i++){
				dx = i + left;
				dy = j + top;
				val = 0;
				if (dx >= 0 && dx < image_get_width(src) && dy >= 0 && dy < image_get_height(src)) {
					val = (int)image_get_pixel_value(src, dx, dy, k);
				}
				image_set_pixel_value(dst, i, j, k, val);
			}
}


uchar image_interpolation(image_t *src, float x, float y, int c)
{
	assert(x >= 0 && x <= image_get_width(src));
	assert(y >= 0 && y <= image_get_height(src));
	assert(c >= 0 && c <= image_get_depth(src));
	uchar interpolated;
	int x0, y0, x1, y1;
	float x_weight, y_weight;
	x0 = (int)x;
	y0 = (int)y;
	/*interpolated = image_get_pixel_value(src, x0, y0, c);*/
	x_weight = x - x0;
	y_weight = y - y0;
	x1 = x0 + 1;
	y1 = y0 + 1;
	if (x == image_get_width(src))
		x1 = image_get_width(src);
	if (y == image_get_height(src))
		y1 = image_get_height(src);
	interpolated =
		image_get_pixel_value(src, x0, y0, c) * (1 - y_weight) * (1 - x_weight) +
		image_get_pixel_value(src, x1, y0, c) * x_weight * (1 - y_weight) +
		image_get_pixel_value(src, x0, y1, c) * y_weight * (1 - x_weight) +
		image_get_pixel_value(src, x1, y1, c) * y_weight * x_weight;
	return interpolated;
}


void image_warp(image_t *src, image_t *dst)
{
	assert(image_get_channel(src) == image_get_channel(dst));
	int c, i, j;
	int  value;
	int channel, width1, width2, height1, height2;
	int u0, v0, u1, v1;
	channel = image_get_channel(dst);
	width1 = image_get_width(src);
	height1 = image_get_height(src);
	width2 = image_get_width(dst);
	height2 = image_get_height(dst);
	float w_rate = (float)width1 / (float)width2;
	float h_rate = (float)height1 / (float)height2;
	int value2, value3, value4, value1;
	int u_dec, v_dec;
	for (j = 0; j < height2; j++)
		for (i = 0; i < width2; i++)
			for (c = 0; c < channel; c++){
				u0 = i * width1 / width2;
				v0 = j * height1 / height2;
				//value = (int)image_get_pixel_value(src, u, v, c);
				u_dec = (i * w_rate - u0) * 2048;
				v_dec = (j * h_rate - v0) * 2048;
				u1 = u0 + 1;
				v1 = v0 + 1;
				if (u0 >= width1-1)
				{
					u1 = width1-1;
				}
				if (v0 >= height1-1)
				{
					v1 = height1-1;
				}
				value1 = (int)image_interpolation(src, u0, v0, c);
				value2 = (int)image_get_pixel_value(src, u1, v0, c);
				value3 = (int)image_get_pixel_value(src, u0, v1, c);
				value4 = (int)image_get_pixel_value(src, u1, v1, c);
				value = ((2048 - u_dec)*(2048 - v_dec)*value1 + u_dec*(2048 - v_dec)*value2
					+ (2048 - u_dec)*v_dec*value3 + u_dec*v_dec*value4) >> 22;
				image_set_pixel_value(dst, i, j, c, value);
			}
}


void image_warp1(image_t *src,
	image_t *dst,
	int src_width,
	int src_height,
	int dst_width,
	int dst_height)
{
	assert(src_width <= src->width&&src_height <= src->height&&dst_width <= dst->width&&dst_height <= dst->height);
	int c, i, j;
	int  value;
	int channel, width1, width2, height1, height2;
	int u0, v0, u1, v1;
	channel = image_get_channel(dst);
	width1 = src_width;
	height1 = src_height;
	width2 = dst_width;
	height2 = dst_height;
	float w_rate = (float)width1 / (float)width2;
	float h_rate = (float)height1 / (float)height2;
	int value2, value3, value4, value1;
	int u_dec, v_dec;
	for (j = 0; j < height2; j++)
		for (i = 0; i < width2; i++)
			for (c = 0; c < channel; c++){
				u0 = i * width1 / width2;
				v0 = j * height1 / height2;
				value = (int)image_get_pixel_value(src, u0, v0, c);
				u_dec = (i * w_rate - u0) * 2048;
				v_dec = (j * h_rate - v0) * 2048;
				u1 = u0 + 1;
				v1 = v0 + 1;
				if (u0 >= width1 - 1)
				{
					u1 = width1 - 1;
				}
				if (v0 >= height1 - 1)
				{
					v1 = height1 - 1;
				}
				value1 = (int)image_interpolation(src, u0, v0, c);
				value2 = (int)image_get_pixel_value(src, u1, v0, c);
				value3 = (int)image_get_pixel_value(src, u0, v1, c);
				value4 = (int)image_get_pixel_value(src, u1, v1, c);
				value = ((2048 - u_dec)*(2048 - v_dec)*value1 + u_dec*(2048 - v_dec)*value2
				+ (2048 - u_dec)*v_dec*value3 + u_dec*v_dec*value4) >> 22;
				image_set_pixel_value(dst, i, j, c, value);
			}
}


float image_entropy(image_t *img)
{
	float temp[256] = { 0.0 };
	/* Calculate the accumulative value of each pixel  */
	int m, n, i;
	int width, height, val;
	width = image_get_width(img);
	height = image_get_height(img);
	for (m = 0; m < height; m++){
		for (n = 0; n < width; n++){
			val = (int)image_get_pixel_value(img, n, m, 0);
			if (val<256 && val>-1){
				temp[val]++;
			}
		}
	}
	/* Calculate the probability of  each pixel  */
	for (i = 0; i < 256; i++){
		temp[i] = temp[i] / (height*width);
	}
	float result = 0;
	/* Calculate the image_entropy of image */
	for (i = 0; i < 256; i++){
		if (temp[i] == 0.0)
			result = result;
		else
			result = result - temp[i] * (log(temp[i]) / log(2.0));
	}
	return result;
}



void image_mask_three_frame_diff(image_t *src1,
	image_t *src2,
	image_t *src3,
	image_t *Imask,
	float threshold)
{
	image_t *Imask1 = image_create(image_get_size(src1),
		image_get_depth(src1),
		image_get_channel(src1));
	image_t *Imask2 = image_create(image_get_size(src1),
		image_get_depth(src1),
		image_get_channel(src1));
	image_abs_diff(src1, src2, Imask1);
	image_abs_diff(src2, src3, Imask2);
	image_threshold_binary(Imask1, Imask1, threshold);
	image_threshold_binary(Imask2, Imask2, threshold);
	image_and(Imask1, Imask2, Imask);
	image_release(Imask1);
	image_release(Imask2);

}


void image_mask_backgroung_diff(image_t *background,
	image_t *src,
	image_t *Bmask,
	float threshold)
{
	image_abs_diff(background, src, Bmask);
	image_threshold_binary(Bmask, Bmask, threshold);
}


#define  SSE
#ifdef SSE
#include "mysse.h"

void image_copy_sse(image_t *src, image_t *dst)
{
	uchar value;
	int i;
	int imgSize;
	__m128i data;
	imgSize = dst->widthstep*dst->height;
	i = 0;
	for (; i <= imgSize - 16; i += 16){
		data = _mm_loadu_si128((const __m128i*)(src->imagedata + i));
		_mm_storeu_si128(dst->imagedata + i, data);
	}
	for (; i < imgSize; i++){
		value = src->imagedata[i];
		dst->imagedata[i] = value;
	}

}


void image_copy_sse1(void **_src, void **_dst)
{
	uchar *dst = *_dst;
	uchar *src = *_src;
	assert((sizeof(src) / sizeof(src[0])) == (sizeof(dst) / sizeof(dst[0])));
	uchar value;
	int i;
	int imgSize;
	__m128i data;
	imgSize = sizeof(src) / sizeof(src[0]);
	i = 0;
	for (; i <= imgSize - 16; i += 16){
		data = _mm_loadu_si128((const __m128i*)(src + i));
		_mm_storeu_si128(dst + i, data);
	}
	for (; i < imgSize; i++){
		value = src[i];
		dst[i] = value;
	}

}


void image_crop_sse(image_t *src,
	image_t *dst,
	int left,
	int top,
	int width,
	int height)
{
	uchar value;
	int i, j;
	int dst_step, step;
	__m128i data;
	dst_step = dst->widthstep;
	step = top*src->widthstep + left*src->channel;
	for (j = 0; j < height; j++){
		i = 0;
		for (; i <= dst_step - 16; i += 16){
			data = _mm_loadu_si128(
				(const __m128i*)(src->imagedata + step + j*src->widthstep + i));
			_mm_storeu_si128(dst->imagedata + j*dst_step + i, data);
		}
		for (; i < dst_step; i++){
			value = src->imagedata[step + j*src->widthstep + i];
			dst->imagedata[j*dst_step + i] = value;
		}
	}

}


void image_crop_sse1(image_t *src,
	image_t *dst,
	int left,
	int top,
	int width,
	int height)
{
	int i, j;
	int dst_step, step;
	__m128i data;
	dst_step = width*dst->channel;
	step = top*src->widthstep + left*src->channel;
	for (j = 0; j < height; j++){
		i = 0;
		for (; i <= dst_step; i += 16){
			data = _mm_loadu_si128(
				(const __m128i*)(src->imagedata + step + j*src->widthstep + i));
			_mm_storeu_si128(dst->imagedata + j*dst->widthstep + i, data);
		}
	}

}


void image_warp_sse(image_t *src, image_t *dst)
{
	uchar value;
	int i, j, u, v;
	int width1, width2, height1, height2;
	int imgSize, dst_step, v_step, step;
	float w_rate, h_rate;
	__m128i data;
	width1 = src->width;
	width2 = dst->width;
	height1 = src->height;
	height2 = dst->height;
	imgSize = dst->widthstep*dst->height;
	w_rate = (float)width1 / (float)width2;
	h_rate = (float)height1 / (float)height2;
	dst_step = dst->widthstep;
	for (j = 0; j < height2; j++){
		i = 0;
		v = j * h_rate;
		v_step = v*src->widthstep;
		for (; i <= dst_step - 16; i += 16){
			u = i*w_rate;
			step = v_step + u;
			data.m128i_u8[0] = src->imagedata[step + (int)(0 * w_rate)];
			data.m128i_u8[1] = src->imagedata[step + (int)(1 * w_rate)];
			data.m128i_u8[2] = src->imagedata[step + (int)(2 * w_rate)];
			data.m128i_u8[3] = src->imagedata[step + (int)(3 * w_rate)];
			data.m128i_u8[4] = src->imagedata[step + (int)(4 * w_rate)];
			data.m128i_u8[5] = src->imagedata[step + (int)(5 * w_rate)];
			data.m128i_u8[6] = src->imagedata[step + (int)(6 * w_rate)];
			data.m128i_u8[7] = src->imagedata[step + (int)(7 * w_rate)];
			data.m128i_u8[8] = src->imagedata[step + (int)(8 * w_rate)];
			data.m128i_u8[9] = src->imagedata[step + (int)(9 * w_rate)];
			data.m128i_u8[10] = src->imagedata[step + (int)(10 * w_rate)];
			data.m128i_u8[11] = src->imagedata[step + (int)(11 * w_rate)];
			data.m128i_u8[12] = src->imagedata[step + (int)(12 * w_rate)];
			data.m128i_u8[13] = src->imagedata[step + (int)(13 * w_rate)];
			data.m128i_u8[14] = src->imagedata[step + (int)(14 * w_rate)];
			data.m128i_u8[15] = src->imagedata[step + (int)(15 * w_rate)];
			_mm_storeu_si128(dst->imagedata + j*dst_step + i, data);
		}
		for (; i < dst_step; i++){
			u = i*w_rate;
			value = src->imagedata[v*src->widthstep + u];
			dst->imagedata[j*dst_step + i] = value;
		}
	}
}


void image_warp_sse1(image_t *src,
	image_t *dst,
	int src_width,
	int src_height,
	int dst_width,
	int dst_height)
{
	assert(src_width <= src->width&&src_height <= src->height&&dst_width <= dst->width&&dst_height <= dst->height);
	int i, j, u, v;
	int width1, width2, height1, height2;
	int dst_step, v_step, step;
	float w_rate, h_rate;
	__m128i data;
	width1 = src_width;
	width2 = dst_width;
	height1 = src_height;
	height2 = dst_height;
	w_rate = (float)width1 / (float)width2;
	h_rate = (float)height1 / (float)height2;
	dst_step = dst_width*dst->channel;
	for (j = 0; j < height2; j++){
		i = 0;
		v = j * h_rate;
		v_step = v*src->widthstep;
		for (; i <= dst_step - 16; i += 16){
			u = i*w_rate;
			step = v_step + u;
			data.m128i_u8[0] = src->imagedata[step + (int)(0 * w_rate)];
			data.m128i_u8[1] = src->imagedata[step + (int)(1 * w_rate)];
			data.m128i_u8[2] = src->imagedata[step + (int)(2 * w_rate)];
			data.m128i_u8[3] = src->imagedata[step + (int)(3 * w_rate)];
			data.m128i_u8[4] = src->imagedata[step + (int)(4 * w_rate)];
			data.m128i_u8[5] = src->imagedata[step + (int)(5 * w_rate)];
			data.m128i_u8[6] = src->imagedata[step + (int)(6 * w_rate)];
			data.m128i_u8[7] = src->imagedata[step + (int)(7 * w_rate)];
			data.m128i_u8[8] = src->imagedata[step + (int)(8 * w_rate)];
			data.m128i_u8[9] = src->imagedata[step + (int)(9 * w_rate)];
			data.m128i_u8[10] = src->imagedata[step + (int)(10 * w_rate)];
			data.m128i_u8[11] = src->imagedata[step + (int)(11 * w_rate)];
			data.m128i_u8[12] = src->imagedata[step + (int)(12 * w_rate)];
			data.m128i_u8[13] = src->imagedata[step + (int)(13 * w_rate)];
			data.m128i_u8[14] = src->imagedata[step + (int)(14 * w_rate)];
			data.m128i_u8[15] = src->imagedata[step + (int)(15 * w_rate)];
			_mm_storeu_si128(dst->imagedata + j*dst->widthstep + i, data);
		}
	}
}


void image_interpolation_sse(image_t *src,
	point2_f32_t *uv,
	__m128i *pixel_value)
{
	assert(src->channel == 3);
	int src_half_w, src_half_h;
	int x_weight[4], y_weight[4];
	int x[4], y[4];
	__m128 u1234, v1234, u1234frac, v1234frac;
	__m128i u1234floor, v1234floor, half_w, half_h;
	u1234 = _mm_set_ps(uv[3].x, uv[2].x, uv[1].x, uv[0].x);//x[4]
	v1234 = _mm_set_ps(uv[3].y, uv[2].y, uv[1].y, uv[0].y);//y[4]

	u1234floor = _mm_cvtps_epi32(_mm_floor(u1234));//(int)u1234
	v1234floor = _mm_cvtps_epi32(_mm_floor(v1234));//(int)v1234
	u1234frac = _mm_sub_ps(u1234, _mm_cvtepi32_ps(u1234floor));
	v1234frac = _mm_sub_ps(v1234, _mm_cvtepi32_ps(v1234floor));

	src_half_w = (src->width >> 1);
	src_half_h = (src->height >> 1);
	half_w = _mm_set_epi32(src_half_w, src_half_w, src_half_w, src_half_w);
	half_h = _mm_set_epi32(src_half_h, src_half_h, src_half_h, src_half_h);
	u1234floor = _mm_add_epi32(half_w, u1234floor);//src_half_w + x
	v1234floor = _mm_sub_epi32(half_h, v1234floor);//src_half_h - y
	_mm_store_si128(x, u1234floor);
	_mm_store_si128(y, v1234floor);

	_mm_store_si128(x_weight, _mm_abs_epi32(_mm_cvtps_epi32(_mm_mul_ps(u1234frac, _mm_set_ps(2048, 2048, 2048, 2048)))));//((float) u1234frac*2048) --> int
	_mm_store_si128(y_weight, _mm_abs_epi32(_mm_cvtps_epi32(_mm_mul_ps(v1234frac, _mm_set_ps(2048, 2048, 2048, 2048)))));//((float) v1234frac*2048) --> int
	/******************************************/
	pixel_value->m128i_u8[0] = (uchar)((
		(int)image_get_pixel_value(src, x[0], y[0], 0) * (2048 - y_weight[0]) * (2048 - x_weight[0]) +
		(int)image_get_pixel_value(src, x[0] + 1, y[0], 0) * x_weight[0] * (2048 - y_weight[0]) +
		(int)image_get_pixel_value(src, x[0], y[0] - 1, 0) * y_weight[0] * (2048 - x_weight[0]) +
		(int)image_get_pixel_value(src, x[0] + 1, y[0] - 1, 0) * y_weight[0] * x_weight[0]) >> 22);
	pixel_value->m128i_u8[1] = (uchar)((
		(int)image_get_pixel_value(src, x[0], y[0], 1) * (2048 - y_weight[0]) * (2048 - x_weight[0]) +
		(int)image_get_pixel_value(src, x[0] + 1, y[0], 1) * x_weight[0] * (2048 - y_weight[0]) +
		(int)image_get_pixel_value(src, x[0], y[0] - 1, 1) * y_weight[0] * (2048 - x_weight[0]) +
		(int)image_get_pixel_value(src, x[0] + 1, y[0] - 1, 1) * y_weight[0] * x_weight[0]) >> 22);
	pixel_value->m128i_u8[2] = (uchar)((
		(int)image_get_pixel_value(src, x[0], y[0], 2) * (2048 - y_weight[0]) * (2048 - x_weight[0]) +
		(int)image_get_pixel_value(src, x[0] + 1, y[0], 2) * x_weight[0] * (2048 - y_weight[0]) +
		(int)image_get_pixel_value(src, x[0], y[0] - 1, 2) * y_weight[0] * (2048 - x_weight[0]) +
		(int)image_get_pixel_value(src, x[0] + 1, y[0] - 1, 2) * y_weight[0] * x_weight[0]) >> 22);

	pixel_value->m128i_u8[3] = (uchar)((
		(int)image_get_pixel_value(src, x[1], y[1], 0) * (2048 - y_weight[1]) * (2048 - x_weight[1]) +
		(int)image_get_pixel_value(src, x[1] + 1, y[1], 0) * x_weight[1] * (2048 - y_weight[1]) +
		(int)image_get_pixel_value(src, x[1], y[1] - 1, 0) * y_weight[1] * (2048 - x_weight[1]) +
		(int)image_get_pixel_value(src, x[1] + 1, y[1] - 1, 0) * y_weight[1] * x_weight[1]) >> 22);
	pixel_value->m128i_u8[4] = (uchar)((
		(int)image_get_pixel_value(src, x[1], y[1], 1) * (2048 - y_weight[1]) * (2048 - x_weight[1]) +
		(int)image_get_pixel_value(src, x[1] + 1, y[1], 1) * x_weight[1] * (2048 - y_weight[1]) +
		(int)image_get_pixel_value(src, x[1], y[1] - 1, 1) * y_weight[1] * (2048 - x_weight[1]) +
		(int)image_get_pixel_value(src, x[1] + 1, y[1] - 1, 1) * y_weight[1] * x_weight[1]) >> 22);
	pixel_value->m128i_u8[5] = (uchar)((
		(int)image_get_pixel_value(src, x[1], y[1], 2) * (2048 - y_weight[1]) * (2048 - x_weight[1]) +
		(int)image_get_pixel_value(src, x[1] + 1, y[1], 2) * x_weight[1] * (2048 - y_weight[1]) +
		(int)image_get_pixel_value(src, x[1], y[1] - 1, 2) * y_weight[1] * (2048 - x_weight[1]) +
		(int)image_get_pixel_value(src, x[1] + 1, y[1] - 1, 2) * y_weight[1] * x_weight[1]) >> 22);

	pixel_value->m128i_u8[6] = (uchar)((
		(int)image_get_pixel_value(src, x[2], y[2], 0) * (2048 - y_weight[2]) * (2048 - x_weight[2]) +
		(int)image_get_pixel_value(src, x[2] + 1, y[2], 0) * x_weight[2] * (2048 - y_weight[2]) +
		(int)image_get_pixel_value(src, x[2], y[2] - 1, 0) * y_weight[2] * (2048 - x_weight[2]) +
		(int)image_get_pixel_value(src, x[2] + 1, y[2] - 1, 0) * y_weight[2] * x_weight[2]) >> 22);
	pixel_value->m128i_u8[7] = (uchar)((
		(int)image_get_pixel_value(src, x[2], y[2], 1) * (2048 - y_weight[2]) * (2048 - x_weight[2]) +
		(int)image_get_pixel_value(src, x[2] + 1, y[2], 1) * x_weight[2] * (2048 - y_weight[2]) +
		(int)image_get_pixel_value(src, x[2], y[2] - 1, 1) * y_weight[2] * (2048 - x_weight[2]) +
		(int)image_get_pixel_value(src, x[2] + 1, y[2] - 1, 1) * y_weight[2] * x_weight[2]) >> 22);
	pixel_value->m128i_u8[8] = (uchar)((
		(int)image_get_pixel_value(src, x[2], y[2], 2) * (2048 - y_weight[2]) * (2048 - x_weight[2]) +
		(int)image_get_pixel_value(src, x[2] + 1, y[2], 2) * x_weight[2] * (2048 - y_weight[2]) +
		(int)image_get_pixel_value(src, x[2], y[2] - 1, 2) * y_weight[2] * (2048 - x_weight[2]) +
		(int)image_get_pixel_value(src, x[2] + 1, y[2] - 1, 2) * y_weight[2] * x_weight[2]) >> 22);

	pixel_value->m128i_u8[9] = (uchar)((
		(int)image_get_pixel_value(src, x[3], y[3], 0) * (2048 - y_weight[3]) * (2048 - x_weight[3]) +
		(int)image_get_pixel_value(src, x[3] + 1, y[3], 0) * x_weight[3] * (2048 - y_weight[3]) +
		(int)image_get_pixel_value(src, x[3], y[3] - 1, 0) * y_weight[3] * (2048 - x_weight[3]) +
		(int)image_get_pixel_value(src, x[3] + 1, y[3] - 1, 0) * y_weight[3] * x_weight[3]) >> 22);
	pixel_value->m128i_u8[10] = (uchar)((
		(int)image_get_pixel_value(src, x[3], y[3], 1) * (2048 - y_weight[3]) * (2048 - x_weight[3]) +
		(int)image_get_pixel_value(src, x[3] + 1, y[3], 1) * x_weight[3] * (2048 - y_weight[3]) +
		(int)image_get_pixel_value(src, x[3], y[3] - 1, 1) * y_weight[3] * (2048 - x_weight[3]) +
		(int)image_get_pixel_value(src, x[3] + 1, y[3] - 1, 1) * y_weight[3] * x_weight[3]) >> 22);
	pixel_value->m128i_u8[11] = (uchar)((
		(int)image_get_pixel_value(src, x[3], y[3], 2) * (2048 - y_weight[3]) * (2048 - x_weight[3]) +
		(int)image_get_pixel_value(src, x[3] + 1, y[3], 2) * x_weight[3] * (2048 - y_weight[3]) +
		(int)image_get_pixel_value(src, x[3], y[3] - 1, 2) * y_weight[3] * (2048 - x_weight[3]) +
		(int)image_get_pixel_value(src, x[3] + 1, y[3] - 1, 2) * y_weight[3] * x_weight[3]) >> 22);

	/************************************************************************/
	/*pixel_value->m128i_u8[12] = 0;
	pixel_value->m128i_u8[13] = 0;
	pixel_value->m128i_u8[14] = 0;
	pixel_value->m128i_u8[15] = 0;*/
}


void image_interpolation_sse1(image_t *src,
	int src_width,
	int src_height,
	point2_f32_t *uv,
	__m128i  *pixel_value)
{
	assert(src->channel == 3);
	int src_half_w, src_half_h;
	int x_weight[4], y_weight[4], x[4], y[4];
	__m128 u1234, v1234, u1234frac, v1234frac;
	__m128i u1234floor, v1234floor, half_w, half_h;
	u1234 = _mm_set_ps(uv[3].x, uv[2].x, uv[1].x, uv[0].x);//x[4]
	v1234 = _mm_set_ps(uv[3].y, uv[2].y, uv[1].y, uv[0].y);//y[4]

	u1234floor = _mm_cvtps_epi32(_mm_floor(u1234));//(int)u1234
	v1234floor = _mm_cvtps_epi32(_mm_floor(v1234));//(int)v1234
	u1234frac = _mm_sub_ps(u1234, _mm_cvtepi32_ps(u1234floor));
	v1234frac = _mm_sub_ps(v1234, _mm_cvtepi32_ps(v1234floor));

	src_half_w = (src_width >> 1);
	src_half_h = (src_height >> 1);
	half_w = _mm_set_epi32(src_half_w, src_half_w, src_half_w, src_half_w);
	half_h = _mm_set_epi32(src_half_h, src_half_h, src_half_h, src_half_h);
	u1234floor = _mm_add_epi32(half_w, u1234floor);//src_half_w + x
	v1234floor = _mm_sub_epi32(half_h, v1234floor);//src_half_h - y
	_mm_store_si128(x, u1234floor);
	_mm_store_si128(y, v1234floor);

	_mm_store_si128(x_weight, _mm_abs_epi32(_mm_cvtps_epi32(_mm_mul_ps(u1234frac, _mm_set_ps(2048, 2048, 2048, 2048)))));//((float) u1234frac*2048) --> int
	_mm_store_si128(y_weight, _mm_abs_epi32(_mm_cvtps_epi32(_mm_mul_ps(v1234frac, _mm_set_ps(2048, 2048, 2048, 2048)))));//((float) v1234frac*2048) --> int
	/******************************************/
	pixel_value->m128i_u8[0] = (uchar)((
		(int)image_get_pixel_value(src, x[0], y[0], 0) * (2048 - y_weight[0]) * (2048 - x_weight[0]) +
		(int)image_get_pixel_value(src, x[0] + 1, y[0], 0) * x_weight[0] * (2048 - y_weight[0]) +
		(int)image_get_pixel_value(src, x[0], y[0] - 1, 0) * y_weight[0] * (2048 - x_weight[0]) +
		(int)image_get_pixel_value(src, x[0] + 1, y[0] - 1, 0) * y_weight[0] * x_weight[0]) >> 22);
	pixel_value->m128i_u8[1] = (uchar)((
		(int)image_get_pixel_value(src, x[0], y[0], 1) * (2048 - y_weight[0]) * (2048 - x_weight[0]) +
		(int)image_get_pixel_value(src, x[0] + 1, y[0], 1) * x_weight[0] * (2048 - y_weight[0]) +
		(int)image_get_pixel_value(src, x[0], y[0] - 1, 1) * y_weight[0] * (2048 - x_weight[0]) +
		(int)image_get_pixel_value(src, x[0] + 1, y[0] - 1, 1) * y_weight[0] * x_weight[0]) >> 22);
	pixel_value->m128i_u8[2] = (uchar)((
		(int)image_get_pixel_value(src, x[0], y[0], 2) * (2048 - y_weight[0]) * (2048 - x_weight[0]) +
		(int)image_get_pixel_value(src, x[0] + 1, y[0], 2) * x_weight[0] * (2048 - y_weight[0]) +
		(int)image_get_pixel_value(src, x[0], y[0] - 1, 2) * y_weight[0] * (2048 - x_weight[0]) +
		(int)image_get_pixel_value(src, x[0] + 1, y[0] - 1, 2) * y_weight[0] * x_weight[0]) >> 22);

	pixel_value->m128i_u8[3] = (uchar)((
		(int)image_get_pixel_value(src, x[1], y[1], 0) * (2048 - y_weight[1]) * (2048 - x_weight[1]) +
		(int)image_get_pixel_value(src, x[1] + 1, y[1], 0) * x_weight[1] * (2048 - y_weight[1]) +
		(int)image_get_pixel_value(src, x[1], y[1] - 1, 0) * y_weight[1] * (2048 - x_weight[1]) +
		(int)image_get_pixel_value(src, x[1] + 1, y[1] - 1, 0) * y_weight[1] * x_weight[1]) >> 22);
	pixel_value->m128i_u8[4] = (uchar)((
		(int)image_get_pixel_value(src, x[1], y[1], 1) * (2048 - y_weight[1]) * (2048 - x_weight[1]) +
		(int)image_get_pixel_value(src, x[1] + 1, y[1], 1) * x_weight[1] * (2048 - y_weight[1]) +
		(int)image_get_pixel_value(src, x[1], y[1] - 1, 1) * y_weight[1] * (2048 - x_weight[1]) +
		(int)image_get_pixel_value(src, x[1] + 1, y[1] - 1, 1) * y_weight[1] * x_weight[1]) >> 22);
	pixel_value->m128i_u8[5] = (uchar)((
		(int)image_get_pixel_value(src, x[1], y[1], 2) * (2048 - y_weight[1]) * (2048 - x_weight[1]) +
		(int)image_get_pixel_value(src, x[1] + 1, y[1], 2) * x_weight[1] * (2048 - y_weight[1]) +
		(int)image_get_pixel_value(src, x[1], y[1] - 1, 2) * y_weight[1] * (2048 - x_weight[1]) +
		(int)image_get_pixel_value(src, x[1] + 1, y[1] - 1, 2) * y_weight[1] * x_weight[1]) >> 22);

	pixel_value->m128i_u8[6] = (uchar)((
		(int)image_get_pixel_value(src, x[2], y[2], 0) * (2048 - y_weight[2]) * (2048 - x_weight[2]) +
		(int)image_get_pixel_value(src, x[2] + 1, y[2], 0) * x_weight[2] * (2048 - y_weight[2]) +
		(int)image_get_pixel_value(src, x[2], y[2] - 1, 0) * y_weight[2] * (2048 - x_weight[2]) +
		(int)image_get_pixel_value(src, x[2] + 1, y[2] - 1, 0) * y_weight[2] * x_weight[2]) >> 22);
	pixel_value->m128i_u8[7] = (uchar)((
		(int)image_get_pixel_value(src, x[2], y[2], 1) * (2048 - y_weight[2]) * (2048 - x_weight[2]) +
		(int)image_get_pixel_value(src, x[2] + 1, y[2], 1) * x_weight[2] * (2048 - y_weight[2]) +
		(int)image_get_pixel_value(src, x[2], y[2] - 1, 1) * y_weight[2] * (2048 - x_weight[2]) +
		(int)image_get_pixel_value(src, x[2] + 1, y[2] - 1, 1) * y_weight[2] * x_weight[2]) >> 22);
	pixel_value->m128i_u8[8] = (uchar)((
		(int)image_get_pixel_value(src, x[2], y[2], 2) * (2048 - y_weight[2]) * (2048 - x_weight[2]) +
		(int)image_get_pixel_value(src, x[2] + 1, y[2], 2) * x_weight[2] * (2048 - y_weight[2]) +
		(int)image_get_pixel_value(src, x[2], y[2] - 1, 2) * y_weight[2] * (2048 - x_weight[2]) +
		(int)image_get_pixel_value(src, x[2] + 1, y[2] - 1, 2) * y_weight[2] * x_weight[2]) >> 22);

	pixel_value->m128i_u8[9] = (uchar)((
		(int)image_get_pixel_value(src, x[3], y[3], 0) * (2048 - y_weight[3]) * (2048 - x_weight[3]) +
		(int)image_get_pixel_value(src, x[3] + 1, y[3], 0) * x_weight[3] * (2048 - y_weight[3]) +
		(int)image_get_pixel_value(src, x[3], y[3] - 1, 0) * y_weight[3] * (2048 - x_weight[3]) +
		(int)image_get_pixel_value(src, x[3] + 1, y[3] - 1, 0) * y_weight[3] * x_weight[3]) >> 22);
	pixel_value->m128i_u8[10] = (uchar)((
		(int)image_get_pixel_value(src, x[3], y[3], 1) * (2048 - y_weight[3]) * (2048 - x_weight[3]) +
		(int)image_get_pixel_value(src, x[3] + 1, y[3], 1) * x_weight[3] * (2048 - y_weight[3]) +
		(int)image_get_pixel_value(src, x[3], y[3] - 1, 1) * y_weight[3] * (2048 - x_weight[3]) +
		(int)image_get_pixel_value(src, x[3] + 1, y[3] - 1, 1) * y_weight[3] * x_weight[3]) >> 22);
	pixel_value->m128i_u8[11] = (uchar)((
		(int)image_get_pixel_value(src, x[3], y[3], 2) * (2048 - y_weight[3]) * (2048 - x_weight[3]) +
		(int)image_get_pixel_value(src, x[3] + 1, y[3], 2) * x_weight[3] * (2048 - y_weight[3]) +
		(int)image_get_pixel_value(src, x[3], y[3] - 1, 2) * y_weight[3] * (2048 - x_weight[3]) +
		(int)image_get_pixel_value(src, x[3] + 1, y[3] - 1, 2) * y_weight[3] * x_weight[3]) >> 22);

	/************************************************************************/
	/*pixel_value->m128i_u8[12] = 0;
	pixel_value->m128i_u8[13] = 0;
	pixel_value->m128i_u8[14] = 0;
	pixel_value->m128i_u8[15] = 0;*/
}

#endif

#ifdef OPENCV
void ipltoimage_t(IplImage *src, image_t *dst)
{
	uchar value;
	int i, j, k, step;
	step = src->widthStep;
	for (k = 0; k < src->nChannels; k++)
		for (j = 0; j < src->height; j++)
			for (i = 0; i < src->width; i++){
				value = src->imageData[j*step + i*src->nChannels + k];
				image_set_pixel_value(dst, i, j, k, (int)value);
			}
}


void ipltoimage_t1(IplImage *src, void **_dst)
{
	uchar value;
	int i, j, k;
	int step, dst_widthstep, dst_height;
	uchar *dst = NULL;
	step = src->widthStep;
	dst_widthstep = src->width *src->nChannels;
	dst_height = src->height;
	if (src->width & 15)
		dst_widthstep = (src->width + 16 - (src->width & 15))*src->nChannels;
	if (src->height & 15)
		dst_height = src->height + 16 - (src->height & 15);
	if (!(*_dst))
		*_dst = (char*)malloc(dst_widthstep*dst_height*sizeof(char));
	dst = *_dst;
	for (k = 0; k < src->nChannels; k++)
		for (j = 0; j < src->height; j++)
			for (i = 0; i < src->width; i++){
				value = src->imageData[j*step + i*src->nChannels + k];
				dst[j*dst_widthstep + i*src->nChannels + k] = value;
			}
}


void image_ttoipl(image_t *src, IplImage *dst)
{
	uchar value;
	int i, j, k;
	int step;
	step = dst->widthStep;
	for (k = 0; k < src->channel; k++)
		for (j = 0; j < src->height; j++)
			for (i = 0; i < src->width; i++){
				value = image_get_pixel_value(src, i, j, k);
				dst->imageData[j*step + i*src->channel + k] = value;
			}
}


void showimage(char *windowsname, image_t *src, int t)
{
	IplImage *img = cvCreateImage(cvSize(src->width, src->height),
		src->depth,
		src->channel);
	image_ttoipl(src, img);
	cvNamedWindow(windowsname, 0);
	/*cvResizeWindow(windowsname, img->width, img->height);*/
	cvShowImage(windowsname, img);
	cvWaitKey(t);
	cvReleaseImage(&img);
	/*cvDestroyAllWindows();*/
}

#endif