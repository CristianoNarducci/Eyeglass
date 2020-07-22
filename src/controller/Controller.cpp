//
// Created by cristiano on 17/07/20.
//

#include "Controller.h"

Controller::Controller(AbstractModel& model): model(model){}

void Controller::removeImages(wxArrayString paths) {

    for(int it = 0; it < paths.size();it++){
        model.removeImage(paths[it]);
    }

}

void Controller::loadImages(wxArrayString paths) {

    for(int it = 0; it < paths.size(); it++){
        model.loadImage(paths[it]);
    }
}

void Controller::compareRGB(wxString path1, wxString path2, double tolerance) {

}

void Controller::compareAlpha(wxString path1, wxString path2, double tolerance) {

}

void Controller::compareHSV(wxString path1, wxString path2, double tolerance) {

}
