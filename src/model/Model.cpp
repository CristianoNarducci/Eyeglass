#include "Model.h"

Model::Model() {}

Model::~Model() {}

// TODO: Error reporting is missing at the moment
void Model::loadImage(const wxString path) {
	wxImage image;
	
	if (image.LoadFile(path)) {
		imageStorage.insert(std::make_pair(path, image));
	}
}

// Also removes the diff cache entry
// NOTE: the iterator might get invalidated upon an erasure call. 
void Model::removeImage(const wxString path) {
	imageStorage.erase(path);
	
	removeCachedDifferences(path);
}

void Model::removeAllImages() {
	imageStorage.clear();
}

const wxImage* Model::getImage(const wxString path) {
	std::map<wxString, wxImage>::const_iterator iter;
	
	iter = imageStorage.find(path);
	if (iter != imageStorage.end()) {
		return & (iter->second);
	}
	
	return nullptr;
}

const std::map<wxString, wxImage>& Model::getAllImages() {
	return imageStorage;
}

double Model::comparePixelAlpha(const char alphaValue1, const char alphaValue2, const double tolerance) {
	double percentual_difference = std::abs(alphaValue2 - alphaValue1) / 255;
	return percentual_difference > tolerance ? percentual_difference : 0;
}

double Model::comparePixelRGB(const wxImage::RGBValue RGBValue1, const wxImage::RGBValue RGBValue2, const double tolerance) {
	unsigned char R_distance = std::abs(RGBValue2.red - RGBValue1.red);
	unsigned char G_distance = std::abs(RGBValue2.green - RGBValue1.green); 
	unsigned char B_distance = std::abs(RGBValue2.blue - RGBValue1.blue);

	double percentual_difference = (R_distance + G_distance + B_distance) / 765;
	return percentual_difference > tolerance ? percentual_difference : 0;
}

double Model::comparePixelHSV(const wxImage::HSVValue HSVValue1, const wxImage::HSVValue HSVValue2, const double tolerance) {
	// The multiplication by 2 is just to take the value on par with the others, otherwise it would be max 0.5
	// std::remainder is needed only for floating poin remainders
	double H_distance = (std::remainder(std::abs(HSVValue2.hue - HSVValue1.hue) + 0.5, 1.0) - 0.5) * 2;
	double S_distance = std::abs(HSVValue2.saturation - HSVValue1.saturation);
	double V_distance = std::abs(HSVValue2.value - HSVValue1.value);
	
	// I might be wrong, but by skimming the wikipedia article about HSV I did not seem to find anything
	// about one of these fields being more important than the other two.
	// So, as for rgb, every channel has a weight of 1
	double percentual_difference = (H_distance + S_distance + V_distance) / 3;
	return percentual_difference > tolerance ? percentual_difference : 0;
}

// An image without the alpha channel is interpreted as having every pixel alpha value set to 255
void Model::compareAlpha(const wxString path1, const wxString path2, const double tolerance) {
	const wxImage* image1 = getImage(path1);
	const wxImage* image2 = getImage(path2);
	
	// TODO: error checking. Maybe move fetch responsibility out of the compare function...?
	// The controller might be a suitable place for such task.
	// At the moment, let's pretend everything goes as smooth as silk.
	
	// TODO: Add equal size control before every compariso
	
	// Fetch the DiffResult container for the pair. Add one if missing.
	DiffResult* diff_container = getDifferences_internal(path1, path2);
	if (diff_container == nullptr) {
		diff_container = new DiffResult();
		diffStorage.insert(std::make_pair(std::make_pair(path1, path2), *diff_container));
	}
	
	unsigned char* image1_alpha = image1->GetAlpha();
	unsigned char* image2_alpha = image2->GetAlpha();
	
	for (int x = 0; x < image1->GetWidth(); x++) {
		for (int y = 0; y < image1->GetHeight(); y++) {
			unsigned long index = x * image1->GetHeight() + y;
			unsigned char percentual_difference = comparePixelAlpha(image1_alpha[index], 
																	image2_alpha[index],
																	tolerance);
			if (percentual_difference > 0) {
				(diff_container->alphaVector).push_back(std::make_tuple(x, y, percentual_difference));
			}
		}
	}
}

void Model::compareRGB(const wxString path1, const wxString path2, const double tolerance) {

}

void Model::compareHSV(const wxString path1, const wxString path2, const double tolerance) {

}

// To implement the unordered usage, first check in one way, then try applying the operation with the
// parameters reversed
const DiffResult* Model::getDifferences(const wxString path1, const wxString path2) {
	std::map<std::pair<wxString, wxString>, DiffResult>::const_iterator iter;
	
	iter = diffStorage.find(std::make_pair(path1, path2));
	if (iter != diffStorage.end()) {
		return & (iter->second);
	}
	
	iter = diffStorage.find(std::make_pair(path1, path2));
	if (iter != diffStorage.end()) {
		return & (iter->second);
	}
	
	return nullptr;
}

// To implement the unordered usage, first check in one way, then try applying the operation with the
// parameters reversed
DiffResult* Model::getDifferences_internal(const wxString path1, const wxString path2) {
	std::map<std::pair<wxString, wxString>, DiffResult>::iterator iter;
	
	iter = diffStorage.find(std::make_pair(path1, path2));
	if (iter != diffStorage.end()) {
		return & (iter->second);
	}
	
	iter = diffStorage.find(std::make_pair(path1, path2));
	if (iter != diffStorage.end()) {
		return & (iter->second);
	}
	
	return nullptr;
}

// Same as above
void Model::removeCachedDifferences(const wxString path1, const wxString path2) {
	if (path2.IsEmpty()) {
		std::map<std::pair<wxString, wxString>, DiffResult>::iterator iter = diffStorage.begin();
		while (iter != diffStorage.end()) {
			std::pair<wxString, wxString> key = iter->first;
		
			if (key.first.IsSameAs(path1) || key.second.IsSameAs(path1)) {
				diffStorage.erase(key); // TODO: checks if it works for equal string with different addresses. It should, though
			}
			
			iter++;
		}
	} else if (diffStorage.erase(std::make_pair(path1, path2)) == 0) {
		diffStorage.erase(std::make_pair(path2, path1));
	}
}

void Model::removeAllCachedDifferences() {
	diffStorage.clear();
}

void Model::registerObserver(Observer* observer) {
	observers.push_back(observer);
}

void Model::removeObserver(Observer* observer) {
	observers.remove(observer);
}

void Model::notify(const int eventCode) {
	std::list<Observer*>::iterator iter = observers.begin();
	
	while(iter != observers.end())
	{
		(*iter)->update(eventCode);
		iter++;
	}
}
