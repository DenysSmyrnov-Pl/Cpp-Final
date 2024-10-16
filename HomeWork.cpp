#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;

// Class that includes FirstName, SecondName, Score
class Person
{
public:
    string FirstName;
    string SecondName;
    int Score;

    // Class constructor
    Person(const string P_FirstName, const string P_SecondName, int P_score)
        : FirstName(P_FirstName), SecondName(P_SecondName), Score(P_score) {}
};

// Function to output all objects
void CoutAllPersons(const vector<Person> &persons)
{
    cout << "━─━─━━─━━━─━─━─━━─━─━━─━━━─━─━─━" << endl;
    cout << "List of people:" << endl;
    for (unsigned long i = 0; i < persons.size(); i++)
    {
        cout << i + 1 << ") " << persons[i].FirstName << " "
             << persons[i].SecondName << " " << persons[i].Score << endl;
    }
    cout << "━─━─━━─━━━─━─━─━━─━─━━─━━━─━─━─━" << endl;
}

char getChar()
{
    string input;

    while (true)
    {
        getline(cin, input);
        // Check if input is exactly one character and it is a letter
        if (input.length() == 1 && isalpha(input[0]))
        {
            return input[0]; // Return the valid letter
        }
        else
        {
            cout << "Please enter one letter!" << endl;
        }
    }
}

// Function to add a new object
void addPerson(vector<Person> &persons)
{
    string firstName, secondName;
    int score = 0;

    // Loop until we get valid inputs for each field
    while (true)
    {
        cout << "Enter new First Name: ";
        getline(cin, firstName);
        // Check if the first name contains only letters
        if (!firstName.empty() && all_of(firstName.begin(), firstName.end(), ::isalpha))
        {
            break;
        }
        else
        {
            cout << "Error: FirstName can have only letters!" << endl;
        }
    }

    while (true)
    {
        cout << "Enter new Second Name: ";
        getline(cin, secondName);
        // Check if the second name contains only letters
        if (!secondName.empty() && all_of(secondName.begin(), secondName.end(), ::isalpha))
        {
            break;
        }
        else
        {
            cout << "Error: SecondName can have only letters!" << endl;
        }
    }

    while (true)
    {
        cout << "Enter new Score: ";
        string scoreInput;
        getline(cin, scoreInput);
        try
        {
            score = stoi(scoreInput); // Convert input string to integer
            break;
        }
        catch (...)
        {
            cout << "Error: Score must be a number!" << endl;
        }
    }

    // Once all inputs are valid, add the new person to the list
    persons.push_back(Person(firstName, secondName, score));
    cout << "Person added successfully!" << endl;
}

// Function for changing the object
void changePerson(vector<Person> &persons)
{
    while (true)
    {
        unsigned long i = 0;
        cout << "Enter the number of the person you want to modify: ";
        string input;
        getline(cin, input);

        try
        {
            i = stoi(input);
            if (i < 1 || i > persons.size())
            {
                cout << "Invalid person number!" << endl;
                continue; // Ask again if number is invalid
            }
            i--; // Decrease by 1, user enters from 1, but vector starts from 0

            while (true)
            {
                // Asking user what exactly they want to change
                cout << "What do you want to change? (First Name (f), Second Name (s), Score (c)): ";
                char choice = getChar(); // Use getChar to handle single-character input

                if (choice == 'f' || choice == 'F')
                { // Change First Name
                    cout << "Enter new First Name: ";
                    getline(cin >> ws, persons[i].FirstName); // Read the full name
                    break;
                }
                else if (choice == 's' || choice == 'S')
                { // Change Second Name
                    cout << "Enter new Second Name: ";
                    getline(cin >> ws, persons[i].SecondName); // Read the full name
                    break;
                }
                else if (choice == 'c' || choice == 'C')
                { // Change Score
                    cout << "Enter new Score: ";
                    string scoreInput;
                    getline(cin >> ws, scoreInput); // Read the full input
                    try
                    {
                        persons[i].Score = stoi(scoreInput); // Check for valid integer input
                    }
                    catch (...)
                    {
                        cout << "Invalid score. Please enter a valid number." << endl;
                        continue; // Ask again if input is invalid
                    }
                    break;
                }
                else
                {
                    cout << "Invalid choice, please enter 'f', 's', or 'c'." << endl;
                }
            }
            cout << "Person updated successfully!" << endl;
            break;
        }
        catch (...)
        {
            cout << "Error: wrong data" << endl;
            continue; // Ask again if input is invalid
        }
    }
}

