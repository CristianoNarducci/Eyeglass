#include "OriginalViewTab.h"

OriginalViewTab::OriginalViewTab(wxWindow* parent): ViewTab(parent) {
	wxBitmap* bmp1 = new wxBitmap(DisplayUtils::generateBlankImage(1, 1));
	wxBitmap* bmp2= new wxBitmap(DisplayUtils::generateBlankImage(1, 1));
	
	staticBitmap1 = new wxGenericStaticBitmap(this, wxID_ANY, *bmp1, wxPoint(0, 0));
	staticBitmap2 = new wxGenericStaticBitmap(this, wxID_ANY, *bmp2, wxPoint(1, 0));
}

void OriginalViewTab::update(const std::list<std::shared_ptr<const PixelDiff>>& diffContainer,
													wxString path1, const std::shared_ptr<const wxImage> image1, 
													wxString path2, const std::shared_ptr<const wxImage> image2) {
	if (markedForUpdate) {
		wxSize size = this->GetClientSize();
		
		int containerWidth;
		int containerHeight;
		wxPoint bitmap1Point;
		wxPoint bitmap2Point;
		
		if (size.GetWidth() > size.GetHeight()) {
			containerWidth = size.GetWidth() / 2;
			containerHeight = size.GetHeight();
			
			bitmap1Point.x = 0;
			bitmap1Point.y = 0;
			bitmap2Point.x = containerWidth;
			bitmap2Point.y = 0;
		} else {
			containerWidth = size.GetWidth();
			containerHeight = size.GetHeight() / 2;
			
			bitmap1Point.x = 0;
			bitmap1Point.y = 0;
			bitmap2Point.x = 0;
			bitmap2Point.y = containerHeight;
		}
		
		if (image1) {
			wxImage img = *image1;
			DisplayUtils::proportionallyRescaleImage(img, containerWidth, containerHeight);
			wxBitmap* bmp = new wxBitmap(img);
			staticBitmap1->SetBitmap(*bmp);
		} else {
			wxBitmap* bmp = new wxBitmap(DisplayUtils::generateBlankImage(1, 1));
			staticBitmap1->SetBitmap(*bmp);
			staticBitmap1->SetPosition(bitmap1Point);
		}
		
		if (image2) {
			wxImage img = *image2;
			DisplayUtils::proportionallyRescaleImage(img, containerWidth, containerHeight);
			wxBitmap* bmp = new wxBitmap(img);
			staticBitmap2->SetBitmap(*bmp);
			staticBitmap2->SetPosition(bitmap2Point);
		} else {
			wxBitmap* bmp = new wxBitmap(DisplayUtils::generateBlankImage(1, 1));
			staticBitmap2->SetBitmap(*bmp);
		}
		
		markedForUpdate = false;
	}
}
