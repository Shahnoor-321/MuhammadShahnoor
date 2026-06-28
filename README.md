Lost & Found item management system
A lightweight, desktop-based graphical application built in C++ using the SFML (Simple and Fast Multimedia Library) framework. This system allows users to log lost items, record found items, list all current records, and search through entries via a dynamic, responsive user interface.

System Architecture & OOP Concepts:
Instead of relying on class inheritance, this project is built using Composition (a "has-a" relationship).

Item (Data Component): A flat data structure (struct) that models a real-world object using attributes for its name, description, and location.

System (Manager Component): A dedicated controller class that manages data operations. It encapsulates two std::vector containers (lost and found) to store collections of Item objects in memory.

Data Persistence: The System class handles flat-file database operations, saving and loading records using a custom pipe-delimited (|) format (lost.txt and found.txt) via C++ file streams (std::ifstream/std::ofstream).

Features
1. Interactive GUI Dashboard: Simple, efficient navigation with custom-built graphical buttons.

2. Real-time Input Feedback: Live UI text updates character-by-character as you type names, descriptions, or search queries.

3. Robust Text Parsing: Seamlessly processes input strings with spaces using std::stringstream tokenizer boundaries.

4. Local Storage: Automatic data persistence ensures logged items are safely retained even after closing the application.

Project Structure
Plaintext
├── main.cpp           Application entry point, GUI layout, and SFML event loop
├── System.h           Header declaring the core business logic and storage class
├── System.cpp         Implementation of data file I/O, search, and string display
├── Item.h             Header declaring the core Item structure
├── arial.ttf          Required font asset for rendering text in SFML
├── lost.txt           Saved local database for lost items (Auto-generated)
└── found.txt          Saved local database for found items (Auto-generated)
Prerequisites & Setup
Windows Configuration (MSYS2 UCRT64)
This project requires a C++ compiler and the SFML library development files. If you are using VS Code and MSYS2, follow these steps:

Install SFML:
Open your MSYS2 UCRT64 Terminal and run the following command to install native runtime and development headers:


pacman -S mingw-w64-ucrt-x86_64-sfml

Configure IntelliSense:
To remove any missing header squiggles in VS Code, open the Command Palette (Ctrl + Shift + P), select C/C++: Edit Configurations (UI), and append the following path to your Include path field:

C:/msys64/ucrt64/include

Compilation and Execution
Because this project is modularized across multiple source files, you must compile all implementation files together and link the necessary SFML modules (graphics, window, and system).

Manual Build via Terminal

Open the project folder in a terminal and execute:
g++ *.cpp -o main.exe -lsfml-graphics -lsfml-window -lsfml-system

Run the application:
./main.exe

How to Use
Add Lost / Found Items: Click the corresponding button, type the requested item field (Name, Description, Location), and press Enter to cycle through steps. Your current typed string will display live on the upper header line.

Review Records: Click Show All to load and render the entire catalog of lost and found data directly inside the main application display panel.

Search: Click Search, type your keyword, and press Enter. The application will search through both titles and descriptions to render matches instantly.
