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
#include "Error.h"
using namespace std;

Error::Error()
{
    m_line  =   0;
}
Error::Error(const string &error, const string &file, unsigned int line):m_error(error),m_file(file),m_line(line)
{

}
void        Error::ShowError()
{
    cerr << "Error: " << m_error <<endl << m_file << " ( " << m_line  << " )"<< endl;
}
