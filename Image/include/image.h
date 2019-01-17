#ifndef IMAGE_H
#define  IMAGE_H
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "mysse.h"
#include "my_error.h"
#ifdef __cplusplus
extern "C" {
#endif

	typedef unsigned char uchar;


	typedef struct image_size_s{
		/* the width of image */
		int width;
		/* the height of image */
		int height;
	}image_size_t;


	typedef struct image_s{
		/* the channel of image */
		int channel;
		/* the depth of image */
		int depth;
		/* the width of image */
		int width;
		/* the height of image */
		int height;
		/* the widthStep of image */
		int widthstep;
		/* the data of image */
		uchar *imagedata;
	}image_t;


	/**
	* image_get_width - get the width of the image
	*
	* Parameters:
	* @img - the image itself
	*
	* Return:
	* The width of image.
	*/
	static __inline int image_get_width(image_t *img)
	{
		return img->width;
	}


	/**
	* image_get_height - get the height of the image
	*
	* Parameters:
	* @img - the image itself
	*
	* Return:
	* The height of image.
	*/
	static __inline int image_get_height(image_t *img)
	{
		return img->height;
	}


	/**
	* image_get_channel - get the channel of the image
	*
	* Parameters:
	* @img - the image itself
	*
	* Return:
	* The channel of image.
	*/
	static __inline int image_get_channel(image_t *img)
	{
		return img->channel;
	}


	/**
	* image_get_depth - get the depth of the image
	*
	* Parameters:
	* @img - the image itself
	*
	* Return:
	* The depth of image.
	*/
	static __inline int image_get_depth(image_t *img)
	{
		return img->depth;
	}


	/**
	* image_get_widthStep - get the widthStep of the image
	*
	* Parameters:
	* @img - the image itself
	*
	* Return:
	* The widthStep of image.
	*/
	static __inline int image_get_widthstep(image_t *img)
	{
		return img->widthstep;
	}


	/**
	* image_get_pixel_value - get the data at (x, y,c) of image
	*
	* Parameters:
	* @img - the image itself
	* @x --- the x-coordinate location
	* @y --- the y-coordinate location
	* @c --- the channel location
	*
	* Return:
	* The pointer to data at (x, y, c) of image
	*/
	static __inline uchar image_get_pixel_value(image_t *img,
		int x,
		int y,
		int c)
	{
		/* get value of the pixel that width = x, height = y,channel = c */
		assert(x >= 0 && y >= 0 && c >= 0);
		return img->imagedata[y*img->widthstep + x*img->channel + c];
	}


	/**
	* image_set_pixel_value - set the data at (x, y,c) of image
	*
	* Parameters:
	* @img - the image itself
	* @x --- the x-coordinate location
	* @y --- the y-coordinate location
	* @c --- the channel location
	* @val - the new value
	*
	* Return:
	* none
	*/
	static __inline void image_set_pixel_value(image_t *img,
		int x,
		int y,
		int c,
		int val)
	{
		/* set value = val to the pixel that width = x, height = y,channel = c */
		assert(x >= 0 && y >= 0 && c >= 0);
		img->imagedata[y*img->widthstep + x*img->channel + c] = (uchar)val;
	}


	/**
	* image_add_pixel_value - add the value to the data at (x, y,c) of image
	*
	* Parameters:
	* @img - the image itself
	* @x --- the x-coordinate location
	* @y --- the y-coordinate location
	* @c --- the channel location
	* @val - the value to be added
	*
	* Return:
	* none
	*/
	static __inline void image_add_pixel_value(image_t *img,
		int x,
		int y,
		int c,
		int val)
	{
		assert(x < image_get_width(img) && y < image_get_height(img) && c < image_get_channel(img));
		img->imagedata[y*img->widthstep + x*img->channel + c] += (uchar)val;
	}


	/**
	* image_mul_pixel_value - multiplies the value to the data at (x, y,c) of image
	*
	* Parameters:
	* @img - the image itself
	* @x --- the x-coordinate location
	* @y --- the y-coordinate location
	* @c --- the channel location
	* @val - the value to be multiplied
	*
	* Return:
	* none
	*/
	static __inline void image_mul_pixel_value(image_t *img,
		int x,
		int y,
		int c,
		int val)
	{
		assert(x < image_get_width(img) && y < image_get_height(img) && c < image_get_channel(img));
		img->imagedata[y*img->widthstep + x*img->channel + c] *= (uchar)val;
	}


	/**
	* image_get_size - get the size of image
	*
	* Parameters:
	* @img - the image itself
	*
	* Return:
	* the size of image
	*/
	static __inline image_size_t image_get_size(image_t *img)
	{
		image_size_t size;
		size.width = image_get_width(img);
		size.height = image_get_height(img);
		return size;
	}


	/**
	* image_set_size - set the size of image
	*
	* Parameters:
	* @width - new width of image
	* @height - new height of image
	*
	* Return:
	* new size of image
	*/
	static __inline  image_size_t image_set_size(int width, int height)
	{
		image_size_t size;
		size.width = width;
		size.height = height;
		return size;
	}


	/**
	* image_create - create the image structure
	*
	* Parameters:
	* @size ----- the size of image
	* @depth ---- the depth of image
	* @channel -- the channel of image
	*
	* Return:
	* The pointer to the image
	*/
	extern image_t *image_create(image_size_t size, int depth, int channel);


	/**
	* Release - release the image
	*
	* Parameters:
	* @img - the image itself
	*
	* Return:
	*none
	*/
	extern uchar image_release(image_t *src);


	/**
	* image_copy - copy src to dst image
	*
	* Parameters:
	* @src - the source image
	* @dst - the destination image
	*
	* Return:
	* none
	*
	* Note:
	* @1. The alloc size of @dst must  equal to the size of @src.
	*/
	extern void image_copy(image_t *src, image_t *dst);


	/**
	* image_flip - flip image
	*
	* Parameters:
	* @src - the source image
	* @dst - the destination image
	* @flip_code - mirror method,
	*
	* Return:
	* none
	*
	* Note:
	* 1.the range of @flip_code is{-1,0,1}. 0 is mirror horizontally,1 is mirror vertically, -1 is flip 180 degrees.
	*/
	extern void image_flip(image_t *src, int flip_code);


	/**
	* image_grayscale - convert image to gray image
	*
	* Parameters:
	* @src -  the source image, size of src must be  width * height * 3
	* @gray - the output gray image, size of gray is width * height
	*
	* Return:
	* none
	*/
	extern void image_grayscale(image_t *src, image_t *gray);


	/**
	* image_abs_diff - calculate the difference image of two images
	*
	* Parameters:
	* @src1 - the first input image
	* @src2 - the second input image
	* @dst - the output difference image
	*
	* Return:
	* none
	* Note:
	* @1. src1 src2,and dst must have the same size and channel.
	*/
	extern void image_abs_diff(image_t *src1, image_t *src2, image_t *dst);


	/**
	* image_threshold_binary - convert the image to the binary one
	*
	* Parameters:
	* @src	------ the source image
	* @dst	------ the output image
	* @threshold - threshold value of binary
	*
	* Return:
	* none
	* Note:
	* @1. src1 and dst must have the same size and channel.
	*/
	extern void image_threshold_binary(image_t *src,
		image_t *dst,
		double threshold);


	/**
	* image_and - 'and' operation of two images, dst = src1 & src2
	*
	* Parameters:
	* @src1 - the first input image
	* @src2 - the second input image
	* @dst - the output image
	*
	* Return:
	* none
	*/
	extern void image_and(image_t *src1, image_t *src2, image_t *dst);


	/**
	* image_add - 'add' operation of two images,dst = src1 + src2
	*
	* Parameters:
	* @src1 - the first input image
	* @src2 - the second input image
	* @dst - the output image
	*
	* Return:
	* none
	*/
	extern void image_add(image_t *src1, image_t *src2, image_t *dst);


	/**
	* image_interpolation - Bilinear interpolation
	*
	* Parameters:
	* @src  --- the source image
	* @x  --- the x-coordinate of point after projection
	* @y --- the y-coordinate of point after projection
	* @c --- the channel of point after projection
	* Return:
	* the unsigned char value of pixel
	*
	*/
	extern uchar image_interpolation(image_t *src, float x, float y, int c);


	/**
	* image_crop - crop rectangle on image
	*
	* Parameters:
	* @src  --- the source image
	* @dst  --- the output image After cropping
	* @x  ----- the x-coordinate of left_top point of cropping image
	* @y  ----- the y-coordinate of left_top point of cropping image
	* @width  - the width of cropping image
	* @height - the height of cropping image
	*
	* Return:
	* none
	*
	* Note:
	* @1. The range of @x is [0,src.width]
	* @2. The range of @y is [0,src.height]
	* @3. The range of @width is [0,src.width]
	* @4. The range of @height is [0,src.height]
	* @5. 0 <= x; x + width <= src.width;
	* @6. 0 <= y; y + height <= src.height;
	*/
	extern void image_crop(image_t *src,
		image_t *dst,
		int x,
		int y,
		int width,
		int height);


	/**
	* image_warp - warp the image
	*
	* Parameters:
	* @src  --- the source image
	* @dst  --- the output image after warping
	*
	* Return:
	* none
	*
	*/
	extern void image_warp(image_t *src, image_t *dst);

	/**
	* image_warp - warp the image
	*
	* Parameters:
	* @src  --- the source image
	* @dst  --- the output image after warping
	* @src_width  --- the width of effective pixel in src image
	* @src_height  --- the height of effective pixel in src image
	* @dst_width  --- the width of effective pixel in dst image
	* @dst_height  --- the height of effective pixel in dst image
	*
	* Return:
	* none
	*
	*/
	extern void image_warp1(image_t *src,
		image_t *dst,
		int src_width,
		int src_height,
		int dst_width,
		int dst_height);


	/**
	* image_mask_three_frame_diff - Calculate the difference mask image of three images.
	*
	* Parameters:
	* @src1 ------ the first input image
	* @src2 ------ the second input image
	* @src3 ------ the third input image
	* @Imask ----- the output difference image_t which is  a mask image
	* @threshold - threshold value of binary
	* Return:
	* none
	* Note:
	* @1. src1 ,src2 ,src3 and dst must have the same size and channel.
	*/
	extern void image_mask_three_frame_diff(image_t *src1,
		image_t *src2,
		image_t *src3,
		image_t *Imask,
		float threshold);


	/**
	* image_mask_backgroung_diff - Calculate the difference mask image between the current image and the background image.
	*
	* Parameters:
	* @src1 ------ the background image
	* @src2 ------ the current image
	* @Imask ----- the output difference image_t which is  a mask image
	* @threshold - threshold value of binary
	* Return:
	* none
	* Note:
	* @1. src1 ,src2 and dst must have the same size and channel.
	*/
	extern void image_mask_backgroung_diff(image_t *src1,
		image_t *src2,
		image_t *Bmask,
		float threshold);


	/**
	* image_entropy - Calculate the entropy of image.
	*
	* Parameters:
	* @img ------ the source image
	* Return:
	* the entropy value of image.
	*/
	extern float image_entropy(image_t *img);


#define SSE
#ifdef SSE
	/**
	* image_copy_sse - copy src to dst image,SSE version
	*
	* Parameters:
	* @src - the source image
	* @dst - the destination image
	*
	* Return:
	* none
	*
	* Note:
	* @1. The alloc size of @dst must  equal to the size of @src.
	*/
	extern void image_copy_sse(image_t * src, image_t * dst);


	/**
	* image_copy_sse1 - copy src to dst image,SSE version
	*
	* Parameters:
	* @src - the imagedata of source image
	* @dst - the imagedata of destination image
	*
	* Return:
	* none
	*
	* Note:
	* @1. The alloc size of @dst must  equal to the size of @src.
	*/
	extern void image_copy_sse1(void ** _src, void ** _dst);


	/**
	* image_crop_sse - crop rectangle on image,SSE version
	*
	* Parameters:
	* @src  --- the source image
	* @dst  --- the output image After cropping
	* @left  ----- the x-coordinate of left_top point of cropping image
	* @top  ----- the y-coordinate of left_top point of cropping image
	* @width  - the width of cropping image
	* @height - the height of cropping image
	*
	* Return:
	* none
	*
	* Note:
	* @1. The range of @left is [0,src.width]
	* @2. The range of @top is [0,src.height]
	* @3. The range of @width is [0,src.width]
	* @4. The range of @height is [0,src.height]
	* @5. 0 <= left; left + width <= src.width;
	* @6. 0 <= top; top + height <= src.height;
	*/
	extern void image_crop_sse(image_t *src,
		image_t *dst,
		int left,
		int top,
		int width,
		int height);


	/**
	* image_crop_sse1 - crop rectangle on image,SSE version
	*
	* Parameters:
	* @src  --- the source image
	* @dst  --- the output image after cropping
	* @x  ----- the x-coordinate of left_top point of cropping image
	* @top  ----- the y-coordinate of left_top point of cropping image
	* @width  - the width of cropping image
	* @height - the height of cropping image
	*
	* Return:
	* none
	*
	* Note:
	* @1. The range of @left is [0,src.width]
	* @2. The range of @top is [0,src.height]
	* @3. The range of @width is [0,src.width]
	* @4. The range of @height is [0,src.height]
	* @5. 0 <= left; left + width <= src.width;
	* @6. 0 <= top; top + height <= src.height;
	* @7. dst and src have the same size and channel
	* @8. the effective pixel area is @width * @height in dst image.
	*/
	extern void image_crop_sse1(image_t *src,
		image_t *dst,
		int left,
		int top,
		int width,
		int height);


	/**
	* image_warp_sse - warp the image,SSE version
	*
	* Parameters:
	* @src  --- the source image
	* @dst  --- the output image after warping
	*
	* Return:
	* none
	*
	*/
	extern void image_warp_sse(image_t *src, image_t *dst);


	/**
	* image_warp_sse1 - warp the image,SSE version
	*
	* Parameters:
	* @src  --- the source image
	* @dst  --- the output image after warping
	* @src_width  --- the width of effective pixel in src image
	* @src_height  --- the height of effective pixel in src image
	* @dst_width  --- the width of effective pixel in dst image
	* @dst_height  --- the height of effective pixel in dst image
	* Return:
	* none
	*
	* Note:
	* @1.dst and src have the same size and channel .
	* @2.src_width <= src->width,src_height <= src->height
	* @3.dst_width <= dst->width,dst_height <= dst->height
	*/
	extern void image_warp_sse1(image_t *src,
		image_t *dst,
		int src_width,
		int src_height,
		int dst_width,
		int dst_height);


	/**
	* image_interpolation_sse - Bilinear interpolation ,SSE version
	*
	* Parameters:
	* @src  --- the source image
	* @uv  --- 4 float points after projection
	* @pixel_value -- the unsigned char value of 16 pixels
	* Return:
	* none
	*
	* Note:
	*@1.  point2_f32_t * uv is uv[4]
	*@2. *pixel_value :(unsigned char) RGBRGBRGBRGB0000
	*/
	extern void image_interpolation_sse(image_t *src,
		point2_f32_t * uv,
		__m128i *pixel_value);


	/**
	* image_interpolation_sse1 - Bilinear interpolation ,SSE version
	*
	* Parameters:
	* @src  --- the source image
	* @uv  --- 4 float points after projection
	* @pixel_value -- the unsigned char value of 16 pixels
	* @src_width  --- the width of effective pixel in src image
	* @src_height  --- the height of effective pixel in src image
	* Return:
	* none
	*
	* Note:
	*@1.  point2_f32_t * uv is uv[4]
	*@2. *pixel_value :(unsigned char) RGBRGBRGBRGB0000
	*@3. src_width <= src->width,src_height <= src->height
	*/
	extern void image_interpolation_sse1(image_t *src,
		int src_width,
		int src_height,
		point2_f32_t * uv,
		__m128i  * pixel_value);


#endif // SSE
#define OPENCV
#ifdef OPENCV

#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui_c.h> 
	/**
	* ipltoimage_t - convert the IplImage struct to image_t struct.
	*
	* Parameters:
	* @src ------ the image which is IplImage type.
	* @dst ------ the image which is image_t type.
	* Return:
	* none
	*/
	extern void ipltoimage_t(IplImage *src, image_t *dst);


	/**
	* ipltoimage_t1 - convert the Iplimage_t struct to image_t struct.
	*
	* Parameters:
	* @src ------ the image which is Iplimage_t type.
	* @dst ------ the imagedata of destination image.
	* Return:
	* none
	*/
	extern void ipltoimage_t1(IplImage *src, void **dst);


	/**
	* image_ttoipl - convert the image struct to IplImage struct.
	*
	* Parameters:
	* @src ------ the image which is image type.
	* @dst ------ the image which is IplImage type.
	* Return:
	* none
	*/
	extern void image_ttoipl(image_t *src, IplImage *dst);


	/**
	* showimage - show the image in window.
	*
	* Parameters:
	* @windowsname -- the windows name
	* @src ------ the image which is image_t type.
	* @t --- waitkey time
	* Return:
	* none
	*/
	extern void showimage(char *windowsname, image_t *src, int t);


#endif 

#ifdef __cplusplus
}
#endif

#endif
