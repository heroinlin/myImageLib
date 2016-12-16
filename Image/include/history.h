#ifndef HISTORY_H
#define  HISTORY_H
#include <stdlib.h>
#include <math.h>
#include <float.h>
#ifdef __cplusplus
extern "C" {
#endif
	typedef struct History {
		/* the bin of histogram */
		int bin;
		/* the range of histogram */
		int ranges;
		/* the data of histogram */
		float *value;
	}History;

	/**
	* GetHistBin - get the bin of the histogram
	*
	* Parameters:
	* @hist - the histogram itself
	*
	* Return:
	* the bin of histogram.
	*/
	static __inline int GetHistBin(History *hist)
	{
		return hist->bin;
	}

	/**
	* GetHistRange - get the range of the histogram
	*
	* Parameters:
	* @hist - the histogram itself
	*
	* Return:
	* the range of histogram.
	*/
	static __inline int GetHistRange(History *hist)
	{
		return hist->ranges;
	}

	/**
	* GetHistValue - get the value of the histogram in a bin.
	*
	* Parameters:
	* @hist - the histogram itself
	* @bin_index - the index of bin which want to get the value.
	*
	* Return:
	* the value of histogram in a bin.
	*/
	static __inline float GetHistValue(History *hist, int bin_index)
	{
		return hist->value[bin_index];
	}

	/**
	* SetHistValue - set the value of the histogram in a bin.
	*
	* Parameters:
	* @hist - the histogram itself
	* @bin_index - the index of bin which want to set the value.
	* @value - new value 
	*
	* Return:
	* none
	*/
	static __inline void SetHistValue(History *hist, int bin_index, float value)
	{
		hist->value[bin_index] = value;
	}

	/**
	* CreateHistory - create the History structure
	*
	* Parameters:
	* @bin ----- the bin of histogram
	* @ranges -- the range of histogram
	*
	* Return:
	* The pointer to the History
	*/
	extern History *CreateHistory(int bin, int ranges);

	/**
	* ReleaseHistory - release the History
	*
	* Parameters:
	* @hist - the histogram itself
	*
	* Return:
	*none
	*/
	extern void ReleaseHistory(History *hist);

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
	
	extern void ThreshHist(History *hist, double threshold);

	/**
	* NormalizeHist - Normalizes histogram by dividing all bins by sum of the bins, multiplied by <factor>.
	*                 After that sum of histogram bins is equal to <factor>
	*
	* Parameters:
	* @hist	--- the source histogram
	* @factor - new sum of histogram bins
	*
	* Return:
	* none
	*/
	extern void NormalizeHist(History *hist, double factor);

	/**
	* minmax_hist - Finds indices and values of minimum and maximum histogram bins
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
	extern void minmax_hist(History *hist, int *minval, int *maxval, float *minval_p, float *maxval_p);

/*the compare method to histograms */
#define CHISQR 1 
#define CORREL 2
#define INTERSECT 3
#define BHATTACHARYYA 4
	/**
	* CompareHist - Compares two histogram 
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
	extern double CompareHist(History *hist1, History *hist2, int method);

#define IMAGE
#ifdef IMAGE
#include "image.h"

	/**
	* clachist - Calculates  histogram of image
	*
	* Parameters:
	* @img	--- the image itself
	* @hist - the histogram itself
	*
	* Return:
	* none
	*/
	extern void clachist(Image *img, History *hist);

#endif
#ifdef __cplusplus
}
#endif
#endif
