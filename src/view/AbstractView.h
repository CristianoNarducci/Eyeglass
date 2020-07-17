//
// Created by cristiano on 17/07/20.
//

#ifndef EYEGLASS_ABSTRACTVIEW_H
#define EYEGLASS_ABSTRACTVIEW_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "../models/AbstractModel.h"
class AbstractView
{
    virtual void removeImages(wxCommandEvent& event)=0;
    virtual void loadImages(wxCommandEvent& event)=0;
    virtual void activateSelectedImages(wxCommandEvent& event)=0;
    virtual void compareImages(wxCommandEvent& event)=0;
    virtual void resetTabs()=0;
    virtual AbstractModel& getModel()=0;
    virtual wxString getMode()=0;
    virtual wxString* getActiveImages()=0;
};

#endif //EYEGLASS_ABSTRACTVIEW_H
