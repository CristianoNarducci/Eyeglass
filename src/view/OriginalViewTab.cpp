#include "OriginalViewTab.h"

OriginalViewTab::OriginalViewTab(wxWindow* parent): ViewTab(parent) {
	wxFlexGridSizer* panelSizer = new wxFlexGridSizer(1,2,0,0);
	panelSizer->AddGrowableCol(0,16);
	panelSizer->AddGrowableCol(1,16);
	panelSizer->AddGrowableRow(0,16);
	wxImage img1(600, 600);
	img1.SetRGB(wxRect(0, 0, 600, 600), 255, 0, 0);
	wxBitmap* bmp1 = new wxBitmap(img1);
	wxImage img2(600,600);
	img2.SetRGB(wxRect(0,0,600,600),0,255,0);
	wxBitmap* bmp2= new wxBitmap(img2);
	staticBitmap1 = new wxGenericStaticBitmap(this, wxID_ANY, *bmp1);
	staticBitmap2 = new wxGenericStaticBitmap(this,wxID_ANY,*bmp2);
	panelSizer->Add(staticBitmap1, 0,wxRIGHT,5);
	panelSizer->Add(staticBitmap2,0);

	this->SetSizer(panelSizer);
}

void OriginalViewTab::update(const std::list<std::shared_ptr<PixelDiff>>& diffContainer,
													wxString path1, const std::shared_ptr<wxImage> image1, 
													wxString path2, const std::shared_ptr<wxImage> image2) {
	if (markedForUpdate) {
		if (image1) {
			wxImage img = *image1;
			img.Rescale(500,500,wxIMAGE_QUALITY_BICUBIC);
			wxBitmap* bmp = new wxBitmap(img);
			staticBitmap1->SetBitmap(*bmp);
		}else {
			wxImage img1(600, 600);
			img1.SetRGB(wxRect(0, 0, 600, 600), 255, 0, 0);
			wxBitmap* bmp = new wxBitmap(img1);
			staticBitmap1->SetBitmap(*bmp);
		}
		if(image2) {
			wxImage img = *image2;
			img.Rescale(500,500,wxIMAGE_QUALITY_BICUBIC);
			wxBitmap* bmp = new wxBitmap(img);
			staticBitmap2->SetSize(image2->GetWidth(),image2->GetHeight());
			staticBitmap2->SetBitmap(*bmp);
		} else {
			wxImage img2(600, 600);
			img2.SetRGB(wxRect(0, 0, 600, 600), 0, 255, 0);
			wxBitmap* bmp = new wxBitmap(img2);
			staticBitmap2->SetBitmap(*bmp);
		}
		
		markedForUpdate = false;
	}
}
