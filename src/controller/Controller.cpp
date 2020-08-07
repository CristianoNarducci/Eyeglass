//
// Created by cristiano on 17/07/20.
//

#include "Controller.h"

Controller::Controller(AbstractModel& model) : model(model){}

void Controller::removeImages(wxArrayString paths) {

    for(int it = 0; it < paths.size();it++){
        model.removeImage(paths[it]);
    }

}

void Controller::prova(){
	std::cout<< "arrivo"<<std::endl;
}
void Controller::loadImages(wxArrayString paths) {

    /*for(int it = 0; it < paths.size(); it++){
        model.loadImage(paths[it]);
    }*/
	std::cout<< "arrivo caricamento"<<std::endl;

}

void Controller::compareRGB(wxString& path1, wxString& path2, double tolerance) {
	std::cout<<"PAPERINO"<<std::endl;
}

void Controller::compareAlpha(wxString path1, wxString path2, double tolerance) {
	std::cout<<"PAPERINO"<<std::endl;
}

void Controller::compareHSV(wxString path1, wxString path2, double tolerance) {
	std::cout<<"PLUTO"<<std::endl;
}
