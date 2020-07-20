//
// Created by cristiano on 17/07/20.
//

#ifndef EYEGLASS_CONTROLLER_H
#define EYEGLASS_CONTROLLER_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "AbstractController.h"
#include "../models/AbstractModel.h"
class controller: public AbstractController {
protected:
    AbstractModel& model;

public:

    /*Remove images from the storage
     * It can remove multiple image at once*/
    void removeImages(wxArrayString paths) override;

    /*Load images on the storage
     * It can load multiple images at once*/
    void loadImages(wxArrayString paths) override;

    /*Compare the active images with RGB mode
     * If the result doesnt reach the tolerance, it consider the images equals*/
    void compareRGB(wxString path1, wxString path2, double tolerance) override;

    /*Compare the active images with Alpha method
     * If the result doesnt reach the tolerance,it consider the images equals*/
    void compareAlpha(wxString path1, wxString path2, double tolerance) override;

    /*Compare the active images with HSV method
     * If the result doesnt reach the tolerance,it consider the images equals*/
    void compareHSV(wxString path1, wxString path2, double tolerance) override;
};


#endif //EYEGLASS_CONTROLLER_H
