/*-----------------------------------------------------------------------------
* 
* Author: Christopher Adams
* Email: ceadams0707@my.msutexas.edu
* Label: 04-P02
* Title: Linear Search - Using Json and Getch
* Course: CMPS 3013
* Semester: Spring 2024
* 
* Description:
*       This program is based on a program provided by Dr. Terry Griffin
* 
*       It loads data from a Json file and uses getch to look up values from
*       said data.
* 
*       It creates an interactive session within the console for the user to
*       type in letters and have autosuggestions appear.
* 
*       The number of matches and the time of the search based on the user
*       input is displayed, as well as a list of (at most 10) matches.
* 
* Files:
*       console.hpp: Contains console functions
*       json.hpp: JSON for modern C++; allows for creation of JSON objects
*       loadJsonEx.hpp: Loads a json object based on a file path
*       rang.hpp: Allows for coloring text in console
*       timer.hpp: Allows for the timing of code execution
* 
*---------------------------------------------------------------------------*/

#include "console.hpp"
#include "json.hpp"
#include "loadJsonEx.hpp"
#include "rang.hpp"
#include "timer.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

using namespace std;
using namespace rang;
using json = nlohmann::json;

consoleSize console_size;   // used to store the size of console 
                            // (width=cols and height=rows)

/*-partialMatch----------------------------------------------------------------
 *
 * Description:
 *      Finds partial matches in an array of strings and returns them. It
 *      doesn't matter where in the string the match is.
 * Params:
 *      vector<string>  array       - array to search
 *      string          substring   - substring to search for in each word
 *
 * Returns:
 *      vector<string> - holding all the matches to substring
 */
vector<string> partialMatchJson(json j_son, string substring)
{
    int substringLength;    // Holds substring.length()
    vector<string> matches; // Holds matches
    size_t found;           // size_t is an integer position of
                            // found item. -1 if its not found

    substringLength = substring.length();

    // Handles empty string
    if (substringLength == 0)
        return matches;

    // Iterate over all key-value pairs
    for (auto& element : j_son.items()) 
    {
        string key = element.key();
        // Check if the key starts with substring
        if (key.substr(0, substringLength) == substring) {
            // Found a match, add to vector
            matches.push_back(key);
        }
    }

    return matches;
}

/*-titleBar--------------------------------------------------------------------
* Prints a long background row of green, with black text centered.
*/
void titleBar(string title, int length = console_size.width) {
    string padding = string((length / 2) - (title.size() / 2), ' ');
    title = padding + title + padding;
    cout << bgB::green << fg::black << title 
         << bg::reset << fg::reset << endl;
}

/*-horizontalBar---------------------------------------------------------------
 *
 * Description:
 *      Prints a horizontal bar of a given length
 * Params:
 *      int length - length of the bar
 * Returns:
 *      void
 */
void horizontalBar(int length = console_size.width) {
    string line = string(length, '_');
    cout << fg::gray << line << fg::reset << endl;
}

/*-printMatches----------------------------------------------------------------
 *
 * Description:
 *      Prints the matches to the screen.
 * Params:
 *      vector<string> matches - vector of matches
 * Returns:
 *      void
 */
void printMenu(vector<string> options) {
    int i = 1;
    for (auto s : options) {
        cout << fg::green << style::bold << i << ". " << s 
             << fg::reset << bg::reset << endl;
        i++;
    }
}

/*-printHighlightedSubstr------------------------------------------------------
 *
 * Description:
 *      Given a word, print the substr underlined and red vs blue for the rest
 *      of the word.
 * Params:
 *      string word - word to print
 *      string substr - substring to highlight in red
 *      int loc - location of substr in word
 * Returns:
 *      void
 */
void printHighlightedSubstr(string word, string substr) {
    for (int j = 0; j < word.size(); j++) {
        // If we are printing the substring turn it cyan
        if (j <= substr.size() - 1) {
            cout << fg::cyan << style::bold << style::underline << word[j]
                << fg::reset << style::reset;
        }
        else {
            cout << fg::green << style::bold << word[j]
                << fg::reset << style::reset;
        }
    }
}

