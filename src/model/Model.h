#ifndef EYEGLASS_MODEL_H
#define EYEGLASS_MODEL_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

// Storage related libs
#include <map>
#include <list>
#include <utility>

#include "DiffResult.h"
#include "../utils/Observer.h"
#include "../utils/Subject.h"
#include "../utils/ImageUtils.h"

#include "../exception/ImageLoaderException.h"


class Model : public Subject {
public:
	Model();

	void registerObserver(Observer *observer) override;
	void removeObserver(Observer *observer) override;
	void notify(int eventCode) override;
	
	/*
	 * Loads an image into the storage.
	 * If the selected file is invalid, the image is discarded. 
	 */
	virtual void loadImage(const wxString path);
	
	/*
	 * Removes the specified image from the storage, if present.
	 */
	virtual void removeImage(const wxString path);
	
	/*
	 * Completely purge the image storage.
	 */
	virtual void removeAllImages();
	
	/*
	 * Returns a non modifiable image 
	 * The images in storage should not be modified directly, as doing so prevents the original image
	 * from being reused in another round of comparison.
	 */
	virtual const wxImage* getImage(const wxString path);
	
	/*
	 * Returns a map containing all the images in storage, with their path identifier.
	 * The returned data is immutable.
	 */
	virtual const std::map<wxString, wxImage>& getAllImages();
	
	/*
	 * For each pixel in both images, compare the alpha value and save the percentual of difference 
	 * in storage if above the tolerance level. Both images should be of the same size, or the comparison
	 * will error.
	 * The order of the images doesn't count.
	 */
	virtual void compareAlpha(const wxString path1, const wxString path2, const double tolerance);
	
	/*
	 * For each pixel in both images, compare the RGB value and save the percentual of difference 
	 * in storage if above the tolerance level. Both images should be of the same size, or the comparison
	 * will error.
	 * The order of the images doesn't count.
	 */
	virtual void compareRGB(const wxString path1, const wxString path2, const double tolerance);
	
	/*
	 * For each pixel in both images, compare the HSV value and save the percentual of difference 
	 * in storage if above the tolerance level. Both images should be of the same size, or the comparison
	 * will error.
	 * The order of the images doesn't count.
	 */
	virtual void compareHSV(const wxString path1, const wxString path2, const double tolerance);
	
	/*
	 * Returns the group of differences found between the two images.
	 * The order of the images doesn't count.
	 */
	virtual const DiffResult* getDifferences(const wxString path1, const wxString path2);
	
	virtual ~Model() {};


protected:
	/*
	 * Fetches the DiffResult container for internal usage, returning a non costant pointer.
	 */
	virtual DiffResult* getDifferences_internal(const wxString path1, const wxString path2);
	 
	/*
	 * Remove the cached differences where one of the images (or both) are involved.
	 * The orger of the images doesn't count.
	 */
	virtual void removeCachedDifferences(const wxString path1, const wxString path2 = "");
	
	/*
	 * Purge every diff cache entry.
	 */
	virtual void removeAllCachedDifferences();

	/*
	 * Holds a list of observer which want to be notified of changes.
	 */
	std::list<Observer*> observers;
	
	/*
	 * The storage where images are saved, after being loaded.
	 * Each image is saved along with its path, which is used as a key for unique identification and retrieval.
	 */
	std::map<wxString, wxImage> imageStorage;
	
	/*
	 * A cache for comparison results.
	 * The comparison retrieval key is comprised of both image paths. The key pair might be ordered,
	 * but in reality the order should be ignored; if matching doesn't work at first, try swapping the
	 * paths.
	 */
	std::map<std::pair<wxString, wxString>, DiffResult> diffStorage;
};

#endif
