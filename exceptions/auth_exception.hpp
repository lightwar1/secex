#ifndef AUTH_EXCEPTION_HPP
#define AUTH_EXCEPTION_HPP

#include "basic_exception.hpp"

class AuthException : public BasicException {

public:
	AuthException(const char *message) : BasicException(message) {
	}
}; //class AuthExecption

#endif /* AUTH_EXCEPTION_HPP */