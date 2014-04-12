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
