#ifndef PUBLIC_FILE_H
#define PUBLIC_FILE_H

#include "publicdata.h"

class Public_File
{
public:
    static PublicData publicData(int id);

private:
    static QString s_fileName;

private:
    static void initFile();
};

#endif // PUBLIC_FILE_H
