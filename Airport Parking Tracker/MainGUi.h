#pragma once
#include <QtWidgets/QMainWindow>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "AirportOrg.h"
#include "ui_MainWindow.h"


class MainGUI : public QMainWindow //AI help
{
    Q_OBJECT

public:
    MainGUI(QWidget* parent = nullptr);
    ~MainGUI();

private slots:
    void on_reserveButton_clicked();
    void on_viewButton_clicked();
    void on_checkoutButton_clicked();

private:
    Ui::MainWindow ui;
    ParkingLot lot;

    void loadData();
    void refreshLotDisplay();
    void saveData();
};