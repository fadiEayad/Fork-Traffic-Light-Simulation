#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <list>

using namespace std;

int counter = 0;

struct cars {
	string plate;
	string direction;
	int time;
	cars(string x) {
		string t;
		stringstream ss(x);
		ss >> plate >> direction >> time;
		ss.str("");
	}
};

void printCars(list<cars> &car, int max) {	//function to print to screen
	pid_t pid;
	for (int i = 0; i < max; i++) {
		if (car.empty()) {
			break;
		}
		else {
			pid = fork();	//creating child process
			if (pid == 0) {	//if child
				cout << "Car " << car.front().plate << " is using the intersection for " << car.front().time << " sec(s)." << endl;
				sleep(car.front().time);
				exit(0);
			}
			else {	//if parent
				wait(0);
				car.pop_front();
			}
			counter--;	//decrementing car counter by 1
		}
	}
}


int main() {
	list<cars> Ncars;
	list<cars> Ecars;
	list<cars> Scars;
	list<cars> Wcars;

	string initialDir;
	string mC;
	int maxCars;
	string p, d, t;

	cin >> initialDir;
	cin >> maxCars;

	string line;
	while (getline(cin, line)) {
		stringstream ss(line);
		ss >> p >> d >> t;
		cars newCar(line);
		if (d == "N") {
			Ncars.push_back(newCar);
		}
		else if (d == "E") {
			Ecars.push_back(newCar);
		}
		else if (d == "S") {
			Scars.push_back(newCar);
		}
		else if (d == "W") {
			Wcars.push_back(newCar);
		}

		ss.str("");
		counter++;
	}

	if (initialDir == "N") {		//start from North if that's the initial direction
		while (counter > 1) {
			if (!Ncars.empty()) {
				cout << "Current direction: Northbound\n";
				printCars(Ncars, maxCars);
			}
			if (!Ecars.empty()) {
				cout << "Current direction: Eastbound\n";
				printCars(Ecars, maxCars);
			}
			if (!Scars.empty()) {
				cout << "Current direction: Southbound\n";
				printCars(Scars, maxCars);
			}
			if (!Wcars.empty()) {
				cout << "Current direction: Westbound\n";
				printCars(Wcars, maxCars);
			}
		}
	}
	else if (initialDir == "E") {	//start from East if that's the initial direction
		while (counter > 1) {
			if (!Ecars.empty()) {
				cout << "Current direction: Eastbound\n";
				printCars(Ecars, maxCars);
			}
			if (!Scars.empty()) {
				cout << "Current direction: Southbound\n";
				printCars(Scars, maxCars);
			}
			if (!Wcars.empty()) {
				cout << "Current direction: Westbound\n";
				printCars(Wcars, maxCars);
			}
			if (!Ncars.empty()) {
				cout << "Current direction: Northbound\n";
				printCars(Ncars, maxCars);
			}
		}
	}
	else if (initialDir == "S") {	//start from South if that's the initial direction
		while (counter > 1) {
			if (!Scars.empty()) {
				cout << "Current direction: Southbound\n";
				printCars(Scars, maxCars);
			}
			if (!Wcars.empty()) {
				cout << "Current direction: Westbound\n";
				printCars(Wcars, maxCars);
			}
			if (!Ncars.empty()) {
				cout << "Current direction: Northbound\n";
				printCars(Ncars, maxCars);
			}
			if (!Ecars.empty()) {
				cout << "Current direction: Eastbound\n";
				printCars(Ecars, maxCars);
			}
		}
	}
	else if (initialDir == "W") {	//start from West if that's the initial direction
		while (counter > 1) {
			if (!Wcars.empty()) {
				cout << "Current direction: Westbound\n";
				printCars(Wcars, maxCars);
			}
			if (!Ncars.empty()) {
				cout << "Current direction: Northbound\n";
				printCars(Ncars, maxCars);
			}
			if (!Ecars.empty()) {
				cout << "Current direction: Eastbound\n";
				printCars(Ecars, maxCars);
			}
			if (!Scars.empty()) {
				cout << "Current direction: Southbound\n";
				printCars(Scars, maxCars);
			}
		}
	}


	return 0;
}
