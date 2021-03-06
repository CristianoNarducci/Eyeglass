#ifndef EYEGLASS_HEATMAPTAB_H
#define EYEGLASS_HEATMAPTAB_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
#include <wx/generic/statbmpg.h>
#include <wx/statbmp.h>

#include "../utils/DisplayUtils.h"

#include "ViewTab.h"

class HeatmapTab: public ViewTab {
public:
	HeatmapTab(wxWindow* parent);
	void update(const std::list<std::shared_ptr<const PixelDiff>>& diffContainer, 
					std::shared_ptr<const wxImage> image1, std::shared_ptr<const wxImage> image2) override;
	
	wxDECLARE_EVENT_TABLE();

protected:
	/*
	 * Repaints the tab, resizing the images and changing layout when needed.
	 */
	void repaintTab();
	
	/*
	 * Calculates the heatmap and applies the effect on the image cached in the tab.
	 */
	void generateHeatmap(const std::list<std::shared_ptr<const PixelDiff>>& diffContainer);
	
	void onTabResize(wxSizeEvent& event);
	
	/*
	 * A cache for the image to display, the one with the original size/resolution.
	 * Initially it's just a copy of one of the images, converted to greyscale and dimmed.
	 * Later on, it contains the heat-mapped image.
	 * It is used as a restart-point from which the displayed images are created, by repaintTab.
	 */
	wxImage image;
	
	/*
	 * What to show when an image is missing.
	 */
	std::shared_ptr<const wxImage> blankImage;
	
	/*
	 * Components that display the images.
	 * wxWidgets documentation suggests the strict use of wxGenericStaticBitmap, instead of just wxStaticBitmap,
	 * for large images.
	 */
	wxGenericStaticBitmap* staticBitmap;
};

#endif
