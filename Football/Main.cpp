//============================================================================
// Name        : MyApp.cpp
// Author      : Adriano
// Version     :
// Copyright   : Your copyright notice
//============================================================================

#include "Main.h"

map<string, string> Main::configMap = map<string, string>();

//map<unsigned int, Stock> analyseFolder(string dir, bool reverse);

void loadConfig(char* configFilename) {
	ifstream configFile(configFilename);

	if (!configFile.is_open() || !configFile.good()) {
		configFile.close();
		configFile.clear();

		//File given as parameter does not exist, or no parameter where given
		char defaultFilename[] = "default.conf";
		configFilename = defaultFilename;
		configFile.open(configFilename);

		//configFile.open(configFilename);
		if (!configFile.is_open() && !configFile.good()) {
			printf(
					"No file given as paramater, and no default file. Quitting\n");
			exit(1);
		}
	}
	printf("Loading configuration file: %s\n", configFilename);

	string scannedLine;
	char* linha = NULL;
	string key;
	string value;

	while (!configFile.eof()) {
		getline(configFile, scannedLine);
		if (scannedLine.size() == 0 || scannedLine[0] == '#'
				|| scannedLine[0] == '\r' || scannedLine[0] == '\n') {
			continue; //It's a comment or null line
		} else {
			linha = (char*) malloc(
					int(sizeof(char) * (scannedLine.size() + 1)));
			strcpy(linha, scannedLine.c_str());
			char* tok = strtok(linha, " =");
			key = string(tok);
			tok = strtok(NULL, " =\r");
			value = string(tok);
			Main::configMap[key] = value;
		}
	}
	configFile.close();
	printf("Configuration file loaded\n");
}

int main(int argc, char **argv) {
	if (argc > 2) {
		printf("Invalid number of arguments.\n");
		return EXIT_FAILURE;
	} else {
		if (argc == 2)
			loadConfig(argv[1]);
		else
			loadConfig(NULL);

		// Detecting the algorithm to use
		string algorithm = Main::configMap[string("algorithm")];

		if (!algorithm.compare("football")) {
			map<unsigned int, FootballLeague> leagues = Utils::analyseFolder(
					Main::configMap[string("dirCotacoes")], false);
			printf("Executing Football\n");
			map<unsigned int, FootballLeague>::iterator i;
			for (i = leagues.begin(); i != leagues.end(); i++) {
				i->second.debugPrint();
			}
			/*std::random_device rd;
			 std::mt19937 gen(rd());
			 // if an event occurs 4 times a minute on average
			 // how often is it that it occurs n times in one minute?
			 std::poisson_distribution<> d(4);
			 printf("Poisson res: %d %d.\n", d(gen), d(gen));*/
		} else {
			printf("Unknown Algorithm:%s\n", algorithm.c_str());
		}

	}
	return EXIT_SUCCESS;
}
