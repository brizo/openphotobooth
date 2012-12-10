#include "Model.h"

#include <ctime>

Model::Model()
{
	init();
	init(0, 0, 0);
}

Model::Model(Model * oldModel, bool delOld)
{
	vidGrabber_ = oldModel->getVideoGrabber();
	texture_ = oldModel->getTexture();
	thumbArr_ = oldModel->getThumbnails();

	imgCnt_ = oldModel->getImgCount();
	imgIndex_ = oldModel->getImgIndex();
	imgSelector_ = oldModel->updateThumbnailSelector(0);
	thmbCnt_ = oldModel->getThumbnailCount();

	init();

	if (delOld)
		delete oldModel;
}

void Model::init()
{
	btnLabelL_ = BTN_LABL_L;
	btnLabelR_ = BTN_LABL_R;

	btnNameL_ = BTN_NAME_L;
	btnNameM_ = BTN_NAME_M;
	btnNameR_ = BTN_NAME_R;
}

void Model::init(int imgCnt, int imgIndex, int imgSelector)
{
	imgCnt_ = imgCnt;
	imgIndex_ = imgIndex;
	imgSelector_ = imgSelector;
	thmbCnt_ = THUMBNAIL_CNT;

	vidGrabber_ = new ofVideoGrabber();
	texture_ = new ofTexture();
	thumbArr_ = new ofImage[THUMBNAIL_CNT];

	vidGrabber_->initGrabber(CAM_WIDTH, CAM_HEIGHT);
	texture_->allocate(CAM_WIDTH, CAM_HEIGHT, GL_RGB);
}

// void Model::loadImage(int index)
// {

// }

/**
 * Saves the current frame from the Webcam with given Width and
 * Height to a File. Saves also the Thumbnail to an Array
 * @param camWidth  width of the Picture
 * @param camHeight height of the Picture
 */
void Model::saveImage()
{
	std::string imgName = getImageName();

	pixelArr_ = vidGrabber_->getPixels();
	texture_->loadData(pixelArr_, CAM_WIDTH, CAM_HEIGHT, GL_RGB);
	saveTextureToFile(imgName);
	saveToThumbnail(imgName);
}

/**
 * Saves the ofPixel Object to a given Filename
 * @param pix  picture Object as Pixel
 * @param name name of the new Filename
 */
void Model::savePixelsToFile(ofPixels pix, std::string name)
{
	ofSaveImage(pix, name);
}

/**
 * Transforms a ofTexture to a ofPixel and saves it to a given
 * Filename
 * @param tex  picture Object as Texture
 * @param name name of the new Filename
 */
void Model::saveTextureToFile(std::string name)
{
	ofPixels p;
	texture_->readToPixels(p);
	savePixelsToFile(p, name);
}

/**
 * Reize and Saves a Picture file into an Array
 * @param tex  picture Object as Texture
 * @param name filename of the Picture which should be saved
 */
void Model::saveToThumbnail(std::string name)
{
	thumbArr_[imgIndex_].loadImage(name);
	// resizeToThumbnail(thumbArr_[imgIndex_], THUMBNAIL_RATIO);
	updateImgCount();
}

/**
 * Updates the Image Count and Index for the Thumbnail Array
 */
void Model::updateImgCount()
{
	imgIndex_ = (imgIndex_ + 1) % THUMBNAIL_CNT;
	imgCnt_ = (imgCnt_ + 1) % (THUMBNAIL_CNT + 1);

	if (imgCnt_ == 0 && imgIndex_ > 0)
	{
		imgCnt_ = 1;
	}
}

/**
 * Resize a given ofImage file to a given aspect Ratio
 * @param img   image which shoule be resized
 * @param ratio aspect ratio in pixel
 */
void Model::resizeToThumbnail(ofImage img, float ratio)
{
	float imgWidth = img.getWidth();
	float imgHeight = img.getHeight();

	if (imgWidth > ratio)
	{
		img.resize(ratio, imgWidth / imgHeight);
	}
	else if (imgHeight > ratio)
	{
		img.resize(imgHeight / imgWidth, ratio);
	}
}

/**
 * Fetches the last Texture from the Webcam
 */
void Model::update()
{
	vidGrabber_->update();
	// unsigned char * myPixelArr = vidGrabber_->getPixels();
	// texture_->loadData(myPixelArr, 640, 480, GL_RGB);
}

/**
 * Returns the current Image Count
 * @return
 */
int Model::getImgCount()
{
	return imgCnt_;
}

