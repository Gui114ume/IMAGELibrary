#ifndef IPGMFILTER_HPP
#define IPGMFILTER_HPP

#include <iostream>
#include <cstdlib>

#include <QString>
#include <QVector>
#include <QFile>
#include <QtDebug>

#include "pixeltype.h"


class IPGMFilter
{
public:
    virtual ~IPGMFilter(){};

    virtual void apply(PGMpicture& picture_in,
                       PGMpicture& picture_out) = 0;

protected:
    IPGMFilter() {};
};

#endif // IPGMFILTER_HPP
