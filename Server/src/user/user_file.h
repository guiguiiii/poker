#ifndef USER_FILE_H
#define USER_FILE_H

#include "userdata.h"

class User_File
{
public:
    static UserData getPersonal(int id);
    static int setPersonal(int id, const UserData &userData);

private:
    static QString s_fileName;

private:
    static void initFile();
};

#endif // USER_FILE_H
