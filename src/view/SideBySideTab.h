#ifndef EYEGLASS_SIDEBYSIDETAB_H
#define EYEGLASS_SIDEBYSIDETAB_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "ViewTab.h"

class SideBySideTab: public ViewTab {
public:
	SideBySideTab(wxWindow* parent);
	void update(const DiffContainer& diffContainer, wxString path1, const wxImage* image1, 
													wxString path2, const wxImage* image2) override;
};

#endif
