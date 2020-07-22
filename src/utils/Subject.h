#ifndef EYEGLASS_SUBJECT_H
#define EYEGLASS_SUBJECT_H

#include "Observer.h"

/*
 * Defines an entity as an observale element.
 */
class Subject {
public:
	virtual void registerObserver(Observer* observer) = 0;
	virtual void removeObserver(Observer* observer) = 0;
	virtual void notify(const int eventCode) = 0;
	
	virtual ~Subject() {};
};

#endif
