#include "View.h"
/* IDs used for id item's definition
 * The IDs are auto-incremental
 * Every id is for a single item(button/slider/combobox) except for "STATIC_ID" because
 * Its used for every static text in the View because there is no event
 * that concern them*/
enum{
    PANEL_ID,
	BUTTON_ADD,
	BUTTON_REMOVE,
	BUTTON_ACTIVATE,
	BUTTON_COMPARE,
	SLIDER_COLOR,
	MODE_SELECTOR,
	LIST_ID,
	ABOUT,
	STATIC_ID,
	VALUE_SLIDER
};
/*Event table of the view*/
wxBEGIN_EVENT_TABLE(View,wxFrame)
	EVT_BUTTON(BUTTON_ADD,View::loadImages)
	EVT_BUTTON(BUTTON_REMOVE,View::removeImages)
	EVT_BUTTON(BUTTON_ACTIVATE,View::activateSelectedImages)
	EVT_BUTTON(BUTTON_COMPARE,View::compareImages)
	EVT_BUTTON(BUTTON_ACTIVATE,View::activateSelectedImages)
	EVT_MENU(ABOUT,View::onAbout)
	EVT_MENU(wxID_EXIT,View::onExit)
	EVT_SLIDER(SLIDER_COLOR,View::onSliderUpdate)
wxEND_EVENT_TABLE()

View::View(const std::string title, const wxPoint &pos, const wxSize &size, AbstractModel& model, AbstractController& controller):model(model),controller(controller),wxFrame(NULL,wxID_ANY,title,pos,size) {
    model.registerObserver(this);  //registration view for successive notification
    /*Definition of View items
     * the buttons for list manipulation and the text information are insert in columns of
     * a FlexGridSizer for a table-style view.
     * Instead of a wxPanel, we used a wxScrolledWindow for implementing the scroll window function*/
    activeImages = new wxString[2];
    panel = new wxScrolledWindow(this,PANEL_ID);
    panel->SetScrollRate(5,5);
	/*Definition of Menutab
	 * It's used for author's information and quick keys*/
    menuFile= new wxMenu;;
    menuFile->Append(ABOUT,"Eyeglass");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);
	menu = new wxMenuBar;
	menu->Append(menuFile,"&File");
	SetMenuBar(menu);
	//Definition of button items
    addImageButton = new wxButton(panel,BUTTON_ADD,_("Aggiungi un immagine"));
    removeImagesButton = new wxButton(panel,BUTTON_REMOVE,_("Rimuovi Immagine"));
	activateImagesButton = new wxButton(panel,BUTTON_ACTIVATE,_("Attiva Immagine"),wxDefaultPosition,addImageButton->GetSize());
    compareButton = new wxButton(panel,BUTTON_COMPARE,_("Compara le immagini"));
    toleranceText = new wxStaticText(panel,STATIC_ID,_("Seleziona tolleranza colore:"),wxDefaultPosition,wxDefaultSize);
    comparisonText = new wxStaticText(panel,STATIC_ID,_("Seleziona comparazione:"),wxDefaultPosition,wxDefaultSize);
    colorToleranceSlider= new wxSlider(panel,SLIDER_COLOR,500,0,1000,wxDefaultPosition,removeImagesButton->GetSize());
	//Definition of color tolerance slider
    sliderValue = new wxTextCtrl(panel,VALUE_SLIDER,_("50.0 %"),wxDefaultPosition,removeImagesButton->GetSize(),wxTE_CENTRE);
	sliderValue->SetEditable(false);
	/*Definition of comparison mode of combobox
	 * the initial text "seleziona" aren't a value
	 * the option for comparison are : HSV, RGB and ALPHA
	 * the combobox obviously is not editable*/
    modeSelector = new wxComboBox(panel,MODE_SELECTOR,_("Seleziona"),wxDefaultPosition,compareButton->GetSize());
    modeSelector->Append(_("RGB"));
    modeSelector->Append(_("HSV"));
    modeSelector->Append(_("ALPHA"));
    modeSelector->SetEditable(false);
    /*Definition of image list
     * the image address that the user select are stored in there */
    list = new wxListView(panel, LIST_ID,wxDefaultPosition, wxSize(500, 400));
    list->InsertColumn(0, "Images",wxLIST_FORMAT_LEFT,250);
    list->InsertColumn(1,"Activated Images",wxLIST_FORMAT_CENTER,150);
	wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer* gs = new wxFlexGridSizer(4,3,10,10);
	hbox->Add(list,0,wxLEFT  | wxBOTTOM, 15);
	vbox->Add(hbox,0,wxALIGN_LEFT | wxTOP ,90);
	/*Adding item in a GridSizer
	 * Border have been inserted for alignment issues with slider and combobox*/
	gs->Add(addImageButton,0);
	gs->Add(new wxStaticText(panel,STATIC_ID,_("")),0);
	gs->Add(removeImagesButton,0);
	gs->Add(toleranceText,0,wxTOP,5);
	gs->Add(colorToleranceSlider,0);
	gs->Add(sliderValue,0);
	gs->Add(comparisonText,0,wxTOP,5);
	gs->Add(modeSelector,0);
	gs->Add(new wxStaticText(panel,STATIC_ID,_("")),0);
	gs->Add(activateImagesButton,0,wxTOP,14);
	gs->Add(new wxStaticText(panel,STATIC_ID,_("")),0);
	gs->Add(compareButton,0,wxTOP,15);
	gs->AddGrowableCol(0);
	vbox->Add(gs,0,wxLEFT ,40);
	panel->SetSizer(vbox); //setting window sizer


}
void View::update(int eventCode) {

}
/*Delete the selected images
 * the while cicle it afflict only the image selected*/
