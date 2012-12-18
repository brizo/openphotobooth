#include "adjust_tint_blue.h"

#include <cmath>

/*************************************************
 File: adjust_tint_blue.cpp
 By: Andy Graulund and Marcel Koglin
 Date: 2012-12-17
 
 Compile: Compiled using OpenFrameworks in Xcode environment, with ofxOpenCV, ofxUI and cURL
 System: Runs on any system supporting OpenFrameworks (the compiled version on a Mac)
 
 Description: This is the image adjustment object for the blue tint adjustment.
 *************************************************/

adjustTintBlue::adjustTintBlue(int newSize, int newAdjust)
: IAdjustment(newSize, newAdjust)
{
	name_   = ADJ_TBL_NAME;
	adjust_ = newAdjust;
}

/**
 * IMAGE ADJUSTMENT: BLUE TINT
 * Uniformly shifts the colors in an image towards the blue.
 * Adjust is from 0 to 100, the higher the closer.
 */
void adjustTintBlue::apply(unsigned char * pxlPtr)
{
#ifdef __openPhotoBooth__DEBUG_FLAG__
	std::cout << "BLUE TINT APPLIED" << std::endl;
#endif
	
	IAdjustment::colorize(pxlPtr, adjust_, 0, 0, 255);
}