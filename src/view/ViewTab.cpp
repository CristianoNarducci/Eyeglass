#include "ViewTab.h"

ViewTab::ViewTab(wxWindow* parent): wxScrolledWindow(parent, wxID_ANY) {
	this->SetScrollRate(5,5);
}

void ViewTab::markForUpdate() {
	markedForUpdate = true;
}