/**
 * Returns the size of the Thumbnail Array
 * @return (int) size of Thumbnail Array
 */
int Model::getThumbnailCount()
{
	return thmbCnt_;
}

/**
 * Updates the new Position of the THumnail Selector. Use a negative
 * int to decrease the Position. a Positive Interger increase the 
 * Position. A Zero return the current Position. If the Thumbnail
 * count below two, no selector is drawn.
 * @param  nextImage positive or Negative Int to change the Position
 * @return
 */
int Model::updateThumbnailSelector(int nextImage)
{
	if (imgCnt_ < 2)
	{
		return 0;
	}
	else if (nextImage > 0)
	{
		if (imgSelector_ + 1 > imgCnt_)
		{
			return (imgSelector_ = 1);
		}
		return ++imgSelector_;
	}
	else if (nextImage < 0)
	{
		if (imgSelector_ - 1 < 1)
		{
			return (imgSelector_ = imgCnt_);
		}
		return --imgSelector_;
	}
	else
	{
		return imgSelector_;
	}
}

/**
 * Returns the Thumbnail Selector
 * @return
 */
int Model::getThumbnailSelector()
{
	return imgSelector_;
}

/**
 * Returns the current Image Index of the Thumbnail Array
 * @return
 */
int Model::getImgIndex()
{
	return imgIndex_;
}

/**
 * Returns the Cam Width in Pixel
 * @return
 */
float Model::getCamWidth()
{
	return float(CAM_WIDTH);
}

/**
 * Returns the Cam Height in Pixel
 * @return
 */
float Model::getCamHeight()
{
	return float(CAM_HEIGHT);
}

/**
 * Returns the Current Date and Time. Used for the Image Names
 * @return
 */
std::string Model::getCurrentDate()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer [80];

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

	strftime (buffer, 80 ,"%Y-%m-%d %I.%M.%S", timeinfo);

	return (buffer);
}

/**
 * Returns the complete filename for a Image
 * @return
 */
std::string Model::getImageName()
{
    std::string imgName;
    imgName += IMG_NAME;
    imgName += " ";
    imgName += getCurrentDate();
    imgName += IMG_EXT;

    return imgName;
}
/**
 * Returns the Icon Path of the Middle Button defined in Model.h
 * @return
 */
std::string Model::getIconURL()
{
	return ICON_URL;
}

/**
 * Return the Button Label of the selected Button. Defined in Model.h
 * One = Left Button, Two = Right Button
 * @param  btnNr the ID of the Button which label should be returned
 * @return
 */
std::string Model::getButtonLabel(int btnNr)
{
	if (btnNr == 1)
	{
		return btnLabelL_;
	}
	else if (btnNr == 2)
	{
		return btnLabelR_;
	}
	else
	{
		return "";
	}
}

std::string Model::getButtonName(int btnNr)
{
	if (btnNr == 1)
	{
		return btnNameL_;
	}
	else if (btnNr == 2)
	{
		return btnNameR_;
	}
	else if (btnNr == 3)
	{
		return btnNameM_;
	}
	else
	{
		return "";
	}
}

/**
 * Returns the VideoGrabber used in this Model
 * @return
 */
ofVideoGrabber * Model::getVideoGrabber()
{
	return vidGrabber_;
}

/**
 * Returns the Texture used to save the current Webcam frame to a File
 * @return
 */
ofTexture * Model::getTexture()
{
	return texture_;
}

ofTexture Model::getThumbnail(int index)
{
	return thumbArr_[index].getTextureReference();
}

/**
 * Returns the Array of Thumbnails
 * @return
 */
ofImage * Model::getThumbnails()
{
	return thumbArr_;
}

bool Model::selectImage(int x, int y)
{
	bool isSelectable = false;

	if (y >= 564 && y <= 664)
	{
		if (x >= 520 && x <= 620 && imgCnt_ > 4)
		{
			imgSelector_ = 5;
			isSelectable = true;
		}
	
		if (x >= 395 && x <= 495 && imgCnt_ > 3)
		{
			imgSelector_ = 4;
			isSelectable = true;
		}
		if (x >= 270 && x <= 370 && imgCnt_ > 2)
		{
			imgSelector_ = 3;
			isSelectable = true;
		}

		if (x >= 145 && x <= 245 && imgCnt_ > 1)
		{
			imgSelector_ = 2;
			isSelectable = true;
		}
		if (x >= 20 && x <= 120 && imgCnt_ > 0)
		{
			imgSelector_ = 1;
			isSelectable = true;
		}
	}

	return isSelectable;
}
