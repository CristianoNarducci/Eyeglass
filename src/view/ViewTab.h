#ifndef EYEGLASS_VIEWTAB_H
#define EYEGLASS_VIEWTAB_H

class ViewTab {
public:
	virtual void reset() = 0;
	virtual void generateDiffView() = 0;
};

#endif
