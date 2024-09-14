#include <iostream>
using namespace std;

class ToDoList
{
    private:
        struct ToDo
        {
            char data[100]; //to store the data of the task
            ToDo *link; //a pointer to the next task
            int count; //to represent the order of a task in the list
        };

        ToDo *start; //pointer to the first task in the linked list

    public:
        ToDoList()
        {
            start = nullptr; //initializes 'start' pointer to 'nullptr', indicating initially To-Do List was empty.
        }

        void welcomeUser();
        void fixCount(); //to adjust the task counts for all tasks in the list
        void displayTasks();
        void addTasks();
        void deleteTasks();
        void updateTasks();
        ~ToDoList();
};

void ToDoList::welcomeUser()
{
    system("color 3F"); //sets the text to bright white(3) on a blue background(F)  of the console window

    cout << "\n\n\n\n\n";
    cout << "\t------------------------------------------------------------------------------------------------------\n\n";
    cout << "\t###########################################  TO-DO LIST APP  #########################################\n\n";
    cout << "\t------------------------------------------------------------------------------------------------------";
    cout << "\n\n\n\t\t\t******************************* WELCOME! *******************************\n\n\n\t\t\t\t\t\t";

    system("pause"); //pauses the execution of the program until the user presses a key
}

void ToDoList::fixCount()
{
    ToDo *temp = start;

    int i = 1; //initialize a counter variable 'i' to 1

    while (temp != nullptr)
    {
        temp->count = i;
        i++;
        temp = temp->link;
    }
}

void ToDoList::displayTasks()
{
    system("cls");

    cout << "\t###########################################  YOUT TO-DO LIST  #########################################\n\n\n\n";

    ToDo *temp = start;

    /* Check if the list is empty or not */
    if (start == nullptr)
    {
        cout << "Your list is empty!\n\n\n";
        system("pause");
        return;
    }
    else
    {
        while (temp != nullptr)
        {
            cout << temp->count << ") " << temp->data << endl; //prints the count and data of the current task
            temp = temp->link;
        }
        cout << "\n\n";

        system("pause");
    }
}

void ToDoList::addTasks()
{
    system("cls");

    cout << "\t############################################  ADD NEW TASKS  ##########################################\n\n\n\n";

    char k; //to store the user's input

    do
    {
        /* user confirmation to ADD?(y/n) */
        do
        {
            cout << "\nADD? (y/n): ";
            cin >> k;

            /* Check if the user's input is valid or not */
            if (cin.fail() || cin.peek() != '\n' || (k != 'y' && k != 'Y' && k != 'n' && k != 'N'))
            {
                cout << "Invalid input! Please enter 'y' or 'n'.\n";
                cin.clear();
                while (cin.get() != '\n'); //continues to read characters until it reaches a newline
            }
            else
            {
                break;
            }
        } while (true);


        if (k == 'n' || k == 'N')
        {
            break;
        }
        else
        {
            ToDo *newToDo = new ToDo; //dynamically allocates memory for a new 'ToDo'

            cout << "Add a new task: ";
            while (cin.get() != '\n');
            cin.getline(newToDo->data, sizeof(newToDo->data)); //read a line of text(up to the size of data array) from the user and stores it in 'data' member of the newly created ToDo structure
            newToDo->count = (start == nullptr) ? 1 : start->count + 1; //sets the count of the new task. If the list is empty(start == nullptr), the count is set to 1. Otherwise, it is set to one more than the current count of the last task in the list.
            newToDo->link = nullptr;

            /* Insert new ToDo node into the linked list */
            if (start == nullptr) //linked list is empty
            {
                start = newToDo;
            }
            else
            {
                ToDo *temp = start;

                while (temp->link != nullptr)
                {
                    temp = temp->link;
                }
                temp->link = newToDo;
            }

            fixCount();

            cout << "New task added successfully!\n";
        }

    }while (true);
}

