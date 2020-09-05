#ifndef EYEGLASS_IMAGELOADEREXCEPTION_H
#define EYEGLASS_IMAGELOADEREXCEPTION_H

#include <stdexcept>
#include <string>

class ImageLoaderException : public std::runtime_error {
public:
	ImageLoaderException() : runtime_error("Could not load the image") {}
	ImageLoaderException(const std::string what) : runtime_error(what) {}
};

#endif
