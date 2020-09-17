#ifndef EYEGLASS_PIXELDIFF_H
#define EYEGLASS_PIXELDIFF_H

/*
 * Keeps record of the percentual of difference found between two images at the x, y coordinates.
 */
class PixelDiff {
public:
	PixelDiff(int x, int y, double percentual_diff): x(x), y(y), percentual_diff(percentual_diff) {};
	int x;
	int y;
	double percentual_diff;
};

#endif
