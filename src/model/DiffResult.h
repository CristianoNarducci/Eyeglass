#ifndef EYEGLASS_DIFFRESULT_H
#define EYEGLASS_DIFFRESULT_H

/*
 * Groups together every cached difference for a couple of images.
 * Each vector keeps record of a tuple of x,y coordinates and the percentual of difference
 * between the two images.
 */
class DiffResult {
public:
	std::vector<std::tuple<int, int, double>> alphaVector;
	std::vector<std::tuple<int, int, double>> RGBVector;
	std::vector<std::tuple<int, int, double>> HSVVector;
};

#endif
