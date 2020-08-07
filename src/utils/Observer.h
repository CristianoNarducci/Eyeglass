#ifndef EYEGLASS_OBSERVER_H
#define EYEGLASS_OBSERVER_H
/*
 * An observer is an entity which is interested in a subject, and therefore it requires subjects to
 * uptade it when a change happens on the subject side.
 */
class Observer {
public:
    virtual void update(const int eventCode) = 0;
    
    virtual ~Observer() {};
};

#endif
