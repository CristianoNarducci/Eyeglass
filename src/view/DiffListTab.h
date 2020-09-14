//
// Created by cristiano on 17/07/20.
//

#ifndef EYEGLASS_DIFFLISTTAB_H
#define EYEGLASS_DIFFLISTTAB_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "AbstractView.h"
#include "ViewTab.h"
#include <wx/listctrl.h>

class DiffListTab:public ViewTab {
protected:
    wxListView* diffListView;
    AbstractView& view;

public:
    void reset() override;

    void generateDiffView() override;
};


#endif //EYEGLASS_DIFFLISTTAB_H
