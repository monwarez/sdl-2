/*
Copyright (C) 2014 Payet thibault

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
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
