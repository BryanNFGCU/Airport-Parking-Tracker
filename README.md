# Airport Parking Tracker

## A C++ program built with Qt 6.12 (Widgets) in Visual Studio for managing airport parking spaces. Users can check spot availability, reserve VIP or standard parking spaces, calculate parking fees, and save to .txt file

## Features

- Spot Availability: View open and taken parking spots and vacate spaces when users leave.
- VIP & Standard Pricing: Automatically calculates fees for VIP (\$15 + $2/hr) and Standard($5/hr) spots.
- Username Reservations: Saves a user's name to their reserved spot and blocks blank or duplicate bookings.
- Auto-Save: Keeps all spot updates saved in AirportParking.txt between sessions.

## Tech Stack & Requirements

- Language: C++17 / C++20
- GUI Framework: Qt 6.12.0 (Qt Widgets)
- IDE & Compiler: Visual Studio 2022 (MSVC x64)
- Extension: Qt Visual Studio Tools (Qt VS Tools)

Setup & Build Steps:

1. Clone the repository from GitHub.
2. Open the file (Airport Parking Tracker.sln) in Visual Studio.
3. Verify Qt Configuration

Go to Extensions > Qt VS Tools > Qt Versions and confirm your MSVC Qt installation (e.g., 6.12.0_msvc2022_64) is registered.

Right-click the Airport Parking Tracker project > Properties > Qt Project Settings, and ensure Qt Installation is assigned for Debug | x64.

Under Configuration Properties > C/C++ > General, ensure SDL checks is set to No (/sdl-) so Qt deprecation notices do not halt compilation.

4. Ensure AirportParking.txt is located inside your active build/working directory (e.g., x64/Debug/ or the project root when launching from Visual Studio).

## AirportParking.txt Data Format

&lt;SpotNumber&gt; &lt;TakenStatus&gt; &lt;VIPStatus&gt; \[Username\]

- SpotNumber: Integer ID of the parking space (1, 2, 3, etc.).
- TakenStatus: 1 = Taken, 0 = Available.
- VIPStatus: 1 = VIP Spot, 0 = Standard Spot.
- Username: (Optional) Name of the user who reserved the spot (included when TakenStatus is 1).

Example:

1 1 0 Billy

2 0 1

3 0 0