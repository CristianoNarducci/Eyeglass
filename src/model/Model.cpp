//
// Created by cristiano on 20/07/20.
//

#include "Model.h"

Model::Model(){}

void Model::loadImage(wxString path) {

}

void Model::removeImage(wxString path) {

}

void Model::removeAllImages(wxArrayString paths) {

}

const wxImage Model::getImage(wxString path) {
    return wxImage();
}

const std::map<wxString, wxImage> Model::getAllImages() {
    return imageStorage;
}

double Model::comparePixelAlpha(const char alphaValue1, const char alphaValue2, const double tolerance) {
    return 0;
}

double Model::comparePixelRGB(wxImage::RGBValue RGBValue1, wxImage::RGBValue RGBValue2, const double tolerance) {
    return 0;
}

double Model::comparePixelHSV(wxImage::HSVValue HSVValue1, wxImage::HSVValue HSVValue2, const double tolerance) {
    return 0;
}

void Model::compareAlpha(wxString path1, wxString path2, const double tolerance) {

}

void Model::compareRGB(wxString path1, wxString path2, const double tolerance) {

}

void Model::compareHSV(wxString path1, wxString path2, const double tolerance) {

}

const DiffResult Model::getDifferences(wxString path1, wxString path2) {
    return DiffResult();
}

void Model::removeCachedDifferences(wxString path1, wxString path2) {

}

void Model::removeAllCachedDifferences() {

}

void Model::registerObserver(Observer* observer) {
    observers.push_back(observer);
}

void Model::removeObserver(Observer* observer) {
    std::vector<Observer*>::iterator iter = observers.begin();
    while(iter != observers.end())
    {
        if(*iter == observer)
        {
            iter = observers.erase(iter);
        }
        else
        {
            ++iter;
        }
    }

}

void Model::notify(int eventCode) {

}

