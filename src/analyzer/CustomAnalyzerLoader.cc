#include "CustomAnalyzerLoader.h"

CustomAnalyzerLoader* CustomAnalyzerLoader::single = NULL;

CustomAnalyzerLoader::CustomAnalyzerLoader()
{
    string line;
    ifstream configFile(FILE_PATH);
    if (configFile.is_open())
    {
        while (getline(configFile, line))
        {
            string proto, value;
            stringstream input_stringstream(line);
            getline(input_stringstream, proto, ' ');
            getline(input_stringstream, value, ' ');
            
            dpi_protocols.insert(pair<string, bool>(proto, std::stoi(value)));                    
        }
        configFile.close();
    } else
    {
        cerr << "Unable to open file " << FILE_PATH << endl;
    }
}

CustomAnalyzerLoader::~CustomAnalyzerLoader()
{
    CustomAnalyzerLoader::single = NULL;
    cout << "leaving..." << endl;
}

CustomAnalyzerLoader* CustomAnalyzerLoader::getInstance()
{
    if (single == NULL)
        single = new CustomAnalyzerLoader();

    return single;
}

bool CustomAnalyzerLoader::apply_dpi(string protocol)
{
    return CustomAnalyzerLoader::dpi_protocols.find(protocol)->second;
}
