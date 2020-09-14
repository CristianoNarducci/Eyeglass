#include "gtest/gtest.h"
#include "../src/utils/ImageUtils.h"
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
int main(int argc, char** argv) {
	wxInitAllImageHandlers();
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
