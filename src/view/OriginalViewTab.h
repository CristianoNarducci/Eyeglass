//
// Created by cristiano on 17/07/20.
//

#ifndef EYEGLASS_ORIGINALVIEWTAB_H
#define EYEGLASS_ORIGINALVIEWTAB_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include "View.h"
#include "ViewTab.h"

#endif

class OriginalViewTab: public ViewTab {
protected:
    wxStaticBitmap* images;
    View& view;

public:

    void reset() override;

    void generateDiffView() override;

};


#endif //EYEGLASS_ORIGINALVIEWTAB_H
