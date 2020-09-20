#ifndef EYEGLASS_ORIGINALVIEWTAB_H
#define EYEGLASS_ORIGINALVIEWTAB_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
#include <wx/generic/statbmpg.h>
#include <wx/statbmp.h>

#include "../utils/DisplayUtils.h"

#include "ViewTab.h"

class OriginalViewTab: public ViewTab {
public:
	OriginalViewTab(wxWindow* parent);
	void update(const std::list<std::shared_ptr<const PixelDiff>>& diffContainer,
													wxString path1, const std::shared_ptr<const wxImage> image1, 
													wxString path2, const std::shared_ptr<const wxImage> image2) override;

protected:
	wxGenericStaticBitmap* staticBitmap1;
	wxGenericStaticBitmap* staticBitmap2;
};

#endif
