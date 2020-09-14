#ifndef EYEGLASS_VIEW_H
#define EYEGLASS_VIEW_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <iostream>
#include <vector>
#include <wx/listctrl.h>
#include "../model/Model.h"
#include "../utils/Observer.h"
#include "ViewTab.h"
#include "../controller/Controller.h"
#include <wx/textctrl.h>
#include <exception>


class View: public wxFrame, public Observer {
public:
	View(const std::string title, const wxPoint& pos, const wxSize& size,Model& model, Controller& controller);
	
	void update(int eventCode);
	
	wxDECLARE_EVENT_TABLE();

protected:
	void removeImages(wxCommandEvent &event);			// Removes images from the list.
	void loadImages(wxCommandEvent &event);				// Loads images into the program.
	void activateSelectedImages(wxCommandEvent &event);	// Activates the selected images.
	void compareImages(wxCommandEvent &event);			// Starts the comparison of the activated images.
	void resetTabs();									// Resets the result view tabs.
	Model& getModel();
	Controller& getController();
	wxString getMode();									// Returns the comparison mode selected in the dropdown.
	std::vector<wxString> getActiveImages();			// Returns the active images names.
	void onAbout(wxCommandEvent &event);
	int imagesActivatedCount();
	void onExit(wxCommandEvent &event);
	void onSliderUpdate(wxCommandEvent &event);			// Detects a slider event and updates the value in the near textbox.
	void deselectImages();								// Deselects the active images.
	
	wxScrolledWindow* panel;				// Application panel.
	wxMenu* menuFile;
	wxMenuBar* menu;
	std::vector<wxString> activeImages;		// Holds the name of the images currently under comparison.
	wxButton* addImageButton;
	wxButton* removeImagesButton;
	wxButton* activateImagesButton;
	wxSlider* colorToleranceSlider;
	wxButton* compareButton;
	std::vector<ViewTab*> tabs;				// Vector which holds all the views for the results.
	wxComboBox* modeSelector;				// Comparison mode selector.
	wxListView* list;						// List of loaded images.
	Model& model;
	Controller& controller;
	wxTextCtrl* sliderValue;
	wxStaticText* toleranceText;
	wxStaticText* comparisonText;
};

#endif
