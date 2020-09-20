#ifndef EYEGLASS_DISPLAYUTILS_H
#define EYEGLASS_DISPLAYUTILS_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <cmath>

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
	 * Scales an image without loosing its original aspect ratio, to the container size.
	 * If the image and the container do not share the same aspect ratio, since the function preserves
	 * the image aspect ratio, the resulting size will not cover the whole container, thus only the largest 
	 * side of the image will touch the container.
	 * 
	 * The rescaling quality can be specified, otherwise BICUBIC (the best) will be used.
	 */
	static void proportionallyRescaleImage(wxImage& image, int containerWidth, int containerHeight,
											wxImageResizeQuality quality = wxIMAGE_QUALITY_BICUBIC) {
		double imageRatio = image.GetWidth() / double(image.GetHeight());
		
		if (imageRatio > 1.0) {
			image.Rescale(containerWidth, containerWidth / imageRatio, quality);
		} else {
			image.Rescale(containerHeight * imageRatio, containerHeight, quality);
		}
	}
};

#endif
