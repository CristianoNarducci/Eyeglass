#include "LayerTab.h"

// Enum used for component identification in event table.
enum {
	CUT_SLIDER
};

wxBEGIN_EVENT_TABLE(LayerTab, wxWindow)
	EVT_SIZE(LayerTab::onTabResize)
	
	EVT_SLIDER(CUT_SLIDER, LayerTab::onSliderUpdate)
wxEND_EVENT_TABLE()

LayerTab::LayerTab(wxWindow* parent): ViewTab(parent) {
	image1 = DisplayUtils::generateBlankImage(1, 1);
	image2 = DisplayUtils::generateBlankImage(1, 1);
	
	wxBitmap* bmp1 = new wxBitmap(image1);
	wxBitmap* bmp2 = new wxBitmap(image2);
	
	staticBitmap1 = new wxGenericStaticBitmap(this, wxID_ANY, *bmp1, wxPoint(0, 0));
	staticBitmap2 = new wxGenericStaticBitmap(this, wxID_ANY, *bmp2, wxPoint(1, 0));
	
	// The order here is important, otherwise the slider would be covered by other UI elements.
	slider = new wxSlider(this, CUT_SLIDER, 1000, 0, 1000);
}

void LayerTab::update(const std::list<std::shared_ptr<const PixelDiff>>& diffContainer,
													wxString path1, std::shared_ptr<const wxImage> image1, 
													wxString path2, std::shared_ptr<const wxImage> image2) {
	if (markedForUpdate) {
		if (image1) {
			this->image1 = *image1;
		} else {
			this->image1 = DisplayUtils::generateBlankImage(1, 1);
		}
		
		if (image2) {
			this->image2 = *image2;
		} else {
			this->image2 = DisplayUtils::generateBlankImage(1, 1);
		}
		
		repaintTab();
		markedForUpdate = false;
	}
}

void LayerTab::repaintTab() {
	wxSize tabSize = this->GetClientSize();
	
	wxImage tempImage1 = image1;
	wxImage tempImage2 = image2;
	
	wxPoint image1Pos;
	wxPoint image2Pos;
	wxSize image1NewSize;
	wxSize image2NewSize;
	
	int sliderHeight = 40;
	
	// Recalculate the size of the images and the new page layout.
	image1NewSize = DisplayUtils::getLargestProportionalSize(image1.GetWidth(), image1.GetHeight(),
																tabSize.GetWidth(), tabSize.GetHeight() - sliderHeight);
	image2NewSize = DisplayUtils::getLargestProportionalSize(image2.GetWidth(), image2.GetHeight(),
																tabSize.GetWidth(), tabSize.GetHeight() - sliderHeight);
	
	// Prefer the image with the smaller width.
	int smallerWidth;
	if (image1NewSize.GetWidth() < image2NewSize.GetWidth()) {
		smallerWidth = image1NewSize.GetWidth();
	} else {
		smallerWidth = image2NewSize.GetWidth();
	}
	
	tempImage1.Rescale(image1NewSize.GetWidth(), image1NewSize.GetHeight());
	tempImage2.Rescale(image2NewSize.GetWidth(), image2NewSize.GetHeight());
	
	// If an image is wider than the other after the rescale, cut a portion from its center,
	// the size of the smaller image.
	if (image1NewSize.GetWidth() > image2NewSize.GetWidth()) {
		tempImage1 = tempImage1.GetSubImage(wxRect(image1NewSize.GetWidth() / 2 - smallerWidth / 2, 0,
															smallerWidth, image1NewSize.GetHeight()));
		image1NewSize.SetWidth(smallerWidth);
	} else {
		tempImage2 = tempImage2.GetSubImage(wxRect(image2NewSize.GetWidth() / 2 - smallerWidth / 2, 0,
															smallerWidth, image2NewSize.GetHeight()));
		image2NewSize.SetWidth(smallerWidth);
	}
	
	// If there's space around the resized image, center the images.
	image1Pos.x += (tabSize.GetWidth() - smallerWidth) / 2;
	image1Pos.y += (tabSize.GetHeight() - image1NewSize.GetHeight()) / 2 - sliderHeight / 2;
	image2Pos.x += (tabSize.GetWidth() - smallerWidth) / 2;
	image2Pos.y += (tabSize.GetHeight() - image2NewSize.GetHeight()) / 2 - sliderHeight / 2;
	
	// If the images are still visible, cut away the non-visible part.
	// When one image becomes fully hidden, display an invisible pixel instead.
	int image1CutLength = (1.0 - slider->GetValue() / 1000.0) * smallerWidth;
	int image2CutLength = smallerWidth - image1CutLength;
	
	if (image1NewSize.GetWidth() - image1CutLength > 0) {
		tempImage1 = tempImage1.GetSubImage(wxRect(0, 0, image1NewSize.GetWidth() - image1CutLength, image1NewSize.GetHeight()));
	} else {
		tempImage1 = DisplayUtils::generateBlankImage(1, 1);
	}
	wxBitmap* bmp1 = new wxBitmap(tempImage1);
	staticBitmap1->SetBitmap(*bmp1);
	staticBitmap1->SetPosition(image1Pos);
	
	if (image2NewSize.GetWidth() - image2CutLength > 0) {
		tempImage2 = tempImage2.GetSubImage(wxRect(image2CutLength, 0, image2NewSize.GetWidth() - image2CutLength, image2NewSize.GetHeight()));
		image2Pos.x += image2CutLength;
	} else {
		tempImage2 = DisplayUtils::generateBlankImage(1, 1);
	}
	wxBitmap* bmp2 = new wxBitmap(tempImage2);
	staticBitmap2->SetBitmap(*bmp2);
	staticBitmap2->SetPosition(image2Pos);
	
	// Resize and move the slider to the bottom of the tab, centered horizontally.
	int sliderWidth = smallerWidth;
	int sliderX = image1Pos.x;
	int sliderY = tabSize.GetHeight() - sliderHeight;
	
	slider->SetSize(sliderX, sliderY, sliderWidth, sliderHeight);
}

void LayerTab::onSliderUpdate(wxCommandEvent& event) {
	repaintTab();
}


void LayerTab::onTabResize(wxSizeEvent& event) {
	repaintTab();
}
