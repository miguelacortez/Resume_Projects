/*---------------------------------------------------------
//  Project 2 - Search Engine
  
// This program will create an inverted index from a given
// .txt file. It will then allow the user to enter a search
// query, executing the applicable search operations and 
// displaying the associated URL links to the user.

// Author: Miguel Cortez
// Course: CS 251, Fall 2022.
// Date: 9/20/2022

// -----// INSTRUCTIONS FOR CREATIVE FEATURE //-----

// Description: The creative feature will allow the 
// user to refine their search, by removing the most
// common stop words in the English language. 

// To execute this command, the user must enter 
// "refine search" into the terminal when prompted; 
// followed by pressing the ENTER key. 

// Following the execution of the index filtering, 
// the user will be asked if they would like to 
// see a list of the stop words that were removed.
---------------------------------------------------------*/

#include <iostream>
#include <cctype>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include "search.h"
using namespace std;

int main() 
{    
    string fileName = "cplusplus.txt";
    searchEngine(fileName);

    // Use this function to call and test the functions you write inside of
    // search.h.  If you do not call the functions here, nothing will run.

    // -------- Various Test Strings that were used -------- //
    
    // string testString = "EGGS! milk, fish,      @  bread cheese";
    // string testStringOne = "vector +container - pointer";
    // string testStringTwo = "information";
    // string testStringThree = "vector -bool";
    // string testStringFour = "uiccs.news.txt";
    // string testStringFive = "wiki-uni.txt";
    // userSentence = "vector +container -pointer";
    

    // --- Various test containers that were declared for testing --- //
    // string fileName, userSentence;
    // set <string> testSet;
    // map <string, set<string>> testMap;
    
    // -------- Various Function Call Tests for Milestones --------

    // -------- Testing For Milestone #1 -------- //

    // string teststringggg = "----...mCoRTE34@uiC.eDU--...";
    // string testttttt = "$$$..;banana--...";
    // string stringstring = "--.O'neil...";
    // cout << cleanToken(testStringTwo) << endl;

    // -------- Testing for Milestone #2 -------- //

    // testSet = gatherTokens(testString);

    // cout << endl << "This is the cleaned set: " << endl;
    // for (auto i : testSet)
    // {
    //     cout << i << endl;
    // }

    // cout << "This is the size of the set: " << testSet.size() << endl;

    // --------- Testing for Milestone #3 -------- //

    // cout << "Stand by while building index..." << endl;
    // cout << "Indexed " << buildIndex(fileName, testMap) << " pages containing " << testMap.size() << " unique terms\n\n";

    // for (auto it = testMap.begin(); it != testMap.end(); it++)
    // {
    //     cout << "Key: " << it->first << " --> Value(s): ";

    //     set<string> tempSet = it->second;

    //     for (auto it = tempSet.begin(); it != tempSet.end(); it++)
    //     {
    //         cout << (*it) << ", ";
    //     }

    //    cout << endl;
    // }

    // -------- Testing for Milestone #4 --------- //

    // testSet = findQueryMatches(testMap, userSentence);

    // cout<< "Found " << testSet.size() << " matching pages\n";

    // for (auto it = testSet.begin(); it != testSet.end(); it++)
    // {
    //     cout << (*it) << endl;
    // }

    // -------- Testing for Milestone #5 --------- //

    // string userInput;
    // vector <string> userVec;

    // cout << "Please enter a sentence: ";
    // getline(cin, userInput);
    // stringstream sssstream(userInput);
    
    //if (userSentence == "")
    // {
    //     cout << "Thank you for searching!" << endl;
    // }

    // -------- Testing for Creative Component --------- //

    // set <string> stopSet = set <string> stopWords = {"a", "an", "and", "but", "each", "how",
    // "for", "if", "in", "it's", "my", "no", "or", "our", "some", "that", "the", "they", "yet"};

    // string stopppp = "in";
    // string stooop = "the";


    return 0;
}

