#ifndef EYEGLASS_LAYERTAB_H
#define EYEGLASS_LAYERTAB_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
#include <wx/generic/statbmpg.h>
#include <wx/statbmp.h>

#include "../utils/DisplayUtils.h"

#include "ViewTab.h"

class LayerTab: public ViewTab {
public:
	LayerTab(wxWindow* parent);
	void update(const std::list<std::shared_ptr<const PixelDiff>>& diffContainer,
													wxString path1, std::shared_ptr<const wxImage> image1, 
													wxString path2, std::shared_ptr<const wxImage> image2) override;
	
	wxDECLARE_EVENT_TABLE();

protected:
	/*
	 * Repaints the tab, resizing the images and changing layout when needed.
	 * It also cuts the images where the slider says.
	 */
	void repaintTab();
	
	void onSliderUpdate(wxCommandEvent& event);
	void onTabResize(wxSizeEvent& event);
	
	/*
	 * The slider that controls the images cut.
	 */
	wxSlider* slider;
	
	/*
	 * A copy of the original images passed on update.
	 * It is used as a restart-point from which the displayed images are created, by repaintTab.
	 */
	wxImage image1;
	wxImage image2;
	
	/*
	 * Components that display the images.
	 * wxWidgets documentation suggests the strict use of wxGenericStaticBitmap, instead of just wxStaticBitmap,
	 * for large images.
	 */
	wxGenericStaticBitmap* staticBitmap1;
	wxGenericStaticBitmap* staticBitmap2;
};

#endif
