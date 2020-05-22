#ifndef IPPMFILTER_HPP
#define IPPMFILTER_HPP

#include <iostream>
#include <cstdlib>

#include <QString>
#include <QVector>
#include <QFile>
#include <QtDebug>

#include "pixeltype.h"


class IPPMFilter
{
public:
    virtual ~IPPMFilter(){};

    virtual void apply(PPMpicture& picture_in,
                       PPMpicture& picture_out) = 0;

protected:
    IPPMFilter() {};
};

#endif // IPPMFILTER_HPP
