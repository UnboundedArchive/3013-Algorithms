## P02 - Using Json and Getch
### Christopher Adams
### Description:
This program is based on a program provided by Dr. Terry Griffin
It loads data from a Json file and uses getch to look up values from
said data.
It creates an interactive session within the console for the user to
type in letters and have autosuggestions appear.
The number of matches and the time of the search based on the user
input is displayed, as well as a list of (at most 10) matches.

### Files
|   #   | File             | Description                               | Location                             |
| :---: | ---------------- | ----------------------------------------- | ------------------------------------ |
|   1   | main.cpp         | Main file that launches program           | [./main.cpp](./main.cpp)             |
|   2   | console.hpp      | Contains console functions                | [./console.hpp](./console.hpp)       |
|   3   | json.hpp         | JSON for modern C++                       | [./json.hpp](./json.hpp)             |
|   4   | loadJsonEx.hpp   | Loads a json object based on a file path  | [./loadJsonEx.hpp](./loadJsonEx.hpp) |
|   5   | rang.hpp         | Allows for coloring text in console       | [./rang.hpp)](./rang.hpp)            |
|   6   | timer.hpp        | Allows for the timing of code execution   | [./timer.hpp](./timer.hpp)           |
