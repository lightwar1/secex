#ifndef DIZOFT_SSH2_HPP
#define DIZOFT_SSH2_HPP

#include "libssh2.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>

#include "../log/log.hpp"

namespace sshclient2 {

libssh2::session session;

class SSH {
public:
	SSH() {
	}

	/**
	 *
	 */
	SSH(std::string host, unsigned short int port = 22) {
		this->connect(host, port);
	}

	/**
	 * [connect description]
	 * @param host [description]
	 * @param port [description]
	 */
	void connect(const std::string& host, const unsigned short int& port = 22) {
		session.open(host, port);
	}

	void exec_command(std::string& command) {

	}
}; // class SSH
} // namespace sshclient2

#endif /* DIZOFT_SSH2_HPP */