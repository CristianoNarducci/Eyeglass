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
 */
class AbstractModel: public Subject {
public:
	/*
	 * Loads an image into the storage.
	 * If the selected file is invalid, the image is discarded. 
	 */
	virtual void loadImage(const wxString path) = 0;
	
	/*
	 * Loads a batch of images into the store.
	 * Invalid files will be skipped.
	 */
	virtual void loadImages(const wxArrayString paths) = 0;
	
	/*
	 * Removes the specified image from the storage, if present.
	 */
	virtual void removeImage(const wxString path) = 0;
	
	/*
	 * Completely purge the image storage.
	 */
	virtual void removeAllImages(const wxArrayString paths) = 0;
	
	/*
	 * Returns a non modifiable image 
	 * The images in storage should not be modified directly, as doing so prevents the original image
	 * from being reused in another round of comparison.
	 */
	virtual const wxImage getImage(const wxString path) = 0;
	
	/*
	 * Returns a map containing all the images in storage, with their path identifier.
	 * The returned data is immutable.
	 */
	virtual const std::map<wxString, wxImage> getAllImages() = 0;
	
	/*
	 * Returns the percentual of difference between the two alpha values, or 0 if below tolerance.
	 */
	virtual double comparePixelAlpha(const char alphaValue1, const char alphaValue2, const double tolerance) = 0;
	
	/*
	 * Returns the percentual of difference between the two RGB values, or 0 if below tolerance.
	 */
	virtual double comparePixelRGB(const wxImage::RGBValue RGBValue1, const wxImage::RGBValue RGBValue2, const double tolerance) = 0;
	
	/*
	 * Returns the percentual of difference between the two HSV values, or 0 if below tolerance.
	 */
	virtual double comparePixelHSV(const wxImage::HSVValue HSVValue1, const wxImage::HSVValue HSVValue2, const double tolerance) = 0;
	
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
	virtual const DiffResult getDifferences(const wxString path1, const wxString path2) = 0;

    virtual void registerObserver(Observer* observer)=0;

    virtual void removeObserver(Observer* observer)=0;

    virtual void notify(int eventCode)=0;
protected:
	/*
	 * Remove the cache entry for the differences found between the two images.
	 * The orger of the images doesn't count.
	 */
	virtual void removeCachedDifferences(const wxString path1, const wxString path2) = 0;
	
	/*
	 * Purge every diff cache entry.
	 */
	virtual void removeAllCachedDifferences() = 0;
};

#endif
