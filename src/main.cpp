#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "model/Model.h"
#include "controller/Controller.h"
#include "view/View.h"
class App : public wxApp {
public:
	virtual bool OnInit() {
		wxInitAllImageHandlers();
		Model luigi;
		Controller pippo(luigi);
		View* appe=new View("Eyeglass",wxPoint(300,500),wxSize(800,600),luigi,pippo);
        appe->Show(true);
		// Model model;
		// Controller controller;
		// View view;

		return true;
	}
};
wxIMPLEMENT_APP(App);