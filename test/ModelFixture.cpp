//
#include "gtest/gtest.h"
#include "../src/model/Model.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class ModelSuite : public ::testing::Test{
protected:
	virtual void SetUp(){
		images.Add(_("/home/cristiano/Scrivania/proge/Eyeglass/test/testImages/car.png"));
		images.Add(_("/home/cristiano/Scrivania/proge/Eyeglass/test/testImages/cat.jpg"));
		images.Add(_("/home/cristiano/Scrivania/proge/Eyeglass/test/testImages/dog.jpg"));
		images.Add(_("/home/cristiano/Scrivania/proge/Eyeglass/test/testImages/river.jpeg"));
		images.Add(_("/home/cristiano/Scrivania/proge/Eyeglass/test/testImages/house.jpeg"));
		for (int i = 0; i < images.size(); i++) {
			model.loadImage(images[i]);
		}
	}
	Model model;
	wxArrayString images;
};
TEST_F(ModelSuite,testRemove){
	model.removeImage(images[0]);
	EXPECT_EQ(nullptr,model.getImage(images[0]));
}
TEST_F(ModelSuite,testLoad){
	model.loadImage(_("/home/cristiano/Scrivania/proge/Eyeglass/test/testImages/plane.jpg"));
	EXPECT_NE(nullptr,model.getImage("/home/cristiano/Scrivania/proge/Eyeglass/test/testImages/plane.jpg"));
}

//

