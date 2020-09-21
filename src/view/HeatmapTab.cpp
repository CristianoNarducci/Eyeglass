#include "HeatmapTab.h"

wxBEGIN_EVENT_TABLE(HeatmapTab, wxWindow)
	EVT_SIZE(HeatmapTab::onTabResize)
wxEND_EVENT_TABLE()

HeatmapTab::HeatmapTab(wxWindow* parent): ViewTab(parent) {
	image = DisplayUtils::generateBlankImage(1, 1);
	
	wxBitmap* bmp = new wxBitmap(image);
	staticBitmap = new wxGenericStaticBitmap(this, wxID_ANY, *bmp, wxPoint(0, 0));
	delete bmp;
}

void HeatmapTab::update(const std::list<std::shared_ptr<const PixelDiff>>& diffContainer, 
					std::shared_ptr<const wxImage> image1, std::shared_ptr<const wxImage> image2) {
	if (markedForUpdate) {
		if (image1) {
			image = *image1;
			generateHeatmap(diffContainer);
		} else {
			image = DisplayUtils::generateBlankImage(1, 1);
		}
		
		repaintTab();
		markedForUpdate = false;
	}
}

void HeatmapTab::repaintTab() {
	wxSize tabSize = this->GetClientSize();
	
	wxImage tempImage = image;
	
	wxPoint imagePos;
	wxSize imageNewSize;
	
	// Recalculate the size of the image.
	imageNewSize = DisplayUtils::getLargestProportionalSize(image.GetWidth(), image.GetHeight(),
															tabSize.GetWidth(), tabSize.GetHeight());
	
	// If there's space around the resized image, center the image.
	imagePos.x = (tabSize.GetWidth() - imageNewSize.GetWidth()) / 2;
	imagePos.y = (tabSize.GetHeight() - imageNewSize.GetHeight()) / 2;
	
	tempImage.Rescale(imageNewSize.GetWidth(), imageNewSize.GetHeight());
	wxBitmap* bmp = new wxBitmap(tempImage);
	staticBitmap->SetBitmap(*bmp);
	staticBitmap->SetPosition(imagePos);
	delete bmp;
}

void HeatmapTab::generateHeatmap(const std::list<std::shared_ptr<const PixelDiff>>& diffContainer) {
	image = image.ConvertToGreyscale().ConvertToDisabled(128);
	
	for (auto it = diffContainer.begin(); it != diffContainer.end(); it++) {
		// 0% difference = green, 50% difference = yellow, 100% difference = red.
		wxImage::HSVValue color(0.33 - (*it)->percentual_diff * 0.33, 1.0, 1.0);
		wxImage::RGBValue rgbColor = wxImage::HSVtoRGB(color);
		
		wxImage::RGBValue sourceColor;
		sourceColor.red = image.GetRed((*it)->x, (*it)->y);
		sourceColor.green = image.GetGreen((*it)->x, (*it)->y);
		sourceColor.blue = image.GetBlue((*it)->x, (*it)->y);
		
		// 0% difference = source color, 100% difference = heatmap color
		rgbColor = DisplayUtils::mixColors(sourceColor, rgbColor, (*it)->percentual_diff);
		
		image.SetRGB((*it)->x, (*it)->y, rgbColor.red, rgbColor.green, rgbColor.blue);
	}
}

void HeatmapTab::onTabResize(wxSizeEvent& event) {
	repaintTab();
}
