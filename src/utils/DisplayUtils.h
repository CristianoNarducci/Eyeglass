#ifndef EYEGLASS_DISPLAYUTILS_H
#define EYEGLASS_DISPLAYUTILS_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

/*
 * Collection of utilities useful in visualization of images.
 */
class DisplayUtils {
public:
	/*
	 * Generates a transparent image of the required size. (It's different from the no-params constructor
	 * of wxImage, as that call does not put any data in the image data buffer)
	 */
	static wxImage generateBlankImage(int width, int height) {
		wxImage image(width, height, true);
		image.InitAlpha();
		
		// There's no call to set it for a given area, as there is for RGB. That's a shame, in my opinion.
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				image.SetAlpha(x, y, 0);
			}
		}
		
		return image;
	}
	
	/*
	 * Calculates the sides that a rectangular object can reach, without loosing its original aspect ratio,
	 * while being resized to fill a container.
	 * When the largest side of the object has the same length of one side of the container, the growth stops.
	 * This means that the object might not fill the container entirely.
	 */
	static wxSize getLargestProportionalSize(int objectWidth, int objectHeight,
												int containerWidth, int containerHeight) {
		double objectRatio = objectWidth / double(objectHeight);
		
		if (containerWidth / objectRatio <= containerHeight) {
			return wxSize(containerWidth, containerWidth / objectRatio);
		} else {
			return wxSize(containerHeight * objectRatio, containerHeight);
		}
	}
	
	/*
	 * Mixes two colors to simulate an overlap effect of an alpha layer.
	 */
	static wxImage::RGBValue mixColors(wxImage::RGBValue sourceColor, wxImage::RGBValue maskColor, double percentage) {
		double inversePercentage = 1.0 - percentage;
		
		wxImage::RGBValue result;
		result.red = sourceColor.red * inversePercentage + maskColor.red * percentage;
		result.green = sourceColor.green * inversePercentage + maskColor.green * percentage;
		result.blue = sourceColor.blue * inversePercentage + maskColor.blue * percentage;
		
		return result;
	}
};

#endif
