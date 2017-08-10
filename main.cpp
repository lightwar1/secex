/**
 * SeCEx
 * Server Command Executator 
 * g++ main.cpp -o main.out -std=c++11
 */

#include <iostream>
#include <fstream>
#include <string>

#include "json.hpp"
#include "cmdline.h"
#include "log.hpp"

using namespace std;
using json = nlohmann::json;

int main(int argc, char const *argv[]) {

	LOG log;
	json config;
	// json temp;
	ifstream configFile("config.json");

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

	return 0;
}