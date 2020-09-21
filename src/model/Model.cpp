#include "Model.h"

Model::Model() {}

void Model::loadImage(wxString path) {
	wxImage image;
	
	if (!image.LoadFile(path)) {
		throw ImageLoaderException();
	}
	
	imageStorage.insert(std::make_pair(path, std::make_shared<wxImage>(image)));
}

void Model::removeImage(wxString path) {
	// Calls wxImage Destroy to deallocate the image memory.
	auto iter = imageStorage.find(path);
	if (iter != imageStorage.end()) {
		iter->second->Destroy();
		imageStorage.erase(path);
	}
}

const std::shared_ptr<const wxImage> Model::getImage(wxString path) {
	auto iter = imageStorage.find(path);
	if (iter != imageStorage.end()) {
		return iter->second;
	}
	
	return std::shared_ptr<const wxImage>(nullptr);
}

std::shared_ptr<std::list<wxString>> Model::getStoredPaths() {
	std::shared_ptr<std::list<wxString>> paths = std::make_shared<std::list<wxString>>();
	
	for (auto iter = imageStorage.begin(); iter != imageStorage.end(); iter++) {
		paths->push_back(iter->first);
	}
	
	return paths;
}

// An image without the alpha channel is interpreted as having every pixel alpha value set to 255
void Model::compareAlpha(wxString path1, wxString path2, double tolerance) {
	const std::shared_ptr<const wxImage> image1 = getImage(path1);
	const std::shared_ptr<const wxImage> image2 = getImage(path2);
	
	if (!image1) {
		throw std::invalid_argument("Could not find " + std::string(path1.mb_str()) + "in the image storage");
	}
	if (!image2) {
		throw std::invalid_argument("Could not find " + std::string(path2.mb_str()) + "in the image storage");
	}
	
	if (!ImageUtils::isGeometryEqual(*image1, *image2)) {
		throw ImageGeometryException();
	}
	
	removeCachedDifferences();
	
	// Alpha data is returned as an array of chars, one for pixel.
	// The reading key is top to bottom, left to right.
	unsigned char* image1_alpha = image1->GetAlpha();
	unsigned char* image2_alpha = image2->GetAlpha();
	
	// select the best mode based on how many images have alpha data.
	if (image1_alpha == nullptr) {
		if (image2_alpha != nullptr) {
			// image2 has alpha while image1 doesn't. Consider image1 as fully opaque.
			for (int y = 0; y < image1->GetHeight(); y++) {
				for (int x = 0; x < image1->GetWidth(); x++) {
					unsigned long i = y * image1->GetWidth() + x;
					double percentual_difference = ImageUtils::comparePixelAlpha(255, 
																				image2_alpha[i],
																				tolerance);
					if (percentual_difference > 0) {
						diffStorage.push_back(std::make_shared<PixelDiff>(x, y, percentual_difference));
					}
				}
			}
		}
		
		// If they both lack alpha data, there's nothing to push in the vector, so no else clause here.
	} else {
		if (image2_alpha == nullptr) {
			// image1 has alpha while image2 doesn't. Consider image2 as fully opaque.
			for (int y = 0; y < image1->GetHeight(); y++) {
				for (int x = 0; x < image1->GetWidth(); x++) {
					unsigned long i = y * image1->GetWidth() + x;
					double percentual_difference = ImageUtils::comparePixelAlpha(image1_alpha[i], 
																				255,
																				tolerance);
					if (percentual_difference > 0) {
						diffStorage.push_back(std::make_shared<PixelDiff>(x, y, percentual_difference));
					}
				}
			}
		} else {
			// both images have alpha data.
			for (int y = 0; y < image1->GetHeight(); y++) {
				for (int x = 0; x < image1->GetWidth(); x++) {
					unsigned long i = y * image1->GetWidth() + x;
					double percentual_difference = ImageUtils::comparePixelAlpha(image1_alpha[i], image2_alpha[i], tolerance);
					if (percentual_difference > 0) {
						diffStorage.push_back(std::make_shared<PixelDiff>(x, y, percentual_difference));
					}
				}
			}
		}
	}
	
	notify(8);
}

