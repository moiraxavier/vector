//
// Created by Mairenn on 2019-06-02.
//

#ifndef LAB4_VECTOREXCEPTION_H
#define LAB4_VECTOREXCEPTION_H

#include <iostream>

class VectorException : public std::exception
{
private:
    std::string m_error;
public:
    VectorException(std::string error) : m_error(error) {}
    const char* what() const noexcept override { return m_error.c_str(); }
    ~VectorException() override {}
};



#endif //LAB4_VECTOREXCEPTION_H
