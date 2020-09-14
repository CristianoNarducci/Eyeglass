#include "Controller.h"

Controller::Controller(Model& model): model(model) {}

void Controller::removeImages(wxArrayString paths) {
    for(int it = 0; it < paths.GetCount(); it++){
        model.removeImage(paths[it]);
    }
}
void Controller::loadImages(wxArrayString paths) {
    for(int it = 0; it < paths.GetCount(); it++){
        model.loadImage(paths[it]);
    }
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
