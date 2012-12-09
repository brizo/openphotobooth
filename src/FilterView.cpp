#include "FilterView.h"

FilterView::FilterView(View * oldView, std::string iconURL, 
	int width, int height) : View(oldView, iconURL, width, height)
{
	delete oldView;
}

/**
 * Draws a given Video Grabber
 * @param vidGrabber Video Grabber which should be drawn to this View
 */
void FilterView::drawVideoGrabber(ofVideoGrabber * vidGrabber,
	float w, float h)
{
	vidGrabber->draw(0, 0, w, h);
}

void FilterView::drawFilter(ofTexture * textureArr, int index)
{
	int y = 0;
	for (int i = 0; i < index; i++)
	{
		if (i < 3)
		{
			textureArr[i].draw(((i + 1) * 213), y, 213, 160);
		}
		if (i > 2)
		{
			y = 160;
			textureArr[i].draw((i * 213) % 639, y, 213, 160);
		}
	}
}

void FilterView::drawFilter(ofTexture texture, int index)
{

//	std::cout << "
	texture.draw(0, 0, 213, 160);
}