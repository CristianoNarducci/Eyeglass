//
#include "gtest/gtest.h"
#include "../src/model/Model.h"
#include "../src/model/DiffContainer.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class ModelSuite : public ::testing::Test{
	/* In the SetUp() function a wxArrayString are loaded with stock images and insert in the model's storage.
	 * There is a DiffContainer object  where are stored the result, in tuple form, of comparison both in RGB,HSV and in Alpha*/
protected:
	virtual void SetUp(){
		images.Add(_("/home/cristiano/Scrivania/proge/Eyeglass/test/testImages/car.png"));
		images.Add(_("/home/cristiano/Scrivania/proge/Eyeglass/test/testImages/cat.jpg"));
		images.Add(_("/home/cristiano/Scrivania/proge/Eyeglass/test/testImages/dog.jpg"));
		images.Add(_("/home/cristiano/Scrivania/proge/Eyeglass/test/testImages/river.jpeg"));
		images.Add(_("/home/cristiano/Scrivania/proge/Eyeglass/test/testImages/house.jpeg"));
		images.Add(_("/home/cristiano/Scrivania/proge/Eyeglass/test/testImages/testAlpha.png"));
		images.Add(_("/home/cristiano/Scrivania/proge/Eyeglass/test/testImages/testAlpha2.png"));
		for (int i = 0; i < images.size(); i++) {
			model.loadImage(images[i]);
		}
	}
	DiffContainer differencesTest;
	Model model;
	wxArrayString images;
	wxString testAlpha1= "/home/cristiano/Scrivania/proge/Eyeglass/test/testImages/testAlpha.png";
	wxString testAlpha2 = "/home/cristiano/Scrivania/proge/Eyeglass/test/testImages/testAlpha2.png";

};
/*This test checks if the function removeCacheDifference
 * if the method works the tuple of HSV.RGB and alpha will result empty*/
TEST_F(ModelSuite,testRemoveDiff){
	model.removeCachedDifferences();
	EXPECT_TRUE(model.getDifferences().HSV.empty());
	EXPECT_TRUE(model.getDifferences().RGB.empty());
	EXPECT_TRUE(model.getDifferences().alpha.empty());
}
	/*This test verify that the remove imageModel function works.
	 * In the model, if a image is not stored, it return a nullptr pointer,otherwise the wxImage object*/
TEST_F(ModelSuite,testRemove){
	model.removeImage(images[0]);
	EXPECT_EQ(nullptr,model.getImage(images[0]));
}
	/*This test check that the load image function works.
	 * The function acts the opposite of the previous one, so if an image is loaded inside, it return the wxImage, otherwise
	 * nullptr pointer*/
TEST_F(ModelSuite,testLoad){
	model.loadImage(_("/home/cristiano/Scrivania/proge/Eyeglass/test/testImages/plane.jpg"));
	EXPECT_NE(nullptr,model.getImage("/home/cristiano/Scrivania/proge/Eyeglass/test/testImages/plane.jpg"));
}
	/*This test verify that the comparison with Alpha works
	 * it control the cartesian position of the pixel and the result of difference*/
TEST_F(ModelSuite,testAlpha){
	model.compareAlpha(testAlpha1,testAlpha2,0);
	differencesTest = model.getDifferences();
	int x = std::get<0>(*(differencesTest.alpha.begin()));
	int y = std::get<1>(*(differencesTest.alpha.begin()));
	double result = std::get<2>(*(differencesTest.alpha.begin()));
	EXPECT_EQ(0,x);
	EXPECT_EQ(0,y);
	EXPECT_DOUBLE_EQ(0.30196078431372547,result);


}
/*This test verify that the comparison with RGB works
	 * it control the cartesian position of the pixel and the result of difference*/
TEST_F(ModelSuite,testRGB){
	model.compareRGB(testAlpha1,testAlpha2,0);
	differencesTest = model.getDifferences();
	int x = std::get<0>(*(differencesTest.RGB.begin()));
	int y = std::get<1>(*(differencesTest.RGB.begin()));
	double result = std::get<2>(*(differencesTest.RGB.begin()));
	EXPECT_EQ(0,x);
	EXPECT_EQ(0,y);
	EXPECT_DOUBLE_EQ(0.36078431372549019,result);
	model.removeCachedDifferences();


}
/*This test verify that the comparison with HSV works
	 * it control the cartesian position of the pixel and the result of difference*/
TEST_F(ModelSuite,testHSV){
	model.compareHSV(testAlpha1,testAlpha2,0);
	differencesTest = model.getDifferences();
	int x = std::get<0>(*(differencesTest.HSV.begin()));
	int y =std::get<1>(*(differencesTest.HSV.begin()));
	double result = std::get<2>(*(differencesTest.HSV.begin()));
	EXPECT_EQ(0,x);
	EXPECT_EQ(0,y);
	EXPECT_DOUBLE_EQ(0.38373983739837403,result);
}
//

