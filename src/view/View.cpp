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

View::View(const std::string title, const wxPoint &pos, const wxSize &size, Model& model, Controller& controller):model(model),controller(controller),wxFrame(NULL,wxID_ANY,title,pos,size) {
    model.registerObserver(this);
    
    /* Definition of View items
     * the buttons for list manipulation and the text information are insert in columns of
     * a FlexGridSizer for a table-style view.
     * Instead of a wxPanel, we used a wxScrolledWindow for implementing the scroll window function*/
    panel = new wxScrolledWindow(this,PANEL_ID);
    panel->SetScrollRate(5,5);
    
	/*Definition of Menutab
	 * It's used for author's information and quick keys*/
    menuFile = new wxMenu;
    menuFile->Append(ABOUT,"Eyeglass");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);
	menu = new wxMenuBar;
	menu->Append(menuFile,"&File");
	SetMenuBar(menu);
	
	// Main interface elements params
    addImageButton = new wxButton(panel, BUTTON_ADD, "Aggiungi immagini");
    removeImagesButton = new wxButton(panel, BUTTON_REMOVE, "Rimuovi immagini");
	activateImagesButton = new wxButton(panel, BUTTON_ACTIVATE, "Attiva immagini");
    compareButton = new wxButton(panel, BUTTON_COMPARE, "Compara immagini");
    toleranceText = new wxStaticText(panel, STATIC_ID, "Soglia di tolleranza:");
    comparisonText = new wxStaticText(panel, STATIC_ID, "Modo comparazione:");
    toleranceSlider = new wxSlider(panel, SLIDER_COLOR, 500, 0, 1000);
    
    sliderValue = new wxTextCtrl(panel,VALUE_SLIDER,"50.0 %", wxDefaultPosition, wxDefaultSize, wxTE_CENTRE);
	sliderValue->SetEditable(false);
	
    modeSelector = new wxComboBox(panel,MODE_SELECTOR, "RGB");
    modeSelector->Append("RGB");
    modeSelector->Append("HSV");
    modeSelector->Append("ALPHA");
    modeSelector->SetEditable(false);

    list = new wxListView(panel, LIST_ID);
    list->InsertColumn(0, "Immagini", wxLIST_FORMAT_LEFT, 350);
    list->InsertColumn(1, "Attiva", wxLIST_FORMAT_CENTER, 100);
    
	// Main panel sizer
    //wxBoxSizer* panelSizer = new wxBoxSizer(wxHORIZONTAL);
    wxFlexGridSizer* panelSizer = new wxFlexGridSizer(1, 2, 0, 0);
    panelSizer->AddGrowableRow(0, 16);
    panelSizer->AddGrowableCol(1, 16);
    panel->SetSizer(panelSizer);
    
    // Sidebar sizers and controls
    wxFlexGridSizer* sidebarSizer = new wxFlexGridSizer(6, 1, 0, 0);
    sidebarSizer->AddGrowableRow(0, 16);
    sidebarSizer->AddGrowableRow(1, 0);
    sidebarSizer->AddGrowableRow(2, 0);
    sidebarSizer->AddGrowableRow(3, 0);
    sidebarSizer->AddGrowableRow(4, 0);
    sidebarSizer->AddGrowableRow(5, 0);
    panelSizer->Add(sidebarSizer, 1, wxEXPAND);
    
    sidebarSizer->Add(list, 1, wxEXPAND);
    
    sidebarSizer->AddSpacer(4);
    
    wxBoxSizer* storageControlSizer = new wxBoxSizer(wxHORIZONTAL);
    sidebarSizer->Add(storageControlSizer, 1, wxEXPAND | wxBOTTOM);
    storageControlSizer->Add(addImageButton, 1, wxALL, 4);
    storageControlSizer->Add(activateImagesButton, 1, wxALL, 4);
    storageControlSizer->Add(removeImagesButton, 1, wxALL, 4);
    
    sidebarSizer->AddSpacer(16);
    
    wxBoxSizer* toleranceControlSizer = new wxBoxSizer(wxHORIZONTAL);
    sidebarSizer->Add(toleranceControlSizer, 1, wxEXPAND | wxBOTTOM);
    toleranceControlSizer->Add(toleranceText, 1, wxALL, 4);
    toleranceControlSizer->Add(toleranceSlider, 1, wxALL, 4);
    toleranceControlSizer->Add(sliderValue, 1, wxALL, 4);
    
    wxBoxSizer* modeControlSizer = new wxBoxSizer(wxHORIZONTAL);
    sidebarSizer->Add(modeControlSizer, 1, wxEXPAND | wxBOTTOM);
    modeControlSizer->Add(comparisonText, 1, wxALL, 4);
    modeControlSizer->Add(modeSelector, 1, wxALL, 4);
    modeControlSizer->Add(compareButton, 1, wxALL, 4);
    
    // Result view area
    wxNotebook* viewtabsNotebook = new wxNotebook(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_BOTTOM);
    wxBoxSizer* container = new wxBoxSizer(wxVERTICAL);
    container->Add(viewtabsNotebook, 1, wxEXPAND);
    panelSizer->Add(container, 1, wxEXPAND);
    
    wxWindow* testPage = new wxWindow(viewtabsNotebook, wxID_ANY);
    viewtabsNotebook->AddPage(testPage, "test page", true);
    
    wxWindow* testPage2 = new wxWindow(viewtabsNotebook, wxID_ANY);
    viewtabsNotebook->AddPage(testPage2, "peepo");
}
void View::update(int eventCode) {

}
/*Delete the selected images
 * the while cicle it afflict only the image selected*/
