#ifndef EYEGLASS_CONTROLLER_H
#define EYEGLASS_CONTROLLER_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "../model/Model.h"

/*
 * The controller acts as a request dispatcher from the view to the model, in an MVC architecture.
 */
class Controller {
public:
	Controller(Model& model);
	
	virtual void removeCachedDifferences();
	virtual void removeImage(wxString path);
	virtual void loadImage(wxString path);
	virtual void compareRGB(wxString path1, wxString path2, double tolerance);
	virtual void compareAlpha(wxString path1, wxString path2, double tolerance);
	virtual void compareHSV(wxString path1, wxString path2, double tolerance);
	
	virtual ~Controller() {};

protected:
	Model& model;
};

#endif
