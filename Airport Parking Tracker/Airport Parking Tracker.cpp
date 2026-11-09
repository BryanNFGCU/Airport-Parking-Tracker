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


#include "MainGUi.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])   //AI Help
{
    // Start the graphical application framework framework backend engine
    QApplication app(argc, argv);

    // Construct and fire up your brand-new system management window dashboard panel
    MainWindow w;
    w.show();

    // Lock execution in frame cycle processing mode until the user clicks close
    return app.exec();


}