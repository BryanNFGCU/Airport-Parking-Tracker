Hello this is the repository for the C++ Airport Parking Tracker, a project for COP 3003

So Far the program:
1. Reads parking spots from `AirportParking.txt`
2. Displays each spot as Available or Unavailable
3. Asks the user for a spot number to reserve
4. Marks that spot as taken and saves the change to the file
  
What we need to add:
1. Way to vacate (free) parking spot
2. Loop for user input
3. Username for Parking spot, and display Username
  
Requirements:
- Operating system: Windows 11
- Compiler : Microsoft Visual Studio 2022
- C++ standard: C17 to C20
- Libraries: no dependencies (standard library only)

How to run:

1. Clone the repository
2. Open the `.sln` file in Visual Studio.
3. Make sure `AirportParking.txt` is in the same folder as the `.vcxproj` file. This is the folder the program reads from when run from Visual Studio.
4. Press **Local Windows Debugger** (or F5) to build and run.
5. Read the list of spots and type the number of an available spot.
6. The program saves the change to `AirportParking.txt` and ends.

TBA Later:
1. View parking spots: see which are available.
2. Check in a vehicle: enter license plate and username, choose a spot, and enter the arrival time.
3. Check out a vehicle: enter license plate and username. The program records departure and the fee.
4. View parking records: license plate, spot, arrival time, departure time, and status.
5. Exit: closes the program and saves the data to the text file.
 
 
