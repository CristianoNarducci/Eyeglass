#include "Model.h"

Model::Model() {}

Model::~Model() {}

void Model::loadImage(const wxString path) {
	wxImage image;
	
	if (!image.LoadFile(path)) {
		throw ImageLoaderException("Could not load " + std::string(path.mb_str()));
	}
	
	imageStorage.insert(std::make_pair(path, image));
}

// Also removes the diff cache entry
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

// An image without the alpha channel is interpreted as having every pixel alpha value set to 255
void Model::compareAlpha(const wxString path1, const wxString path2, const double tolerance) {
	const wxImage* image1 = getImage(path1);
	const wxImage* image2 = getImage(path2);
	
	if (image1 == nullptr) {
		throw std::invalid_argument("Could not find " + std::string(path1.mb_str()) + "in the image storage");
	}
	if (image2 == nullptr) {
		throw std::invalid_argument("Could not find " + std::string(path2.mb_str()) + "in the image storage");
	}
	
	if (!ImageUtils::isGeometryEqual(*image1, *image2)) {
		throw std::domain_error(std::string(path1.mb_str()) + " and " + std::string(path2.mb_str())
											+ " have different gemetries");
	}
	
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
			unsigned char percentual_difference = ImageUtils::comparePixelAlpha(image1_alpha[index], 
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

