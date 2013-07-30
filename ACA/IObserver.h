#ifndef ACA_IOBSERVER_H
#define ACA_IOBSERVER_H

namespace aca {

class ISubject;

class IObserver
{
public:
    virtual void notify() = 0;
};

class ISubject
{
public:
    virtual void add(IObserver* observer) = 0;
};

}

#endif