void View::removeImages(wxCommandEvent& event){
	bool checkDelete = false;
	long item;
	wxArrayString paths;
	while((item = list->GetNextItem(-1,wxLIST_NEXT_ALL,wxLIST_STATE_SELECTED)) != -1){
		paths.Add(list->GetItemText(item));
		list->DeleteItem(item);
		checkDelete = true;
	}
	if(checkDelete){
		controller.removeImages(paths);
		deselectImages();
	}
}
/*load images on storage
 * It load the paths in the list view but in the Model there is a map that associate
 * the wxImage object with his relative path*/
void View::loadImages(wxCommandEvent& event){
	wxFileDialog* fileDialog=new wxFileDialog(this, _("Scegli una o più foto"),wxEmptyString,wxEmptyString,wxFileSelectorDefaultWildcardStr,wxFD_MULTIPLE);
	if(fileDialog->ShowModal() == wxID_CANCEL){
		return;
	}
	wxArrayString paths;
	fileDialog->GetPaths(paths);
	
	try {
		controller.loadImages(paths);
	} catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	try {
		for (auto iterator = paths.begin(); iterator < paths.end(); ++iterator) {
			list->InsertItem(0,*iterator);
		}

	}
	catch (std::exception& error) {
		std::cout << "Caught exception: " << error.what() << std::endl;
	}
	controller.loadImages(paths);
}
/*
 * Count the image that are in the list
 */
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
/* Deselect the activated images
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
/*
 * Activate the selected images
 * when the image count have vaue 2, it store the paths in a vector corresponding in the image active image paths
 */
void View::activateSelectedImages(wxCommandEvent& event) {
	int imageActive = imagesActivatedCount();
	int itemCount=0;
	long item = -1;
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
	if (imageActive == 2) {
		itemCount = 0;
		item = -1;
		wxString text;
		if (!activeImages.empty()){
			activeImages.clear();
		}
		while((item = list->GetNextItem(item,wxLIST_NEXT_ALL,wxLIST_STATE_DONTCARE)) != -1){
			text = list->GetItemText(item,1);
			if (text.IsSameAs(_("*"))){
				activeImages.push_back(list->GetItemText(item));
				itemCount++;
			}

		}
	}
}
/* Compare images depending of the method chosen by the user
 * if there is only one image activated or the mode aren't choice the function will visualize an error by a message box
 * */
void View::compareImages(wxCommandEvent &event){
	int imagesActive = imagesActivatedCount();
	wxString mode = getMode();
	double tolerance = toleranceSlider->GetValue();
	if(imagesActive < 2){
		wxMessageBox("Nel frattempo, attiva due immagini per iniziare una comparazione", 
						"Vivi a lungo e prospera", wxOK | wxICON_EXCLAMATION);
	}
	else if(mode.IsSameAs("RGB")) {
		controller.compareRGB(activeImages[0], activeImages[1], tolerance);
	}
	else if(mode.IsSameAs("HSV")) {
		controller.compareHSV(activeImages[0], activeImages[1], tolerance);
	}
	else if(mode.IsSameAs("ALPHA")) {
		controller.compareAlpha(activeImages[0], activeImages[1], tolerance);
	}
}

void View::resetTabs(){

}

Model& View::getModel(){
    return model;
}

wxString View::getMode(){
    wxString mode = modeSelector->GetStringSelection();
    return mode;
}

std::vector<wxString> View::getActiveImages(){
	return activeImages;
}
void View::onAbout(wxCommandEvent &event){

}

void View::onExit(wxCommandEvent &event){
	Close(true);
}

void View::onSliderUpdate(wxCommandEvent &event){
	long intValue = toleranceSlider->GetValue();
	wxString stringValue;
	stringValue << (intValue/10.0);
	sliderValue->SetValue(stringValue + " %");
}

Controller &View::getController() {
	return controller;
}

