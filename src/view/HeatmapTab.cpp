#include "HeatmapTab.h"

HeatmapTab::HeatmapTab(wxWindow* parent): ViewTab(parent) {
	
}

void HeatmapTab::update(const std::list<std::shared_ptr<PixelDiff>>& diffContainer,
													wxString path1, const std::shared_ptr<wxImage> image1, 
													wxString path2, const std::shared_ptr<wxImage> image2) {
	if (markedForUpdate) {
		
		markedForUpdate = false;
	}
}
