#include "MainGUi.h"
#include <QtWidgets/QMessageBox>

MainWindow::MainWindow(QWidget* parent)                   //AI HELPED.              
    : QMainWindow(parent)
{
    ui.setupUi(this); // Initializes all your drag-and-drop objects

    loadData();

    // Populate your visual dropdown picker tool automatically with spot IDs
    for (int i = 0; i < lot.getSize(); i++) {
        ui.spotSelector->addItem(QString("Spot %1").arg(lot.getSpot(i).getId())); // ai help
    }
    refreshLotDisplay();
}

MainWindow::~MainWindow() {}

// C#-style double-click event click handler for your confirmation button
void MainWindow::on_reserveButton_clicked()   //AI HELPED
{
    try {
        int choice = ui.spotSelector->currentIndex();
        if (choice < 0 || choice >= lot.getSize()) return;

        Spot& spot = lot.getSpot(choice);

        // Validation check 1: Occupancy check
        if (spot.isTaken()) {
            throw runtime_error("That parking spot is already checked in and taken.");
        }

        // Validation check 2: Parse text fields duration hours
        bool parseOk;
        int hours = ui.hoursInput->text().toInt(&parseOk);
        if (!parseOk || hours <= 0) {
            throw runtime_error("Please enter a valid, positive number for hours.");
        }

        // Validation check 3: String whitespace cleanup
        string name = ui.nameInput->text().trimmed().toStdString();
        if (name.empty()) {
            throw runtime_error("Reservation name profile field cannot be blank.");
        }

        // Your original Polymorphism Fee calculation logic engine
        StandardRate stdRate;
        VIPRate vipRate;
        ParkingRate* rate = spot.isVIP() ? (ParkingRate*)&vipRate : (ParkingRate*)&stdRate;
        double calculatedFee = rate->calculateFee(hours);

        // Track and lock changes into data memory structure configurations
        spot.reserve(name);

        // Write updated logs down to the persistent text database block
        saveData();

        // Repaint the dashboard text area boards
        refreshLotDisplay();
        ui.hoursInput->clear();
        ui.nameInput->clear();

        // Operational Summary Pop-up Alert    //AI HELP
        QMessageBox::information(this, "Reservation Confirmed!",
            QString("Spot %1 successfully booked for %2!\nTotal Calculated Fee Due: $%3")
            .arg(spot.getId()).arg(QString::fromStdString(name)).arg(calculatedFee, 0, 'f', 2));

    }
    catch (const exception& e) {     //AI HELP
        // Pop-up warning dialog alerts replacing your console 'cout' errors
        QMessageBox::warning(this, "Validation Error", e.what());
    }
}

// C#-style handler for your second 'View/Refresh' layout button
void MainWindow::on_viewButton_clicked()                                 //AI HELP
{
    lot = ParkingLot(); // Resets your memory array structures so vectors don't duplicate logs
    loadData();
    refreshLotDisplay();

    ui.hoursInput->clear();
    ui.nameInput->clear();

    QMessageBox::information(this, "Dashboard Refreshed", "The parking display tracking board has been updated successfully.");
}

void MainWindow::loadData() {   //AI HELP
    ifstream inFile("AirportParking.txt");
    if (!inFile) return;
    int id, taken, vip;
    while (inFile >> id >> taken >> vip) {
        string name; getline(inFile, name);
        size_t start = name.find_first_not_of(" \t\r");
        if (start == string::npos) name = "";
        else name = name.substr(start, name.find_last_not_of(" \t\r") - start + 1);

        lot.addSpot(Spot(id, taken, vip, name));
    } 
    inFile.close();
}

void MainWindow::refreshLotDisplay() {                                        //AI HELP
    QString htmlOutput = "";
    for (int i = 0; i < lot.getSize(); i++) {
        Spot& s = lot.getSpot(i);
        htmlOutput += QString("<b>Spot %1</b>").arg(s.getId());
        htmlOutput += s.isVIP() ? " <span style='color:purple;'>[VIP]</span> " : " <span style='color:blue;'>[Standard]</span> ";
        htmlOutput += s.isTaken() ? QString(" — <span style='color:red;'>Occupied</span> by <i>%1</i>").arg(QString::fromStdString(s.getUsername())) : " — <span style='color:green;'>Available</span>";
        htmlOutput += "<br>";
    }
    ui.lotDisplay->setHtml(htmlOutput);
}

void MainWindow::saveData() {        // Ai Help
    ofstream outFile("AirportParking.txt");
    for (int i = 0; i < lot.getSize(); i++) {
        Spot& s = lot.getSpot(i);
        outFile << s.getId() << " " << s.isTaken() << " " << s.isVIP();
        if (!s.getUsername().empty()) outFile << " " << s.getUsername();
        outFile << "\n";
    }
    outFile.close();
}
