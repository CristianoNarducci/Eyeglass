#include "Controller.h"

Controller::Controller(Model& model): model(model) {}


void Controller::removeCachedDifferences() {
	model.removeCachedDifferences();
}

void Controller::removeImage(wxString path) {
	model.removeImage(path);
}
void Controller::loadImage(wxString path) {
	model.loadImage(path);
}
void Controller::compareRGB(wxString path1, wxString path2, double tolerance) {
	model.compareRGB(path1, path2, tolerance);
}
void Controller::compareAlpha(wxString path1, wxString path2, double tolerance) {
	model.compareAlpha(path1, path2, tolerance);
}
void Controller::compareHSV(wxString path1, wxString path2, double tolerance) {
	model.compareHSV(path1, path2, tolerance);
}
