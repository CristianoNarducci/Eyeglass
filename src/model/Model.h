#ifndef EYEGLASS_MODEL_H
#define EYEGLASS_MODEL_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <map>
#include <list>
#include <utility>

#include "AbstractModel.h"
#include "DiffResult.h"
#include "../utils/Observer.h"

/*
 * Implements an AbstractModel with a local in-memory storage.
 */
class Model : public AbstractModel {
public:
	Model();

	void registerObserver(Observer *observer) override;
	void removeObserver(Observer *observer) override;
	void notify(int eventCode) override;
	void loadImage(wxString path) override;
	void loadImages(wxArrayString paths) override;
	void removeImage(wxString path) override;
	void removeImages(wxArrayString paths) override;
	void removeAllImages() override;
	const wxImage* getImage(wxString path) override;
	const std::map<wxString, wxImage>& getAllImages() override;
	double comparePixelAlpha(const char alphaValue1, const char alphaValue2, const double tolerance) override;
	double comparePixelRGB(wxImage::RGBValue RGBValue1, wxImage::RGBValue RGBValue2, const double tolerance) override;
	double comparePixelHSV(wxImage::HSVValue HSVValue1, wxImage::HSVValue HSVValue2, const double tolerance) override;
	void compareAlpha(wxString path1, wxString path2, const double tolerance) override;
	void compareRGB(wxString path1, wxString path2, const double tolerance) override;
	void compareHSV(wxString path1, wxString path2, const double tolerance) override;
	const DiffResult* getDifferences(wxString path1, wxString path2) override;
	
	virtual ~Model() override;

protected:
	void removeCachedDifferences(wxString path1, wxString path2 = "") override;
	void removeAllCachedDifferences() override;

	/*
	 * Holds a list of observer which want to be notified of changes.
	 */
	std::list<Observer*> observers;
	
	/*
	 * The storage where images are saved, after being loaded.
	 * Each image is saved along with its path, which is used as a key for unique identification and retrieval.
	 */
	std::map<wxString, wxImage> imageStorage; // TODO: create map with a comparison object which uses wxString IsSameAs, otherwise matches could fail
	
	/*
	 * A cache for comparison results.
	 * The comparison retrieval key is comprised of both image paths. The key pair might be ordered,
	 * but in reality the order should be ignored; if matching doesn't work at first, try swapping the
	 * paths.
	 */
	std::map<std::pair<wxString, wxString>, DiffResult> diffStorage; // TODO: create map with a comparison object which uses wxString IsSameAs, otherwise matches could fail 
};

#endif
