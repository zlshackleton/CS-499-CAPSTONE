#include <iostream> 
#include <iomanip>
#include <string>
using namespace std;

int main() {

    int h, h12;
    int m;
    int s;
    string ampm;
    int userOption = 0;

    cout << "Input time as: (hh mm ss:) ";
    cin >> h >> m >> s;

    while (userOption != 4) {
        if (h == 0) {
            h12 = 12;
            ampm = " A M";
        }
        else if (h < 12) {
            h12 = h;
            ampm = " A M";
        }
        else if (h == 12) {
            h12 = 12;
            ampm = " P M";
        }
        else {
            h12 = h - 12;
            ampm = " P M";
        }
        // display clocks
        cout << "****************************        ****************************" << endl;
        cout << "*       12-Hour Clock      *        *      24-Hour Clock       *" << endl;
        cout << "*       " << setfill('0') << setw(2) << h12 << ":" << setw(2) << m << ":" << setw(2) << s << ampm
            << "       *        *        " << setw(2) << h << ":" << setw(2) << m << ":" << setw(2) << s << "        " << endl;
        cout << "****************************        ****************************" << endl;

        cout << "***************************" << endl;  //menu created in while loop to always display until false.
        cout << "* 1 - Add One Hour        *" << endl;
        cout << "* 2 - Add One Minute      *" << endl;
        cout << "* 3 - Add One Second      *" << endl;
        cout << "* 4 - Exit Program        *" << endl;
        cout << "***************************" << endl;

        cin >> userOption;

        switch (userOption) { // cases created almost like an if statement automatically adds the time based off userOption.
        case 1:
            h++;
            break;
        case 2:
            m++;
            break;
        case 3:
            s++;
            break;
        case 4:
            cout << "Exit Program." << endl;
            break;
        default:
            cout << "Invalid Option" << endl;
            cin.clear();                // Clear the error state of cin
            cin.ignore(10000, '\n');
        }

        if (s >= 60) { //if the timer becomes greater than h m s, then the next time value increases by 1 while the other resets to 0.
            s = 0;
            m++;
        }

        if (m >= 60) {
            m = 0;
            h++;
        }
        if (h >= 24) {
            h = 0;
        }


    } // end while loop




}