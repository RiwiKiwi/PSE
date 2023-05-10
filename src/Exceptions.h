/**
 * Enkele exceptions.
 */

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

using namespace std;


/**
 * class IllegalArgumentException is a class that is derived from the Standard std::exception class.
 * it is used as an exception when a method/function is called with an illegal argument.
 */
class IllegalArgumentException: public exception{
    
    const char* message;
public:
    /**
     * Constructor for an IllegalArgumentException
     * @param message: the string identifying the actual exception.
     */
    IllegalArgumentException(const char * message){
        this->message = message;
    }
    
    /**
     * Get the string identifying the exception
     * Returns a null terminated character sequence that may be used to identify the exception.
     */
    virtual const char* what() const throw(){
        return message;
    }
};


#endif
