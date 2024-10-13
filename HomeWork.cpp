#include <fstream>
#include <iostream>
#include <sstream>
#include <vector> // I chose vector instead of list due to its flexibility and if we can't predict the amount of Pearson in Input file

using namespace std;

class Person // Сlass that include FirstName, SecondName, Score
{
public:
    string FirstName;
    string SecondName;
    int Score;

    // Сlass properties
    Person(const string P_FirstName, const string P_SecondName, int P_score)
        : FirstName(P_FirstName), SecondName(P_SecondName), Score(P_score) {}
};

// Function to output all objects
void CoutAllPersons(vector<Person> persons)
{
    cout << "List of people:" << endl;
    for (int i = 0; i < persons.size(); i++)
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
    std::string firstName, secondName;
    int score;

    cout << "Enter First Name: ";
    cin >> firstName;
    cout << "Enter Second Name: ";
    cin >> secondName;
    cout << "Enter Score: ";
    cin >> score;

    persons.emplace_back(firstName, secondName, score);
}

// Function for changing the object
void changePerson(vector<Person> &persons)
{
    int index;
    cout << "Enter the number of the person you want to modify: ";
    cin >> index;

    if (index < 1 || index > persons.size())
    {
        cout << "Invalid person number!" << endl;
        return;
    }

    index--; // Decrease by 1, since the user enters from 1, and indexing starts from 0

    cout << "Enter new First Name: ";
    cin >> persons[index].FirstName;

    cout << "Enter new Second Name: ";
    cin >> persons[index].SecondName;

    cout << "Enter new Score: ";
    cin >> persons[index].Score;
}

// Function to delete an object
void removePerson(vector<Person> persons)
{
    int i;
    cout << "Enter the number of the person you want to delete: ";
    cin >> i;

    if (i < 1 || i > persons.size()) // check if User wrote correct index line
    {
        cout << "Invalid person number!" << endl;
    }

    i--; // Decrease by 1, the user enters from 1, but indexing starts from 0

    persons.erase(persons.begin() + i);
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
            return 1;
        }

        string line;
        int lineIndex = 0;

        while (getline(file, line))
        {
            lineIndex++;
            istringstream iss(line);
            string firstName;
            string secondName;
            int score;

            if (!(iss >> firstName >> secondName >> score))
            {

                if (line == "")
                {
                    cout << "Empty line! => " << lineIndex << endl;
                }

                cout << "Error: Incorrect data! => " << lineIndex << endl;
                continue;
            }
            persons.emplace_back(firstName, secondName, score);
        }
        file.close();
    }
    catch (exception error)
    {
        cout << "Error: " << error.what() << endl;
    }

    CoutAllPersons(persons); // Output of all created objects

    try // Changing, adding, deleting objects at the user request
    {
        char choice;
        cout << "Do you want to change (c), add (a) or remove (r) a person? (Enter (n) if no): ";
        cin >> choice;

        if (choice == 'c')
        {
            changePerson(persons);
        }
        else if (choice == 'a')
        {
            addPerson(persons);
        }
        else if (choice == 'r')
        {
            removePerson(persons);
        }
        else if (choice == 'n')
        {
        }
        else
        {
            cout << "No command found!" << endl;
        }
        CoutAllPersons(persons); // Output the new list
    }
    catch (exception error)
    {
        cout << "Error: " << error.what() << endl;
    }
    // Write to output file
    try
    {
        cout << "Enter the output file name: ";
        cin >> filename;

        ofstream outputFile(filename);
        if (!outputFile.is_open())
        {
            cout << "Error opening output file!" << endl;
        }

        for (auto person : persons)
        {
            outputFile << person.FirstName << " " << person.SecondName << " " << person.Score << endl;
        }

        outputFile.close();
    }
    catch (exception error)
    {
        cout << "Error: " << error.what() << endl;
    }
}
