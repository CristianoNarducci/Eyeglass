#ifndef EYEGLASS_IMAGEUTILS_H
#define EYEGLASS_IMAGEUTILS_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

// Libraries neede for comparison. Strangely enough, the absolute function for integers requires
// cstdlib, while the one for floats is defined in cmath. Or so says cppreference
#include <cmath>
#include <cstdlib>

// Collection of utilities built upon wxImage and related classes, like pixels and colors.
class ImageUtils {
public:
	/*
	 * Checks if the images have the same geometry (size).
	 * Does not check if the images have data. The check must be executed beforehand. (See IsOk method)
	 */
	static bool isGeometryEqual(const wxImage& image1, const wxImage& image2);
	
	/*
	 * Returns the percentual of difference between the two alpha values, or 0 if below tolerance.
	 */
	static double comparePixelAlpha(const char alphaValue1, const char alphaValue2, const double tolerance);
	
	/*
	 * Returns the percentual of difference between the two RGB values, or 0 if below tolerance.
	 */
	static double comparePixelRGB(const wxImage::RGBValue RGBValue1, const wxImage::RGBValue RGBValue2, const double tolerance);
	
	/*
	 * Returns the percentual of difference between the two HSV values, or 0 if below tolerance.
	 */
	static double comparePixelHSV(const wxImage::HSVValue HSVValue1, const wxImage::HSVValue HSVValue2, const double tolerance);
};

#endif
