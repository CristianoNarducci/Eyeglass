//
// Created by cristiano on 17/07/20.
//

#ifndef EYEGLASS_ABSTRACTCONTROLLER_H
#define EYEGLASS_ABSTRACTCONTROLLER_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
class AbstractController{

public:
    virtual void removeImages(wxArrayString paths)=0;
    virtual void loadImages(wxArrayString paths)=0;
    virtual void compareRGB(wxString& path1,wxString& path2,double tolerance)=0;
    virtual void compareAlpha(wxString path1,wxString path2,double tolerance)=0;
    virtual void compareHSV(wxString path1, wxString path2,double tolerance)=0;
    virtual void prova()=0;

};
#endif //EYEGLASS_ABSTRACTCONTROLLER_H
