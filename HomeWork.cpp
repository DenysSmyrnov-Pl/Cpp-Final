#include <fstream>
#include <iostream>
#include <sstream>
#include <vector> // I chose vector instead of list due to its flexibility and if we can't predict the amount of Pearson in Input file

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
    unsigned long i = 0;
    cout << "List of people:" << endl;
    for (i = 0; i < persons.size(); i++)
    {
        cout << i + 1 << ") ";
        cout << persons[i].FirstName << " ";
        cout << persons[i].SecondName << " ";
        cout << persons[i].Score << endl;
    }
}

// Function to add a new object
void addPerson(vector<Person> &persons)
{
    string firstName, secondName;
    int score;

    cout << "Enter new First Name: ";
    cin >> firstName;

    cout << "Enter new Second Name: ";
    cin >> secondName;

    cout << "Enter new Score: ";
    cin >> score;

    persons.push_back(Person(firstName, secondName, score));
}

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
        cin >> i;

        if (i < 1 || i > persons.size()) // check if User wrote correct index line
        {
            cout << "Invalid person number!" << endl;
            break;
            return;
        }

        i--; // Decrease by 1, the user enters from 1, but indexing starts from 0
        persons.erase(persons.begin() + i);
        break;
    }
}

bool continueChanging(vector<Person> &persons)
{
    while (true)
    {
        cout << "Continue changing list? Yes (y) / No (n): ";
        char Y_N;
        cin >> Y_N;
        if (Y_N == 'n')
        {
            return false;
            break;
        }
        else if (Y_N == 'y')
        {
            CoutAllPersons(persons); // Output of all created objects
            break;
            return 0;
        }
        else
        {
            cout << "No command found, try again! " << endl;
            return 1;
        }
    }
}

int main()
{
    vector<Person> persons;
    string filename;

    try // trying to read file
    {
        cout << "Enter the file name: ";
        cin >> filename;

        ifstream file(filename);

        if (!file.is_open()) // Checking if the fileName is Empty
        {
            cout << "Error opening file!" << endl;
            main();
        }

        cout << "━─━─━━─━━━─━─━─━━─━─━━─━━━─━─━─━" << endl;

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

    CoutAllPersons(persons); // Output of all created objects
    while (true)
    {
        try // Changing, adding, deleting objects at the user request
        {
            char choice;
            cout << "Do you want to change (c), add (a) or remove (r) a person? (Enter (n) if no): ";
            cin >> choice;
            if (choice == 'c')
            {
                changePerson(persons);
                if (continueChanging(persons))
                {
                    break;
                }
                else
                {
                    break;
                }
            }
            else if (choice == 'a')
            {
                addPerson(persons);
                if (continueChanging(persons))
                {
                    break;
                }
                else
                {
                    break;
                }
            }
            else if (choice == 'r')
            {
                removePerson(persons);
                if (continueChanging(persons))
                {
                    break;
                }
                else
                {
                    break;
                }
            }
            else if (choice == 'n')
            {
                break;
            }
            else
            {

                cout << "No command found, try again! " << endl;
                main();
            }
        }
        catch (exception error)
        {
            cout << error.what() << endl;
        }
    }

    CoutAllPersons(persons); // Output the new list
    try
    {
        cout << "Enter the output file name: ";
        cin >> filename;

        ofstream outputFile(filename);
        if (!outputFile.is_open())
        {
            cout << "Error opening output file!" << endl;
            return 1;
        }

        for (unsigned long i = 0; i < persons.size(); i++)
        {
            Person person = persons[i];
            outputFile << person.FirstName << " " << person.SecondName << " " << person.Score << endl;
        }

        outputFile.close();
    }
    catch (exception error)
    {
        cout << error.what() << endl;
    }

    while (true)
    {
        cout << "set the program again? Yes (y) / No (n): ";
        char Y_N;
        cin >> Y_N;
        if (Y_N == 'y')
        {
            main();
        }
        else if (Y_N == 'n')
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
