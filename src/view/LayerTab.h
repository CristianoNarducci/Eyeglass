//
// Created by cristiano on 17/07/20.
//

#ifndef EYEGLASS_LAYERTAB_H
#define EYEGLASS_LAYERTAB_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include "View.h"
#include "ViewTab.h"

#endif

class LayerTab:public ViewTab {
protected:
    wxStaticBitmap* images;
    View& view;

public:
    void reset() override;

    void generateDiffView() override;
};


#endif //EYEGLASS_LAYERTAB_H
