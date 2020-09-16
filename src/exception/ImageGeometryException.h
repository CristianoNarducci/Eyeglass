#ifndef EYEGLASS_IMAGEGEOMETRYEXCEPTION_H
#define EYEGLASS_IMAGEGEOMETRYEXCEPTION_H

#include <stdexcept>

class ImageGeometryException: public std::exception {
public:
	ImageGeometryException(): exception() {}
};

#endif
