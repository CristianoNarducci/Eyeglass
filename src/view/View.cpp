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
	LIST_ID,
	ABOUT,
	STATIC_ID,
	VALUE_SLIDER
};
wxBEGIN_EVENT_TABLE(View,wxFrame)
	EVT_BUTTON(BUTTON_ADD,View::loadImages)
	EVT_BUTTON(BUTTON_REMOVE,View::removeImages)
	EVT_BUTTON(BUTTON_ACTIVATE,View::activateSelectedImages)
	EVT_BUTTON(BUTTON_COMPARE,View::compareImages)
	EVT_MENU(ABOUT,View::onAbout)
	EVT_MENU(wxID_EXIT,View::onExit)
	EVT_SLIDER(SLIDER_COLOR,View::onSliderUpdate)
wxEND_EVENT_TABLE()
View::View(const std::string title, const wxPoint &pos, const wxSize &size, AbstractModel& model, AbstractController& controller): wxFrame(NULL,wxID_ANY,title,pos,size),model(model),controller(controller) {

    model.registerObserver(this);  //registration view for successive notification

    panel = new wxPanel(this,PANEL_ID);
    menuFile= new wxMenu;
    menuFile->Append(ABOUT,"Eyeglass");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);
	menu = new wxMenuBar;
	menu->Append(menuFile,"&File");
	SetMenuBar(menu);
    addImageButton = new wxButton(panel,BUTTON_ADD,_T("Aggiungi un immagine"));
    removeImagesButton = new wxButton(panel,BUTTON_REMOVE,_T("Rimuovi Immagine"));
    activateImages = new wxButton(panel,BUTTON_ACTIVATE,_T("Attiva Immagine"));
    compareButton = new wxButton(panel,BUTTON_COMPARE,_T("Compara le immagini"));
    alphaToleranceSlider = new wxSlider(panel,SLIDER_ALPHA,500,0,1000,wxDefaultPosition,wxSize(100,50));
    colorToleranceSlider= new wxSlider(panel,SLIDER_COLOR,500,0,1000,wxDefaultPosition,removeImagesButton->GetSize());
	sliderValue = new wxTextCtrl(panel,VALUE_SLIDER,_("500"),wxDefaultPosition,wxDefaultSize,wxTE_CENTRE);
	sliderValue->SetEditable(false);
    modeSelector = new wxComboBox(panel,MODE_SELECTOR,wxEmptyString);
    list = new wxListView(panel, LIST_ID, wxPoint(50, 50), wxSize(500, 400));
    list->InsertColumn(0, "Images",wxLIST_FORMAT_LEFT,250);
	wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
	wxGridSizer* gs = new wxGridSizer(3,3,10,10);
	hbox->Add(list,0,wxEXPAND);
	vbox->Add(hbox,wxALIGN_LEFT);
	gs->Add(addImageButton,0);
	gs->Add(removeImagesButton,0);
	gs->Add(activateImages,0);
	gs->Add(new wxStaticText(panel, wxID_ANY, wxT("Seleziona tolleranza colore:")),0);
	gs->Add(colorToleranceSlider,1);
	gs->Add(sliderValue,0);
	vbox->Add(gs,0,wxLEFT);
	panel->SetSizer(vbox);


	Centre();

}
void View::update(int eventCode) {

}

void View::removeImages(wxCommandEvent& event) {
	long item;
	while((item = list->GetNextItem(-1,wxLIST_NEXT_ALL,wxLIST_STATE_SELECTED)) != -1){
		list->DeleteItem(item);
	}
}

void View::loadImages(wxCommandEvent& event) {
	wxFileDialog* fileDialog=new wxFileDialog(this,_("Scegli una o più foto"),wxEmptyString,wxEmptyString,wxEmptyString,wxFD_MULTIPLE);
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

void View::onAbout(wxCommandEvent &event) {

}

void View::onExit(wxCommandEvent &event) {
	Close(true);
}

void View::onSliderUpdate(wxCommandEvent &event) {
	int myint = colorToleranceSlider->GetValue();
	wxString mystring;
	mystring << myint;
	sliderValue->SetValue(mystring);

}
