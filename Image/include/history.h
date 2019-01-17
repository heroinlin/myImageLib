#ifndef HISTORY_H
#define  HISTORY_H
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "elem_type.h"
#ifdef __cplusplus
extern "C" {
#endif


	typedef struct histogram_s {
		/* the bin of histogram */
		int bin;
		/* the range of histogram */
		int ranges;
		/* the data of histogram */
		float *value;
	}histogram_t;


	/**
	* histogram_get_bin - get the bin of the histogram
	*
	* Parameters:
	* @hist - the histogram itself
	*
	* Return:
	* the bin of histogram.
	*/
	static __inline int histogram_get_bin(histogram_t *hist)
	{
		return hist->bin;
	}


	/**
	* histogram_get_range - get the range of the histogram
	*
	* Parameters:
	* @hist - the histogram itself
	*
	* Return:
	* the range of histogram.
	*/
	static __inline int histogram_get_range(histogram_t *hist)
	{
		return hist->ranges;
	}


	/**
	* histogram_get_value - get the value of the histogram in a bin.
	*
	* Parameters:
	* @hist - the histogram itself
	* @bin_index - the index of bin which want to get the value.
	*
	* Return:
	* the value of histogram in a bin.
	*/
	static __inline float histogram_get_value(histogram_t *hist, int bin_index)
	{
		return hist->value[bin_index];
	}


	/**
	* histogram_set_value - set the value of the histogram in a bin.
	*
	* Parameters:
	* @hist - the histogram itself
	* @bin_index - the index of bin which want to set the value.
	* @value - new value
	*
	* Return:
	* none
	*/
	static __inline void histogram_set_value(histogram_t *hist,
		int bin_index,
		float value)
	{
		hist->value[bin_index] = value;
	}


	/**
	* histogram_create - create the histogram_t structure
	*
	* Parameters:
	* @bin ----- the bin of histogram
	* @ranges -- the range of histogram
	*
	* Return:
	* The pointer to the histogram_t
	*/
	extern histogram_t *histogram_create(int bin, int ranges);


	/**
	* histogram_release - release the histogram_t
	*
	* Parameters:
	* @hist - the histogram itself
	*
	* Return:
	*none
	*/
	extern u8_t histogram_release(histogram_t *hist);


	/**
	* ThreshHistory - Clear all histogram bins that are below the threshold
	*
	* Parameters:
	* @hist	------ the source histogram
	* @threshold - threshold value of bin
	*
	* Return:
	* none
	*/
	extern void histogram_threshold(histogram_t *hist, double threshold);


	/**
	* histogram_normalize - Normalizes histogram by dividing all bins by sum of the bins, multiplied by <factor>.
	*                 After that sum of histogram bins is equal to <factor>
	*
	* Parameters:
	* @hist	--- the source histogram
	* @factor - new sum of histogram bins
	*
	* Return:
	* none
	*/
	extern void histogram_normalize(histogram_t *hist, double factor);


	/**
	* histogram_min_max - Finds indices and values of minimum and maximum histogram bins
	*
	* Parameters:
	* @hist	--- the source histogram
	* @minval - the indices of minimum histogram bins
	* @maxval - the indices of maximum histogram bins
	* @minval - the values of minimum histogram bins
	* @minval - the values of maximum histogram bins
	*
	* Return:
	* none
	*/
	extern void histogram_min_max(histogram_t *hist,
		int *minval,
		int *maxval,
		float *minval_p,
		float *maxval_p);


	/*the compare method to histograms */
#define CHISQR 1 
#define CORREL 2
#define INTERSECT 3
#define BHATTACHARYYA 4
	/**
	* histogram_compare - Compares two histogram
	*
	* Parameters:
	* @hist1	--- the first histogram
	* @hist2 - the second histogram
	* @method - the index of method use to compare
	*
	* Return:
	* compare difference value
	* Note:
	* @1. The range of method is [1,4]
	* @2. method 1 is CHISQR,2 is CORREL,3 is INTERSECT,4 is BHATTACHARYYA
	*/
	extern double histogram_compare(histogram_t *hist1,
		histogram_t *hist2,
		int method);


#define IMAGE
#ifdef IMAGE
#include "image.h"


	/**
	* histogram_calculate - Calculates  histogram of image
	*
	* Parameters:
	* @img	--- the image itself
	* @hist - the histogram itself
	*
	* Return:
	* none
	*/
	extern void histogram_calculate(image_t *img, histogram_t *hist);


#endif
#ifdef __cplusplus
}
#endif
#endif
