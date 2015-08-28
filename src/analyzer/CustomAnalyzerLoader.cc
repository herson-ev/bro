#include "CustomAnalyzerLoader.h"

CustomAnalyzerLoader* CustomAnalyzerLoader::single = NULL;

CustomAnalyzerLoader::CustomAnalyzerLoader()
{
	read_config_file_now();
	
	thread polling_thread(&CustomAnalyzerLoader::poll_config_file, this);
	polling_thread.detach();	
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
    return dpi_protocols.find(protocol)->second;
}

/**
 * This function reads the configuration file and loads it to a memory map
 * called: map<string, bool> dpi_protocols.
 * It is called from the Constructor when the class is initialized
 */ 
void CustomAnalyzerLoader::read_config_file_now()
{
	map<string, bool> tmp_map;
	string line;
    ifstream configFile(CustomAnalyzerLoader::FILE_PATH);
    if (configFile.is_open())
    {
        while (getline(configFile, line))
        {
            string proto, value;
            stringstream input_stringstream(line);
            getline(input_stringstream, proto, ' ');
            getline(input_stringstream, value, ' ');
            
            tmp_map.insert(pair<string, bool>(proto, std::stoi(value)));                    
        }
        configFile.close();
    } else
    {
        cerr << "Unable to open file " << FILE_PATH << endl;
    }
    swap(tmp_map, dpi_protocols);
    //print_map_ds();
}

/**
 * One thread will keep polling the config file just in case some change in
 * the policy is applied.
 */ 
void CustomAnalyzerLoader::poll_config_file()
{
	while(true)
	{
		this_thread::sleep_for(chrono::milliseconds(MILLIS));
		read_config_file_now();
	}
}

/**
 * Prints the map data structure for debugging purposes
 * 
 */
void CustomAnalyzerLoader::print_map_ds()
{
	for (map<string, bool>::iterator it = CustomAnalyzerLoader::dpi_protocols.begin(); 
			it != CustomAnalyzerLoader::dpi_protocols.end(); ++it)
	{
		cout << it->first << " : " << it->second << endl;
	}
	cout << endl;
}
