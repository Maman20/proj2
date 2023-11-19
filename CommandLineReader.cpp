/**
 * @file CommandLineReader.cpp
 * @callergraph
 * @callgraph
 * @author Abdirahman Abdi
 * @brief Member function definitions for class CommandLineReader
 * @see CommandLineReader.h for declaration.
 * @details
 * This class provides functionality to:
 * - Display a menu to the user.
 * - Accept commands from the user.
 * - Search for a given ZIP code in a database.
 * - Find the ZIP code of a place based on its name and latitude.
 * - Exit the application.
 * 
 * Assumptions:
 * - The database file 'us_postal_codes.txt' is properly formatted and available.
 * - The user provides valid input.
 */

#include "CommandLineReader.h"
#include <string>
#include <iostream>
#include <fstream>  
#include <sstream>

/**
 * @brief Default constructor that initializes the application state.
 * @pre None.
 * @post The CommandLineReader object is constructed and the application is ready to run.
 */
CommandLineReader::CommandLineReader() {
    running = true;
}

/**
 * @brief Main loop that displays the menu and accepts commands from the user.
 * @pre The CommandLineReader object is initialized.
 * @post The user has interacted with the application, and possibly chosen to exit.
 */
void CommandLineReader::Main() {
    std::cout << "\n-- welcome to command reader --\n\n";
    while (running) {
        std::cout << "press E to enter zip code and see if it's in database\n";
        std::cout << "press F to find and print zipcode\n";
        std::cout << "press T to close program\n";
        
        std::string input;
        std::cin >> input;

        ParseCommandLine(input);
    }
}

/**
 * @brief Parses and executes the command entered by the user.
 * @param input The user's input string.
 * @pre The application is running and waiting for user input.
 * @post The user's command is executed.
 */
void CommandLineReader::ParseCommandLine(const std::string& input) {
    std::string line, fileZip, fileCity, state, county, latitude, longitude;
    bool found = false;

    if (input == "E" || input == "e") {
        std::cout << "Enter the zip code: ";
        std::string enteredZip;  // Use a different variable to capture user input
        std::cin >> enteredZip;
        std::ifstream file("us_postal_codes.txt"); // reead file
        while (getline(file, line)) { // goes through all the lines in us_postal_codes.csv
            std::istringstream iss(line); //reading across the line using ',' as breakpoint
            getline(iss, fileZip, ','); 
            if (fileZip == enteredZip) {
                std::cout << "Zip code " << enteredZip << " is in the database." << std::endl;
                found = true;
                break; //break the reading loop
            }
        }
        if (!found) { // if loop is done but still no zip file then come here and print
            std::cout << "Zip code " << enteredZip << " is not in the database." << std::endl;
        }
        //close file 
        file.close();

    }
    else if (input == "F" || input == "f") {
        //finding zip of place from the name
        std::cout << "Enter the place name to find its zip code: e.g 'Amherst' ";
        std::string enteredCity;  // read user entered city
        std::cin >> enteredCity;
        std::cout << "Enter the place latitude to find its zip code: e.g '42.3671' ";
        std::string enteredLat;  // read user entered latitude
        std::cin >> enteredLat;
        
        std::ifstream file("us_postal_codes.txt"); //read from database
        while (getline(file, line)) {
            std::istringstream iss(line); // go through each line
            // go across the line with breakpoints ',' and input each data into string format and their relevant variables
            getline(iss, fileZip, ',');
            getline(iss, fileCity, ',');  // save cityname in strings with break point ',' 
            getline(iss, state, ',');
            getline(iss, county, ',');
            getline(iss, latitude, ','); // save latitude 
            getline(iss, longitude, ',');
            if (fileCity == enteredCity && latitude == enteredLat ) { // if for accuracy both cityname and latitude point match then 
                std::cout << "Zip code for " << enteredCity << " @Latitude: " << enteredLat << " is: " << fileZip << std::endl;
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "City of " << enteredCity << " or its latitude @: " << enteredLat <<" not found in the database." << std::endl;
        }
        file.close(); //close file read buffer

    } else if (input == "T" || input == "t") {
        running = false;  // Exit the loop
    } else {
        std::cout << "Invalid input. Please try again.\n";
    }
}




