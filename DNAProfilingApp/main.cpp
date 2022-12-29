/*---------------------------------------------------------
//  Project 1 Starter Code - DNA Profiling
//  
// This application will build DNA strands, manipulate &
// analyze against DNA STR's and find a potential match.
// Course: CS 251, Fall 2022.
// Author: Miguel Cortez
// Date: 9/19/2022

// ---- Instructions for the special command/creative aspect ----
// 
// For the special command to work properly, please ensure that 
// you first load in a desired database, otherwise there will not
// be a randomly generated relative to guess, nor will there be 
// a list of potential relatives to choose from listed. 
// To initiate the special commend, you must enter "special_cmd" 
// into the terminal. You may also enter "C" (not case sensitive)
// if you would like to cheat at know who your relative is.
// IF you guess correctly, you will then be presented with a special
// message. Otherwise, have better luck next time.
---------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ourvector.h"
using namespace std;

struct dnaData
{
    string dataName;
    ourvector <int> dnaCounts;
};

// This function will parse a given string into its characters & push back into a vector
void parseStrToChar(string &databaseString, ourvector <char> tempVector , ourvector <ourvector<char>> &dataVector)
{
    for (int i = 0; i < databaseString.length(); i++)
    {
        tempVector.clear();
        tempVector.push_back(databaseString[i]);
    }
}

// This function will parse the first line in a string into their respective containers
void firstLineStrChar(string &databaseString, ourvector <char> &tempVector, ourvector <ourvector<char>> &dataFirstLine)
{
    tempVector.clear();

    for(int i = 0; i < databaseString.length(); i++)
    {   
        tempVector.push_back(databaseString[i]);
    }

    dataFirstLine.push_back(tempVector);
}

// This function will parse the first line of the small.txt/large.txt files and push_back into dnaData ourvector
void parseFirstLine(string &databaseString, ourvector <char> tempVector, ourvector <ourvector<char>> &dataFirstLine)
{
    stringstream sStream(databaseString);

    while (sStream.good())
    {
        int i = 0;
        string substr;
        getline(sStream, substr, ',');
        firstLineStrChar(substr, tempVector, dataFirstLine);
        
        i++;
    }
}

// This function will parse comma separated valued strings and call parseStrToChar
void parseCsvString(string &databaseString, ourvector <char> tempVector, ourvector <dnaData> &dataVector)
{
    stringstream sStream(databaseString);

    int dataVecRow = 0;

    while (sStream.good())
    {
        string substr;
        dnaData dnaSubject;

        getline(sStream, substr, ',');

        if (substr == "")
        {
            break;
        }

        // This line will assign the name to the current struct object
        dnaSubject.dataName = substr;

        // This while loop while loop will store the DNA STR counts w/ its associated name
        while (sStream.good())
        {
            getline(sStream, substr, ',');

            dnaSubject.dnaCounts.push_back(stoi(substr));
        }

        // This line will push the current struct object into the struct vector
        dataVector.push_back(dnaSubject);
        
        dataVecRow++; // Do I need this at all?
    }
}

// This function will read in a database file/DNA Data into a vector
void readDatabaseFile(string userFile, ourvector <char> tempVector , ourvector <dnaData> &dataVector, ourvector <ourvector<char>> &dataFirstLine)
{
    string fileLine;
    string tempString;

    ifstream fStream;
    fStream.open(userFile);

    // Condition to check if file is valid/open
    if (!fStream.is_open())
    {
        cout << "Error: unable to open " << "'" << userFile << "'" << endl;
        return;
    }

    dataFirstLine.clear();
    dataVector.clear();

    // This will handle the first line of the given database file
    getline(fStream, tempString);
    parseFirstLine(tempString, tempVector, dataFirstLine);

    // This will handle the rest of the file
    while (!fStream.eof())
    {
        getline(fStream, tempString);
        parseCsvString(tempString, tempVector, dataVector);
    }

    fStream.close();
}

// This function will read in a file/DNA sequence into a vector
void readDnaFile(string userDnaFile, ourvector <char> &dnaSeqVec)
{
    string fileLine;
    string tempString;

    ifstream fStream;
    fStream.open(userDnaFile);

    // Condition to check if file is valid/open
    if (!fStream.is_open())
    {
        cout << "Error: unable to open " << "'" <<userDnaFile << "'" << endl;
        return;
    }

    getline(fStream, tempString);

    for (int i = 0; i < tempString.length(); i++)
    {
        dnaSeqVec.push_back(tempString[i]);
    }
        
    fStream.close();

}

// This function will load the DNA database and display it
void loadDatabase(string userFile, ourvector <char> &tempVector , ourvector <dnaData> &dataVector, ourvector <ourvector<char>> &dataFirstLine)
{
    cout << "Loading database... ";
    readDatabaseFile(userFile, tempVector, dataVector, dataFirstLine);
}

// This function will load the DNA data and display it
void loadDNA(string userDnaFile, ourvector <char> &dnaSeqVec)
{
    cout << "Loading DNA... ";
    readDnaFile(userDnaFile, dnaSeqVec);
}

// This function will compare the current STR vector to the current temporary DNA vector
bool compareDnaStrVec(ourvector <char> currTempStrVector, ourvector <char> currTempDnaVec)
{
    for (int i = 0; i < currTempStrVector.size(); i++)
    {
        // cout << "DNA FILE CONTENTS: " << currTempDnaVec[i] << endl;

        if (currTempStrVector[i] != currTempDnaVec[i])
        {
            // cout << "\nThis is a false return from line 297 from index: " << i << endl;
            return false;
        }
    }

    // cout << "This is returning true." << endl;
    return true;
}

// This function will assign a temporary vector to the current characters in the DNA sequence, to the give size of the current STR
void assignTempDnaVec(ourvector<char> currentStrVec, ourvector <char> dnaSeqVec, ourvector <char> &tempDnaVec, int tempCounter, int currDnaChar)
{
    tempDnaVec.clear();

    for (int i = currDnaChar; i < currentStrVec.size() + currDnaChar; i++)
    {
        tempDnaVec.push_back(dnaSeqVec[i]);
    }
}

// This function will assign a temporary vector to the current STR vector we are comparing
void assignTempStrVec(ourvector <char> currStrVec, ourvector <char> &tempStrVec, int currStr)
{
    tempStrVec.clear();

    for (int i = 0; i < currStrVec.size(); i++)
    {
        tempStrVec.push_back(currStrVec[i]);
    }
}

// This function will process the DNA sequence and count the number of consecutive STR's
void processDna(ourvector <ourvector <char>> dnaStrVec, ourvector <char> dnaSequence, ourvector <int> &strCountsVec, ourvector <dnaData> databaseVec)
{
    int currDnaChar = 0, currentStreak = 0, maxStreak = 0, currStrChar = 0, tempCounter = 0;
    int currStr = 1;
    int maxPosition = dnaStrVec.size() - 1;
    int matchNucleoCount = 0;
    bool finalStrCheck = false;
    ourvector <char> tempStrVec;
    ourvector <char> tempDnaVec;
    
    if (databaseVec.size() == 0)
    {
        cout << "No database loaded.";
        return;
    }

    if (dnaSequence.size() == 0)
    {
        cout << "No DNA loaded.";
        return;
    }

    cout << "Processing DNA... " << endl;


    // This loop will count the number of consecutive STR's
    for (int i = 1; i < dnaStrVec.size(); i++)
    {
        currDnaChar = 0;
        currentStreak = 0;
        maxStreak = 0;
        tempCounter = 0;

        assignTempStrVec(dnaStrVec[i], tempStrVec, i);

        while (finalStrCheck != true)
        {
            tempCounter = currDnaChar + dnaStrVec[i].size();


            assignTempDnaVec(tempStrVec, dnaSequence, tempDnaVec, tempCounter, currDnaChar);

            // Condition to check with tempCounter that we dont go out of bounds
            if (tempCounter >= dnaSequence.size())
            {
                break;
            }

            if (compareDnaStrVec(tempStrVec, tempDnaVec) == true)
            {
                currDnaChar += tempStrVec.size();
                currentStreak++;
            }

            else
            {
                currDnaChar++;

                if (currentStreak > maxStreak)
                {
                    maxStreak = currentStreak;
                }

                currentStreak = 0;
            }
        }

        strCountsVec.push_back(maxStreak);
    }

}
// This function will return true if there is a match within a given database
bool findMatch(ourvector <int> strCountsVec, dnaData dnaObj)
{
    int matchCount = 0;

    for (int i = 0; i < strCountsVec.size(); i++)
    {
        if (strCountsVec[i] == dnaObj.dnaCounts[i])
        {
            matchCount++;
        }
    }

    if (matchCount == strCountsVec.size())
    {
        return true;
    }

    return false;
}

// This function will compare the STR counts found to the all of the STR counts of the users in the database
void searchDatabase(ourvector <int> strCountsVec, ourvector <dnaData> databaseVec, ourvector <char> dnaSeqVec)
{
    if (databaseVec.size() == 0)
    {
        cout << "No database loaded." << endl;
        return;
    }

    if (dnaSeqVec.size() == 0)
    {
        cout << "No DNA loaded." << endl;
        return;
    }

    if (strCountsVec.size() == 0)
    {
        cout << "No DNA processed." << endl;
        return;
    }

    cout << "Searching database..." << endl;

    for (int i = 0; i < databaseVec.size(); i++)
    {
        if (findMatch(strCountsVec, databaseVec[i]) == true)
        {
            cout << "Found in database! DNA Matches: " << databaseVec[i].dataName << endl;
            return;
        }
    }

    cout << "No match found." << endl;
    
}

// This function will randomly assign a person within a given database, to the user's relative
void specialCommand(ourvector <dnaData> databaseVec, string &randSubjRelative)
{
    int randSubjIdx = rand() % databaseVec.size();

    randSubjRelative = databaseVec[randSubjIdx].dataName;

    cout << "This is the name of the random database subject: " << randSubjRelative << endl;
}

// This function will display the special command message(s)
void displaySpecialMsg()
{
    cout << "---------------------------------------------------------------------\n"
                    "------------------------ SPECIAL COMMAND ----------------------------\n"
                    "---------------------------------------------------------------------\n"
                    "You have now entered the the special command menu of this application.\n"
                    "---------------------------------------------------------------------\n"
                    "---------------------------------------------------------------------\n"
                    "Please be sure to load in a database before proceeding to avoid errors\n"
                    "---------------------------------------------------------------------\n\n"
                    "Within this command you have come to find out that one of the subjects\n"
                    "within this given database may be a relative of yours.\n\n"
                    "You are now tasked with guessing which user is your relative.\n"
                    "Listed below are the list of people in the given database:\n\n";
}

// This function will check if the user's guess is correct or not, displaying the respective messages
void checkSpecialCmd(string userGuess, string randSubjRelative)
{
    if (userGuess == "c" || userGuess == "C")
    {
        cout << "\nYou cheater! This is your relative: " << randSubjRelative << endl;
        return;
    }

    if (randSubjRelative == userGuess)
    {
            cout << "-----------------------------------------------\n"
                    "-----------------------------------------------\n"
                    "\n"
                    "´´´´´´´´´´´´´´´´´´´´¶¶´´´´´´´´´´¶¶\n"
                    "´´´´´´¶¶¶¶¶´´´´´´´¶¶´´´´´´´´´´´´´´¶¶\n"
                    "´´´´´¶´´´´´¶´´´´¶¶´´´´´¶¶´´´´¶¶´´´´´¶¶\n"
                    "´´´´´¶´´´´´¶´´´¶¶´´´´´´¶¶´´´´¶¶´´´´´´´¶¶\n"
                    "´´´´´¶´´´´¶´´¶¶´´´´´´´´¶¶´´´´¶¶´´´´´´´´¶¶\n"
                    "´´´´´´¶´´´¶´´´¶´´´´´´´´´´´´´´´´´´´´´´´´´¶¶\n"
                    "´´´´¶¶¶¶¶¶¶¶¶¶¶¶´´´´´´´´´´´´´´´´´´´´´´´´¶¶\n"
                    "´´´¶´´´´´´´´´´´´¶´¶¶´´´´´´´´´´´´´¶¶´´´´´¶¶\n"
                    "´´¶¶´´´´´´´´´´´´¶´´¶¶´´´´´´´´´´´´¶¶´´´´´¶¶\n"
                    "´¶¶´´´¶¶¶¶¶¶¶¶¶¶¶´´´´¶¶´´´´´´´´¶¶´´´´´´´¶¶\n"
                    "´¶´´´´´´´´´´´´´´´¶´´´´´¶¶¶¶¶¶¶´´´´´´´´´¶¶\n"
                    "´¶¶´´´´´´´´´´´´´´¶´´´´´´´´´´´´´´´´´´´´¶¶\n"
                    "´´¶´´´¶¶¶¶¶¶¶¶¶¶¶¶´´´´´´´´´´´´´´´´´´´¶¶\n"
                    "´´¶¶´´´´´´´´´´´¶´´¶¶´´´´´´´´´´´´´´´´¶¶\n"
                    "´´´¶¶¶¶¶¶¶¶¶¶¶¶´´´´´¶¶´´´´´´´´´´´´¶¶\n"
                    "´´´´´´´´´´´´´´´´´´´´´´¶¶¶¶¶¶¶¶¶¶¶\n"
                    "\n";

            cout << "-----------------------------------------------\n"
                    "-----------------------------------------------\n"
                    "C O N G R A T S  O N  F I N D I N G  T H E M\n"
                    "-----------------------------------------------\n"
                    "-----------------------------------------------\n";
                 
    }

    else
    {
        cout << "Better luck next time. But don't fret, your family is still out there. " << endl;
    }
}

// This function will display the database of a given file
void displayDatabase(ourvector <dnaData> databaseVec)
{
    if (databaseVec.size() != 0)
    {
        cout << "Database loaded:" << endl;

        for (int i = 0; i < databaseVec.size(); i++)
        {
            cout << databaseVec[i].dataName << " ";
            
            for (int j = 0; j < databaseVec[i].dnaCounts.size(); j++)
            {
                cout << databaseVec[i].dnaCounts[j] << " ";
            }

            cout << endl;
        }
    }

    else
    {
        cout << "\nNo Database loaded." << endl;
    }
    
}

// This function will display the DNA Sequence of a give file
void displayDnaSeq(ourvector <char> dnaSeqVec)
{
    if (dnaSeqVec.size() != 0)
    {
        cout << "\nDNA loaded:" << endl;

        for (int i = 0; i < dnaSeqVec.size(); i++)
        {
            cout << dnaSeqVec[i];
        }

        cout << endl;
    }

    else
    {
        cout << "\nNo DNA loaded.";
    }
}

// This function will display the STR counts of a processed DNA sequence
void displayStrCounts(ourvector <ourvector<char>> firstLineStrVec, ourvector <int> strCounts)
{  
    if (strCounts.size() != 0)
    {
        cout << "\nDNA Processed, STR counts:" << endl;

        for (int i = 1; i < firstLineStrVec.size(); i++)
        {
            for (int j = 0; j < firstLineStrVec[i].size(); j++)
            {
                cout << firstLineStrVec[i][j];
            }

            cout << ": " << strCounts[i - 1] << endl;
        }
    }

    else
    {
        cout << "\n\nNo DNA has been processed." << endl;
    }
    
}

// This function will serve as the applications menu
void appMenu(string &userInput)
{
    cout << "\nEnter command or # to exit: ";
    cin >> userInput;
}

// This function will hand the applications functionalities 
void appFunctionality()
{
    string userString, userFile, randSubjRelative, userSubjGuess;
    ourvector <dnaData> databaseVec;
    ourvector <ourvector<char>> dataLineOne;
    ourvector <char> tempVector;
    ourvector <char> dnaSequenceVec;
    ourvector <int> strCountVector;

    while (userString != "#")
    {
        appMenu(userString);

        if (userString == "load_db")
        {
            cin.ignore();
            cin >> userFile;
            databaseVec.clear();
            dataLineOne.clear();
            loadDatabase(userFile, tempVector, databaseVec, dataLineOne);
        }

        if (userString == "load_dna")
        {
            cin.ignore();
            cin >> userFile;
            dnaSequenceVec.clear();
            loadDNA(userFile, dnaSequenceVec);
        }

        if (userString == "process")
        {
            processDna(dataLineOne, dnaSequenceVec, strCountVector, databaseVec);
        }
        
        if (userString == "display")
        {
            // Multiple function call to display DNA data
            displayDatabase(databaseVec);
            displayDnaSeq(dnaSequenceVec);
            displayStrCounts(dataLineOne, strCountVector);
        }

        if (userString == "search")
        {
            searchDatabase(strCountVector, databaseVec, dnaSequenceVec);
        }

        if (userString == "special_cmd")
        {
            displaySpecialMsg();

            for (int i = 0; i < databaseVec.size(); i++)
            {
                cout << i + 1 << "." << databaseVec[i].dataName << " ";
            }

            cout << endl;
            specialCommand(databaseVec, randSubjRelative);

            cout << "\nPlease enter your guess, making sure that you enter the person's name correctly (case sensitive): ";
            cin >> userSubjGuess;
            checkSpecialCmd(userSubjGuess, randSubjRelative);
        }
    }
}

int main() 
{
    cout << "Welcome to the DNA Profiling Application.";
    appFunctionality();    

    return 0;
}
