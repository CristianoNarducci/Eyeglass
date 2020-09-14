//
// Created by cristiano on 17/07/20.
//

#ifndef EYEGLASS_CONTROLLER_H
#define EYEGLASS_CONTROLLER_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "../model/Model.h"

class Controller {
protected:
    Model& model;

public:

    Controller(Model& model);
    /*Remove images from the storage
     * It can remove multiple image at once*/
    virtual void removeImages(wxArrayString paths);

    /*Load images on the storage
     * It can load multiple images at once*/
    virtual void loadImages(wxArrayString paths);

    /*Compare the active images with RGB mode
     * If the result doesnt reach the tolerance, it consider the images equals*/
    virtual void compareRGB(wxString path1, wxString path2, double tolerance);

    /*Compare the active images with Alpha method
     * If the result doesnt reach the tolerance,it consider the images equals*/
    virtual void compareAlpha(wxString path1, wxString path2, double tolerance);

    /*Compare the active images with HSV method
     * If the result doesnt reach the tolerance,it consider the images equals*/
    virtual void compareHSV(wxString path1, wxString path2, double tolerance);
};


#endif //EYEGLASS_CONTROLLER_H
