/*-----------------------------------------------
// search.h file

// This file contains all the functions and its related
// implementations for the search engine. The functions
// will be executed within main.cpp. See main.cpp for 
// program description and creative component instructions.

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

-----------------------------------------------*/
#pragma once

#include <iostream>
#include <cctype>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>
using namespace std;


// This function will take in a token and return it lowercased, and free
// from any leading/trailing punctuation. Otherwise, returns an empty string.
string cleanToken(string s) 
{
    bool alphaCheck = false;

    if (s == " ")
    {
        return "";
    }
    
    // Condition to check if any of char's within s are alpha.
    if (any_of(s.begin(), s.end(), ::isalpha) == true)
    {
        alphaCheck = true;
    }

    else
    {
        return "";
    }

    // Condition to begin cleaning token if it contains an alpha.
    if (alphaCheck == true)
    {   
        // This loop will iterate until it reaches an alpha. letter or digit, starting from beginning
        while (!isalpha(s[0]))
        {
            if (isalpha(s[0]) == true || isdigit(s[0]) == true)
            {
                break;
            }

            if (s == "")
            {
                return "";
            }

            if (ispunct(s[0]))
            {
                s.erase(0, 1);
            }
        }

        // This loop will iterate until it reaches a alpha. letter or digit, starting from end
        while (!isalpha(s[s.length() - 1]))
        {   
            if (isalpha(s[s.length() - 1]) == true || isdigit(s[s.length() - 1]) == true)
            {
                break;
            }

            if (s == "")
            {
                return "";
            }
            

            if (ispunct(s[s.length() - 1]))
            {
                s.erase(s.length() - 1, 1);
            }
        }

        // This line will convert the clean token into lowercase
        transform(s.begin(), s.end(), s.begin(), ::tolower);

        return s;
    }    

    return "";
}

// This function will extract the set of unique tokens from the body text.
// It will make use of cleanToken() and return a set of "cleaned" tokens.
set <string> gatherTokens(string fileText) 
{
    set <string> tokensSet;

    stringstream sStream (fileText);
    string tempCleanTok, bufferToken;

    // This loop will iterate (and clean) the body text 
    // until it's end, whilst inserting into a set.
    while (sStream.good())
    {
        getline(sStream, tempCleanTok, ' ');
        
        bufferToken = cleanToken(tempCleanTok);

        if (bufferToken == "")
        {
            continue;
        }

        tokensSet.insert(bufferToken);
    }
    
    return tokensSet;
}

// This function will read the contents from the database file and processes it into
// the form of an inverted index. It will return the num. of documents processed.
int buildIndex(string filename, map<string, set<string>>& index) 
{
    ifstream fileStream;
    set <string> tokenSet;
    set <string> tempUrlSet;
    string bodyText, urlLink;
    int pagesCounter = 0;

    fileStream.open(filename);

    if (!fileStream.is_open())
    {
        cout << "Error: unable to open " << "'" << filename << "'" << endl;
        return 0;
    }

    index.clear();

    // This loop will iterate into the end of the file, reading its contents
    while(!fileStream.eof())
    {
        // This line will retrieve the URL link of the given
        // database file and increment the counter if valid
        getline(fileStream, urlLink);

        if (urlLink == "")
        {
            continue;
        }

        // Condition to count num. of webpages processed
        else
        {
            ++pagesCounter;
        }

        // This block will retrieve the body text of the given 
        // database file and process it into clean tokens
        getline(fileStream, bodyText);

        if (bodyText == "")
        {
            continue;
        }

        // Function call to "clean" body text, inserting into a set
        tokenSet = gatherTokens(bodyText);

        // This loop will iterate through our set, populating the map with key-value pairs (building inverted index)
        for (auto tempCleanTok : tokenSet)
        {
            tempUrlSet.clear();

            // Condition to check if the unique word exists in the map, 
            // if so add the URL link to its associated set-value
            if (index.count(tempCleanTok) > 0)
            {
                tempUrlSet = index[tempCleanTok];
                tempUrlSet.insert(urlLink);
                index[tempCleanTok] = tempUrlSet;
            }

            // Otherwise, create a new key-value pair with its associated URL link
            else
            {
                tempUrlSet.insert(urlLink);
                index[tempCleanTok] = tempUrlSet;
            }
        }
    }

    return pagesCounter;
}

