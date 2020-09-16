#ifndef EYEGLASS_VIEWTAB_H
#define EYEGLASS_VIEWTAB_H

/*
 * Inteface for a group of small views which are responsible for showing images and computation results
 * for the program.
 * In addition to this, they are enabled to do some heavylifting regarding visualization and image manipulation
 * (altough only for the temporary visualization - the image storage is not impacted).
 */
class ViewTab {
public:
	virtual void reset() = 0;
	virtual void generateView() = 0;
};

#endif
