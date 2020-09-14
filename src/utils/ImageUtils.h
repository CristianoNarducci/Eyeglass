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
	static bool isGeometryEqual(const wxImage& image1, const wxImage& image2) {
		return image1.GetWidth() == image2.GetWidth() && image1.GetHeight() == image2.GetHeight();
	};
	
	/*
	 * Returns the percentual of difference between the two alpha values, or 0 if below tolerance.
	 */
	static double comparePixelAlpha(const char alphaValue1, const char alphaValue2, const double tolerance) {
		double percentual_difference = std::fabs(alphaValue2 - alphaValue1) / 255.0;
		if (percentual_difference <= tolerance) {
			percentual_difference = 0;
		}
		
		return percentual_difference;
	};
	
	/*
	 * Returns the percentual of difference between the two RGB values, or 0 if below tolerance.
	 */
	static double comparePixelRGB(const wxImage::RGBValue RGBValue1, const wxImage::RGBValue RGBValue2, const double tolerance) {
		unsigned char R_distance = std::abs(RGBValue2.red - RGBValue1.red);
		unsigned char G_distance = std::abs(RGBValue2.green - RGBValue1.green); 
		unsigned char B_distance = std::abs(RGBValue2.blue - RGBValue1.blue);

		double percentual_difference = (R_distance + G_distance + B_distance) / 765.0;
		if (percentual_difference <= tolerance) {
			percentual_difference = 0;
		}
		
		return percentual_difference;
	};
	
	/*
	 * Returns the percentual of difference between the two HSV values, or 0 if below tolerance.
	 */
	static double comparePixelHSV(const wxImage::HSVValue HSVValue1, const wxImage::HSVValue HSVValue2, const double tolerance) {
		// The multiplication by 2 is just to take the value on par with the others, otherwise it would be max 0.5
		// std::remainder is needed only for floating poin remainders
		double H_distance = (std::remainder(std::abs(HSVValue2.hue - HSVValue1.hue) + 0.5, 1.0) - 0.5) * 2.0;
		double S_distance = std::abs(HSVValue2.saturation - HSVValue1.saturation);
		double V_distance = std::abs(HSVValue2.value - HSVValue1.value);
		
		// I might be wrong, but while skimming the wikipedia article about HSV I did not seem to find anything
		// about one of these fields being more important than the other two.
		// So, as for rgb, every channel has a weight of 1
		double percentual_difference = (H_distance + S_distance + V_distance) / 3.0;
		if (percentual_difference <= tolerance) {
			percentual_difference = 0;
		}
		
		return percentual_difference;
	};
};

#endif
