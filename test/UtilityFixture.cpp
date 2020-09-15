//
#include "gtest/gtest.h"
#include "../src/utils/ImageUtils.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
class ImageUtilsSuite : public ::testing::Test{
	/* In the SetUp() function two stock images are loaded as example
	 * There is a ImageUtils object for function calling in the fixture's test */
protected:
	virtual void SetUp(){
		image1.LoadFile(_("/home/cristiano/Scrivania/proge/Eyeglass/test/testImages/house.jpeg"));
		image2.LoadFile(_("/home/cristiano/Scrivania/proge/Eyeglass/test/testImages/river.jpeg"));
	}
	ImageUtils utility; //ImageUtils object for function calling
	wxImage image1;		//stock images
	wxImage image2;
};
/*This test verify that the function isGeometryEqual return the right results
 * If the size of two images are not the same, it return false, otherwise it return true*/
TEST_F(ImageUtilsSuite ,TestGeometry){
	ASSERT_FALSE(utility.isGeometryEqual(image1,image2)); //sizes are different
	ASSERT_TRUE(utility.isGeometryEqual(image1,image1));	//sizes are equals
}
/*This test verify that the function comparePixelAlpha return the right results.
 * If the percentage difference are minus than the tolerance it return the value 0, otherwise it return the percentage*/
TEST_F(ImageUtilsSuite,TestAlphaPixel){
	EXPECT_DOUBLE_EQ(0.039215686274509803,utility.comparePixelAlpha(80,90,0));
	EXPECT_EQ(1,utility.comparePixelAlpha(0,255,0));
}
/*This test check that the function comparePixelRGB return the results as excepted.
 * If the percentage difference are minus than the tolerance it return the value 0,otherwise it act like the previous function*/
TEST_F(ImageUtilsSuite,TestRGBPixel){
	EXPECT_DOUBLE_EQ(0.33333333333333331,utility.comparePixelRGB((0,0,0),(0,0,255),0));
	EXPECT_DOUBLE_EQ(0,utility.comparePixelRGB((255,50,60),(78,22,120),1.0)); //percentage max so if not equals it return 0
}
/*This test check that the function comparePixelRGB return the results as excepted.
 * If the percentage difference are minus than the tolerance it return the value 0,otherwise it act like the previous function*/
TEST_F(ImageUtilsSuite,TestHSVPixel){
	EXPECT_DOUBLE_EQ(0.16,utility.comparePixelHSV((0.8,0.47,0.12),(0.77,0.21,0.36),0));
	EXPECT_DOUBLE_EQ(0,utility.comparePixelHSV((0.47,0.33,0.88),(0.25,0.74,0.63),1.0)); //percentage max so if not equals it return 0
}
//