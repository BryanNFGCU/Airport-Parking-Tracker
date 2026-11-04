/*
AIRPORT PARKING TRACKER - CHECKPOINT 5
11/3/26

- Spot class: one parking space
- ParkingLot class: holds a vector of Spot objects (composition)
- ParkingRate: abstract class with a pure virtual function
- StandardRate and VIPRate: override calculateFee (polymorphism)
- try/throw/catch: handles bad spot numbers, taken spots, bad hours

Needs "AirportParking.txt" in the build folder. 
Format 
First Number: Spot number
Second Number: avaiblility (1 = taken, 0 = open) 
Third Number: VIP (1 = VIP, 0 = standard)
Example:
1 1 0
2 0 1
3 0 0
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

class Spot
{
private:
    int id;
    bool taken;
    bool vip;

public:
    Spot(int i, bool t, bool v)
    {
        id = i;
        taken = t;
        vip = v;
    }
    int getId() { return id; }
    bool isTaken() { return taken; }
    bool isVIP() { return vip; }
    void reserve() { taken = true; }
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
            cout << "Spot " << spots[i].getId();
            if (spots[i].isVIP())
                cout << " [VIP] ";
            else
                cout << " [Standard] ";
            if (spots[i].isTaken())
                cout << "- Taken\n";
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
        lot.addSpot(Spot(id, taken, vip));
    }
    inFile.close();

    lot.show();

    bool done = false;
    while (!done)
    {
        try
        {
            int choice, hours;

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
            if (spot.isTaken())
                throw runtime_error("That spot is already taken.");

            cout << "Enter hours: ";
            cin >> hours;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                throw runtime_error("Please enter hours as a number.");
            }
            if (hours <= 0)
                throw runtime_error("Hours must be greater than zero.");

            //Pick the rate, then call it through the base class pointer
            StandardRate stdRate;
            VIPRate vipRate;
            ParkingRate* rate;
            if (spot.isVIP())
                rate = &vipRate;
            else
                rate = &stdRate;

            cout << "Total fee: $" << rate->calculateFee(hours) << "\n";

            spot.reserve();
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
        outFile << s.getId() << " " << s.isTaken() << " " << s.isVIP() << "\n";
    }
    outFile.close();
    cout << "Spot reserved and saved!\n";

    return 0;
}