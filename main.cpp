/**
 * SeCEx
 * Server Command Executator
 * g++ main.cpp -o main.out -std=c++11
 */

#include <iostream>
#include <fstream>
#include <string>

#include "libraries/include.hpp"
#include "log.hpp"

using namespace std;
using json = nlohmann::json;

int main(int argc, char *argv[]) {

	LOG log;
	cmdline::add('c', "config");

	json config;
	// json temp;
	ifstream configFile;

	if (argc > 1) {
		cmdline::CMDLINE cmdArgs(argc, argv);

		configFile.open(cmdArgs.get("config"));

		if (configFile) {

#if LEVEL_DEBUG
			log.print_log("File open! Read config", "DEBUG");
#endif

			configFile >> config;

#if LEVEL_DEBUG
			log.print_log("File parsed! Get all metadata", "DEBUG");
#endif

			for (auto data : config["commands"]) {
				cout << "data -- " << data << endl;
			}

		} else {
			log.print_log("file not found", "ERROR");
		}

		configFile.close();
		config.clear();
	} else {
		log.print_log("Not found some arguments. Try -h or --help", "ERROR");
	}

	return 0;
}