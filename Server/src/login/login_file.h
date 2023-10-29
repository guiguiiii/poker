#ifndef LOGIN_FILE_H
#define LOGIN_FILE_H

#include "logindata.h"
#include "signupdata.h"

class Login_File
{
public:
    static int login(const LoginData &loginData);
    static int signUp(const SignUpData &signUpData);
    static int userID(const QString &username);

private:
    static QString s_fileName;

private:
    static void initFile();
};

#endif // LOGIN_FILE_H
