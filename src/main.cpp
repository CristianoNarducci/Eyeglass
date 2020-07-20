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
		
		// Model model;
		// Controller controller;
		// View view;
	}
};
