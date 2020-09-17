#ifndef EYEGLASS_DIFFLISTTAB_H
#define EYEGLASS_DIFFLISTTAB_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
#include <wx/listctrl.h>

#include "ViewTab.h"

class DiffListTab: public ViewTab  {
public:
	DiffListTab(wxWindow* parent);
	void update(const std::list<std::shared_ptr<PixelDiff>>& diffContainer,
													wxString path1, const std::shared_ptr<wxImage> image1, 
													wxString path2, const std::shared_ptr<wxImage> image2) override;

protected:
	wxListView* list;
};

#endif
