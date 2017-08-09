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

	ifstream in("config.json");

	if (in){
		string jsonData = "";
		log.print_log("from log", "INFO");

		stringstream ss;
		ss << in.rdbuf();

		log.print_log(ss.str(), "DEBUG");
	} else {
		log.print_log("file not found", "ERROR");
	}

	in.close();

/*	json j = {
		{"name", "Ruslan"},
		{"age", 21}
	};*/

/*	json j;
	j["name"] = "ruslan";
	j["info"]["age"] = 21;*/

	// cout << "size = " << j.size() << endl << j.dump() << endl ;

	return 0;
}