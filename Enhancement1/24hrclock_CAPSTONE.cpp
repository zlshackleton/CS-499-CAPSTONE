#include <iostream> 
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

// The class Time that encapsulates all our timely needs
class Time {
public:
	int hours, minutes, seconds;
	string ampm;

	Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {}

	// Func to add hours
	void addHour() {
		hours++;
		if (hours == 24) hours = 0;
	}

	// Func to add minutes
	void addMinute() {
		minutes++;
		if (minutes == 60) {
			addHour(), minutes = 0;
		}
	}

	// Func to add seconds
	void addSecond() {
		seconds++;
		if (seconds == 60) {
			addMinute(), seconds = 0;
		}
	}

	// Displays time in 24 hour format
	void displayTime() {
		cout << "24-Hour Format: " << setw(2) << hours << ":" << setw(2) << minutes << ":" << setw(2) << seconds << endl;
	}

	// Save set time to the file time.txt
	void saveTimeToFile() {
		ofstream outputFile("time.txt", ios::trunc);
		if (outputFile) {
			outputFile << hours << " " << minutes << " " << seconds;
		}
		else {
			cout << "Error: Could not fetch file" << endl;
		}
		outputFile.close();
	}

	// Load time from the file time.txt
	void loadTimeFromFile() {
		ifstream inputFile("time.txt");
		if (inputFile) {
			inputFile >> hours >> minutes >> seconds;
		}
		else {
			cout << "Warning: No saved time found, starting at default." << endl;
		}
	}

	// Dynamic Clock that increments by second
	void runClock() {
		while (true) {
			system("cls");
			displayTime();
			this_thread::sleep_for(chrono::seconds(1));
			addSecond();
		}
	}
};

// Main function
int main() {
	Time clock(13, 55, 55);

	clock.loadTimeFromFile();

	int userOption = 0;
	while (userOption != 3) {
		clock.displayTime();

		// Show menu
		cout << "***************************" << endl;
		cout << "* 1 - Change Time         *" << endl;
		cout << "* 2 - Start Time          *" << endl;
		cout << "* 3 - Exit Program        *" << endl;
		cout << "* 4 - Clear Interface     *" << endl;
		cout << "***************************" << endl;
		cout << "Select an option: ";

		// Checks if user entered a proper number
		if (!(cin >> userOption)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		switch (userOption) {
		case 1: {
			int h, m, s;
			cout << "Enter new time (HH MM SS): ";
			cin >> h >> m >> s;

			// Edge case for when a user accidentally enters a letter
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid option please select 1, 2, 3, or 4. \n";
				break;
			}

			// Edge case to make sure the input is within military time bounds
			if (h < 0 || h > 24 || m < 0 || m > 59 || s < 0 || s > 59) {
				cout << "ERROR: Keep range of numbers within time bounds. ";
				cout << "\nMAX VAL = 24 59 59\nMIN VAL = 0 0 0";
			}
			else {
				clock = Time(h, m, s);  // Update time
			}
			break;
		}
		case 2:
			clock.runClock();  // Start live clock
			break;
		case 3:
			clock.saveTimeToFile();  
			cout << "Current time saved. Exiting..." << endl;
			break;
		case 4:
			system("cls");
			break;
		default:
			cout << "Invalid Option. Try again." << endl;
		}
	}
	return 0;
}