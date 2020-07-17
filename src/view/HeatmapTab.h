//
// Created by cristiano on 17/07/20.
//

#ifndef EYEGLASS_HEATMAPTAB_H
#define EYEGLASS_HEATMAPTAB_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include "ViewTab.h"
#include "AbstractView.h"

#endif

class HeatmapTab: public ViewTab {
protected:
    wxStaticBitmap* images;
    AbstractView& view;

public:
    void reset() override;

    void generateDiffView() override;
};


#endif //EYEGLASS_HEATMAPTAB_H
