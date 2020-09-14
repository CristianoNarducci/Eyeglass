#ifndef EYEGLASS_ORIGINALVIEWTAB_H
#define EYEGLASS_ORIGINALVIEWTAB_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "ViewTab.h"
#include "View.h"

class OriginalViewTab: public ViewTab {
protected:
	wxStaticBitmap* images;
	View& view;

public:
	void reset() override;
	void generateDiffView() override;
};

#endif