void ToDoList::deleteTasks()
{
    system("cls");

    cout << "\t###########################################  DELETE TASKS  #########################################\n\n\n\n";

    char response; //to store the user's response

    do
    {
        ToDo *temp = start;

        /* Check if the list is empty or not */
        if (start == nullptr)
        {
            cout << "Your list is empty!\n\n\n";
            system("pause");
            return;
        }
        else
        {
            /* Display the current tasks in the to-do list, along with their corresponding numbers */
            while (temp != nullptr)
            {
                cout << temp->count << ". " << temp->data << endl;
                temp = temp->link;
            }
        }

        /* user's response for Delete?(y/n) */
        do
        {
            cout << "\nDelete? (y/n): ";
            cin >> response;

            /* Check if the user's input is valid or not */
            if (cin.fail() || cin.peek() != '\n' || (response != 'y' && response != 'Y' && response != 'n' && response != 'N'))
            {
                cout << "Invalid input! Please enter 'y' or 'n'.\n";
                cin.clear();
                while (cin.get() != '\n');
            }
            else
            {
                break;
            }
        } while (true);


        if (response == 'n' || response == 'N')
        {
            break;
        }
        else
        {
            int taskNumber; //to store the user's input for the task number

            do
            {
                cout << "\nEnter the number of the task you want to delete: ";
                cin >> taskNumber;

                if (cin.fail() || cin.peek() != '\n')
                {
                    cout << "Invalid input! Please enter a valid number.\n";
                    cin.clear();
                    while (cin.get() != '\n');
                }
                else
                {
                    ToDo *current = start;
                    ToDo *previous = nullptr;

                    /* Loop through the list until the end is reached or until the task with the specified number is found. */
                    while (current != nullptr && current->count != taskNumber)
                    {
                        previous = current;
                        current = current->link;
                    }

                    /*  Checks if the task with the specified number was found or not */
                    if (current == nullptr)
                    {
                        cout << "Task with specified number not found.\n";
                    }
                    else
                    {
                        if (previous == nullptr) //task is the first in the list
                        {
                            start = current->link;
                        }
                        else
                        {
                            previous->link = current->link;
                        }

                        delete current; //free the memory occupied by the deleted node
                        cout << "Task deleted successfully!\n";

                        fixCount();

                        break;
                    }
                }
            } while (true);
        }
    } while (true);
}

void ToDoList::updateTasks()
{
    system("cls");

    cout << "\t#########################################  UPDATE A TO-DO LIST  #######################################\n\n\n\n";

    char response;

    do
    {
        ToDo *temp = start;

        if (start == nullptr)
        {
            cout << "Your list is empty!\n\n\n";
            system("pause");
            return;
        }
        else
        {
            while (temp != nullptr)
            {
                cout << temp->count << ". ";
                cout << temp->data << endl;
                temp = temp->link;
            }
        }

        do
        {
            cout << "\nEdit? (y/n): ";
            cin >> response;

            if (cin.fail() || cin.peek() != '\n' || (response != 'y' && response != 'Y' && response != 'n' && response != 'N'))
            {
                cout << "Invalid input! Please enter 'y' or 'n'.\n";
                cin.clear();
                while (cin.get() != '\n');
            }
            else
            {
                break;
            }
        } while (true);

        if (response == 'n' || response == 'N')
        {
            break;
        }

        int u;
        ToDo *temp2 = nullptr;
        bool validInput;

        do
        {
            cout << "\nEnter the number of the task you want to edit: ";
            cin >> u;

            if (cin.fail() || cin.peek() != '\n')
            {
                cout << "Invalid input! Please enter a valid number.\n";
                cin.clear();
                while (cin.get() != '\n');
                validInput = false;
            }
            else
            {
                validInput = true;

                temp2 = start;
                while (temp2 != nullptr)
                {
                    //Find the task with the specified number
                    if (temp2->count == u)
                    {
                        cout << "Edit: ";
                        while (cin.get() != '\n');
                        cin.getline(temp2->data, sizeof(temp2->data));
                        cout << "Your task updated successfully!\n";
                        break;
                    }
                    else
                    {
                        temp2 = temp2->link;
                    }
                }

                if (temp2 == nullptr)
                {
                    cout << "Invalid input! To-Do item with specified number not found.\n";
                }
            }
        } while (!validInput || temp2 == nullptr);

    } while (true);
}

ToDoList::~ToDoList()
{
    ToDo *temp;

    while (start != nullptr)
    {
        temp = start;
        start = start->link;
        delete temp;
    }
}

int main()
{
    ToDoList toDoList;

    toDoList.welcomeUser();

    while(true)
    {
        system("color 3F");

        system("cls"); //clears the console screen

        cout << "\t------------------------------------------------------------------------------------------------------\n";
        cout << "\t##############################################  DASHBOARD  ###########################################\n";
        cout << "\t------------------------------------------------------------------------------------------------------\n\n\n\n";

        /* Display menu items for the user to choose actions */
        cout << "\t\t\t\t\t\t1. Display Tasks\n\n";
        cout << "\t\t\t\t\t\t2. Add Tasks\n\n";
        cout << "\t\t\t\t\t\t3. Delete Tasks\n\n";
        cout << "\t\t\t\t\t\t4. Edit Tasks\n\n";
        cout << "\t\t\t\t\t\t5. Exit\n\n\n\n";


        int choice; //to store the user's choice from the menu
        cout << "\t\t\t\t\t\tEnter your choice: ";
        cin >> choice; //'cin' read the user's input from the console and store it in the variable 'choice'

        /* Check the input validation after reading user's choice from the console */
        if (cin.fail() || choice<1 || choice>5)
        {
            cin.clear(); //clears the error state of the input stream 'cin'
            while (cin.get() != '\n'); //Clears the remaining characters from the input buffer up to the newline character ('\n')
        }

        switch (choice)
        {
            case 1:
                toDoList.displayTasks();
                break;
            case 2:
                toDoList.addTasks();
                break;
            case 3:
                toDoList.deleteTasks();
                break;
            case 4:
                toDoList.updateTasks();
                break;
            case 5:
                return 0;
        }
    }
}
