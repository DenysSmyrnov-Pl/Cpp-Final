#include <fstream>
#include <iostream>
#include <sstream>
#include <vector> // I chose vector instead of list due to its flexibility and if we can't predict the amount of Pearson in Input file
#include <cctype>

using namespace std;

// Сlass that include FirstName, SecondName, Score
class Person
{
public:
    string FirstName;
    string SecondName;
    int Score;

    // Сlass constructor
    Person(const string P_FirstName, const string P_SecondName, int P_score)
        : FirstName(P_FirstName), SecondName(P_SecondName), Score(P_score) {}
};

// Function to output all objects
void CoutAllPersons(vector<Person> persons)
{
    cout << "━─━─━━─━━━─━─━─━━─━─━━─━━━─━─━─━" << endl;
    unsigned long i = 0;
    cout << "List of people:" << endl;
    for (i = 0; i < persons.size(); i++)
    {
        cout << i + 1 << ") ";
        cout << persons[i].FirstName << " ";
        cout << persons[i].SecondName << " ";
        cout << persons[i].Score << endl;
    }
    cout << "━─━─━━─━━━─━─━─━━─━─━━─━━━─━─━─━" << endl;
}

char getChar()
{
    string input;

    while (true)
    {
        getline(cin, input); // Capture the entire input, including spaces))

        // Check if input is exactly one character and it is a letter
        if (input.length() == 1 && isalpha(input[0]))
        {
            return input[0]; // Return the valid letter
        }
        else
        {
            cout << "Plese enter one letter!" << endl;
            //  cout << "Do you want to change (c), add (a) or remove (r) a person? (Enter (n) if no): "; // Print error message
            // Clear input buffer to prevent any further issues
            cin.clear();
        }
    }
}

// Function to add a new object
void addPerson(vector<Person> &persons)
{
    string firstName, secondName;
    string score;

    cout << "Enter new First Name: ";
    getline(cin, firstName);

    cout << "Enter new Second Name: ";
    getline(cin, secondName);

    cout << "Enter new Score: ";
    getline(cin, score);
    try
    {
        int Newscore = stoi(score);
        persons.push_back(Person(firstName, secondName, Newscore));
    }
    catch (...)
    {
        cout << "Error: wrong data" << endl;
        addPerson(persons);
    }
}
bool continueChanging(vector<Person> &persons);
// Function for changing the object
void changePerson(vector<Person> &persons)
{

    while (true)
    {
        unsigned long i = 0;
        cout << "Enter the number of the person you want to modify: ";
        cin >> i;

        if (i < 1 || i > persons.size())
        {
            cout << "Invalid person number!" << endl;

            break;
            return;
        }

        i--; // Decrease by 1, the user enters from 1, but vector start from 0

        cout << "Enter new First Name: ";
        cin >> persons[i].FirstName;

        cout << "Enter new Second Name: ";
        cin >> persons[i].SecondName;

        cout << "Enter new Score: ";
        cin >> persons[i].Score;
        break;
    }
}

// Function to delete an object
void removePerson(vector<Person> &persons)
{
    while (true)
    {
        unsigned long i = 0;
        cout << "Enter the number of the person you want to delete: ";
        // cin >> i;
        string input;

        getline(cin, input);

        try
        {
            i = stoi(input);
            if (i < 1 || i > persons.size()) // check if User wrote correct index line
            {
                cout << "Invalid person number!" << endl;
                break;
                return;
            }
            else
            {
            }

            i--; // Decrease by 1, the user enters from 1, but indexing starts from 0
            persons.erase(persons.begin() + i);
            cout << "Sucsecfully" << endl;
            break;
            break;
        }
        catch (...)
        {
            cout << "Error: wrong data" << endl;
            removePerson(persons);
        }
    }
}

// Function to check if the user wants to continue changing
bool continueChanging(vector<Person> &persons)
{
    char Y_N;
    while (true)
    {
        cout << "Continue changing list? Yes (y) / No (n): ";
        cin >> Y_N;

        if (Y_N == 'y' || Y_N == 'Y') // If the user wants to continue
        {
            CoutAllPersons(persons); // Output the list of persons before continuing
            return true;             // Return true to continue editing
        }
        else if (Y_N == 'n' || Y_N == 'N') // If the user wants to stop
        {
            return false; // Return false to stop the loop
        }
        else
        {
            cout << "Invalid input. Please enter 'y' or 'n'." << endl; // Invalid input handling
        }
    }
}

// Main function
int main()
{
    vector<Person> persons;
    string filename;

    // Reading from file
    try // trying to read file
    {
        cout << "Enter the file name: " << filename;
        getline(cin, filename);

        ifstream file(filename);

        if (!file.is_open()) // Checking if the fileName is Empty
        {
            cout << "Error opening file! => " << filename << endl;
            main();
        }
        else
        {
            cout << "file opened successfully! => " << filename << endl;
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
    catch (exception error)
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

            // Ask if the user wants to continue modifying the list
            if (!continueChanging(persons)) // If the user says 'n', exit the loop
            {
                break;
            }
        }
        catch (exception error)
        {
            cout << error.what() << endl;
        }
    }

    CoutAllPersons(persons); // Output the final list after modifications

    // Output to file
    try
    {
        cout << "Enter the output file name: ";
        getline(cin, filename);

        ofstream outputFile(filename);
        if (!outputFile.is_open())
        {
            cout << "Error opening output file! => " << filename << endl;
            return 1;
        }

        for (unsigned long i = 0; i < persons.size(); i++) // Write all persons to file
        {
            Person person = persons[i];
            outputFile << person.FirstName << " " << person.SecondName << " " << person.Score << endl;
        }
        outputFile.close();
    }
    catch (exception &error)
    {
        cout << error.what() << endl;
    }
    while (true)
    {
        cout << "set the program again? Yes (y) / No (n): ";
        char Y_N;
        cin >> Y_N;
        if (Y_N == 'y' || Y_N == 'Y')
        {
            main();
        }
        else if (Y_N == 'n' || Y_N == 'N')
        {
            break;
            return 0;
        }
        else
        {
            cout << "No command found, try again! " << endl;
            continue;
        }
    }
}