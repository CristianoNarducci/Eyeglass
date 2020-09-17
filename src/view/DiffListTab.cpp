#include "DiffListTab.h"

DiffListTab::DiffListTab(wxWindow* parent): ViewTab(parent) {
	wxFlexGridSizer* panelSizer = new wxFlexGridSizer(1, 1, 0, 0);
	panelSizer->AddGrowableRow(0, 16);
	panelSizer->AddGrowableCol(0, 16);
	this->SetSizer(panelSizer);
	
	list = new wxListView(this, wxID_ANY);
	list->InsertColumn(0, "Asse X", wxLIST_FORMAT_LEFT, 120);
	list->InsertColumn(1, "Asse Y", wxLIST_FORMAT_LEFT, 120);
	list->InsertColumn(2, "Percentuale di differenza", wxLIST_FORMAT_LEFT, 200);
	panelSizer->Add(list, 1, wxEXPAND);
}

void DiffListTab::update(const std::list<PixelDiff*>& diffContainer, wxString path1, const wxImage* image1, 
																	wxString path2, const wxImage* image2) {
	if (markedForUpdate) {
		std::cout << std::string(path1.mb_str()) << std::endl;
		std::cout << std::string(path2.mb_str()) << std::endl;
		
		list->DeleteAllItems();
		
		if (image1 != nullptr && image2 != nullptr) {
			long itemIndex = 0;
			long nextIndex;
			for (auto it = diffContainer.begin(); it != diffContainer.end(); it++) {
				// x
				wxString xString;
				xString << (*it)->x;
				nextIndex = list->InsertItem(itemIndex, xString);
				
				// y
				wxString yString;
				yString << (*it)->y;
				list->SetItem(itemIndex, 1, yString);
				
				// diff
				wxString diffString;
				diffString << ((*it)->percentual_diff * 100);
				list->SetItem(itemIndex, 2, diffString + " %");
				
				itemIndex = nextIndex;
			}
		}
		
		markedForUpdate = false;
	}
}
