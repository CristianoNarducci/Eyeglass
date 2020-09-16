#include "View.h"

// Enum used for component identification in event table.
enum {
	ADD_IMAGES_BUTTON,
	REMOVE_IMAGES_BUTTON,
	ACTIVATE_IMAGES_BUTTON,
	COMPARE_IMAGES_BUTTON,
	TOLERANCE_SLIDER,
	
	ABOUT
};

// wx event table
wxBEGIN_EVENT_TABLE(View, wxFrame)
	EVT_BUTTON(ADD_IMAGES_BUTTON, View::loadImages)
	EVT_BUTTON(REMOVE_IMAGES_BUTTON, View::removeImages)
	EVT_BUTTON(ACTIVATE_IMAGES_BUTTON, View::activateSelectedImages)
	EVT_BUTTON(COMPARE_IMAGES_BUTTON, View::compareImages)
	EVT_SLIDER(TOLERANCE_SLIDER, View::onSliderUpdate)
	
	EVT_MENU(ABOUT, View::onAbout)
	EVT_MENU(wxID_EXIT, View::onExit)
wxEND_EVENT_TABLE()

View::View(const std::string title, const wxPoint &pos, const wxSize &size, Model& model, Controller& controller): 
									model(model), controller(controller), wxFrame(NULL, wxID_ANY, title, pos, size) {
	model.registerObserver(this);
	
	// TODO: Check if wxBORDER_THEME setting actually does something (could be just my wayland/sway theme, but I see no border here)
	panel = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_THEME);
	panel->SetScrollRate(5, 5);
	
	appDropdownMenu = new wxMenu;
	appDropdownMenu->Append(ABOUT, "Informazioni sul progetto");
	appDropdownMenu->Append(wxID_EXIT, "Esci");
	
	menu = new wxMenuBar;
	menu->Append(appDropdownMenu, "Eyeglass");
	SetMenuBar(menu);
	
	// Main interface elements
	addImagesButton = new wxButton(panel, ADD_IMAGES_BUTTON, "Aggiungi immagini");
	removeImagesButton = new wxButton(panel, REMOVE_IMAGES_BUTTON, "Rimuovi immagini");
	activateImagesButton = new wxButton(panel, ACTIVATE_IMAGES_BUTTON, "Attiva immagini");
	compareImagesButton = new wxButton(panel, COMPARE_IMAGES_BUTTON, "Compara immagini");
	toleranceText = new wxStaticText(panel, wxID_ANY, "Soglia di tolleranza:");
	comparisonText = new wxStaticText(panel, wxID_ANY, "Modo comparazione:");
	toleranceSlider = new wxSlider(panel, TOLERANCE_SLIDER, 500, 0, 1000);
	
	toleranceSliderValue = new wxTextCtrl(panel, wxID_ANY, "50.0 %", wxDefaultPosition, wxDefaultSize, wxTE_CENTRE);
	toleranceSliderValue->SetEditable(false);
	
	modeSelector = new wxComboBox(panel, wxID_ANY);
	modeSelector->Append("RGB");
	modeSelector->Append("HSV");
	modeSelector->Append("ALPHA");
	modeSelector->SetEditable(false);
	modeSelector->SetSelection(0);
	
	list = new wxListView(panel, wxID_ANY);
	list->InsertColumn(0, "Immagini", wxLIST_FORMAT_LEFT, 350);
	list->InsertColumn(1, "Attiva", wxLIST_FORMAT_CENTER, 100);
	
	// Main panel sizer
	wxFlexGridSizer* panelSizer = new wxFlexGridSizer(1, 2, 16, 16);
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
	storageControlSizer->Add(addImagesButton, 1, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	storageControlSizer->Add(activateImagesButton, 1, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	storageControlSizer->Add(removeImagesButton, 1, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	
	sidebarSizer->AddSpacer(16);
	
	wxBoxSizer* toleranceControlSizer = new wxBoxSizer(wxHORIZONTAL);
	sidebarSizer->Add(toleranceControlSizer, 1, wxEXPAND | wxBOTTOM);
	toleranceControlSizer->Add(toleranceText, 1, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	toleranceControlSizer->Add(toleranceSlider, 1, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	toleranceControlSizer->Add(toleranceSliderValue, 1, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	
	wxBoxSizer* modeControlSizer = new wxBoxSizer(wxHORIZONTAL);
	sidebarSizer->Add(modeControlSizer, 1, wxEXPAND | wxBOTTOM);
	modeControlSizer->Add(comparisonText, 1, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	modeControlSizer->Add(modeSelector, 1, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	modeControlSizer->Add(compareImagesButton, 1, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	
	// Result view area
	wxNotebook* viewtabsNotebook = new wxNotebook(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_BOTTOM);
	wxBoxSizer* container = new wxBoxSizer(wxVERTICAL);
	container->Add(viewtabsNotebook, 1, wxEXPAND);
	panelSizer->Add(container, 1, wxEXPAND);
	
	// TODO: Remove placeholder elements
	wxWindow* testView = new wxWindow(viewtabsNotebook, wxID_ANY);
	viewtabsNotebook->AddPage(testView, "view_1", true);
	
	wxWindow* testView2 = new wxWindow(viewtabsNotebook, wxID_ANY);
	viewtabsNotebook->AddPage(testView2, "view_2");
	
	// TODO: Add viewtabs initialization code here!
}


void View::loadImages(wxCommandEvent& event) {
	wxFileDialog* fileDialog=new wxFileDialog(this, "Seleziona le immagini da analizzare", wxEmptyString, 
												wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_MULTIPLE);
	if (fileDialog->ShowModal() == wxID_CANCEL) {
		return;
	}
	
	wxArrayString paths;
	fileDialog->GetPaths(paths);
	
	// Tries to load each image. The ones not loaded will be put into a separate array.
	wxArrayString pathsNotLoaded;
	for (auto iterator = paths.begin(); iterator < paths.end(); ++iterator) {
		try {
			controller.loadImage(*iterator);
		} catch (ImageLoaderException& error) {
			pathsNotLoaded.Add(*iterator);
			continue;
		}
		
		list->InsertItem(0, *iterator);
	}
	
	// Shows which images have not been loaded.
	if (!pathsNotLoaded.IsEmpty()) {
		wxString message = "";
		for (auto iterator = pathsNotLoaded.begin(); iterator < pathsNotLoaded.end(); ++iterator) {
			message += "\n" + *iterator;
		}
		
		wxMessageBox(message, "Non e' stato possibile caricare i seguenti file", wxOK | wxICON_ERROR);
	}
}

void View::removeImages(wxCommandEvent& event) {
	long item;
	
	while ((item = list->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != -1) {
		if (activeImages.Index(list->GetItemText(item)) != wxNOT_FOUND) {
			activeImages.Remove(list->GetItemText(item));
		}
		controller.removeImage(list->GetItemText(item));
		
		list->DeleteItem(item);
	}
	
	// disables the images if the removal impacts one of the actives.
	if (activeImages.GetCount() < 2) {
		deselectImages();
	}
}

void View::activateSelectedImages(wxCommandEvent& event) {
	if (activeImages.GetCount() > 1 || list->GetSelectedItemCount() > 1) {
		deselectImages();
	}
	
	long item = -1;
	while ((item = list->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != -1) {
		if (activeImages.GetCount() < 2) {
			list->SetItem(item, 1, "*");
			activeImages.Add(list->GetItemText(item));
		} else {
			break;
		}
	}
}

void View::deselectImages() {
	long item = -1;
	while ((item = list->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_DONTCARE)) != -1) {
		if (list->GetItemText(item, 1).IsSameAs("*")){
			list->SetItem(item, 1, "");
		}
	}
	
	activeImages.Empty();
	resetTabs();
}

void View::compareImages(wxCommandEvent &event) {
	wxString mode = getMode();
	double tolerance = toleranceSlider->GetValue();
	
	try {
		if (activeImages.GetCount() < 2){
			wxMessageBox("Nel frattempo, attiva due immagini per iniziare una comparazione", 
							"Vivi a lungo e prospera", wxOK | wxICON_EXCLAMATION);
		} else if (mode.IsSameAs("RGB")) {
			controller.compareRGB(activeImages[0], activeImages[1], tolerance);
		} else if (mode.IsSameAs("HSV")) {
			controller.compareHSV(activeImages[0], activeImages[1], tolerance);
		} else if (mode.IsSameAs("ALPHA")) {
			controller.compareAlpha(activeImages[0], activeImages[1], tolerance);
		}
	} catch (ImageGeometryException& error) {
		wxMessageBox("Causa: geometria diversa. \nE' necessario che le immagini abbiano altezze e larghezze uguali",
						"Impossibile confrontare le immagini scelte", wxOK | wxICON_EXCLAMATION);
	}
}

void View::update(int eventCode) {
	// TODO: Move event-related code here!
}

void View::resetTabs() {
	// TODO: Implement the loop which resets each viewtab
}

void View::onAbout(wxCommandEvent &event) {
	// TODO: Implement a little message box with some info about the project itself
}

void View::onExit(wxCommandEvent &event) {
	Close(true);
}

void View::onSliderUpdate(wxCommandEvent &event) {
	wxString stringValue;
	stringValue << (toleranceSlider->GetValue() / 10.0);
	toleranceSliderValue->SetValue(stringValue + " %");
}

wxString View::getMode() {
	return modeSelector->GetStringSelection();
}

wxArrayString View::getActiveImages() {
	return activeImages;
}

Model& View::getModel() {
	return model;
}

Controller& View::getController() {
	return controller;
}
