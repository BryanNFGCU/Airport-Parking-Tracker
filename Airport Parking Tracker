/* 
First iteration, needs AirportParking.txt file in build folder.
Layout:
1 1
2 1
3 0
4 0
5 0

First number is the parking spot, second number is either 1 or 0. 1 Means Unavailable and 0 means Available

So far the program:
 * 1. Reads parking spots from AirportParking.txt
 * 2. Displays each spot as Available or Unavailable
 * 3. Asks the user for a spot number to reserve
 * 4. Marks that spot as taken and saves the change to the file
Other additions will be produced later on.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Spot
{
    int id;
    bool isTaken;
};

int main()
{
    //read "AirportParking" .txt file
    std::string filename = "AirportParking.txt";
    std::vector<Spot> spots;
    std::ifstream inFile(filename);
    int id;
    bool taken;

    while (inFile >> id >> taken)
    {
        spots.push_back({ id, taken });
    }
    inFile.close();

    //display status based on .txt file
    std::cout << "AIRPORT PARKING STATUS\n";
    for (const auto& s : spots)
    {
        std::cout << "Spot " << s.id << ": ";
        if (s.isTaken)
        {
            std::cout << "Unavailable\n";
        }
        else
        {
            std::cout << "Available\n";
        }
    }

    //user input for parking spot
    int spotChoice;
    std::cout << "\nEnter spot number to reserve (1-5): ";
    std::cin >> spotChoice;

    //update vector if valid
    if (spotChoice >= 1 && spotChoice <= spots.size())
    {
        if (spots[spotChoice - 1].isTaken)
        {
            std::cout << "That spot is already unavailable!\n";
            return 0;
        }
        spots[spotChoice - 1].isTaken = true;
    }
    else
    {
        std::cout << "Invalid spot number.\n";
        return 0;
    }

    //save changes back to the text file
    std::ofstream outFile(filename);
    for (const auto& s : spots)
    {
        outFile << s.id << " " << s.isTaken << "\n";
    }
    outFile.close();

    std::cout << "Spot successfully reserved and saved to file!\n";

    return 0;
}
