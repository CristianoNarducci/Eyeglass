//
// Created by cristiano on 17/07/20.
//

#include "View.h"
enum{                           //IDs used for id item's definition
    BUTTON_ADD = 1
};
enum{
    BUTTON_REMOVE = 2
};
enum{
    BUTTON_ACTIVATE=3
};
enum{
    BUTTON_COMPARE=4
};
enum
{
    SLIDER_ALPHA = 5
};
enum{
    SLIDER_COLOR = 6
};
enum{
    MODE_SELECTOR=7
};
wxBEGIN_EVENT_TABLE(View,wxFrame)

wxEND_EVENT_TABLE()
View::View(const std::string title, const wxPoint &pos, const wxSize &size, AbstractModel& model, AbstractController& controller): wxFrame(NULL,wxID_ANY,title,pos,size),model(model),controller(controller) {

    //model.registerObserver(this);

    addImageButton = new wxButton(this,BUTTON_ADD,_T("Aggiungi un immagine"),wxPoint(30,30));
    removeImagesButton = new wxButton(this,BUTTON_REMOVE,_T("Rimuovi Immagine"));
    activateImages= new wxButton(this,BUTTON_ACTIVATE,_T("Attiva Immagine"));
    compareButton = new wxButton(this,BUTTON_COMPARE,_T("Compara le immagini"),wxPoint(90,100));
    alphaToleranceSlider = new wxSlider(this,SLIDER_ALPHA,500,0,1000,wxPoint(80,80));
    colorToleranceSlider= new wxSlider(this,SLIDER_COLOR,500,0,100,wxPoint(100,100));
    modeSelector = new wxComboBox(this,MODE_SELECTOR,wxEmptyString,wxPoint(200,100));
}
void View::update(int eventCode) {

}

void View::removeImages(wxCommandEvent &event) {

}

void View::loadImages(wxCommandEvent &event) {

}

void View::activateSelectedImages(wxCommandEvent &event) {

}

void View::compareImages(wxCommandEvent &event) {

}

void View::resetTabs() {

}

AbstractModel& View::getModel() {
    return model;
}

wxString View::getMode() {
    wxString mode = modeSelector->GetStringSelection();
    return mode;
}

wxString* View::getActiveImages() {
    return activeImages;
}
