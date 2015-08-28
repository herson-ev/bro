
#ifndef CUSTOMANALYZERLOADER_H
#define	CUSTOMANALYZERLOADER_H

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
// Two libraries used for polling the config file every "x" seconds
#include <thread>
#include <chrono>

using namespace std;

class CustomAnalyzerLoader {
public:
    static CustomAnalyzerLoader* getInstance();
    bool apply_dpi(string protocol);
    ~CustomAnalyzerLoader();

private:
    CustomAnalyzerLoader();
    void read_config_file_now();
    void print_map_ds();
    static CustomAnalyzerLoader* single;
    //const char* FILE_PATH = "/home/bro/config.txt";
    const char* FILE_PATH = "/home/herson/config.txt";
    map<string, bool> dpi_protocols;
    const unsigned int MILLIS = 3000;

    void poll_config_file();
};

#endif	/* CUSTOMANALYZERLOADER_H */
