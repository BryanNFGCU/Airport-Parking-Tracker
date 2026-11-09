/*
AIRPORT PARKING TRACKER - USERNAME UPDATE
11/7/26

- Username: the user types their name when reserving. Shown and saved to file. 
- User must type something, currently will allow any user input like 8 or b. Might have character requirement later.

Needs "AirportParking.txt" in the build folder.
Format (one spot per line)
First Number: Spot number
Second Number: availability (1 = taken, 0 = open)
Third Number: VIP (1 = VIP, 0 = standard)
Last line: username (only on reserved spots)
Example:
1 1 0 Billy
2 0 1
3 0 0
(Old files with only 3 numbers still work.)
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

class Spot
{
private:
    int id;
    bool taken;
    bool vip;
    string username;    // who reserved the spot (empty if nobody)

public:
    Spot(int i, bool t, bool v, string name)
    {
        id = i;
        taken = t;
        vip = v;
        username = name;
    }
    int getId() { return id; }
    bool isTaken() { return taken; }
    bool isVIP() { return vip; }
    string getUsername() { return username; }

    // Reserve the spot and remember who reserved it
    void reserve(string name)
    {
        taken = true;
        username = name;
    }
    void vacate()
    {
        taken = false;
        username.clear();
    }
};
class ParkingLot
{
private:
    vector<Spot> spots;

public:
    void addSpot(Spot s) { spots.push_back(s); }
    int getSize() { return spots.size(); }
    Spot& getSpot(int index) { return spots[index]; }

    void show()
    {
        for (int i = 0; i < getSize(); i++)
        {
            if (spots[i].isTaken())
                continue;
            cout << "Spot " << spots[i].getId();
            if (spots[i].isVIP())
                cout << " [VIP] ";
            else
                cout << " [Standard] ";
            if (spots[i].isTaken())
            {
                cout << "- Taken";
                // Only show the username if the spot has one
                if (spots[i].getUsername() != "")
                    cout << " by " << spots[i].getUsername();
                cout << "\n";
            }
            else
                cout << "- Available\n";
        }
    }
};

class ParkingRate
{
public:
    virtual double calculateFee(int hours) = 0;
    virtual ~ParkingRate() {}
};

//$5 per hour
class StandardRate : public ParkingRate
{
public:
    double calculateFee(int hours) { return hours * 5.0; }
};

//$15 flat fee + $2 per hour
class VIPRate : public ParkingRate
{
public:
    double calculateFee(int hours) { return 15.0 + hours * 2.0; }
};

int main()
{
    ParkingLot lot;

    ifstream inFile("AirportParking.txt");
    if (!inFile)
    {
        cout << "Could not open AirportParking.txt\n";
        return 1;
    }
    int id, taken, vip;
    while (inFile >> id >> taken >> vip)
    {
        // Read the rest of the line as the username (may be empty)
        string name;
        getline(inFile, name);

        // Remove the spaces around the name
        size_t start = name.find_first_not_of(" \t\r");
        if (start == string::npos)
            name = "";
        else
            name = name.substr(start, name.find_last_not_of(" \t\r") - start + 1);

        lot.addSpot(Spot(id, taken, vip, name));
    }
    inFile.close();

    lot.show();
    int action = 0;
    bool done = false;
    while (!done)
    {
        try
        {
            int choice, hours;
            string name;
            cout << "\n1 Reserve Spot\n";
            cout << "2.Vacate a Spot\n";
            cout << "Choose an action: ";
            if (!(cin >> action))
            {
                cin.clear();
                cin.ignore(1000, '\n'); //throws away the invalid input
                throw runtime_error("please enter a number.");
            }
            if (action != 1 && action != 2)
                throw runtime_error("Please enter 1 or 2.");
            cout << "\nEnter spot number (1-" << lot.getSize() << "): ";
            cin >> choice;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                throw runtime_error("Please enter a number.");
            }
            if (choice < 1 || choice > lot.getSize())
                throw runtime_error("That spot number does not exist.");

            
            Spot& spot = lot.getSpot(choice - 1);
            if (action ==2)
            {
            if (!spot.isTaken())
                throw runtime_error("That spot is already available.");
            spot.vacate();
            done = true;
            continue;
        }
            if (spot.isTaken())
                throw runtime_error("That spot is already taken. ");
        

            cout << "Enter hours: ";
            cin >> hours;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                throw runtime_error("Please enter hours as a number.");
            }
            cin.ignore(1000, '\n');     // clear the Enter key before reading the name
            if (hours <= 0)
                throw runtime_error("Hours must be greater than zero.");

            // Ask for the username (getline allows spaces)
            cout << "Enter your name: ";
            getline(cin, name);

            // Remove spaces at the start and end of the name
            size_t start = name.find_first_not_of(" \t");
            if (start == string::npos)
                name = "";      // only spaces, so treat it as blank
            else
                name = name.substr(start, name.find_last_not_of(" \t") - start + 1);

            // A blank name is not allowed
            if (name == "")
                throw runtime_error("Name cannot be blank.");

            //Pick the rate, then call it through the base class pointer
            StandardRate stdRate;
            VIPRate vipRate;
            ParkingRate* rate;
            if (spot.isVIP())
                rate = &vipRate;
            else
                rate = &stdRate;

            cout << "Total fee: $" << rate->calculateFee(hours) << "\n";

            // Reserve the spot only after everything was valid
            spot.reserve(name);
            done = true;
        }
        catch (exception& e)
        {
            cout << "Error: " << e.what() << " Try again.\n";
        }
    }

    //Save the updated spots 
    ofstream outFile("AirportParking.txt");
    for (int i = 0; i < lot.getSize(); i++)
    {
        Spot& s = lot.getSpot(i);
        outFile << s.getId() << " " << s.isTaken() << " " << s.isVIP();
        if (s.getUsername() != "")
            outFile << " " << s.getUsername();
        outFile << "\n";
    }
    outFile.close();
    cout << "Spot reserved and saved!\n";

    return 0;
}