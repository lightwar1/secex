/**
 * CMDLINE interface
 * Created by DIZOFT
 *
 * Use this class with namespace for parsing
 * cmd arguments
 *
 * For help see README.md
 *
 * v 1.0
 */

#pragma once

#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <map>

namespace cmdline {

// TODO: посмотреть работу с вектором и добавить реализацию defaultValue
// std::vector<char> v;

/**
 * List of errors
 */
std::vector<const char*> errors;

/**
 * User command list (@see add)
 */
std::map<char, std::string> listCommands;

/**
 * Commands, geting from cmdLine
 */
std::map<std::string, std::string> commands;


/**
 * [add Add simple command]
 * @param short_name [command [-h]]
 * @param full_name  [full name of command (write in help and use for find) [help]]
 */
void add(char short_name,
         const char *full_name) {
  //TODO: remove it
  //debug
  /*  std::cout << "try to add : \n\t"
              << "-" << short_name << " "
              << "[" << description << "]\n";*/

  listCommands.insert(std::pair<char, std::string>(short_name, full_name));
}

class CMDLINE {

  /**
   * [checkArg]
   * @param argv [argument from cmdLine]
   */
  void checkArg(char *argv) {
    // convert to string, to use c++ libraries
    std::string arg(argv, strlen(argv));

    /**
     * get command
     *
     * example
     *
     * -[c]=config.json
     */
    std::string command = (arg.substr(0, arg.find('='))).substr(1, arg.length());

    char c = command[0];

    /**
     * get argument of command
     *
     * example
     *
     * -c=[config.json]
     */
    std::string argument = (arg.substr(arg.find('='), arg.length())).substr(1, arg.length());

    /**
     * Insert command
     *
     * example
     *
     * config | config.json
     * help | bla
     */
    commands.insert(std::pair<std::string, std::string>((*listCommands.find(c)).second, argument));
  }

  /**
   * TODO: перевести на С варинат поиска позиции [char] ch в [char*] str | make in C style find position in [char*] str by [char] ch
   *
   * [strchrplc description]
   * @param  str [description]
   * @param  ch  [description]
   * @return     [description]
   */
  unsigned short int strchrplc(char *str, char ch) {

  }

public:
  CMDLINE() {
    // cout << "init cmdline\n";
  }

  CMDLINE(int argc, char *argv[]) {
    if (argc > 1) {
      // TODO: перевести на C++11 for (foreach) | remake with C++11 for (foreach)
      for (int i = 1; i < argc; i++) {
        this->checkArg(argv[i]);
      }
    }
  }

  //TODO: переписать, используя template! | ReWrite using template!

  /**
   * [getString [string] value from cmdLine arguments by [char] key]
   * 
   * @param  key [key [char] for find]
   * @return     [value [string]]
   */
  std::string getString(char key) {
    //if in list of user commands have key
    if (listCommands.find(key) != listCommands.end()) {
      return (*commands.find((*listCommands.find(key)).second)).second;
    } else {
      // TODO: добавлять описание переменных
      // errors.push_back("cant find record with [char] key {" + key + "}");
      errors.push_back("cant find record with [char] key}");
      return NULL;
    }
  }

  /**
   * [get [string] value from cmdLine arguments by [string] key]
   * 
   * @param  key [description]
   * @return     [description]
   */
  std::string getString(std::string key) {
    //if in list of user commands have key
    if (commands.find(key) != commands.end()) {
      return (*commands.find(key)).second;
    } else {
      // TODO: добавлять описание переменных
      // errors.push_back("cant find record with [char] key {" + key + "}");
      errors.push_back("cant find record with [string] key");
      return NULL;
    }
  }

  /**
   * [getInt [int] value from cmdLine arguments]
   * 
   * @param  key [key [char] for find]
   * @return     [value [int]]
   */
  /*  int getInt(char key) {
      if (listCommands.find(key) != listCommands.end()) {
        return (*listCommands.find(key)).second;
      } else {
        return NULL;
      }
    }*/
};
}
