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

    // Сlass properties
    Person(const string P_FirstName, const string P_SecondName, int P_score)
        : FirstName(P_FirstName), SecondName(P_SecondName), Score(P_score) {}
};

// Function to output all objects
void CoutAllPersons(vector<Person> persons)
{
    size_t i = 0;
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
    // OR
    // persons.emplace_back(firstName, secondName, score);
}

// Function for changing the object
void changePerson(vector<Person> &persons)
{
    // WARNING: that about this comment?
    size_t i = 0; // size_t becouse compare with vector size
    cout << "Enter the number of the person you want to modify: ";
    cin >> i;

    if (i < 1 || i > persons.size())
    {
        cout << "Invalid person number!" << endl;
        return;
    }

    i--; // Decrease by 1, the user enters from 1, but vector start from 0

    cout << "Enter new First Name: ";
    cin >> persons[i].FirstName;

    cout << "Enter new Second Name: ";
    cin >> persons[i].SecondName;

    cout << "Enter new Score: ";
    cin >> persons[i].Score;
}

// Function to delete an object
void removePerson(vector<Person> &persons)
{
    size_t i;
    cout << "Enter the number of the person you want to delete: ";
    cin >> i;

    if (i < 1 || i > persons.size()) // check if User wrote correct index line
    {
        cout << "Invalid person number!" << endl;
        // WARNING: that happen after error?
    }

    i--; // Decrease by 1, the user enters from 1, but indexing starts from 0

    // WARNING: that is 'persons.begin()'?

    persons.erase(persons.begin() + i);
}

bool continueChanging()
{
    cout << "Continue changing list? Yes (y) / No (n): ";
    char Y_N;
    cin >> Y_N;
    if (Y_N == 'n')
    {
        return false;
    }
    return true;
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
        }

        string line;
        int lineIndex = 0;

        while (getline(file, line))
        {
            lineIndex++;

            if (line.empty())
            {
                cout << "Empty line! => " << lineIndex << endl;
                continue;
            }

            istringstream iss(line);
            string firstName;
            string secondName;
            int score;

            if (!(iss >> firstName >> secondName >> score))
            {
                cout << "Error: Incorrect data! => " << lineIndex << endl;
                continue;
            }
            // WARNING: what is this???
            persons.push_back(Person(firstName, secondName, score));
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
                if (continueChanging())
                {
                    break;
                }
            }
            else if (choice == 'a')
            {
                addPerson(persons);
                if (continueChanging())
                {
                    break;
                }
            }
            else if (choice == 'r')
            {
                removePerson(persons);
                if (continueChanging())
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
            }
        }
        catch (exception error)
        {
            cout << error.what() << endl;
        }
    }

    CoutAllPersons(persons); // Output the new list
    // Write to output file
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

        for (size_t i = 0; i < persons.size(); i++)
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
    cout << "    ⊂ヽ" << endl;
    cout << "   　 ＼＼   Λ＿Λ" << endl;
    cout << "    　　 ＼( ˘ω˘ )" << endl;
    cout << "    　　　 >　⌒ヽ" << endl;
    cout << "    　　　/ 　 へ＼" << endl;
    cout << "    　　 /　　/　＼＼" << endl;
    cout << "    　　 ﾚ　ノ　　 ヽ_つ" << endl;
    cout << "    　　/　/" << endl;
    cout << "    　 /　/|" << endl;
    cout << "    　(　(ヽ" << endl;
    cout << "    　|　|、＼" << endl;
    cout << "    　| 丿 ＼ ⌒)" << endl;
    cout << "    　| |　　) /" << endl;
    cout << "     ノ )   Lﾉ" << endl;
    cout << "    (_／" << endl;
}
