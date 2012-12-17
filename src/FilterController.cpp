#include "FilterController.h"

FilterController::FilterController(Controller * oldController, int offset) :
	Controller(oldController), filterOffset_(offset)
{
	std::cout << "FILTER CONTROLLER CREATED WITH OFFSET " << filterOffset_ << std::endl;
	
	model_ = new FilterModel(oldController->getModel(), filterOffset_);
	view_ = new FilterView(oldController->getView(), model_->getIconURL(), 
		model_->getCamWidth(), model_->getCamHeight(), filterOffset_);

	view_->setButtonLabel(1, model_->getButtonLabel(1));
	view_->setButtonLabel(2, model_->getButtonLabel(2));

	// view_->clearButtonStatus(1);
	// view_->clearButtonStatus(2);
	// view_->clearButtonStatus(3);

	initName();

	myTexture.allocate(640, 480, GL_RGB);

	delete oldController;
}

FilterController::~FilterController()
{
	// delete model_;
	// delete view_;
}

void FilterController::update()
{
	model_->update();
}

void FilterController::mousePressed(int x, int y, int button)
{
	static_cast<FilterModel*>(model_)->selectFilter(x, y);
	// std::cout << model_->getFilterSelector() << std::endl;
	// Controller::mousePressed(x, y, button);
}

void FilterController::draw()
{
	int filtersLeft = std::min(FILTER_PAGE_LENGTH, static_cast<FilterModel*>(model_)->getFilterCount() - filterOffset_);
	
	view_->drawVideoGrabber(model_->getVideoGrabber(),
		model_->getCamWidth(), model_->getCamHeight(), model_->getCamWidth(), model_->getCamHeight());
	static_cast<FilterView*>(view_)->drawFilter(
		static_cast<FilterModel*>(model_)->getTextureArray(),
		static_cast<FilterModel*>(model_)->getFilterNames(),
		filtersLeft);
	view_->drawThumbnails(model_->getThumbnails(),
		model_->getImgIndex(), model_->getImgCount());
	view_->drawThumbnailSelector(model_->updateThumbnailSelector(0));
	static_cast<FilterView*>(view_)->drawFilterSelector(
		model_->getFilterSelector());
}

void FilterController::guiEvent(ofxUIEventArgs & newEvent)
{
	string buttonName = newEvent.widget->getName();
	ofxUIButton * button = (ofxUIButton *) newEvent.widget;
	
	if (buttonName == "Load Filter")
	{
		if (button->getValue() == 1){
			static_cast<FilterModel*>(model_)->loadFilterFromFileUI();
		}
	}
}

void FilterController::keyPressed(int key)
{
	if (key == 'a')
	{

	}

	Controller::keyPressed(key);
}

int FilterController::getFilterOffset(){
	return filterOffset_;
}

void FilterController::setFilterOffset(int offset){
	filterOffset_ = offset;
}