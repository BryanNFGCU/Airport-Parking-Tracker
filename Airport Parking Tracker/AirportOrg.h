#pragma once

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

int action = 0;
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
Spot& spot = lot.getSpot(choice - 1);
if (action == 2)
{
    if (!spot.isTaken())
        throw runtime_error("That spot is already available.");
    spot.vacate();
    done = true;
    continue;
}
throw runtime_error("That spot is already taken. ");
























 

