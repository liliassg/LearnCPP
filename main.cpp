#include "include/wrapper.h"
#include "interface/interface.h"
#include "machine/statemachine.h"
#include "parser/parser.h"
#include "lexer/lexer.h"
#include "compiler/tcompiler.h"
#include "database/database.h"
#include<functional>
#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>

void setup_db() {
    database::ParseTXT parser;
    database::ParseCONFIG config;
    std::vector<std::string> files{};
    for (const std::string& rdfile : config.readfiles()) {
        std::ifstream local_file(rdfile);
        if (!local_file) {
            std::cout << "error parsing file: " << rdfile << std::endl;
            continue;
        }
        std::stringstream cache;
        cache << local_file.rdbuf();
        files.push_back(cache.str());
    }
    for (const std::string file : files) {
        parser.parseFile(file);
    }
    std::string intro = parser.confirmTitle("HALLO");
    if (parser.lastErr) {
        return;
    }
    parser.visualizeText(intro, 0, 3);
}

void setup() {
    setup_db();
}

int main() {
    setup();
}