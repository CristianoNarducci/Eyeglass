//
// Created by cristiano on 17/07/20.
//

#ifndef EYEGLASS_VIEW_H
#define EYEGLASS_VIEW_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "AbstractView.h"
#include <iostream>
#include <vector>
#include <wx/listctrl.h>
#include "../model/AbstractModel.h"
#include "../utils/Observer.h"
#include "ViewTab.h"
#include "../controller/AbstractController.h"


class View: public wxFrame, public AbstractView, public Observer {
protected:
    wxPanel* panel;            //application panel
    wxString* activeImages;   //Image activate array
    wxButton* addImageButton;   //adding image button
    wxButton* removeImagesButton;   //remove image button
    wxButton* activateImages;       //activate image button
    wxSlider* alphaToleranceSlider;     //slider for alpha tolerance
    wxSlider* colorToleranceSlider;     //slider for color tolerance
    wxButton* compareButton;            //button for comparation inizialize
    std::vector<ViewTab*> tabs;     //Tab's vector for different results
    wxComboBox* modeSelector;       //Comparation mode selector
    wxListView* list;
    AbstractModel& model;
    AbstractController& controller;


public:

    View(const std::string title, const wxPoint& pos, const wxSize& size,AbstractModel& model, AbstractController& controller);

    void update(int eventCode) override;

    void removeImages(wxCommandEvent &event) override; //Remove images from list

    void loadImages(wxCommandEvent &event) override;    //upload the images to the list

    void activateSelectedImages(wxCommandEvent &event) override;    //activate the selected image

    void compareImages(wxCommandEvent &event) override; //compare activated images

    void resetTabs() override;      //reset tabs

    AbstractModel& getModel() override;

    wxString getMode() override; //get selected comparation mode

    wxString* getActiveImages() override;   //get activated images
	wxDECLARE_EVENT_TABLE();
};


#endif //EYEGLASS_VIEW_H
