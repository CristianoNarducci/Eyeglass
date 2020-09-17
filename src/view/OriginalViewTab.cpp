#include "OriginalViewTab.h"

OriginalViewTab::OriginalViewTab(wxWindow* parent): ViewTab(parent) {
	wxImage img1(600, 600);
	img1.SetRGB(wxRect(0, 0, 600, 600), 255, 0, 0);
	wxBitmap* bmp1 = new wxBitmap(img1);
	
	wxFlexGridSizer* panelSizer = new wxFlexGridSizer(1);
	this->SetSizer(panelSizer);
	
	staticBitmap1 = new wxGenericStaticBitmap(this, wxID_ANY, *bmp1);
	panelSizer->Add(staticBitmap1, 0);
}

void OriginalViewTab::update(const std::list<std::shared_ptr<PixelDiff>>& diffContainer,
													wxString path1, const std::shared_ptr<wxImage> image1, 
													wxString path2, const std::shared_ptr<wxImage> image2) {
	if (markedForUpdate) {
		if (image1) {
			wxBitmap* bmp = new wxBitmap(*image1);
			staticBitmap1->SetBitmap(*bmp);
		} else {
			wxImage img1(600, 600);
			img1.SetRGB(wxRect(0, 0, 600, 600), 255, 0, 0);
			wxBitmap* bmp = new wxBitmap(img1);
			staticBitmap1->SetBitmap(*bmp);
		}
		
		markedForUpdate = false;
	}
}
