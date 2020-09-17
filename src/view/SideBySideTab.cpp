#include "SideBySideTab.h"

SideBySideTab::SideBySideTab(wxWindow* parent): ViewTab(parent) {
	
}

void SideBySideTab::update(const std::list<PixelDiff*>& diffContainer, wxString path1, const wxImage* image1, 
																		wxString path2, const wxImage* image2) {
	if (markedForUpdate) {
		
		markedForUpdate = false;
	}
}
