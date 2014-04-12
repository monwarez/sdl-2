#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED
#include <string>
#include <iostream>
#ifndef GEST_ERROR
#define GEST_ERROR(a) Error(a,__FILE__,__LINE__);
#endif
class Error
{
    public:
        Error(const std::string &error,const std::string &file, unsigned int line);
        virtual     void    ShowError();
        Error();

        std::string     m_error;
        std::string     m_file;
        unsigned int    m_line;
};
#endif // ERROR_H_INCLUDED
