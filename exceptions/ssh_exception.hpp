#ifndef SSH_EXCEPTION_HPP
#define SSH_EXCEPTION_HPP

#include "basic_exception.hpp"

class SshException : public BasicException {

public:
	SshException(const char *message) : BasicException(message) {
	}
}; //class SshException

#endif /* SSH_EXCEPTION_HPP */