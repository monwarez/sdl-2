#include "DebugGL.h"

using namespace std;
bool Debug::glCheck(string filename, int line)
{
    switch (glGetError())
            {
                case GL_NO_ERROR:
                    return true;
                break;

                case GL_OUT_OF_MEMORY:
                    cerr << "**********************************************************************" << endl;
                    cerr << "there is not enought memory left to execute the command.\nThe state of the GL is undefined in\n" << filename << "( "<< line << " )"<< endl;
                    cerr << "**********************************************************************" << endl;
                break;
                case GL_INVALID_ENUM:
                    cerr << "**********************************************************************" << endl;
                    cerr << "An unacceptable value is specified for an enumerated argument.\nThe offending command is ignored and has no other side effect\n" ;
                    cerr << filename << "( "<< line << " )"<< endl;
                    cerr << "**********************************************************************" << endl;
                break;
                case GL_INVALID_OPERATION:
                    cerr << "**********************************************************************" << endl;
                    cerr << "The specified operation is not allowed in the current state.\nThe offending command is ignored and has no other side effect\n" ;
                    cerr << filename << "( "<< line << " )"<< endl;
                    cerr << "**********************************************************************" << endl;
                break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                    cerr << "**********************************************************************" << endl;
                    cerr << "The framebuffer object is not complete.\nThe offending command is ignored" ;
                    cerr << filename << "( "<< line << " )"<< endl;
                    cerr << "**********************************************************************" << endl;
                break;
                case GL_STACK_UNDERFLOW:
                    cerr << "**********************************************************************" << endl;
                    cerr << "An attempt has been made to perform an operation that \nwould cause an internal stack to underflow\n" ;
                    cerr << filename << "( "<< line << " )"<< endl;
                    cerr << "**********************************************************************" << endl;
                break;
                case GL_STACK_OVERFLOW:
                    cerr << "**********************************************************************" << endl;
                    cerr << "An attempt has been made to perform an operation that \nwould cause an internal stack to overflow\n" ;
                    cerr << filename << "( "<< line << " )"<< endl;
                    cerr << "**********************************************************************" << endl;
                break;
                default:
                    cerr << "**********************************************************************" << endl;
                    cerr << "Unexpected error in\n" << filename << "( "  << line << " )"<< endl;
                    cerr << "**********************************************************************" << endl;
                break;
            }
            return false;
}
