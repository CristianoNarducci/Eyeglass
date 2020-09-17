#include "HeatmapTab.h"

HeatmapTab::HeatmapTab(wxWindow* parent): ViewTab(parent) {
	
}

void HeatmapTab::update(const std::list<PixelDiff*>& diffContainer, wxString path1, const wxImage* image1, 
																	wxString path2, const wxImage* image2) {
	if (markedForUpdate) {
		
		markedForUpdate = false;
	}
}