/*-printCurrent----------------------------------------------------------------
 *
 * Description:
 *      Prints the current key pressed and the current substr to the screen.
 * Params:
 *      char k - last character pressed.
 *      string word - current substring being printed.
 * Returns:
 *      void
 */
void printCurrent(char k, string word) {
    
    cout << fg::green << style::bold << "KeyPressed: \t\t" << style::reset
         << fgB::yellow;

    if (int(k) == 8) {
        cout << "backspace";
    }
    else if (int(k) == 127) {
        cout << "del";
    }
    else {
        cout << k;
    }

    cout << " = " << (int)k << fg::reset << endl;
    cout << fg::green << style::bold << "Current Substr: \t" << fg::reset
         << fgB::cyan << word << fg::reset << style::reset << endl << endl;
}

/*-errorMessage----------------------------------------------------------------
 *
 * Description:
 *      Prints an error message to the screen.
 * Params:
 *      string message - message to print
 * Returns:
 *      void
 */
void errorMessage(string message) {
    cout << bgB::red << fgB::gray << message 
         << bg::reset << fg::reset << endl;
    Sleep(1);
}

/*-main----------------------------------------------------------------------*/
int main() {

    bool deleting 
        = false;
    char k;             // holder for character being typed
    console_size        // width and height of console
        = getConsoleSize();
    int loc;            // location of substring to change its color
    json dictionary     // Dictionary of words
        = loadJsonFile("dictionary.json");
    json matches;       // Any matches found in dictionary
    string key;         // string version of char for printing
    string str = "";
    string substr       // var to concatenate letters to
        = "";
    vector<string> mainMenu;

    mainMenu.push_back("Type letters and watch the results change.");
    mainMenu.push_back(
        "Hit the BACKSPACE key to erase a letter from your search string.");
    mainMenu.push_back(
        "Enter 0 to end the program.");
    mainMenu.push_back(
        "When a single word is found, hit enter. (this is for real assignment.");

    clearConsole();
    titleBar("Getch Example", console_size.width);
    printMenu(mainMenu);

    // While 0 is not typed keep looping
    while ((k = getchNewName()) != '0') {

        Timer T;   // create a timer
        T.Start(); // start it

        clearConsole();
        titleBar("Getch Example", console_size.width);
        printMenu(mainMenu);

        // If backspace
        if ((int)k == 8) {
            // Delete last letter from "substr"
            if (substr.size() > 0) {
                substr = substr.substr(0, substr.size() - 1);
                deleting = true;
            }
        }
        // If not a letter, print error message
        else if (!isalpha(k))
            errorMessage("Letters only!");
        // Must be a letter
        else {
            if ((int)k < 97)    // if uppercase
                k += 32;        // Make lower
            // Append letter to substr
            substr += k;
        }
        
        /*-Print key pressed and cumulative substring------------------------*/
        horizontalBar();
        printCurrent(k, substr);

        /*-Print matches-----------------------------------------------------*/
        horizontalBar();
        
        // Find any words in the json that start with
        // our substr word
        matches = partialMatchJson(dictionary, substr);
        
        // Print match count
        cout << style::bold << style::underline << fg::green
            << "MATCHES: " << fg::green << matches.size() << style::reset
            << fg::reset << endl
            << endl;

        for (auto& c : substr)
            c = tolower(c);
        key = to_string(k);
        
        // This prints found matches
        // Display 10 results at most
        int loopMax = min(10, matches.size());
        // Loop through matches
        for (int i = 0; i < loopMax; i++)
        {
            // Print matches with substring highlighted
            string key = matches[i];
            printHighlightedSubstr(key, substr);
            cout << " ";
        }
        cout << endl << endl << endl << endl;

        // End timer
        T.End();
        // Print time
        cout << fg::green << style::bold;
        printf("Search time: %.3f", (double)T.NanoSeconds() / 1000000000);
        cout << " nanoseconds.\n" 
             << fg::reset << style::reset;
    }
    return 0;
}
