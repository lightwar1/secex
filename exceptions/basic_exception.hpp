/**
 * BasicExecption
 *
 * v 1.0
 */

#ifndef BASIC_EXCEPTION_HPP
#define BASIC_EXCEPTION_HPP

#pragma once

#include <exception>

class BasicException : public std::exception {

	const char *message;

public:
	BasicException(const char *message){
		this->message = message;
	}

	virtual const char *what() const throw() {
		return this->message;
	}

	// TODO: посмотреть, почему и так и так работает (без const throw())
	// virtual const char * what() {
	// 	return "basic_exception.hpp!!";
	// }
}; // class BasicException

#endif /* BASIC_EXCEPTION_HPP */