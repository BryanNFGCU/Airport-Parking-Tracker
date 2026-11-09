#include "MainGUI.h"
#include <QtWidgets/QMessageBox>

MainGUI::MainGUI(QWidget* parent)                   //AI HELPED.              
    : QMainWindow(parent)
{
    ui.setupUi(this); 

    loadData();
    for (int i = 0; i < lot.getSize(); i++) {
        ui.spotSelector->addItem(QString("Spot %1").arg(lot.getSpot(i).getId())); // ai help
    }
    refreshLotDisplay();
}

MainGUI::~MainGUI() {}


void MainGUI::on_reserveButton_clicked()   //AI HELPED
{
    try {
        int choice = ui.spotSelector->currentIndex();
        if (choice < 0 || choice >= lot.getSize()) return;

        Spot& spot = lot.getSpot(choice);

        if (spot.isTaken()) {
            throw runtime_error("That parking spot is already checked in and taken.");
        }

      
        bool parseOk;
        int hours = ui.hoursInput->text().toInt(&parseOk);
        if (!parseOk || hours <= 0) {
            throw runtime_error("Please enter a valid, positive number for hours.");
        }

      
        string name = ui.nameInput->text().trimmed().toStdString();
        if (name.empty()) {
            throw runtime_error("Reservation name profile field cannot be blank.");
        }

       
        StandardRate stdRate;
        VIPRate vipRate;
        ParkingRate* rate = spot.isVIP() ? (ParkingRate*)&vipRate : (ParkingRate*)&stdRate;
        double calculatedFee = rate->calculateFee(hours);

        spot.reserve(name);

       
        saveData();

      
        refreshLotDisplay();
        ui.hoursInput->clear();
        ui.nameInput->clear();

           //AI HELP
        QMessageBox::information(this, "Reservation Confirmed!",
            QString("Spot %1 successfully booked for %2!\nTotal Calculated Fee Due: $%3")
            .arg(spot.getId()).arg(QString::fromStdString(name)).arg(calculatedFee, 0, 'f', 2));

    }
    catch (const exception& e) {     //AI HELP
        
        QMessageBox::warning(this, "Validation Error", e.what());
    }
}


void MainGUI::on_viewButton_clicked()                                 //AI HELP
{
    lot = ParkingLot(); 
    loadData();
    refreshLotDisplay();

    ui.hoursInput->clear();
    ui.nameInput->clear();

    QMessageBox::information(this, "Dashboard Refreshed", "The parking display tracking board has been updated successfully.");


}
void MainGUI::on_checkoutButton_clicked()
{
    try {
        int choice = ui.spotSelector->currentIndex();
        if (choice < 0 || choice >= lot.getSize()) return;

        Spot& spot = lot.getSpot(choice);
        if (!spot.isTaken()) {
            throw runtime_error("That parking spot is already vacant and available.");
        }

        string customerName = spot.getUsername();
        spot.checkout(); 
        saveData();
        refreshLotDisplay();

        ui.hoursInput->clear();
        ui.nameInput->clear();

        QMessageBox::information(this, "Check Out Successful",
            QString("Spot %1 has been freed up! Goodbye, %2.")
            .arg(spot.getId()).arg(QString::fromStdString(customerName)));
    }
    catch (const exception& e) {
        QMessageBox::warning(this, "Action Failure", e.what());
    }
}

void MainGUI::loadData() {   //AI HELP
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

void MainGUI::refreshLotDisplay() {                                        //AI HELP
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

void MainGUI::saveData() {        // Ai Help
    ofstream outFile("AirportParking.txt");
    for (int i = 0; i < lot.getSize(); i++) {
        Spot& s = lot.getSpot(i);
        outFile << s.getId() << " " << s.isTaken() << " " << s.isVIP();
        if (!s.getUsername().empty()) outFile << " " << s.getUsername();
        outFile << "\n";
    }
    outFile.close();
}