// Function to delete an object
void removePerson(vector<Person> &persons)
{
    while (true)
    {
        unsigned long i = 0;
        cout << "Enter the number of the person you want to delete: ";
        string input;
        getline(cin, input);

        try
        {
            i = stoi(input);
            if (i < 1 || i > persons.size())
            { // Check if user wrote correct index
                cout << "Wrong person number!" << endl;
                continue; // Ask again if number is invalid
            }

            i--; // Decrease by 1, the user enters from 1, but indexing starts from 0
            persons.erase(persons.begin() + i);
            cout << "Successfully deleted" << endl;
            break; // Exit after successful deletion
        }
        catch (...)
        {
            cout << "Error: wrong data" << endl;
        }
    }
}

// Function to output to file
void outputToFile(const vector<Person> &persons)
{
    string filename;
    try
    {
        cout << "Enter the output file name: ";
        getline(cin, filename); // Get filename before opening

        ofstream outputFile(filename);
        if (!outputFile.is_open())
        {
            cout << "Error opening output file! => " << filename << endl;
            return; // Exit if file cannot be opened
        }

        for (const auto &person : persons)
        { // Write all persons to file
            outputFile << person.FirstName << " " << person.SecondName << " " << person.Score << endl;
        }
        outputFile.close();
    }
    catch (exception &error)
    {
        cout << error.what() << endl;
    }
}

// Main function
int main()
{
    vector<Person> persons;
    string filename;

    // Reading from file
    try
    {
        cout << "Enter the file name: ";
        getline(cin, filename);

        ifstream file(filename);

        if (!file.is_open())
        { // Checking if the file is open
            cout << "Error opening file! => " << filename << endl;
            return 1; // Exit the program if file can't be opened
        }
        else
        {
            cout << "File opened successfully! => " << filename << endl;
        }

        cout << "\n━─━─━━─━━━─━─━─━━─━─━━─━━━─━─━─━" << endl;

        string line;
        int lineIndex = 0;

        while (getline(file, line))
        {
            lineIndex++;

            if (line.empty())
            {
                cout << lineIndex << ") <= Empty line!" << endl;
                continue;
            }

            istringstream iss(line);
            string firstName;
            string secondName;
            int score;

            if (!(iss >> firstName >> secondName >> score))
            {
                cout << lineIndex << ") <= Error: Incorrect data!" << endl;
                continue;
            }
            persons.push_back(Person(firstName, secondName, score));
            cout << lineIndex << ") <= Correct line!" << endl;
        }
        file.close();
    }
    catch (exception &error)
    {
        cout << error.what() << endl;
    }

    CoutAllPersons(persons); // Output all objects

    // Main loop for modification
    while (true)
    {
        try
        {
            cout << "Do you want to change (c), add (a) or remove (r) a person? (Enter (n) if no): ";

            char choice = getChar(); // Get user input for action

            if (choice == 'c')
            {
                changePerson(persons); // Modify an existing person
            }
            else if (choice == 'a' || choice == 'A')
            {
                addPerson(persons); // Add a new person
            }
            else if (choice == 'r' || choice == 'R')
            {
                removePerson(persons); // Remove a person
            }
            else if (choice == 'n' || choice == 'N')
            {
                break; // Exit the loop if user chooses 'n'
            }
            else
            {
                cout << "No command found, try again!" << endl;
                continue;
            }

            CoutAllPersons(persons); // Output the list of persons after any modification
        }
        catch (exception &error)
        {
            cout << error.what() << endl;
        }
    }

    outputToFile(persons); // Output the final list after modifications

    return 0;
}
