#ifndef EYEGLASS_LAYERTAB_H
#define EYEGLASS_LAYERTAB_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "ViewTab.h"
#include "View.h"

class LayerTab: public ViewTab {
protected:
	wxStaticBitmap* images;
	AbstractView& view;

public:
	void reset() override;
	void generateDiffView() override;
};

#endif
