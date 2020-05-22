#ifndef IPPMPROCESSOR_HPP
#define IPPMPROCESSOR_HPP

#include "IPPMFilter.hpp"

#include "pixeltype.h"

#include <iostream>
#include <cstdlib>

#include <QString>
#include <QVector>
#include <QFile>
#include <QtDebug>



class IPPMProcessor
{
public:
    virtual ~IPPMProcessor() {};

    virtual void loadPPM(QString& filename,
                         PPMpicture& picture) = 0;

    virtual void applyFilter(IPPMFilter& filter,
                             PPMpicture& picture,
                             PPMpicture& picture_out) = 0;

    virtual void savePicture(QString& filename,
                             PPMpicture& picture) = 0;

protected:
    IPPMProcessor() {};

private:
    virtual bool isPPMFile(QString& filename,
                           PPMpicture& picture) = 0;

    virtual void loadPicture(QString& filename,
                             PPMpicture& picture) = 0;

};

#endif
