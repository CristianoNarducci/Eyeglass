#include "View.h"

// Enum used for component identification in event table.
enum {
	ADD_IMAGES_BUTTON,
	REMOVE_IMAGES_BUTTON,
	ACTIVATE_IMAGES_BUTTON,
	COMPARE_IMAGES_BUTTON,
	TOLERANCE_SLIDER,
	
	TAB_NOTEBOOK,
	
	ABOUT
};

// wx event table for this panel only.
// Events generated by tabs are handled inside the tabs.
wxBEGIN_EVENT_TABLE(View, wxFrame)
	EVT_BUTTON(ADD_IMAGES_BUTTON, View::loadImages)
	EVT_BUTTON(REMOVE_IMAGES_BUTTON, View::removeImages)
	EVT_BUTTON(ACTIVATE_IMAGES_BUTTON, View::activateSelectedImages)
	EVT_BUTTON(COMPARE_IMAGES_BUTTON, View::compareImages)
	EVT_SLIDER(TOLERANCE_SLIDER, View::onSliderUpdate)
	
	EVT_NOTEBOOK_PAGE_CHANGED(TAB_NOTEBOOK, View::onTabChanged)
	
	EVT_MENU(ABOUT, View::onAbout)
	EVT_MENU(wxID_EXIT, View::onExit)
wxEND_EVENT_TABLE()

