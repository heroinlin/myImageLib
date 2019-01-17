#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/highgui/highgui_c.h>  
#ifdef __cplusplus
extern "C" {
#endif
#include"image.h"
#include "history.h"
#ifdef __cplusplus
}
#endif

void test()
{
	IplImage *img1 = cvLoadImage("1.jpg", 1);
	IplImage *img2 = cvLoadImage("2.jpg", 1);
	float max_value_p = 0.0, min_value_p = 0.0;
	int max_value = 0, min_value = 0;
	
	/*int bins = 256;
	int sizes[] = { bins };
	CvHistogram *hst1 = cvCreateHist(1, sizes, CV_HIST_ARRAY);
	cvCalcHist(&img1, hst1);
	cvNormalizeHist(hst1, 1);
	cvGetMinMaxHistValue(hst1, &min_value_p, &max_value_p, &min_value, &max_value);
	printf("Hist: %f\t%f\t%d\t%d\n", min_value_p, max_value_p, min_value, max_value);
	CvHistogram *hst2 = cvCreateHist(1, sizes, CV_HIST_ARRAY);
	cvCalcHist(&img2, hst2);
	cvNormalizeHist(hst2, 1);
	double result0 = cvCompareHist(hst1, hst2, CV_COMP_BHATTACHARYYA);
	printf("result0=%f\n", result0);*/
	/*此处创建图像时对图像进行了16位补齐，src1的size和img1的size不相同*/
	image_t *src1 = image_create(image_set_size(img1->width, img1->height), img1->depth, img1->nChannels); 
	image_t *src2 = image_create(image_set_size(img1->width, img1->height), img1->depth, img1->nChannels);
	image_t *src3 = image_create(image_set_size(img1->width/2, img1->height/2), img1->depth, img1->nChannels);
	image_t *src = image_create(image_set_size(img1->width, img1->height), img1->depth, 1);
	ipltoimage_t(img1, src1);
	ipltoimage_t(img2, src2);
	for (int i = 0; i < 100; i++) {
		printf("opencv_data: %d\t", (uchar)img1->imageData[i]);
		printf("image_data: %d\n", (uchar)src1->imagedata[i]);
	}
	histogram_t *hist1 = histogram_create(9, 255);
	histogram_calculate(src1, hist1);
	histogram_normalize(hist1, 1.0);
	histogram_min_max(hist1, &min_value, &max_value, &min_value_p, &max_value_p);
	printf("Hist1: %f\t%f\t%d\t%d\n", min_value_p, max_value_p, min_value, max_value);

	histogram_t *hist2 = histogram_create(9, 255);
	histogram_calculate(src2, hist2);
	histogram_normalize(hist2, 1.0);
	double result = histogram_compare(hist1, hist2, 4);
	printf("result=%f\n", result);
	image_warp(src1, src3);
	image_and(src1, src2, src1);
	//image_copy(img1, img);
	//image_crop(img1,img, 0, 0, 200, 225);
	//image_abs_diff(img1, img2,img);
	//image_threshold_binary(src1,src1, 100);
	
	showimage("image3", src3, 0);
	image_grayscale(src1, src);
	IplImage *img = cvCreateImage(cvSize(src->width, src->height), src->depth, 1);
	image_ttoipl(src, img);
	cvShowImage("src", img);
	cvWaitKey(0);
	image_release(src);
	histogram_release(hist1);
	histogram_release(hist2);
	image_ttoipl(src, img);
	cvShowImage("src1", img);
	cvWaitKey(0);

}

int main()
{
	test();
	return 1;
}

