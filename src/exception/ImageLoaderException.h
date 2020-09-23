#ifndef EYEGLASS_IMAGELOADEREXCEPTION_H
#define EYEGLASS_IMAGELOADEREXCEPTION_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <stdexcept>

class ImageLoaderException: public std::exception {
public:
	ImageLoaderException(wxString imagePath): exception(), imagePath(imagePath) {}
	
	const wxString getErroredPath() const noexcept {
		return imagePath;
	};

protected:
	const wxString imagePath;
};

#endif
