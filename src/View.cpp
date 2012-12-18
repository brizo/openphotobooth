/*************************************************
 File: View.cpp
 By: Andy Graulund and Marcel Koglin
 Date: 2012-12-17
 
 Compile: Compiled using OpenFrameworks in Xcode environment, with ofxOpenCV, ofxUI and cURL
 System: Runs on any system supporting OpenFrameworks (the compiled version on a Mac)
 
 Description: Follows the MVC/Mediator Pattern. It does hold all the 
 Style Elements for the Scene. Gets the Data injected form the 
 Controller. Unlikely other MVCs it holds the Buttons it self. This is
 due a characteristic from ofxUI
 *************************************************/

#include "View.h"
#include "Controller.h"

View::View(std::string iconURL, int width, int height, ofxUICanvas * canvas)
{
	init(iconURL, width, height, canvas);
}

/**
 * Copy constructor, called when View switched back from another one
 */
View::View(View * oldView, std::string iconURL, int width, int height)
{
	buttonLeft_ = oldView->buttonLeft_;
	buttonRight_ = oldView->buttonRight_;
	buttonCenter_ = oldView->buttonCenter_;
	actButtonCenter_ = oldView->actButtonCenter_;
	buttonDrop_ = oldView->buttonDrop_;
	editorDrop_ = oldView->editorDrop_;

	buttonLeft_->setVisible(true);
	buttonLeft_->setValue(0);
	buttonCenter_->setVisible(true);
	buttonDrop_->setVisible(false);
	editorDrop_->setVisible(false);
	actButtonCenter_->setVisible(false);
	actButtonCenter_->setValue(0);
	buttonRight_->setValue(0);

	// init(iconURL, width, height, false);
}

/**
 * Initial Method. Called when the Application starts
 * @param iconURL Image for the Middle Button
 * @param width   width of the Camera/Scene/Window
 * @param height  Height of the Camera/Scene/Window
 * @param canvas  Canvas element from ofxUICanvas, to draw buttons on it
 */
void View::init(std::string iconURL, int width, int height, ofxUICanvas * canvas)
{
	buttonLeft_      = new ofxUILabelToggle(
		                 "BUTTON_LEFT", false, 100, 32, 8, 8, OFX_UI_FONT_MEDIUM);
	buttonCenter_    = new ofxUIImageButton(
		                 304, 8, 32, 32, false, iconURL, "BUTTON_CENT");
	actButtonCenter_ = new ofxUILabelButton("BUTTON_ACTCENT", false, 100, 32, 270, 8, OFX_UI_FONT_MEDIUM);
	buttonRight_     = new ofxUILabelToggle(
		                 "BUTTON_RIGHT", false, 100, 32, 532, 8, OFX_UI_FONT_MEDIUM);
    
    buttonItems_.push_back("Facebook");
    buttonItems_.push_back("Save");
    buttonDrop_ = new ofxUIDropDownList("Publish", buttonItems_, 100, 8, 9);
	
	// Filter editor drop down
	editorItems_.push_back("Create Filter");
	editorItems_.push_back("Load Filter");
	editorDrop_ = new ofxUIDropDownList("Editor", editorItems_, 120, 8, 9);
	
	canvas->addWidget(buttonLeft_);
	canvas->addWidget(buttonCenter_);
	canvas->addWidget(actButtonCenter_);
	canvas->addWidget(buttonRight_);
	canvas->addWidget(buttonDrop_);
	canvas->addWidget(editorDrop_);

	buttonDrop_->setVisible(false);
	buttonDrop_->setName("PREVBTN_L_D");
	
	editorDrop_->setVisible(false);
	editorDrop_->setName("EDITORDROP");
	
	actButtonCenter_->setVisible(false);
}

/**
 * Draws a given Video Grabber
 * @param vidGrabber Video Grabber which should be drawn to this View
 */
void View::drawVideoGrabber(ofVideoGrabber * vidGrabber, 
	float w, float h)
{
	View::drawVideoGrabber(vidGrabber, w, h, 0, 0);
}

/**
 * Draw the video grabber
 * @param vidGrabber VideoGrabber Object
 * @param w          width of the videograbber
 * @param h          height of the videograbber
 * @param x          x position on the scene
 * @param y          y position on the scene
 */
void View::drawVideoGrabber(ofVideoGrabber * vidGrabber,
							float w, float h, float x, float y)
{
	vidGrabber->draw(x, y, w, h);
}

/**
 * Draws a given Thumbnail array
 * @param thumbArr array of Thumbnail
 * @param imgIndx  current maximal image Index
 * @param imgCnt   current maximal image Count
 */
void View::drawThumbnails(ofImage * thumbArr, int imgIndx, int imgCnt)
{
	if (imgCnt > 0)
	{
		ofPushStyle();
		ofSetRectMode(OF_RECTMODE_CENTER);
		for (int i = 0; i < imgCnt; i++)
		{
			thumbArr[i].draw(70 + (125 * i), 614, 100, 100);
		}
		ofPopStyle();
	}
}

/**
 * Draw the Thumbnail Selector dependent of the given Int. If there is
 * less then two Thumbnails, no Selector will drawn.
 * @param imgNbr number of selected Thumbnail
 */
void View::drawThumbnailSelector(int imgNbr)
{
	if (imgNbr > 0)
	{
		ofPushStyle();
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofSetHexColor(0x00B2B2);
		ofNoFill();
		ofRect(70 + (125 * (imgNbr-1)), 614, 100, 100);
		ofPopStyle();
	}
}

/**
 * Set the Label of the Button. Select the button via a given Int.
 * @param btnNbr number of Button. One = Left, Two = Right
 * @param btnLbl label of the Button.
 */
void View::setButtonLabel(int btnNbr, std::string btnLbl)
{
	if (btnNbr == 1)
	{
		buttonLeft_->setLabelText(btnLbl);
	}
	else if (btnNbr == 2)
	{
		buttonRight_->setLabelText(btnLbl);
	}
	else if (btnNbr == 4)
	{
		actButtonCenter_->setLabelText(btnLbl);
	}
}

/**
 * Set the button at index to status to zero. We use this since we have
 * some Toggle Buttons in the Application which dont clear the status
 * when we change the scene, that would have the effect that the buttons
 * are still highlighted.
 * @param btnNbr Index of the Button which should be cleared
 */
void View::clearButtonStatus(int btnNbr)
{
	if (btnNbr == 1)
	{
		buttonLeft_->setValue(0);
	}
	else if (btnNbr == 2)
	{
		buttonRight_->setValue(0);
	}
	else if (btnNbr == 3)
	{
		buttonCenter_->setValue(0);
	}
	else if (btnNbr == 4)
	{
		actButtonCenter_->setValue(0);
	}
}

/**
 * Set the Name (Not LABEL!) of a Button selected by Index
 * @param btnNbr  Button Index
 * @param btnName New Name of the Button
 */
void View::setButtonName(int btnNbr, std::string btnName)
{
	if (btnNbr == 1)
	{
		buttonLeft_->setName(btnName);
	}
	else if (btnNbr == 2)
	{
		buttonRight_->setName(btnName);
	}
	else if (btnNbr == 3)
	{
		buttonCenter_->setName(btnName);
	}
	else if (btnNbr == 4)
	{
		actButtonCenter_->setName(btnName);
	}
}

/**
 * Draws the Filter to the Main Scene
 * @param texture Teture which should be drawn. Must be updated by 
 * another method (mostly update method in a Model)
 */
void View::drawFilter(ofTexture texture)
{
	texture.draw(0, 0, 640, 480);
}
