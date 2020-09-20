#ifndef EYEGLASS_MODEL_H
#define EYEGLASS_MODEL_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <memory>

// Storage related libs
#include <map>
#include <list>

#include "PixelDiff.h"

#include "../utils/Observer.h"
#include "../utils/Subject.h"
#include "../utils/ImageUtils.h"

#include "../exception/ImageLoaderException.h"
#include "../exception/ImageGeometryException.h"

/*
 * Stores the images which need to be examined and the results of the latest examination.
 * The image comparison logic is also implemented here.
 */
class Model: public Subject {
public:
	Model();

	void registerObserver(Observer& observer) override;
	void removeObserver(Observer& observer) override;
	void notify(int eventCode) override;
	
	/*
	 * Loads an image into the storage.
	 * If the selected file is invalid, the image is discarded. 
	 */
	virtual void loadImage(wxString path);
	
	/*
	 * Removes the specified image from the storage, if present.
	 */
	virtual void removeImage(wxString path);
	
	/*
	 * Completely purge the image storage.
	 */
	virtual void removeAllImages();
	
	/*
	 * Returns a non modifiable image 
	 * The images in storage should not be modified directly, as doing so prevents the original image
	 * from being reused in another round of comparison.
	 */
	virtual const std::shared_ptr<const wxImage> getImage(wxString path);
	
	/*
	 * Returns a map containing all the images in storage, with their path identifier.
	 * The returned data is immutable.
	 */
	virtual const std::map<wxString, const std::shared_ptr<const wxImage>>& getAllImages();
	
	/*
	 * For each pixel in both images, compare the alpha value and save the percentual of difference 
	 * in storage if above the tolerance level. Both images should be of the same size, or the comparison
	 * will error.
	 * The order of the images doesn't count.
	 */
	virtual void compareAlpha(wxString path1, wxString path2, double tolerance);
	
	/*
	 * For each pixel in both images, compare the RGB value and save the percentual of difference 
	 * in storage if above the tolerance level. Both images should be of the same size, or the comparison
	 * will error.
	 * The order of the images doesn't count.
	 */
	virtual void compareRGB(wxString path1, wxString path2, double tolerance);
	
	/*
	 * For each pixel in both images, compare the HSV value and save the percentual of difference 
	 * in storage if above the tolerance level. Both images should be of the same size, or the comparison
	 * will error.
	 * The order of the images doesn't count.
	 */
	virtual void compareHSV(wxString path1, wxString path2, double tolerance);
	
	/*
	 * Returns the cached differences. If no comparison was performed, every list will be empty.
	 */
	virtual const std::list<std::shared_ptr<const PixelDiff>>& getDifferences();
	
	/*
	 * Removes the cached differences, if any.
	 */
	virtual void removeCachedDifferences();
	
	virtual ~Model() {};


protected:
	/*
	 * Holds a list of observer which want to be notified of changes.
	 */
	std::list<Observer*> observers;
	
	/*
	 * The storage where images are saved, after being loaded.
	 * Each image is saved along with its path, which is used as a key for unique identification and retrieval.
	 */
	std::map<wxString, const std::shared_ptr<const wxImage>> imageStorage;
	
	/*
	 * A cache for comparison results.
	 * Contains always the latest comparison result, given one was performed of course.
	 */
	std::list<std::shared_ptr<const PixelDiff>> diffStorage;
};

#endif