// This function will take in a sentence entered by the user, the built index and will parse the
// user's search query, applying the appropriate set operations, then returning the resultant set.
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) 
{
    vector <string> queryTokenVec;
    set <string> result, tempSet;
    set <string> intersectSet;
    set <string> differenceSet;
    set <string> unionSet;
    string tempString, tempCleanTok, tokenToInsp;
    
    stringstream sStream (sentence);
    
    // This loop will separate the user's query into multiple vector indexes
    while(sStream.good())
    {
        getline(sStream, tempString, ' ');
        queryTokenVec.push_back(tempString);
    }    

    // Condition to check if there are more than a single term within query
    if (queryTokenVec.size() > 1)
    {
        // Function call to clean and obtain set of first query keyword
        tempCleanTok = cleanToken(queryTokenVec[0]);
        result = index[tempCleanTok];

        // This loop will iterate over the vector containing query keywords,
        // cleaning them and performing the appropriate set operations 
        for (int i = 1; i < queryTokenVec.size(); i++)
        {
            tokenToInsp = queryTokenVec[i];
            tempSet.clear();

            // Condition to find the intersection between the two sets
            if (queryTokenVec[i][0] == '+')
            {
                tempCleanTok = cleanToken(queryTokenVec[i]);

                intersectSet.clear();

                set_intersection(result.begin(), result.end(), index[tempCleanTok].begin(), index[tempCleanTok].end(), std::inserter(intersectSet, intersectSet.begin()));

                result.clear();

                result.insert(intersectSet.begin(), intersectSet.end());
            }

            // Condition to find the difference between the two sets
            else if (queryTokenVec[i][0] == '-')
            {
                tempCleanTok = cleanToken(queryTokenVec[i]);

                differenceSet.clear();

                set_difference(result.begin(), result.end(), index[tempCleanTok].begin(), index[tempCleanTok].end(), std::inserter(differenceSet, differenceSet.begin()));

                result.clear();

                result.insert(differenceSet.begin(), differenceSet.end());
            }

            // Condition to find the union of the two sets
            else
            {
                tempCleanTok = cleanToken(queryTokenVec[i]);

                result.insert(index[tempCleanTok].begin(), index[tempCleanTok].end());
            }
        }
    }

    // Otherwise, there was only one keyword entered into query
    else
    {
        tempCleanTok = cleanToken(queryTokenVec[0]);
        result = index[tempCleanTok];
    }
    
    return result;
}

// This function will remove all of the specified stop words from a given database and compare
// the size of the inverted index. It will also allow the to see the list of removed stop words.
void specialCommand(map <string, set<string>> &index)
{
    // Set declaration of stop-words
    set <string> stopWords = {"a", "an", "and", "but", "each", "how", "for", "if", "in", "it's", "my", "no", "or", "our", "some", "that", "the", "they", "yet"};
    vector <string> wordsRemoved;
    char userInput;

    // This loop will iterate through stopWords, deleting matches from inverted index
    for (auto stopWord : stopWords)
    {
        if (index.count(stopWord) > 0)
        {
            index.erase(stopWord);
            wordsRemoved.push_back(stopWord);
        }
    }

    cout << "\nWould you like to see the words that were removed from our index (Enter y/n)?: ";
    cin >> userInput;

    userInput = tolower(userInput);

    // Condition to display the list of removed stop words
    if (userInput == 'y')
    {
        cout << "-----------------------------------------------------------------------------------------------------------\n";
        cout << "\nThese were the stop-words that were removed from our index: ";

        for (int i = 0; i < wordsRemoved.size(); i++)
        {
            cout << wordsRemoved[i];

            if (i == (wordsRemoved.size() - 1))
            {
                cout << ".";
            }

            else
            {
                cout << ", ";
            }
        }

        cout << "\n-----------------------------------------------------------------------------------------------------------\n";

        cin.ignore();

        return;
    }

    // Condition to check if the user declines list display
    if (userInput == 'n')
    {
        cout << "Suit yourself.";

        cin.ignore();

        return;
    }
    
    else
    {
        cout << "Invalid input.";

        cin.ignore();

        return;
    }
}

// This function will build an inverted index for a given database. It will also prompt the
// user to enter a search query and will then return the webpage links to said token(s).
void searchEngine(string filename) 
{
    map <string, set <string>> databaseIndex;
    set <string> querySet;
    string userSentence;
    int pagesProcessed = 0;
    bool userQuit = false;

    pagesProcessed = buildIndex(filename, databaseIndex);

    cout << "Stand by while building index..." << endl;
    cout << "Indexed " << pagesProcessed << " pages containing " << databaseIndex.size() << " unique terms\n\n";

    // This loop will prompt the user for input until the user presses the ENTER key alone
    while (userQuit != true)
    {
        userSentence.clear();

        cout << "Enter query sentence (press enter to quit OR enter \"refine search\"): ";
        getline(cin, userSentence);

        // Condition to check if the user presses the ENTER key alone
        if (userSentence == "")
        {
            cout << "Thank you for searching!" << endl;
            userQuit = true;
            return;
        }

        // Condition to check if the enters "refine search" as a query
        if (userSentence == "refine search")
        {
            cout << "-----------------------------------------------------------------------------------------------------------\n";
            cout << "You have now prompted the search engine to remove all instances of the most commonly used stop words.\n";
            cout << "-----------------------------------------------------------------------------------------------------------\n";
            cout << "-----------------------------------------------------------------------------------------------------------\n";
            cout << "There were originally " << databaseIndex.size() << " unique terms that were processed.\n";
            cout << "-----------------------------------------------------------------------------------------------------------\n";

            specialCommand(databaseIndex);

            cout << "\nAfter filtering out the stop words from the inverted index, ther are now " << databaseIndex.size() << " unique terms.\n\n";
            continue;
        }

        querySet.clear();

        // Function call to perform token search within inverted index
        querySet = findQueryMatches(databaseIndex, userSentence);

        cout<< "Found " << querySet.size() << " matching pages\n";

        // This loop will display the token's associated URL links, if any
        for (auto it : querySet)
        {
            cout << it << endl;
        }

        cout << endl;
    }

    return;    
    
}
