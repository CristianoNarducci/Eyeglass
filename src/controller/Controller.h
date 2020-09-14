#ifndef EYEGLASS_CONTROLLER_H
#define EYEGLASS_CONTROLLER_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "../model/Model.h"

class Controller {
public:
	Controller(Model& model);

	/*
	 * Remove the specified images from the storage.
	 * It can remove multiple image at once.
	 */
	virtual void removeImages(wxArrayString paths);

	/*
	 * Loads images on the storage.
	 * It can load multiple images at once.
	 */
	virtual void loadImages(wxArrayString paths);

	/* 
	 * Compares the active images RGB values.
	 * If the result doesn't reach the tolerance, it considers the images equals.
	 */
	virtual void compareRGB(wxString path1, wxString path2, double tolerance);

	/*
	 * Compares the active images Alpha values.
	 * If the result doesn't reach the tolerance,it considers the images equals.
	 */
	virtual void compareAlpha(wxString path1, wxString path2, double tolerance);

	/*
	 * Compares the active imagesHSV values.
	 * If the result doesn't reach the tolerance, it considers the images equals.
	 */
	virtual void compareHSV(wxString path1, wxString path2, double tolerance);

protected:
	Model& model;
};

#endif
