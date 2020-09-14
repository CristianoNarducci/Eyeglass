//
#include "gtest/gtest.h"
#include "../src/utils/ImageUtils.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class ImageUtilsSuite : public ::testing::Test{

protected:
	virtual void SetUp(){
		image1.LoadFile(_("/home/cristiano/Scrivania/proge/Eyeglass/test/testImages/house.jpeg"));
		image2.LoadFile(_("/home/cristiano/Scrivania/proge/Eyeglass/test/testImages/river.jpeg"));
	}
	ImageUtils utility;
	wxImage image1;
	wxImage image2;
};
TEST_F(ImageUtilsSuite ,TestGeometry){
	ASSERT_FALSE(utility.isGeometryEqual(image1,image2));
	ASSERT_TRUE(utility.isGeometryEqual(image1,image1));
}

TEST_F(ImageUtilsSuite,TestAlphaPixel){
	EXPECT_EQ(1,utility.comparePixelAlpha(0,255,0));
}
//

