#include "View.h"

enum{                //IDs used for id item's definition
    PANEL_ID,
	BUTTON_ADD,
	BUTTON_REMOVE,
	BUTTON_ACTIVATE,
	BUTTON_COMPARE,
	SLIDER_ALPHA,
	SLIDER_COLOR,
	MODE_SELECTOR,
	LIST_ID

};
enum{

};
wxBEGIN_EVENT_TABLE(View,wxFrame)
	EVT_BUTTON(BUTTON_ADD,View::loadImages)
	EVT_BUTTON(BUTTON_REMOVE,View::removeImages)
	EVT_BUTTON(BUTTON_ACTIVATE,View::activateSelectedImages)
	EVT_BUTTON(BUTTON_COMPARE,View::compareImages)
wxEND_EVENT_TABLE()
View::View(const std::string title, const wxPoint &pos, const wxSize &size, AbstractModel& model, AbstractController& controller): wxFrame(NULL,wxID_ANY,title,pos,size),model(model),controller(controller) {

    model.registerObserver(this);  //registration view for successive notification
    panel = new wxPanel(this,PANEL_ID);
    addImageButton = new wxButton(panel,BUTTON_ADD,_T("Aggiungi un immagine"));
    removeImagesButton = new wxButton(panel,BUTTON_REMOVE,_T("Rimuovi Immagine"));
    activateImages = new wxButton(panel,BUTTON_ACTIVATE,_T("Attiva Immagine"));
    compareButton = new wxButton(panel,BUTTON_COMPARE,_T("Compara le immagini"));
    alphaToleranceSlider = new wxSlider(panel,SLIDER_ALPHA,500,0,1000,wxDefaultPosition,wxSize(200,200));
    colorToleranceSlider= new wxSlider(panel,SLIDER_COLOR,500,0,100);
    modeSelector = new wxComboBox(panel,MODE_SELECTOR,wxEmptyString);
    list = new wxListView(panel, LIST_ID, wxPoint(50, 50), wxSize(500, 400));
    list->InsertColumn(0, "Images");
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);

    hbox1->Add(new wxPanel(panel,PANEL_ID));

    vbox->Add(hbox1,1,wxEXPAND);

    hbox2->Add(addImageButton);
    hbox2->Add(removeImagesButton);
    hbox2->Add(alphaToleranceSlider);
    hbox2->Add(activateImages);
    hbox2->Add(compareButton);

    vbox->Add(hbox2,0,wxALIGN_CENTER);
    panel->SetSizer(vbox);
    Centre();

}
void View::update(int eventCode) {

}

void View::removeImages(wxCommandEvent& event) {
	std::cout<<"BUO";
	long item;
	while((item = list->GetNextItem(-1,wxLIST_NEXT_ALL,wxLIST_STATE_SELECTED)) != -1){
		list->DeleteItem(item);
	}
}

void View::loadImages(wxCommandEvent& event) {
	std::cout<<"prova";
	wxFileDialog* fileDialog=new wxFileDialog(this,"Scegli una foto",wxEmptyString,wxEmptyString,wxEmptyString,wxFD_MULTIPLE);
	if(fileDialog->ShowModal() == wxID_CANCEL){
		return;
	}
	wxArrayString paths;
	fileDialog->GetPaths(paths);
	try {
		for (auto iterator = paths.begin(); iterator < paths.end(); ++iterator) {
			list->InsertItem(0,*iterator);
		}

	}
	catch (std::exception& error) {
		std::cout << "Caught exception: " << error.what() << std::endl;
	}
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