View::View(const std::string title, const wxPoint& pos, const wxSize& size, Model& model, Controller& controller): 
									model(model), controller(controller), wxFrame(NULL, wxID_ANY, title, pos, size) {
	model.registerObserver(*this);
	
	panel = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_THEME);
	panel->SetScrollRate(5, 5);
	
	appDropdownMenu = new wxMenu;
	appDropdownMenu->Append(ABOUT, "Informazioni sul progetto");
	appDropdownMenu->Append(wxID_EXIT, "Esci");
	
	menu = new wxMenuBar;
	menu->Append(appDropdownMenu, "Eyeglass");
	SetMenuBar(menu);
	
	// Main interface elements
	addImagesButton = new wxButton(panel, ADD_IMAGES_BUTTON, "Aggiungi immagini", wxDefaultPosition, wxSize(150, 30));
	removeImagesButton = new wxButton(panel, REMOVE_IMAGES_BUTTON, "Rimuovi immagini", wxDefaultPosition, wxSize(150, 30));
	activateImagesButton = new wxButton(panel, ACTIVATE_IMAGES_BUTTON, "Attiva immagini", wxDefaultPosition, wxSize(150, 30));
	compareImagesButton = new wxButton(panel, COMPARE_IMAGES_BUTTON, "Compara immagini", wxDefaultPosition, wxSize(150, 30));
	toleranceText = new wxStaticText(panel, wxID_ANY, "Soglia di tolleranza", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
	comparisonText = new wxStaticText(panel, wxID_ANY, "Modalita' di comparazione", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
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
	list->InsertColumn(0, "Immagini", wxLIST_FORMAT_LEFT, 280);
	list->InsertColumn(1, "S", wxLIST_FORMAT_CENTER, 40);
	
	// Main panel sizer
	wxFlexGridSizer* panelSizer = new wxFlexGridSizer(1, 2, 8, 8);
	panelSizer->AddGrowableRow(0, 16);
	panelSizer->AddGrowableCol(1, 16);
	panel->SetSizer(panelSizer);
	
	// Sidebar sizers and controls
	wxFlexGridSizer* sidebarSizer = new wxFlexGridSizer(10, 1, 0, 0);
	sidebarSizer->AddGrowableRow(0, 16);
	sidebarSizer->AddGrowableRow(1, 0);
	sidebarSizer->AddGrowableRow(2, 0);
	sidebarSizer->AddGrowableRow(3, 0);
	sidebarSizer->AddGrowableRow(4, 0);
	sidebarSizer->AddGrowableRow(5, 0);
	sidebarSizer->AddGrowableRow(6, 0);
	sidebarSizer->AddGrowableRow(7, 0);
	sidebarSizer->AddGrowableRow(8, 0);
	sidebarSizer->AddGrowableRow(9, 0);
	
	panelSizer->Add(sidebarSizer, 1, wxEXPAND);
	
	sidebarSizer->Add(list, 1, wxEXPAND);
	
	sidebarSizer->AddSpacer(4);
	
	wxBoxSizer* storageControlSizer = new wxBoxSizer(wxHORIZONTAL);
	sidebarSizer->Add(storageControlSizer, 1, wxEXPAND | wxBOTTOM);
	storageControlSizer->Add(addImagesButton, 1, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	storageControlSizer->Add(removeImagesButton, 1, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	
	wxBoxSizer* activeImagesControlSizer = new wxBoxSizer(wxHORIZONTAL);
	sidebarSizer->Add(activeImagesControlSizer, 1, wxEXPAND | wxBOTTOM);
	activeImagesControlSizer->Add(activateImagesButton, 1, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	
	sidebarSizer->AddSpacer(16);
	
	wxBoxSizer* toleranceControlText = new wxBoxSizer(wxHORIZONTAL);
	sidebarSizer->Add(toleranceControlText, 1, wxEXPAND | wxBOTTOM);
	toleranceControlText->Add(toleranceText, 1, wxEXPAND | wxALIGN_TOP, 4);
	
	wxBoxSizer* toleranceControlSizer = new wxBoxSizer(wxHORIZONTAL);
	sidebarSizer->Add(toleranceControlSizer, 1, wxEXPAND | wxBOTTOM);
	toleranceControlSizer->Add(toleranceSlider, 2, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	toleranceControlSizer->Add(toleranceSliderValue, 1, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	
	sidebarSizer->AddSpacer(16);
	
	wxBoxSizer* modeControlText = new wxBoxSizer(wxHORIZONTAL);
	sidebarSizer->Add(modeControlText, 1, wxEXPAND | wxBOTTOM);
	modeControlText->Add(comparisonText, 1, wxEXPAND | wxALIGN_TOP, 4);
	
	wxBoxSizer* modeControlSizer = new wxBoxSizer(wxHORIZONTAL);
	sidebarSizer->Add(modeControlSizer, 1, wxEXPAND | wxBOTTOM);
	modeControlSizer->Add(modeSelector, 1, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	modeControlSizer->Add(compareImagesButton, 1, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	
	// Result view area
	tabsNotebook = new wxNotebook(panel, TAB_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxNB_BOTTOM);
	//tabsNotebook->InvalidateBestSize();
	wxBoxSizer* container = new wxBoxSizer(wxVERTICAL);
	container->Add(tabsNotebook, 1, wxEXPAND);
	panelSizer->Add(container, 1, wxEXPAND);

	generateTabs();
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
		// Do not try to re-add images. While the storage does not do that, the list does.
		// While this might not be the most elegant way, I feel that is best, between filtering the list
		// or regenerating the list from scratch every time.
		if (!model.getImage(*iterator)) {
			try {
				controller.loadImage(*iterator);
			} catch (ImageLoaderException& error) {
				pathsNotLoaded.Add(*iterator);
				continue;
			}
		
			list->InsertItem(0, *iterator);
		}
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
	bool activeImageAffected = false;
	
	while ((item = list->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != -1) {
		if (activeImages.Index(list->GetItemText(item)) != wxNOT_FOUND) {
			activeImages.Remove(list->GetItemText(item));
			activeImageAffected = true;
		}
		controller.removeImage(list->GetItemText(item));
		
		list->DeleteItem(item);
	}
	
	if (activeImageAffected) {
		markTabsForUpdate();
		updateSelectedTab();
	}
}

void View::activateSelectedImages(wxCommandEvent& event) {
	// If there are already two active images, moving the selection will deselect the currently active ones.
	if (activeImages.GetCount() > 1 || list->GetSelectedItemCount() > 1) {
		long item = -1;
		while ((item = list->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_DONTCARE)) != -1) {
			if (list->GetItemText(item, 1).IsSameAs("*")){
				list->SetItem(item, 1, "");
			}
		}
		
		activeImages.Empty();
		controller.removeCachedDifferences();
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
	
	// Update the selected tab immmediately and mark the others for update.
	markTabsForUpdate();
	updateSelectedTab();
}

void View::compareImages(wxCommandEvent& event) {
	wxString mode = modeSelector->GetStringSelection();
	double tolerance = toleranceSlider->GetValue() / 1000.0;
	
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
		
		// Update the selected tab immmediately and mark the others for update.
		markTabsForUpdate();
		updateSelectedTab();
	} catch (ImageGeometryException& error) {
		wxMessageBox("Causa: geometria diversa. \nE' necessario che le immagini abbiano altezze e larghezze uguali",
						"Impossibile confrontare le immagini scelte", wxOK | wxICON_EXCLAMATION);
	}
}

void View::update(int eventCode) {
	// TODO: Move event-related code here!
}

void View::generateTabs() {
	OriginalViewTab* originalTab = new OriginalViewTab(tabsNotebook);
	tabsNotebook->AddPage(originalTab, "Immagini originali", true);
	
	DiffListTab* diffTab = new DiffListTab(tabsNotebook);
	tabsNotebook->AddPage(diffTab, "Lista di differenze");
	
	LayerTab* layerTab = new LayerTab(tabsNotebook);
	tabsNotebook->AddPage(layerTab, "Vista a livelli");
	
	HeatmapTab* heatmapTab = new HeatmapTab(tabsNotebook);
	tabsNotebook->AddPage(heatmapTab, "Heatmap");
}

void View::markTabsForUpdate() {
	for (int i = 0; i < tabsNotebook->GetPageCount(); i++) {
		// If the page currently pointed is not a ViewTab for some reason, then dynamic_cast returns a nullptr.
		ViewTab* tab = dynamic_cast<ViewTab*>(tabsNotebook->GetPage(i));
		if (tab != nullptr) {
			tab->markForUpdate();
		}
	}
}

void View::updateSelectedTab() {
	// No need to check if GetCurrentPage is not null,
	// ad dynamic_cast will just cast the nullptr to a nullptr of the desired type
	ViewTab* tab = dynamic_cast<ViewTab*>(tabsNotebook->GetCurrentPage());
	if (tab != nullptr) {
		wxString path1 = activeImages.GetCount() > 0 ? activeImages[0] : "";
		wxString path2 = activeImages.GetCount() > 1 ? activeImages[1] : "";
		tab->update(model.getDifferences(), path1, model.getImage(path1), path2, model.getImage(path2));
		tab->FitInside();
	}

}

void View::onTabChanged(wxBookCtrlEvent& event) {
	updateSelectedTab();
}

void View::onSliderUpdate(wxCommandEvent& event) {
	wxString stringValue;
	stringValue << (toleranceSlider->GetValue() / 10.0);
	toleranceSliderValue->SetValue(stringValue + " %");
}

void View::onAbout(wxCommandEvent& event) {
	// TODO: Implement a little message box with some info about the project itself
}

void View::onExit(wxCommandEvent& event) {
	Close(true);
}
