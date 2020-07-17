//
// Created by cristiano on 17/07/20.
//

#ifndef EYEGLASS_SIDEBYSIDETAB_H
#define EYEGLASS_SIDEBYSIDETAB_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include "ViewTab.h"
#include "AbstractView.h"

#endif

class SideBySideTab: public ViewTab {
protected:
    wxStaticBitmap* images;
    AbstractView& view;

public:
    void reset() override;

    void generateDiffView() override;
};


#endif //EYEGLASS_SIDEBYSIDETAB_H
