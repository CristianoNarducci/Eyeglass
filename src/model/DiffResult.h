#ifndef EYEGLASS_DIFFRESULT_H
#define EYEGLASS_DIFFRESULT_H

#include <list>
#include <tuple>

/*
 * Groups together every cached difference for a couple of images.
 * Each list keeps record of a tuple of x,y coordinates and the percentual of difference
 * between the two images.
 */
class DiffResult {
public:
	std::list<std::tuple<int, int, double>> alphaVector;
	std::list<std::tuple<int, int, double>> RGBVector;
	std::list<std::tuple<int, int, double>> HSVVector;
};

#endif
