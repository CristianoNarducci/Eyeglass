#ifndef EYEGLASS_VIEW_H
#define EYEGLASS_VIEW_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <memory>

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
	std::shared_ptr<wxWindow> panel;
	//wxWindow* panel;
	
	/*
	 * The top menu bar with its clickable dropdown menus.
	 */
	std::shared_ptr<wxMenuBar> menu;
	std::shared_ptr<wxMenu> appDropdownMenu;
	
	/*
	 * The storage and comparison controls.
	 */
	std::shared_ptr<wxListView> list;
	std::shared_ptr<wxButton> addImagesButton;
	std::shared_ptr<wxButton> removeImagesButton;
	std::shared_ptr<wxButton> activateImagesButton;
	std::shared_ptr<wxButton> compareImagesButton;
	std::shared_ptr<wxSlider> toleranceSlider;
	std::shared_ptr<wxComboBox> modeSelector;
	
	/*
	 * Labels and indicators.
	 */
	std::shared_ptr<wxTextCtrl> toleranceSliderValue;
	
	std::shared_ptr<wxStaticText> toleranceText;
	std::shared_ptr<wxStaticText> comparisonText;
	
	/*
	 * Holds the paths of the currently active images. It also serves as a counter for them.
	 */
	wxArrayString activeImages;
	
	/*
	 * All the viewtabs this program can use to display the results of a comparison.
	 * The "visual" container is kind of a tab chooser, something like a web browser.
	 */
	std::shared_ptr<wxNotebook> tabsNotebook;
	
	Model& model;
	Controller& controller;
};

#endif
