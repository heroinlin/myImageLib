#ifndef IMAGE_H
#define  IMAGE_H
#include <assert.h>
#include <math.h>
#ifdef __cplusplus
extern "C" {
#endif
	typedef unsigned char uchar;

	typedef struct Imagesize{
		/* the width of image */
		int width;
		/* the height of image */
		int height;
	}Imagesize;

	typedef struct Image
	{
		/* the channel of image */
		int nChannels;
		/* the depth of image */
		int depth;
		/* the width of image */
		int width;
		/* the height of image */
		int height;
		/* the data of image */
		char *imageData;
	}Image;

	/**
	* get_img_width - get the width of the image
	*
	* Parameters:
	* @img - the image itself
	*
	* Return:
	* The width of image.
	*/
	static __inline int get_img_width(Image *img)
	{
		return img->width;
	}

	/**
	* get_img_height - get the height of the image
	*
	* Parameters:
	* @img - the image itself
	*
	* Return:
	* The height of image.
	*/
	static __inline int get_img_height(Image *img)
	{
		return img->height;
	}

	/**
	* get_img_channel - get the channel of the image
	*
	* Parameters:
	* @img - the image itself
	*
	* Return:
	* The channel of image.
	*/
	static __inline int get_img_channel(Image *img)
	{
		return img->nChannels;
	}

	/**
	* get_img_depth - get the depth of the image
	*
	* Parameters:
	* @img - the image itself
	*
	* Return:
	* The depth of image.
	*/
	static __inline int get_img_depth(Image *img)
	{
		return img->depth;
	}

	/**
	* get_pixel - get the data at (x, y,c) of image
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
	static __inline uchar get_pixel(Image *img, int x, int y, int c)
	{
		/* get value of the pixel that width = x, height = y,channel = c */
		assert(x >= 0 && y >= 0 && c >= 0);
		int step = img->width*img->nChannels;
		return img->imageData[y*step + x*img->nChannels + c];
	}

	/**
	* set_pixel - set the data at (x, y,c) of image
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
	static __inline void set_pixel(Image *img, int x, int y, int c, int val)
	{
		/* set value = val to the pixel that width = x, height = y,channel = c */
		assert(x >= 0 && y >= 0 && c >= 0);
		int step = img->width*img->nChannels;
		img->imageData[y*step + x*img->nChannels + c] = (uchar)val;
	}

	/**
	* add_pixel - add the value to the data at (x, y,c) of image
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
	static __inline void add_pixel(Image *img, int x, int y, int c, int val)
	{
		assert(x < get_img_width(img) && y < get_img_height(img) && c < get_img_channel(img));
		int step = img->width*img->nChannels;
		img->imageData[y*step + x*img->nChannels + c] += (uchar)val;
	}

	/**
	* mul_pixel - multiplies the value to the data at (x, y,c) of image
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
	static __inline void mul_pixel(Image *img, int x, int y, int c, int val)
	{
		assert(x < get_img_width(img) && y < get_img_height(img) && c < get_img_channel(img));
		int step = img->width*img->nChannels;
		img->imageData[y*step + x*img->nChannels + c] *= (uchar)val;
	}

	/**
	* get_img_size - get the size of image
	*
	* Parameters:
	* @img - the image itself
	*
	* Return:
	* the size of image
	*/
	static __inline Imagesize get_img_size(Image *img)
	{
		Imagesize size;
		size.width = get_img_width(img);
		size.height = get_img_height(img);
		return size;
	}

	/**
	* set_img_size - set the size of image
	*
	* Parameters:
	* @width - new width of image 
	* @height - new height of image
	*
	* Return:
	* new size of image
	*/
	static __inline  Imagesize set_img_size(int width, int height)
	{
		Imagesize size;
		size.width = width;
		size.height = height;
		return size;
	}

	/**
	* CreateImage - create the image structure
	*
	* Parameters:
	* @size ----- the size of image
	* @depth ---- the depth of image
	* @channel -- the channel of image
	*
	* Return:
	* The pointer to the image
	*/
	extern Image *CreateImage(Imagesize size, int depth, int channel);

	/**
	* Release - release the image
	*
	* Parameters:
	* @img - the image itself
	*
	* Return:
	*none
	*/
	extern void ReleaseImage(Image *src);

	/**
	* CopyImage - copy src to dst image
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
	extern void CopyImage(Image *src, Image *dst);

	/**
	* Img_flip - flip image
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
	extern void Img_flip(Image *src, int flip_code );

	/**
	* Img_Grayscale - convert image to gray image
	*
	* Parameters:
	* @src -  the source image, size of src must be  width * height * 3
	* @gray - the output gray image, size of gray is width * height
	*
	* Return:
	* none
	*/
	extern void Img_Grayscale(Image *src, Image *gray);

	/**
	* Img_Abs_Diff - calculate the difference image of two images
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
	extern void Img_Abs_Diff(Image *src1, Image *src2, Image *dst);

	/**
	* Img_Threshold_Binary - convert the image to the binary one
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
	extern void Img_Threshold_Binary(Image *src, Image *dst, double threshold);

	/**
	* Img_And - 'and' operation of two images, dst = src1 & src2
	*
	* Parameters:
	* @src1 - the first input image
	* @src2 - the second input image
	* @dst - the output image
	*
	* Return:
	* none
	* Note:
	* @1.src1,src2,dst must have the same size and channel
	*/
	extern void Img_And(Image *src1, Image *src2, Image *dst);

	/**
	* Img_Add - 'add' operation of two images,dst = src1 + src2
	*
	* Parameters:
	* @src1 - the first input image
	* @src2 - the second input image
	* @dst - the output image
	*
	* Return:
	* none
	* Note:
	* @1.src1,src2,dst must have the same size and channel
	*/
	extern void Img_Add(Image *src1, Image *src2, Image *dst);

	/**
	* Img_Crop - crop rectangle on image
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
	extern void Img_Crop(Image *src, Image *dst, int x, int y, int width, int height);

	/**
	* Img_Warp - warp the image
	*
	* Parameters:
	* @src  --- the source image
	* @dst  --- the output image after warping
	*
	* Return:
	* none
	*
	*/
	extern void Img_Warp(Image *src, Image *dst);

	/**
	* Mask_three_frame_diff - Calculate the difference mask image of three images.
	*
	* Parameters:
	* @src1 ------ the first input image
	* @src2 ------ the second input image
	* @src3 ------ the third input image
	* @Imask ----- the output difference image which is  a mask image 
	* @threshold - threshold value of binary 
	* Return:
	* none
	* Note:
	* @1. src1 ,src2 ,src3 and dst must have the same size and channel.
	*/
	extern void Mask_three_frame_diff(Image *src1, Image *src2, Image *src3, Image *Imask, float threshold);

	/**
	* Mask_backgroung_diff - Calculate the difference mask image between the current image and the background image.
	*
	* Parameters:
	* @src1 ------ the background image
	* @src2 ------ the current image
	* @Imask ----- the output difference image which is  a mask image
	* @threshold - threshold value of binary
	* Return:
	* none
	* Note:
	* @1. src1 ,src2 and dst must have the same size and channel.
	*/
	extern void Mask_backgroung_diff(Image *src1, Image *src2, Image *Bmask, float threshold);

	/**
	* Entropy - Calculate the entropy of image.
	*
	* Parameters:
	* @img ------ the source image
	* Return:
	* the entropy value of image.
	*/
	extern float Entropy(Image *img);

#define OPENCV
#ifdef OPENCV
#include <opencv/cv.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui_c.h> 

	/**
	* ipltoImage - convert the IplImage struct to Image struct.
	*
	* Parameters:
	* @src ------ the image which is IplImage type. 
	* @dst ------ the image which is Image type.
	* Return:
	* none
	*/
	extern void ipltoImage(IplImage *src, Image *dst);

	/**
	* Imagetoipl - convert the Image struct to IplImage struct.
	*
	* Parameters:
	* @src ------ the image which is Image type.
	* @dst ------ the image which is IplImage type.
	* Return:
	* none
	*/
	extern void Imagetoipl(Image *src, IplImage *dst);

	/**
	* showimage - show the image in window.
	*
	* Parameters:
	* @windowsname -- the windows name
	* @src ------ the image which is Image type.
	* @t --- waitkey time
	* Return:
	* none
	*/
	extern void showimage(char *windowsname, Image *src, int t);

#endif 

#define RECT
#ifdef RECT
#include "rectangle.h"


#endif // RECT

#ifdef __cplusplus
}
#endif

#endif
