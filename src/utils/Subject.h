//
// Created by cristiano on 20/07/20.
//

#ifndef EYEGLASS_SUBJECT_H
#define EYEGLASS_SUBJECT_H
#include "Observer.h"
class Subject{
public:
    virtual void registerObserver(Observer* observer)=0;
    virtual void removeObserver(Observer* observer)=0;
    virtual void notify(int eventCode)=0;

};


#endif //EYEGLASS_SUBJECT_H
