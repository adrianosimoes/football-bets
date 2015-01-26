/*
 * utils.cpp
 *
 *  Created on: 26/01/2015
 *      Author: Adriano
 */

#include "Utils.h"
using namespace std;

void Utils::debugprint(string print) {
	if (!Main::configMap[string("debug")].compare("true")) {
		printf("%s\n", print.c_str());
	}
}

void Utils::print(string print) {
	printf("%s\n", print.c_str());
}

bool Utils::debugOn() {
	return !Main::configMap[string("debug")].compare("true");
}

map<unsigned int, FootballLeague> Utils::analyseFolder(string dirName,
		bool reverse) {
	Utils::debugprint(string("Loading Dir: ").append(dirName));

	map<unsigned int, FootballLeague> leagues;

	const char* dir = dirName.c_str();
	DIR *dirPt = opendir(dir);
	struct dirent *ep;

	unsigned int key = 0;

	if (dirPt != NULL) {
		string filepath(dirName);

		while ((ep = readdir(dirPt))) {
			if (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0) {

				char* filepath = (char*) malloc(
						(int) (sizeof(char) * strlen(dir) + strlen(ep->d_name)
								+ 2));

				char *fileName = ep->d_name;

				filepath[0] = '\0';
				strcat(filepath, dir);

				if (dir[strlen(dir) - 1] != '/') {
					strcat(filepath, "/");
				}

				strcat(filepath, ep->d_name);

				const char *currentFile = filepath;

				//Ignore entry if it is a directory
				ifstream stockFile((char *) currentFile);
				string scannedLine;
				getline(stockFile, scannedLine);

				if (stockFile.is_open()
						&& !(stockFile.rdstate() & ifstream::badbit)) {
					stockFile.close();
					stockFile.clear();
				} else {
					stockFile.close();
					stockFile.clear();
					continue;
				}

				// Creates the appropriated stock
				FootballLeague* league = new FootballLeague();
				Utils::readMatchesToLeague((char *) currentFile, league);

				// Creates the desired indicator for all the data relative to the market stocks.
				//defineStrategies(stPointer);

				// Inserts the market stock within the stock map which contains all market stocks.
				if (strcmp(fileName, "^DJI.csv") != 0
						&& strcmp(fileName, "^GSPC.csv") != 0) {
					leagues[key] = *league;
					cout << "Created " << league->getName() << " with key "
							<< key << endl;
					++key;
				}
			}
		}
		closedir(dirPt);
	} else
		printf("Error: Cannot open dir\n");

	return leagues;
}

void Utils::readMatchesToLeague(char* filename, FootballLeague* league) {
	string temp(filename);

// Splits the complete filename
	char *ticker = strtok(filename, "/");
	ticker = strtok(NULL, "/");
	ticker = strtok(ticker, ".");

// Initializes the League fields
	league->setName(ticker);

// File Processing in order to fill the desired vectors
	ifstream newProcessing(temp.c_str());
	newProcessing.seekg(ios::beg);

// Discarding the first line of the file
	ifstream file(temp.c_str());

	string discardLine;
	getline(newProcessing, discardLine);

	while (!newProcessing.eof()) {
		string homeTeamName, awayTeamName, date, homeTeamScore, awayTeamScore;
		int homeTeamGoals, awayTeamGoals;
		vector<string> fields(CSV_FIELDS);
		string field, period, scannedLine;

		getline(newProcessing, scannedLine);
		stringstream iss(scannedLine);

		// Process all the fields of each record
		unsigned int w = 0;
		while (getline(iss, field, ',')) {
			fields[w++] = field;
		}

		stringstream sdate(fields[CSV_DATE]);
		stringstream shome(fields[CSV_HOME_TEAM_NAME]);
		stringstream saway(fields[CSV_AWAY_TEAM_NAME]);
		date = sdate.str();
		homeTeamName = shome.str();
		awayTeamName = saway.str();
		homeTeamScore = fields[CSV_HOME_TEAM_SCORE];
		awayTeamScore = fields[CSV_AWAY_TEAM_SCORE];
		homeTeamGoals = atoi((char*) homeTeamScore.c_str());
		awayTeamGoals = atoi((char*) awayTeamScore.c_str());
		FootballTeam* homeTeam = league->getTeam(homeTeamName);
		FootballTeam* awayTeam = league->getTeam(awayTeamName);
		FootballGame* game = new FootballGame(date, homeTeam, awayTeam,
				homeTeamGoals, awayTeamGoals);

		league->addGame(game);

	}
	newProcessing.close();

}
