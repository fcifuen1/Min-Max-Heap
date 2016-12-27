/*
 * File:    MyException.h
 * Author:  Federico Cifuentes-Urtubey
 * Date:    4/15/16
 *
 * Definition of the MyException class.
 */

#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <iostream>
#include <string>

class MyException
{
  public:
  
    /* MyException() - constructor
     * pre - pass in a string to describe an error
     * post - sets the error message of the exception
     */
    MyException(std::string message) : m_message(message) {}
  
    /* getMessage()
     * pre - none
     * post - returns the message of an exception object
     */
    const std::string getMessage() { return m_message; }
  
  private:
    std::string m_message; // The error message
};

#endif