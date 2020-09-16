#ifndef EYEGLASS_HEATMAPTAB_H
#define EYEGLASS_HEATMAPTAB_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "ViewTab.h"

class HeatmapTab: public ViewTab {
public:
	HeatmapTab(wxWindow* parent);
	void update(const DiffContainer& diffContainer, wxString path1, const wxImage* image1, 
													wxString path2, const wxImage* image2) override;
};

#endif
