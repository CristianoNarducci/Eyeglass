#include "ViewTab.h"

ViewTab::ViewTab(wxWindow* parent): wxWindow(parent, wxID_ANY) {};

void ViewTab::markForUpdate() {
	markedForUpdate = true;
}
