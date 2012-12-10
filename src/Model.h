#ifndef __myOpenPhotoBooth__Model__
#define __myOpenPhotoBooth__Model__ 

#include "ofMain.h"

#include <string>

//----------------------------------
#define CAM_WIDTH 640
#define CAM_HEIGHT 480
//----------------------------------
#define THUMBNAIL_CNT 5
#define THUMBNAIL_RATIO 100
//----------------------------------
#define IMG_NAME "myPhoto"
#define IMG_EXT ".jpg"
//----------------------------------
#define ICON_URL "./GUI/Images/Icon.png"
#define BTN_LABL_L "Facebook"
#define BTN_LABL_M "CNTRL"
#define BTN_LABL_R "Effects"
#define BTN_NAME_L "MAINRIGHT"
#define BTN_NAME_M "MAINMIDDLE"
#define BTN_NAME_R "MAINRIGHT"
//----------------------------------

class Model
{
protected:
	int imgCnt_, imgIndex_, imgSelector_, thmbCnt_;
	
	unsigned char * pixelArr_;
	std::string btnLabelL_, btnLabelR_, btnLabelM_, 
		btnNameL_, btnNameM_, btnNameR_;

	ofVideoGrabber * vidGrabber_;
	ofTexture * texture_;
	ofImage * thumbArr_;

	
	virtual void saveTextureToFile(std::string);
	virtual void saveToThumbnail(std::string);
	virtual void resizeToThumbnail(ofImage, float);
public:
	Model();
	Model(Model *, bool = false);
	void init();
	void init(int , int, int);
	// ~Model();

	virtual void saveImage();
	virtual void savePixelsToFile(ofPixels, std::string);

	virtual void update();

	virtual void updateImgCount();
	virtual int updateThumbnailSelector(int);

	virtual int getThumbnailSelector();
	virtual int getImgCount();
	virtual int getImgIndex();
	virtual int getThumbnailCount();
	virtual float getCamWidth();
	virtual float getCamHeight();
    virtual std::string getCurrentDate();
    virtual std::string getImageName();
    virtual std::string getIconURL();
    virtual std::string getButtonLabel(int);
    virtual std::string getButtonName(int);
    virtual ofVideoGrabber * getVideoGrabber();
    virtual ofTexture * getTexture();
    virtual ofTexture getThumbnail(int);
    virtual ofImage * getThumbnails();
    virtual bool selectImage(int, int);
};

#endif
