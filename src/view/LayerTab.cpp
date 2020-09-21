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
	
	// If there's space around the resized image, center the images.
	image1Pos.x += (tabSize.GetWidth() - image1NewSize.GetWidth()) / 2;
	image1Pos.y += (tabSize.GetHeight() - image1NewSize.GetHeight()) / 2 - sliderHeight / 2;
	image2Pos.x += (tabSize.GetWidth() - image2NewSize.GetWidth()) / 2;
	image2Pos.y += (tabSize.GetHeight() - image2NewSize.GetHeight()) / 2 - sliderHeight / 2;
	
	// Calculate the offset to maintain position after the cut, along with the new sizes.
	double image1CutPercent = 1.0 - slider->GetValue() / 1000.0;
	double image2CutPercent = slider->GetValue() / 1000.0;
	
	int image1CutLength = image1NewSize.GetWidth() * image1CutPercent;
	int image2CutLength = image2NewSize.GetWidth() * image2CutPercent;
	
	image2Pos.x += image2CutLength;
	
	if (image1NewSize.GetWidth() - image1CutLength > 0) {
		tempImage1.Rescale(image1NewSize.GetWidth(), image1NewSize.GetHeight());
		tempImage1 = tempImage1.GetSubImage(wxRect(0, 0, image1NewSize.GetWidth() - image1CutLength, image1NewSize.GetHeight()));
	} else {
		tempImage1 = DisplayUtils::generateBlankImage(1, 1);
	}
	wxBitmap* bmp1 = new wxBitmap(tempImage1);
	staticBitmap1->SetBitmap(*bmp1);
	staticBitmap1->SetPosition(image1Pos);
	
	if (image2NewSize.GetWidth() - image2CutLength > 0) {
		tempImage2.Rescale(image2NewSize.GetWidth(), image2NewSize.GetHeight());
		tempImage2 = tempImage2.GetSubImage(wxRect(image2CutLength, 0, image2NewSize.GetWidth() - image2CutLength, image2NewSize.GetHeight()));
	} else {
		tempImage2 = DisplayUtils::generateBlankImage(1, 1);
	}
	wxBitmap* bmp2 = new wxBitmap(tempImage2);
	staticBitmap2->SetBitmap(*bmp2);
	staticBitmap2->SetPosition(image2Pos);
	
	// Resize and move the slider to the bottom of the tab, centered horizontally.
	int sliderWidth = image1NewSize.GetWidth() > image2NewSize.GetWidth() ? image1NewSize.GetWidth() : image2NewSize.GetWidth();
	int sliderX = (tabSize.GetWidth() - sliderWidth) / 2;
	int sliderY = tabSize.GetHeight() - sliderHeight;
	
	slider->SetSize(sliderX, sliderY, sliderWidth, sliderHeight);
}

void LayerTab::onSliderUpdate(wxCommandEvent& event) {
	repaintTab();
}


void LayerTab::onTabResize(wxSizeEvent& event) {
	repaintTab();
}
