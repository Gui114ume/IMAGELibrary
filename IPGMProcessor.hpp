#ifndef IPGMPROCESSOR_HPP
#define IPGMPROCESSOR_HPP

#include "IPGMFilter.hpp"

#include "pixeltype.h"

#include <iostream>
#include <cstdlib>

#include <QString>
#include <QVector>
#include <QFile>
#include <QtDebug>



class IPGMProcessor
{
public:
    virtual ~IPGMProcessor() {};

    virtual void loadPGM(QString& filename,
                         PGMpicture& picture) = 0;

    virtual void applyFilter(IPGMFilter& filter,
                             PGMpicture& picture,
                             PGMpicture& picture_out) = 0;

    virtual void savePicture(QString& filename,
                             PGMpicture& picture) = 0;

protected:
    IPGMProcessor() {};

private:
    virtual bool isPGMFile(QString& filename,
                           PGMpicture& picture) = 0;

    virtual void loadPicture(QString& filename,
                             PGMpicture& picture) = 0;

};

#endif //IPGMPROCESSOR_HPP
