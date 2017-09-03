/**
 * SeCEx
 * Server Command Executator
 * g++ main.cpp -o main.out -std=c++11
 */

#include <iostream>
#include <fstream>
#include <string>

#include "exceptions/include.hpp"
#include "libraries/include.hpp"

using namespace std;
using json = nlohmann::json;

#define LEVEL_DEBUG 0

// TODO: move in helperLibrary (DHelper (class?))
string& trim(string& s, char c) {
	for (unsigned short int i = 0; i < s.size(); i++) {
		if (s[i] == c) {
			s.erase(i, 1);
		}
	}

	return s;
}

int main(int argc, char *argv[]) {

	LOG log;
	json config;
	ifstream configFile;
	sshclient::SSH client;

	cmdline::add('c', "config");

	if (argc > 1) {
		cmdline::CMDLINE cmdArgs(argc, argv);

		configFile.open(cmdArgs.getString("config"));

		if (configFile) {

#if LEVEL_DEBUG == 1
			log.print_log("File open! Read config", "DEBUG");
#endif

			configFile >> config;

#if LEVEL_DEBUG == 1
			log.print_log("File parsed! Get all metadata", "DEBUG");
#endif

			client.init(config["host"].get<string>(), config["username"].get<string>());
			try {

				client.connect();

			} catch (AuthException& e) {
				log.print_log(e.what(), "ERROR");

				configFile.close();
				config.clear();

				return 1;
			}

			for (auto data : config["commands"]) {
				//TODO: need fix to get config from config
				cout << "data -- " << data << endl;
			}

			// TODO: причесать @bug
			client.exec_command("ls");
			// client.exec_command("ls");

		} else {
			log.print_log("file not found", "ERROR");
		}

		configFile.close();
		config.clear();

		return 1;
	} else {
		//TODO: not realized yet @tommorow
		// log.print_log("Not found some arguments. Try -h", "ERROR");
		log.print_log("Not found some arguments.", "ERROR");

		return 1;
	}

	return 0;
}