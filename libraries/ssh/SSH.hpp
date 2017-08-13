/**
 * This is file is a module for work with libssh
 *
 * Copyright (c) 2017 by DIZOFT (WiRight)
 *
 * The SSH Library is free software;
 *
 * v 1.0
 */

#ifndef DIZOFT_SSH_HPP
#define DIZOFT_SSH_HPP

#pragma once

#include <libssh/libssh.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>

#include "../log/log.hpp"

namespace sshclient {

ssh_session session;

class SSH {
private:

	/**
	 * [verify_knownhost description]
	 * @return [description]
	 */
	short int verify_knownhost() {
		int state, hlen;
		unsigned char *hash = NULL;
		char *hexa;
		char buf[10];

		state = ssh_is_server_known(session);
		hlen = ssh_get_pubkey_hash(session, &hash);
		if (hlen < 0) {
			return -1;
		}
		switch (state) {
		case SSH_SERVER_KNOWN_OK:
			break; /* ok */
		case SSH_SERVER_KNOWN_CHANGED:
			std::cerr << "Host key for server changed: it is now:\n";
			ssh_print_hexa("Public key hash", hash, hlen);
			std::cerr << "For security reasons, connection will be stopped\n";
			free(hash);
			return -1;
		case SSH_SERVER_FOUND_OTHER:
			std::cerr << "The host key for this server was not found but an other type of key exists.\n";
			std::cerr << "An attacker might change the default server key to confuse your client into thinking the key does not exist\n";
			free(hash);
			return -1;
		case SSH_SERVER_FILE_NOT_FOUND:
			std::cerr << "Could not find known host file.\n";
			std::cerr << "If you accept the host key here, the file will be automatically created.\n";
		/* fallback to SSH_SERVER_NOT_KNOWN behavior */
		case SSH_SERVER_NOT_KNOWN:
			hexa = ssh_get_hexa(hash, hlen);
			std::cerr << "The server is unknown. Do you trust the host key? [yes/no]\n";
			std::cerr << "Public key hash: " << hexa << std::endl;
			free(hexa);
			if (fgets(buf, sizeof(buf), stdin) == NULL) {
				free(hash);
				return -1;
			}
			if (strncasecmp(buf, "yes", 3) != 0) {
				free(hash);
				return -1;
			}
			if (ssh_write_knownhost(session) < 0) {
				std::cerr << "Error: " << std::endl;
				free(hash);
				return -1;
			}
			break;
		case SSH_SERVER_ERROR:
			std::cerr << "Error :" << ssh_get_error(session);
			free(hash);
			return -1;
		}
		free(hash);
		return 0;
	}



	/********* EXECUTE COMMAND **********/

	int show_remote_processes(const char *command) {
		ssh_channel channel;
		int rc;
		char buffer[256];
		int nbytes;
		channel = ssh_channel_new(session);
		if (channel == NULL) {
			return SSH_ERROR;
		}
		rc = ssh_channel_open_session(channel);
		if (rc != SSH_OK) {
			ssh_channel_free(channel);
			return rc;
		}
		rc = ssh_channel_request_exec(channel, command);
		if (rc != SSH_OK) {
			ssh_channel_close(channel);
			ssh_channel_free(channel);
			return rc;
		}
		nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
		while (nbytes > 0) {
			if (write(1, buffer, nbytes) != (unsigned int) nbytes) {
				ssh_channel_close(channel);
				ssh_channel_free(channel);
				return SSH_ERROR;
			}
			nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
		}

		if (nbytes < 0)
		{
			ssh_channel_close(channel);
			ssh_channel_free(channel);
			return SSH_ERROR;
		}
		ssh_channel_send_eof(channel);
		ssh_channel_close(channel);
		ssh_channel_free(channel);
		return SSH_OK;
	}

	/********* /EXECUTE COMMAND *********/

	/**
	 * [free Free from memory. Called by desstructor and any functions]
	 */
	void freeSSH() {
		ssh_disconnect(session);
		ssh_free(session);
	}


public:
	short int connection;

	/**
	 *
	 */
	SSH() {
		session = ssh_new();
		if (session == NULL) {
			// TODO: переделать на класс SessionException | remake in SessionException
			throw "Cant create session!";
		}

		this->connection = 0;
	}

	/**
	 * [init description]
	 * @param host     [description]
	 * @param username [description]
	 * @param port     [description]
	 */
	void init(std::string *host, std::string *username, unsigned short int port = 22) {
		ssh_options_set(session, SSH_OPTIONS_HOST, host->c_str());
		ssh_options_set(session, SSH_OPTIONS_USER, username->c_str());
		ssh_options_set(session, SSH_OPTIONS_PORT, &port);
	}

	/**
	 * [init description]
	 * @param host     [description]
	 * @param username [description]
	 * @param port     [description]
	 */
	void init(const char *host, const char *username, unsigned short int port = 22) {
		ssh_options_set(session, SSH_OPTIONS_HOST, host);
		ssh_options_set(session, SSH_OPTIONS_USER, username);
		ssh_options_set(session, SSH_OPTIONS_PORT, &port);
	}

	/**
	 * [getStatusConnect description]
	 * @return [description]
	 */
	short int getStatusConnect() {
		return this->connection;
	}

	/**
	 * [connect description]
	 */
	void connect() {
		std::cout << "Try connect...\n";
		this->connection = ssh_connect(session);

		if (this->connection == SSH_OK) {
			std::cout << "CONNECT!!!!!!\n";

			if (this->verify_knownhost() < 0) {
				std::cerr << "PIZDEC\n";
				ssh_disconnect(session);
				ssh_free(session);
			}

			std::cout << "All OK\n";

			/***** AUTHORIZE *****/
			// TODO: in function
			int rc;
			const char *password = "2580";
			rc = ssh_userauth_password(session, NULL, password);

			if (rc != SSH_AUTH_SUCCESS) {
				std::cerr << "Error authenticating with password: " << ssh_get_error(session) << "\n";
				ssh_disconnect(session);
				ssh_free(session);
				exit(-1);
			}
			/***** /AUTHORIZE *****/

			std::cout << "CAN AUTHORIZE!!!\n";

		} else {
			// TODO: переделать на класс ConnectException | remake in ConnectException
			throw "Cant connect!";
		}
	}

	void exec_command(const char *command) {
		if (this->show_remote_processes(command) != SSH_OK) {
			std::cerr << "Error executing request\n";
			ssh_get_error(session);
			ssh_disconnect(session);
			ssh_free(session);
			// TODO: переделать на класс ExecCommandException | remake in ExecCommandException
			throw "Cant exec command!";
		} else {
			std::cout << "\n\n====================\nRequest completed successfully!\n";
		}
	}

	~SSH() {
		this->freeSSH();
	}

}; // class SSH

} // namespace sshclient

#endif /* DIZOFT_SSH_HPP */