void Model::compareRGB(wxString path1, wxString path2, double tolerance) {
	const std::shared_ptr<const wxImage> image1 = getImage(path1);
	const std::shared_ptr<const wxImage> image2 = getImage(path2);
	
	if (!image1) {
		throw std::invalid_argument("Could not find " + std::string(path1.mb_str()) + "in the image storage");
	}
	if (!image2) {
		throw std::invalid_argument("Could not find " + std::string(path2.mb_str()) + "in the image storage");
	}
	
	if (!ImageUtils::isGeometryEqual(*image1, *image2)) {
		throw ImageGeometryException();
	}
	
	removeCachedDifferences();
	
	// The rgb data is returned as a char array which is made of alternating rgb triplets.
	// The reading key is top to bottom, left to right.
	// The order of the rgb chars is red, green, blue.
	unsigned char* image1_RGB = image1->GetData();
	unsigned char* image2_RGB = image2->GetData();
	
	for (int y = 0; y < image1->GetHeight(); y++) {
		for (int x = 0; x < image1->GetWidth(); x++) {
			unsigned long i = y * image1->GetWidth() + x;
			
			// Put the rgb separate chars in an envelope which represents a pixel
			wxImage::RGBValue image1_pixel(image1_RGB[i * 3], image1_RGB[i * 3 + 1], image1_RGB[i * 3 + 2]);
			wxImage::RGBValue image2_pixel(image2_RGB[i * 3], image2_RGB[i * 3 + 1], image2_RGB[i * 3 + 2]);
			
			double percentual_difference = ImageUtils::comparePixelRGB(image1_pixel, 
																		image2_pixel,
																		tolerance);
			if (percentual_difference > 0) {
				diffStorage.push_back(std::make_shared<PixelDiff>(x, y, percentual_difference));
			}
		}
	}
	
	notify(8);
}

void Model::compareHSV(wxString path1, wxString path2, double tolerance) {
	const std::shared_ptr<const wxImage> image1 = getImage(path1);
	const std::shared_ptr<const wxImage> image2 = getImage(path2);
	
	if (!image1) {
		throw std::invalid_argument("Could not find " + std::string(path1.mb_str()) + "in the image storage");
	}
	if (!image2) {
		throw std::invalid_argument("Could not find " + std::string(path2.mb_str()) + "in the image storage");
	}
	
	if (!ImageUtils::isGeometryEqual(*image1, *image2)) {
		throw ImageGeometryException();
	}
	
	removeCachedDifferences();
	
	// Unfortunately there's no builtin function to get hsv data directly, so we read rgb data as described
	// in the compareRGB function, then convert the value for each pixel.
	unsigned char* image1_RGB = image1->GetData();
	unsigned char* image2_RGB = image2->GetData();
	
	for (int y = 0; y < image1->GetHeight(); y++) {
		for (int x = 0; x < image1->GetWidth(); x++) {
			unsigned long i = y * image1->GetWidth() + x;
			
			// Put the rgb separate chars in an envelope which represents a pixel
			wxImage::RGBValue image1_pixel(image1_RGB[i * 3], image1_RGB[i * 3 + 1], image1_RGB[i * 3 + 2]);
			wxImage::RGBValue image2_pixel(image2_RGB[i * 3], image2_RGB[i * 3 + 1], image2_RGB[i * 3 + 2]);
			
			double percentual_difference = ImageUtils::comparePixelHSV(wxImage::RGBtoHSV(image1_pixel), 
																		wxImage::RGBtoHSV(image2_pixel),
																		tolerance);
			if (percentual_difference > 0) {
				diffStorage.push_back(std::make_shared<PixelDiff>(x, y, percentual_difference));
			}
		}
	}
	
	notify(8);
}

const std::list<std::shared_ptr<const PixelDiff>>& Model::getDifferences() {
	return diffStorage;
}

void Model::removeCachedDifferences() {
	diffStorage.clear();
}

void Model::registerObserver(Observer& observer) {
	observers.push_back(&observer);
}

void Model::removeObserver(Observer& observer) {
	observers.remove(&observer);
}

void Model::notify(int eventCode) {
	auto iter = observers.begin();
	
	while(iter != observers.end())
	{
		(*iter)->update(eventCode);
		iter++;
	}
}

