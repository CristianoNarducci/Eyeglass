#include "OriginalViewTab.h"

OriginalViewTab::OriginalViewTab(wxWindow* parent): ViewTab(parent) {
	wxFlexGridSizer* panelSizer = new wxFlexGridSizer(1,2,0,0);
	panelSizer->AddGrowableCol(0,16);
	panelSizer->AddGrowableCol(1,16);
	panelSizer->AddGrowableRow(0,16);
	
	wxBitmap* bmp1 = new wxBitmap(DisplayUtils::generateBlankImage(600, 600));
	wxBitmap* bmp2= new wxBitmap(DisplayUtils::generateBlankImage(600, 600));
	
	staticBitmap1 = new wxGenericStaticBitmap(this, wxID_ANY, *bmp1);
	staticBitmap2 = new wxGenericStaticBitmap(this, wxID_ANY, *bmp2);
	panelSizer->Add(staticBitmap1, 0);
	panelSizer->Add(staticBitmap2, 0);

	this->SetSizer(panelSizer);
}

void OriginalViewTab::update(const std::list<std::shared_ptr<const PixelDiff>>& diffContainer,
													wxString path1, const std::shared_ptr<const wxImage> image1, 
													wxString path2, const std::shared_ptr<const wxImage> image2) {
	if (markedForUpdate) {
		if (image1) {
			wxImage img = *image1;
			DisplayUtils::proportionallyRescaleImage(img, 600, 600, wxIMAGE_QUALITY_BICUBIC);
			wxBitmap* bmp = new wxBitmap(img);
			staticBitmap1->SetBitmap(*bmp);
		}else {
			wxBitmap* bmp = new wxBitmap(DisplayUtils::generateBlankImage(600, 600));
			staticBitmap1->SetBitmap(*bmp);
		}
		if(image2) {
			wxImage img = *image2;
			DisplayUtils::proportionallyRescaleImage(img, 600, 600, wxIMAGE_QUALITY_BICUBIC);
			wxBitmap* bmp = new wxBitmap(img);
			staticBitmap2->SetBitmap(*bmp);
		} else {
			wxBitmap* bmp = new wxBitmap(DisplayUtils::generateBlankImage(600, 600));
			staticBitmap2->SetBitmap(*bmp);
		}
		
		markedForUpdate = false;
	}
}
