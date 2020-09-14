#ifndef EYEGLASS_HEATMAPTAB_H
#define EYEGLASS_HEATMAPTAB_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "ViewTab.h"
#include "View.h"

class HeatmapTab: public ViewTab {
protected:
	wxStaticBitmap* images;
	AbstractView& view;

public:
	void reset() override;
	void generateDiffView() override;
};

#endif
