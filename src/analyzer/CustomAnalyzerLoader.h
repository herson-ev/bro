
#ifndef CUSTOMANALYZERLOADER_H
#define	CUSTOMANALYZERLOADER_H

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

class CustomAnalyzerLoader {
public:
    static CustomAnalyzerLoader* getInstance();
    bool apply_dpi(string protocol);
    ~CustomAnalyzerLoader();

private:
    CustomAnalyzerLoader();
    static CustomAnalyzerLoader* single;
    const char* FILE_PATH = "/home/bro/config.txt";
    map<string, bool> dpi_protocols;
};

#endif	/* CUSTOMANALYZERLOADER_H */
