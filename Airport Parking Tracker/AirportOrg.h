#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <QtWidgets/QMessageBox>
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

    //Checks out the spot 

    void checkout()
    {
        taken = false;
        username = "";
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

// Check Out Function

void MainWindow::on_checkoutButton_clicked()
{
    try
    {
        int choice = ui.spotSelector->currentIndex();
        if (choice < 0 || choice >= lot.getSize()) return;

        Spot& spot = lot.getSpot(choice);


        if (!spot.isTaken())
        {
            throw runtime_error("That parking spot is already vacant and avaliable.");
        }

        string customerName = spot.getUsername();

        spot.checkout();

        saveData();

        refreshLotDisplay();

        ui.hoursInput -> clear();
        ui.nameInput -> clear();

        
        QMessageBox::information(this, "Check Out Successful", //AI HELP
            QString("Spot %1 has been freed up! Goodbye, %2.")
            .arg(spot.getId()).arg(QString::fromStdString(customerName)));

    }
    catch (const exception& e) {
        // Catch-all safety warning popup window   //AI HELP
        QMessageBox::warning(this, "Action Failure", e.what());
    }

























 }

