


#include <QDebug>
#include "CPUInfoObject.h"




CPUInfoObject::CPUInfoObject(QObject *parent)
    : QObject(parent)
{
}


CPUInfoObject::CPUInfoObject(const QString &credit, const QString &runrate, const QString &moredata, QObject *parent)
    : QObject(parent), _credit(credit), _runrate(runrate), _moredata(moredata)
{
}



QString CPUInfoObject::credit() const
{
    return _credit;
}

void CPUInfoObject::setCredit(const QString &credit)
{
    if (credit != _credit) {
        _credit = credit;
        emit creditChanged();
    }
}


QString CPUInfoObject::runrate() const
{
    return _runrate;
}


void CPUInfoObject::setRunrate(const QString &runrate)
{
    if (runrate != _runrate) {
        _runrate = runrate;
        emit runrateChanged();
    }
}




QString CPUInfoObject::moredata() const
{
    return(_moredata);
}


void CPUInfoObject::setMoredata(const QString &moredata)
{
    if (moredata != _moredata) {
        _moredata = moredata;
        emit moredataChanged();
    }
}
