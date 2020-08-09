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
		Model* model = new Model();
		Controller* controller = new Controller(*model);
		View* eyeglass=new View("Eyeglass",wxPoint(300,500),wxSize(1440,720),*model,*controller);
        eyeglass->Show(true);


		return true;
	}
};
wxIMPLEMENT_APP(App);