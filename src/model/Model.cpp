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

void Model::loadImages(const wxArrayString paths) {
	for (int i = 0; i < paths.GetCount(); i++) {
		loadImage(paths.Item(i));
	}
}

// Also removes the diff cache entry
// NOTE: the iterator might get invalidated upon an erasure call. 
void Model::removeImage(const wxString path) {
	imageStorage.erase(path);
	
	removeCachedDifferences(path);
}

void Model::removeImages(const wxArrayString paths) {
	for (int i = 0; i < paths.GetCount(); i++) {
		imageStorage.erase(paths.Item(i));
	}
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
	return 0;
}

double Model::comparePixelRGB(const wxImage::RGBValue RGBValue1, const wxImage::RGBValue RGBValue2, const double tolerance) {
	return 0;
}

double Model::comparePixelHSV(const wxImage::HSVValue HSVValue1, const wxImage::HSVValue HSVValue2, const double tolerance) {
	return 0;
}

void Model::compareAlpha(const wxString path1, const wxString path2, const double tolerance) {

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
		(*iter)->update(eventCode); // TODO check why this doesn't work just with an arrow operator. According to docs, it should.
		iter++;
	}
}
