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
#include <wx/filename.h>
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
	/*
	 * Shows a file picker and tries to load the chosen files. If something goes wrong, Model signals it and this shows a dialog.
	 */
	void loadImages(wxCommandEvent& event);
	
	/*
	 * Tells model to remove from storage, the images selected from the list.
	 * If an active image was affected, its path is removed from the list of active images and the others are renumbered.
	 * In that case, every tab is marked for update and the one in view is instantly updated.
	 */
	void removeImages(wxCommandEvent& event);
	
	/*
	 * Activates the images selected from the list.
	 * If there were no previously active images, the first two are activated.
	 * In case there was only an active image and only one image is selected, that selected image is activated.
	 * Otherwise, the previously active images are deactivated and the new selection becomes active, based on the previously stated rules.
	 * This marks every tab for update and instantly refreshes the active tab.
	 */
	void activateSelectedImages(wxCommandEvent& event);
	
	/*
	 * Reassigns the correct number to each active image in list.
	 */
	void renumberActiveImages();
	
	/*
	 * Tells the model to start the comparison with the given settings and images.
	 * If the model throws an exception regarding different geometry of the active images, a dialog is shown.
	 */
	void compareImages(wxCommandEvent& event);
	
	/*
	 * Initializes each tab and adds it to the tabsNotebook.
	 */
	void generateTabs();
	
	/*
	 * Calls each tab's markForUpdate method, telling the tabs to refresh their content on the next update call.
	 */
	void markTabsForUpdate();
	
	/*
	 * Updates only the currently selected tab with the currently active images and the differences calculated.
	 * The combination of markForUpdate and updateSelectedTab creates a deferred loading mechanism.
	 */
	void updateSelectedTab();
	
	/*
	 * Handles the change of shown tab, telling the new tab to refresh itself.
	 */
	void onTabChanged(wxBookCtrlEvent& event);
	
	/*
	 * Refreshes the tolerance textual indicator when the slider changes.
	 */
	void onSliderUpdate(wxCommandEvent& event);
	
	/*
	 * Displays a dialog with some informations on the program.
	 */
	void onAbout(wxCommandEvent& event);
	
	/*
	 * Shows a little guide for the program.
	 */
	void onHelp(wxCommandEvent& event);
	
	void onExit(wxCommandEvent& event);
	
	/*
	 * The main application panel, where each element resides.
	 */
	wxWindow* panel;
	
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
