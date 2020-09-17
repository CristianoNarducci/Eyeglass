#ifndef EYEGLASS_LAYERTAB_H
#define EYEGLASS_LAYERTAB_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "ViewTab.h"

class LayerTab: public ViewTab {
public:
	LayerTab(wxWindow* parent);
	void update(const std::list<std::shared_ptr<PixelDiff>>& diffContainer,
													wxString path1, const std::shared_ptr<wxImage> image1, 
													wxString path2, const std::shared_ptr<wxImage> image2) override;
};

#endif
