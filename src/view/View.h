//
// Created by cristiano on 17/07/20.
//

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
protected:
    wxScrolledWindow* panel;          //application panel
    wxMenu* menuFile;
    wxMenuBar* menu;
    std::vector<wxString> activeImages;   //Image activate array
    wxButton* addImageButton;   //adding image button
    wxButton* removeImagesButton;   //remove image button
    wxButton* activateImagesButton;       //activate image button
    wxSlider* colorToleranceSlider;     //slider for color tolerance
    wxButton* compareButton;            //button for comparation inizialize
    std::vector<ViewTab*> tabs;     //Tab's vector for different results
    wxComboBox* modeSelector;       //Comparation mode selector
    wxListView* list;
    Model& model;
    Controller& controller;
	wxTextCtrl* sliderValue;
	wxStaticText* toleranceText;
	wxStaticText* comparisonText;

public:

    View(const std::string title, const wxPoint& pos, const wxSize& size,Model& model, Controller& controller);

    void update(int eventCode);

    void removeImages(wxCommandEvent &event); //Remove images from list

    void loadImages(wxCommandEvent &event);    //upload the images to the list

    void activateSelectedImages(wxCommandEvent &event);    //activate the selected image

    void compareImages(wxCommandEvent &event); //compare activated images

    void resetTabs();      //reset tabs

    Model& getModel();

	Controller& getController();

	wxString getMode(); //get selected comparation mode

	std::vector<wxString> getActiveImages();   //get activated images

	void onAbout(wxCommandEvent &event);

	int imagesActivatedCount();

	void onExit(wxCommandEvent &event);

	void onSliderUpdate(wxCommandEvent &event);	//it change the textbox value of comparison tolerance

	void deselectImages();  //deselect the activate images

wxDECLARE_EVENT_TABLE();
};


#endif //EYEGLASS_VIEW_H
