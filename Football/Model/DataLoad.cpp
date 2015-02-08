/*
 * IO.cpp
 *
 *  Created on: 27/01/2015
 *      Author: Adriano
 */

#include "DataLoad.h"

map<unsigned int, FootballLeague*> DataLoad::analyseFolder(string dirName) {
	Utils::debugprint(string("Loading Dir: ").append(dirName));

	map<unsigned int, FootballLeague*> leagues;

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
				DataLoad::readMatchesToLeague((char *) currentFile, league);

				// Creates the desired indicator for all the data relative to the market stocks.
				//defineStrategies(stPointer);

				// Inserts the market stock within the stock map which contains all market stocks.
				if (strcmp(fileName, "^DJI.csv") != 0
						&& strcmp(fileName, "^GSPC.csv") != 0) {
					leagues[key] = league;
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

void DataLoad::readMatchesToLeague(char* filename, FootballLeague* league) {
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
		string homeTeamName, awayTeamName, date, homeTeamScore, awayTeamScore,
				homeOddsStr, drawOddsStr, awayOddsStr;
		int homeTeamGoals, awayTeamGoals;
		double homeOdds, drawOdds, awayOdds;
		vector<string> fields(CSV_FIELDS);
		string thisField, period, scannedLine;

		getline(newProcessing, scannedLine);
		stringstream iss(scannedLine);

		// Process all the fields of each record
		unsigned int w = 0;
		while (getline(iss, thisField, ',')) {
			fields[w++] = thisField;
		}

		stringstream sdate(fields[CSV_DATE]);
		stringstream shome(fields[CSV_HOME_TEAM_NAME]);
		stringstream saway(fields[CSV_AWAY_TEAM_NAME]);
		date = sdate.str();
		homeTeamName = shome.str();
		awayTeamName = saway.str();

		FootballTeam* homeTeam = league->getTeam(homeTeamName);
		FootballTeam* awayTeam = league->getTeam(awayTeamName);

		homeTeamScore = fields[CSV_HOME_TEAM_SCORE];
		awayTeamScore = fields[CSV_AWAY_TEAM_SCORE];
		homeTeamGoals = atoi((char*) homeTeamScore.c_str());
		awayTeamGoals = atoi((char*) awayTeamScore.c_str());

		homeOddsStr = fields[CSV_HOME_TEAM_ODDS];
		drawOddsStr = fields[CSV_DRAW_ODDS];
		awayOddsStr = fields[CSV_AWAY_ODDS];

		homeOdds = atof((char*) homeOddsStr.c_str());
		drawOdds = atof((char*) drawOddsStr.c_str());
		awayOdds = atof((char*) awayOddsStr.c_str());

		if (homeTeamName.size() > 0) {
			FootballGame* game = new FootballGame(date, homeTeam, awayTeam,
					homeTeamGoals, awayTeamGoals);
			league->addGame(game);
			game->setOdds(homeOdds, drawOdds, awayOdds);
		}
	}
	newProcessing.close();

}

DataLoad::~DataLoad() {
}

