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
	string plate;	//license plate of car
	string direction;	//direction where car is going
	int time;	//time for car to pass intersection
	cars(string x) {
		stringstream ss(x);
		ss >> plate >> direction >> time;	//storing info into "plate", "direction", and "time"
		ss.str("");	//clear ss
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
				sleep(car.front().time);	//sleep until car passes intersection
				exit(0);	//end child process
			}
			else {	//if parent
				wait(0);	//wait for child process(es)
				car.pop_front();	//remove car from list
			}
			counter--;	//decrementing car counter by 1
		}
	}
}


int main() {
	list<cars> Ncars;	//creating list for Northbound cars
	list<cars> Ecars;	//creating list for Eastbound cars
	list<cars> Scars;	//creating list for Southbound cars
	list<cars> Wcars;	//creating list for Westbound cars

	string initialDir;
	string mC;
	int maxCars;
	string p, d, t;

	cin >> initialDir;	//storing initial direction
	cin >> maxCars;	//storing max numbers of cars that can pass intersection from same direction before switching direction

	string line;
	while (getline(cin, line)) {	//reding from file
		stringstream ss(line);
		ss >> p >> d >> t;	//storing license plate, direction, and time into "p", "d", and "t", respectively
		cars newCar(line);	//creating cars object
		if (d == "N") {	//if car is going North
			Ncars.push_back(newCar);	//store car into Northbound list
		}
		else if (d == "E") {	//if car is going East
			Ecars.push_back(newCar);	//store car into Eastbound list
		}
		else if (d == "S") {	//if car is going South
			Scars.push_back(newCar);	//store car into Southbound list
		}
		else if (d == "W") {	//if car is going West
			Wcars.push_back(newCar);	//store car into Westbound list
		}

		ss.str("");	//clear ss
		counter++;	//increment counter of total cars
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
