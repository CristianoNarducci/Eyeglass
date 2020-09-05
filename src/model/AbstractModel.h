#ifndef EYEGLASS_ABSTRACTMODEL_H
#define EYEGLASS_ABSTRACTMODEL_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <map>

#include "DiffResult.h"
#include "../utils/Subject.h"
#include "../utils/Observer.h"


/*
 * AbstractModel provides a generic interface to implement a model for this program.
 * The model is considered an element which should be subjected to observation, so it extends the Subject class.
 */
class AbstractModel : public Subject {
public:
	/*
	 * Loads an image into the storage.
	 * If the selected file is invalid, the image is discarded. 
	 */
	virtual void loadImage(const wxString path) = 0;
	
	/*
	 * Removes the specified image from the storage, if present.
	 */
	virtual void removeImage(const wxString path) = 0;
	
	/*
	 * Completely purge the image storage.
	 */
	virtual void removeAllImages() = 0;
	
	/*
	 * Returns a non modifiable image 
	 * The images in storage should not be modified directly, as doing so prevents the original image
	 * from being reused in another round of comparison.
	 */
	virtual const wxImage* getImage(const wxString path) = 0;
	
	/*
	 * Returns a map containing all the images in storage, with their path identifier.
	 * The returned data is immutable.
	 */
	virtual const std::map<wxString, wxImage>& getAllImages() = 0;
	
	/*
	 * For each pixel in both images, compare the alpha value and save the percentual of difference 
	 * in storage if above the tolerance level. Both images should be of the same size, or the comparison
	 * will error.
	 * The order of the images doesn't count.
	 */
	virtual void compareAlpha(const wxString path1, const wxString path2, const double tolerance) = 0;
	
	/*
	 * For each pixel in both images, compare the RGB value and save the percentual of difference 
	 * in storage if above the tolerance level. Both images should be of the same size, or the comparison
	 * will error.
	 * The order of the images doesn't count.
	 */
	virtual void compareRGB(const wxString path1, const wxString path2, const double tolerance) = 0;
	
	/*
	 * For each pixel in both images, compare the HSV value and save the percentual of difference 
	 * in storage if above the tolerance level. Both images should be of the same size, or the comparison
	 * will error.
	 * The order of the images doesn't count.
	 */
	virtual void compareHSV(const wxString path1, const wxString path2, const double tolerance) = 0;
	
	/*
	 * Returns the group of differences found between the two images.
	 * The order of the images doesn't count.
	 */
	virtual const DiffResult* getDifferences(const wxString path1, const wxString path2) = 0;
	
	virtual ~AbstractModel() {};

protected:
	/*
	 * Fetches the DiffResult container for internal usage, returning a non costant pointer.
	 */
	virtual DiffResult* getDifferences_internal(const wxString path1, const wxString path2) = 0;
	 
	/*
	 * Remove the cached differences where one of the images (or both) are involved.
	 * The orger of the images doesn't count.
	 */
	virtual void removeCachedDifferences(const wxString path1, const wxString path2 = "") = 0;
	
	/*
	 * Purge every diff cache entry.
	 */
	virtual void removeAllCachedDifferences() = 0;

};

#endif
