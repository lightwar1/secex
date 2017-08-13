/**
 * SeCEx
 * Server Command Executator
 * g++ main.cpp -o main.out -std=c++11
 */

#include <iostream>
#include <fstream>
#include <string>

#include "libraries/include.hpp"

using namespace std;
using json = nlohmann::json;

int main(int argc, char *argv[]) {

	LOG log;
	json config;
	ifstream configFile;
	sshclient::SSH client;

	cmdline::add('c', "config");
	cmdline::add('l', "log");

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

			for (auto data : config["commands"]) {
				cout << "data -- " << data << endl;
			}

			// TODO: причесать

			const char *hostChC = "dizoft.ru";
			const char *nameChC = "wiright";
			client.init(hostChC, nameChC); //use const char
			client.connect();
			client.exec_command("ls");
			client.exec_command("cat file");

		} else {
			log.print_log("file not found", "ERROR");
		}

		configFile.close();
		config.clear();
	} else {
		log.print_log("Not found some arguments. Try -h", "ERROR");
	}

	return 0;
}