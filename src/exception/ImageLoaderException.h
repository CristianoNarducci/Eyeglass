#ifndef EYEGLASS_IMAGELOADEREXCEPTION_H
#define EYEGLASS_IMAGELOADEREXCEPTION_H

#include <stdexcept>

class ImageLoaderException: public std::exception {
public:
	ImageLoaderException(): exception() {}
};

#endif
