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

void OriginalViewTab::update(const std::list<PixelDiff*>& diffContainer, wxString path1, const wxImage* image1, 
																		wxString path2, const wxImage* image2) {
	if (markedForUpdate) {
		std::cout << std::string(path1.mb_str()) << std::endl;
		std::cout << std::string(path2.mb_str()) << std::endl;
		
		if (image1 != nullptr) {
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
