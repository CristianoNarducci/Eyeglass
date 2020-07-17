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
#include "../utils/Observer.h"
#include "ViewTab.h"

class View: public wxFrame, public AbstractView,public Observer {

protected:
    wxString* activeImages[2];
    wxButton* addImageButton;
    wxButton* removeImagesButton;
    wxButton* activateImages;
    wxSlider* alphaToleranceSlider;
    wxSlider* colorToleranceSlider;
    wxButton* compareButton;
    std::vector<ViewTab*> tabs;
    wxComboBox* modeSelector;
    AbstractModel& model;
    AbstractController& controller;

public:
    bool onInit();

    View();

    void update(int eventCode) override;

    void removeImages(wxCommandEvent &event) override;

    void loadImages(wxCommandEvent &event) override;

    void activateSelectedImages(wxCommandEvent &event) override;

    void compareImages(wxCommandEvent &event) override;

    void resetTabs() override;

    AbstractModel &getModel() override;

    wxString getMode() override;

    wxString *getActiveImages() override;

};


#endif //EYEGLASS_VIEW_H
