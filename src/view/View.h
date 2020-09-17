#ifndef EYEGLASS_VIEW_H
#define EYEGLASS_VIEW_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/listctrl.h>
#include <wx/notebook.h>
#include <wx/bookctrl.h>
#include <wx/textctrl.h>

#include "../utils/Observer.h"
#include "../model/Model.h"
#include "../controller/Controller.h"

#include "ViewTab.h"
#include "OriginalViewTab.h"
#include "DiffListTab.h"
#include "SideBySideTab.h"
#include "LayerTab.h"
#include "HeatmapTab.h"

#include "../exception/ImageLoaderException.h"
#include "../exception/ImageGeometryException.h"

/*
 * The view of the program. The controls are implemented here, while images and results visualization
 * is responsibility of a list of "sub-views" which can be toggled at will.
 */
class View: public wxFrame, public Observer {
public:
	View(const std::string title, const wxPoint& pos, const wxSize& size, Model& model, Controller& controller);
	
	void update(int eventCode) override;
	
	wxDECLARE_EVENT_TABLE();
	
	virtual ~View() {};

protected:
	void loadImages(wxCommandEvent& event);
	void removeImages(wxCommandEvent& event);
	void activateSelectedImages(wxCommandEvent& event);
	void compareImages(wxCommandEvent& event);
	void generateTabs();
	void markTabsForUpdate();
	void updateSelectedTab();
	void onTabChanged(wxBookCtrlEvent& event);
	void onSliderUpdate(wxCommandEvent& event);
	void onAbout(wxCommandEvent& event);
	void onExit(wxCommandEvent& event);
	
	/*
	 * The main application panel, where each element resides.
	 */
	wxScrolledWindow* panel;
	
	/*
	 * The top menu bar with its clickable dropdown menus.
	 */
	wxMenuBar* menu;
	wxMenu* appDropdownMenu;
	
	/*
	 * The storage and comparison controls.
	 */
	wxListView* list;
	wxButton* addImagesButton;
	wxButton* removeImagesButton;
	wxButton* activateImagesButton;
	wxButton* compareImagesButton;
	wxSlider* toleranceSlider;
	wxComboBox* modeSelector;
	
	/*
	 * Labels and indicators.
	 */
	wxTextCtrl* toleranceSliderValue;
	
	wxStaticText* toleranceText;
	wxStaticText* comparisonText;
	
	/*
	 * Holds the paths of the currently active images. It also serves as a counter for them.
	 */
	wxArrayString activeImages;
	
	/*
	 * All the viewtabs this program can use to display the results of a comparison.
	 * The "visual" container is kind of a tab chooser, something like a web browser.
	 */
	wxNotebook* tabsNotebook;
	
	Model& model;
	Controller& controller;
};

#endif
