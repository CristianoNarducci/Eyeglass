#ifndef EYEGLASS_IMAGEUTILS_H
#define EYEGLASS_IMAGEUTILS_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <cmath>

/*
 * Collection of utilities built upon wxImage and related classes, like pixels and colors.
 */
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
	static double comparePixelAlpha(unsigned char alphaValue1, unsigned char alphaValue2, double tolerance) {
		double percentual_difference = std::abs(alphaValue2 - alphaValue1) / 255.0;
		if (percentual_difference <= tolerance) {
			percentual_difference = 0;
		}
		
		return percentual_difference;
	};
	
	/*
	 * Returns the percentual of difference between the two RGB values, or 0 if below tolerance.
	 */
	static double comparePixelRGB(wxImage::RGBValue RGBValue1, wxImage::RGBValue RGBValue2, double tolerance) {
		unsigned char R_distance = std::abs(RGBValue2.red - RGBValue1.red);
		unsigned char G_distance = std::abs(RGBValue2.green - RGBValue1.green); 
		unsigned char B_distance = std::abs(RGBValue2.blue - RGBValue1.blue);

		double percentual_difference = std::sqrt(R_distance * R_distance + G_distance * G_distance + B_distance * B_distance) / std::sqrt(255 * 255 * 3);
		if (percentual_difference <= tolerance) {
			percentual_difference = 0;
		}
		
		return percentual_difference;
	};
	
	/*
	 * Returns the percentual of difference between the two HSV values, or 0 if below tolerance.
	 */
	static double comparePixelHSV(wxImage::HSVValue HSVValue1, wxImage::HSVValue HSVValue2, double tolerance) {
		// The multiplication by 2 is just to take the value on par with the others, otherwise it would be max 0.5
		double H_distance = std::remainder(std::abs(HSVValue2.hue - HSVValue1.hue), 1.0) * 2.0;
		double S_distance = std::abs(HSVValue2.saturation - HSVValue1.saturation);
		double V_distance = std::abs(HSVValue2.value - HSVValue1.value);
		
		double percentual_difference = std::sqrt(H_distance * H_distance + S_distance * S_distance + V_distance * V_distance) / std::sqrt(3);
		if (percentual_difference <= tolerance) {
			percentual_difference = 0;
		}
		
		return percentual_difference;
	};
};

#endif
