#ifndef EYEGLASS_DIFFLISTTAB_H
#define EYEGLASS_DIFFLISTTAB_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "ViewTab.h"
#include "View.h"

#include <wx/listctrl.h>

class DiffListTab: public ViewTab {
protected:
	wxListView* diffListView;
	View& view;

public:
	void reset() override;
	void generateView() override;
};

#endif