void View::removeImages(wxCommandEvent& event){
	long item;
	while((item = list->GetNextItem(-1,wxLIST_NEXT_ALL,wxLIST_STATE_SELECTED)) != -1){
		list->DeleteItem(item);
	}
}
/*load images on storage
 * It load the paths in the list view but in the model there is a map that associate
 * the wxImage object with his relative path*/
void View::loadImages(wxCommandEvent& event){
	wxFileDialog* fileDialog=new wxFileDialog(this, _("Scegli una o più foto"),wxEmptyString,wxEmptyString,wxFileSelectorDefaultWildcardStr,wxFD_MULTIPLE);
	if(fileDialog->ShowModal() == wxID_CANCEL){
		return;
	}
	wxArrayString paths;
	fileDialog->GetPaths(paths);
	//controller.loadImages(paths);
	try {
		for (auto iterator = paths.begin(); iterator < paths.end(); ++iterator) {
			list->InsertItem(0,*iterator);
		}

	}
	catch (std::exception& error) {
		std::cout << "Caught exception: " << error.what() << std::endl;
	}
}
int View::imagesActivatedCount() {
	int count = 0;
	long item = -1;
	while((item = list->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_DONTCARE)) != -1){
		if (list->GetItemText(item,1).IsSameAs(_("*")))
		{
			count++;
		}
	}
	return count;
}
/*Deselect the activated images
 * this function is called on activatedSelectImages function for deselect before activate the new images
 * For practical reasons the function scan every row in the list and if in the column next to him is present the "*"
 * symbol it deselect him and clear the activated images array
 */
void View::deselectImages() {
	long item = -1;
	while((item = list->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_DONTCARE)) != -1){
		if(list->GetItemText(item,1).IsSameAs(_("*"))){
			list->SetItem(item,1,_(""));
		}
	}
}
void View::activateSelectedImages(wxCommandEvent& event) {
	int imageActive = imagesActivatedCount();
	int itemCount=0;
	long item = -1;
	wxString arr[2];
	if(imageActive >= 2 || list->GetSelectedItemCount() >= 2)
	{
		deselectImages();
		imageActive = 0;
	}
	while((item = list->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_SELECTED)) != -1){
		if(itemCount < 2){
			list->SetItem(item,1,_("*"));
			itemCount++;
			imageActive++;
		}
	}
	if (imageActive == 2)
	{
		itemCount=0;
		item = -1;
		wxString text;
		while((item = list->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_DONTCARE)) != -1){
			text = list->GetItemText(item,1);
			if (text.IsSameAs(_("*"))){
				activeImages[itemCount] = list->GetItemText(item);
				itemCount++;
			}

		}
	//	std::cout<<activeImages[0]<<std::endl;

	}
}

void View::compareImages(wxCommandEvent &event){
	int imagesActive = imagesActivatedCount();
	wxString mode = getMode();
	double tolerance = colorToleranceSlider->GetValue();
	//std::cout<<activeImages[0]<<std::endl;

	if(imagesActive < 2){
		wxMessageBox(_("SELEZIONARE DUE IMMAGINI DA COMPARARE"),_("ERRORE"),wxOK | wxICON_EXCLAMATION);
	}
	else if(mode == "RGB"){
		/*wxString pathImage1 = activeImages[0];
		std::cout<<pathImage1<<std::endl;
		wxString pathImage2 = activeImages[1];
		std::cout<<pathImage2<<std::endl;
		controller.compareRGB(pathImage1,pathImage2,tolerance);*/

	}
	else if(mode.IsSameAs(_("HSV"))){
		wxString pathImage1 = activeImages[0];
		wxString pathImage2 = activeImages[1];
		std::cout<<"luigi"<<std::endl;
		controller.compareHSV(pathImage1,pathImage2,tolerance);
	}
	else if(mode.IsSameAs(_("ALPHA"))){
		wxString pathImage1 = activeImages[0];
		wxString pathImage2 = activeImages[1];
		std::cout<<"paperino"<<std::endl;
		controller.compareAlpha(pathImage1,pathImage2,tolerance);
	}
	else{
		wxMessageBox(_("SCEGLIERE METODO DI COMPARAZIONE"),_("ERRORE"),wxOK | wxICON_EXCLAMATION);
	}
}

void View::resetTabs(){

}

AbstractModel& View::getModel(){
    return model;
}

wxString View::getMode(){
    wxString mode = modeSelector->GetStringSelection();
    return mode;
}

wxString* View::getActiveImages(){
	return activeImages;
}



void View::onAbout(wxCommandEvent &event){

}

void View::onExit(wxCommandEvent &event){
	Close(true);
}

void View::onSliderUpdate(wxCommandEvent &event){
	long intValue = colorToleranceSlider->GetValue();
	wxString stringValue;
	stringValue << (intValue/10.0);
	sliderValue->SetValue(stringValue + " %");
}

AbstractController &View::getController() {
	return controller;
}

