//
#include "gtest/gtest.h"
#include "../src/view/View.h"
#include "../src/controller/Controller.h"
#include "../src/model/Model.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class ViewSuite : public ::testing::Test, public wxApp  {
protected:
	virtual void SetUp() {
	}
};


//

