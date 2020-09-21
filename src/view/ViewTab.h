#ifndef EYEGLASS_VIEWTAB_H
#define EYEGLASS_VIEWTAB_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "../model/PixelDiff.h"

#include <memory>
#include <list>

/*
 * Inteface for a group of small views which are responsible for showing images and computation results
 * for the program.
 * In addition to this, they are enabled to do some heavylifting regarding visualization and image manipulation
 * (altough only for the temporary visualization - the image storage is not impacted).
 */
class ViewTab: public wxWindow {
public:
	ViewTab(wxWindow* parent);
	
	virtual void markForUpdate();
	
	/*
	 * Updates the tab with the content provided as parameter, but only if marked for updated beforehand.
	 */
	virtual void update(const std::list<std::shared_ptr<const PixelDiff>>& diffContainer, 
					std::shared_ptr<const wxImage> image1, std::shared_ptr<const wxImage> image2) = 0;
	
	virtual ~ViewTab() {};

protected:
	/*
	 * States if the tab needs to be updated or not, when the next update call comes.
	 * Starts as true by default, as no content is rendered at first.
	 */
	bool markedForUpdate = true;
};

#endif
