//
// Created by cristiano on 17/07/20.
//

#ifndef EYEGLASS_VIEWTAB_H
#define EYEGLASS_VIEWTAB_H


class ViewTab
{
	//TODO virtual descructor
public:
    virtual void reset()=0;  //reset tabs function
    /*Generate the viewtab*/
    virtual void generateDiffView()=0;
};

#endif //EYEGLASS_VIEWTAB_H
