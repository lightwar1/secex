/**
 * SeCEx
 * Server Command Executator
 * g++ main.cpp -o main.out -std=c++11
 */

#include <iostream>
#include <fstream>
#include <string>

#include "json.hpp"
#include "cmdline.hpp"
#include "log.hpp"

using namespace std;
using json = nlohmann::json;

int main(int argc, char *argv[]) {

	LOG log;
	//TODO: разобраться
	// cmdline::parser argParser;
	//TODO: переделать на класс
	//CMDLINE cmdline(argc, **argv);

	json config;
	// json temp;
	ifstream configFile;

	// TODO: разобраться
	// argParser.add<string>("host", 'h', "hostname", true, 0);
	// argParser.parse_check(argc, argv);

	if (argc > 1) {
		configFile.open(argv[1]);

		if (configFile) {
			log.print_log("File open! Read config", "DEBUG");

			configFile >> config;

			log.print_log("File parsed! Get all metadata", "DEBUG");

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