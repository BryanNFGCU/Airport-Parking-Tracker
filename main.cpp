

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
