#include <iostream>
#include <fstream>
#include <string>

#include "json.hpp"
#include "cmdline.h"
#include "log.hpp"

using namespace std;
using json = nlohmann::json;

int main(int argc, char const *argv[]){

	LOG log;
	json config, temp;
	ifstream configFile("config.json");

	if (configFile){
		stringstream ss;
		ss << configFile.rdbuf();

		config = json::parse(ss.str());

		// cout << "DEBUG : " << config.size() << endl << temp << endl << temp["username"];
	} else {
		log.print_log("file not found", "ERROR");
	}

	configFile.close();

/*	json j = {
		{"name", "Ruslan"},
		{"age", 21}
	};*/

/*	json j;
	j["name"] = "ruslan";
	j["configFilefo"]["age"] = 21;*/

	// cout << "size = " << j.size() << endl << j.dump() << endl ;

	return 0;
}