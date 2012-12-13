#include "adjust_brightness.h"

adjustBrightness::adjustBrightness(int newSize, int newAdjust)
	: IAdjustment(newSize, newAdjust)
{
	name_ = NAME;
}

/**
 * IMAGE ADJUSTMENT: BRIGHTNESS
 * Range of adjust is from -100 to 100.
 */
void adjustBrightness::apply(unsigned char * pxlPtr)
{
	#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "BRIGHTNESS APPLYED" << std::endl;
	#endif

	int x = (int) floor(255.0F * (adjust_ / 100.0F));
	
	for (int i = 0; i < imageSize_; i++)
	{
		pxlPtr[i] = IAdjustment::unclip(pxlPtr[i] + x);
	}
}