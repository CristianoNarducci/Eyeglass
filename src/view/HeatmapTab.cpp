#include "HeatmapTab.h"

HeatmapTab::HeatmapTab(wxWindow* parent): ViewTab(parent) {
	
}

void HeatmapTab::update(const DiffContainer& diffContainer, wxString path1, const wxImage* image1, 
															wxString path2, const wxImage* image2) {
	if (markedForUpdate) {
		std::cout << std::string(path1.mb_str()) << std::endl;
		std::cout << std::string(path2.mb_str()) << std::endl;
		
		markedForUpdate = false;
	}
}
