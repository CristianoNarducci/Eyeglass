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

class controller: public AbstractController {
protected:
    AbstractModel& model;

public:
    void removeImages(wxArrayString paths) override;

    void loadImages(wxArrayString paths) override;

    void compareRGB(wxString path1, wxString path2, double tolerance) override;

    void compareAlpha(wxString path1, wxString path2, double tolerance) override;

    void compareHSV(wxString path1, wxString path2, double tolerance) override;
};


#endif //EYEGLASS_CONTROLLER_H
