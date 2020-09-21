#include "OriginalViewTab.h"

wxBEGIN_EVENT_TABLE(OriginalViewTab, wxWindow)
	EVT_SIZE(OriginalViewTab::onTabResize)
wxEND_EVENT_TABLE()

OriginalViewTab::OriginalViewTab(wxWindow* parent): ViewTab(parent) {
	blankImage = std::make_shared<wxImage>(DisplayUtils::generateBlankImage(1, 1));
	
	image1 = blankImage;
	image2 = blankImage;
	
	std::shared_ptr<wxBitmap> bmp1 = std::make_shared<wxBitmap>(*image1);
	std::shared_ptr<wxBitmap> bmp2 = std::make_shared<wxBitmap>(*image2);
	
	staticBitmap1 = new wxGenericStaticBitmap(this, wxID_ANY, *bmp1, wxPoint(0, 0));
	staticBitmap2 = new wxGenericStaticBitmap(this, wxID_ANY, *bmp2, wxPoint(1, 0));
}

void OriginalViewTab::update(const std::list<std::shared_ptr<const PixelDiff>>& diffContainer, 
						std::shared_ptr<const wxImage> image1, std::shared_ptr<const wxImage> image2){
	if (markedForUpdate) {
		if (image1) {
			this->image1 = image1;
		} else {
			this->image1 = blankImage;
		}
		
		if (image2) {
			this->image2 = image2;
		} else {
			this->image2 = blankImage;
		}
		
		repaintTab();
		markedForUpdate = false;
	}
}

void OriginalViewTab::repaintTab() {
	wxSize tabSize = this->GetClientSize();
	
	int imageContainerWidth;
	int imageContainerHeight;
	
	wxImage tempImage1 = *image1;
	wxImage tempImage2 = *image2;
	
	wxPoint image1Pos;
	wxPoint image2Pos;
	wxSize image1NewSize;
	wxSize image2NewSize;
	
	// Count how many non-blank images are there, so that if there's only an image, it is shown fullscreen.
	int nonBlankCount;
	if (!image1->IsSameAs(*blankImage) && !image2->IsSameAs(*blankImage)) {
		nonBlankCount = 2;
	} else {
		nonBlankCount = 1;
	}
	
	// Recalculate the size of the images and the new page layout.
	if (tabSize.GetWidth() > tabSize.GetHeight()) {
		imageContainerWidth = tabSize.GetWidth() / nonBlankCount;
		imageContainerHeight = tabSize.GetHeight();
		
		image1NewSize = DisplayUtils::getLargestProportionalSize(image1->GetWidth(), image1->GetHeight(),
																imageContainerWidth, imageContainerHeight);
		image2NewSize = DisplayUtils::getLargestProportionalSize(image2->GetWidth(), image2->GetHeight(),
																imageContainerWidth, imageContainerHeight);
		
		image2Pos.x = imageContainerWidth;
	} else {
		imageContainerWidth = tabSize.GetWidth();
		imageContainerHeight = tabSize.GetHeight() / nonBlankCount;
		
		image1NewSize = DisplayUtils::getLargestProportionalSize(image1->GetWidth(), image1->GetHeight(),
																imageContainerWidth, imageContainerHeight);
		image2NewSize = DisplayUtils::getLargestProportionalSize(image2->GetWidth(), image2->GetHeight(),
																imageContainerWidth, imageContainerHeight);
		
		image2Pos.y = imageContainerHeight;
	}
	
	// If there's space around the resized image, center the images.
	image1Pos.x += (imageContainerWidth - image1NewSize.GetWidth()) / 2;
	image1Pos.y += (imageContainerHeight - image1NewSize.GetHeight()) / 2;
	image2Pos.x += (imageContainerWidth - image2NewSize.GetWidth()) / 2;
	image2Pos.y += (imageContainerHeight - image2NewSize.GetHeight()) / 2;
	
	tempImage1.Rescale(image1NewSize.GetWidth(), image1NewSize.GetHeight());
	std::shared_ptr<wxBitmap> bmp1 = std::make_shared<wxBitmap>(tempImage1);
	staticBitmap1->SetBitmap(*bmp1);
	staticBitmap1->SetPosition(image1Pos);
	
	tempImage2.Rescale(image2NewSize.GetWidth(), image2NewSize.GetHeight());
	std::shared_ptr<wxBitmap> bmp2 = std::make_shared<wxBitmap>(tempImage2);
	staticBitmap2->SetBitmap(*bmp2);
	staticBitmap2->SetPosition(image2Pos);
}

void OriginalViewTab::onTabResize(wxSizeEvent& event) {
	repaintTab();
}
