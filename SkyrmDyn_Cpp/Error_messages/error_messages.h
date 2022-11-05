#ifndef ERROR_MESSAGES_H
#define ERROR_MESSAGES_H

#include <string>

#define AssignationError( var ) ( std::string("Error in ") + __FILE__ + "  :  " + __FUNCTION__ + std::string("  : assignation of ") + std::string( var ) + std::string(" failed.") )

#define DeclarationError( var ) ( std::string("Error in ") + __FILE__ + "  :  " + __FUNCTION__ + std::string("  : declaration of ") + std::string( var ) + std::string(" failed.") )

#define UnfoudVariableError( var ) ( std::string("Error in ") + __FILE__ + "  :  " + __FUNCTION__ + std::string("  :  ") + std::string( var ) + std::string(" not found.") )

#define OperationError( operation, var ) ( std::string("Error in ") + __FILE__ + "  :  " + __FUNCTION__ + std::string( operation ) + std::string( var ) + std::string(" failed.") )

#define OperationImpossible( operation, var, cause ) ( std::string("Error in ") + __FILE__ + "  :  " + __FUNCTION__ + std::string( operation ) + std::string(" impossible because ") + std::string( var ) + std::string( " provoked " ) + std::string( cause ) + std::string( "." ) )

#endif // ERROR_MESSAGES_H
