//########################## HEADER FILES ###############################
// Standard headers used for input/output, vector container, and regex operations
#include <iostream>    // For input/output stream operations
#include <string>
#include <vector>      // Used for managing priorities by names and the logging system
#include <regex>       // For string validation using regular expressions
#include <limits>      // For numeric_limits
//######################### NAMESPACES ##################################
// Using directive for standard namespace to avoid std:: prefix
using namespace std;

//######################### MACROS ##################################
// Add or Remove passenger
#define ADD 1
#define REMOVE 2
//----------
// Priority Handling
#define REGULAR 1
#define BUSINESS 2
#define SPECIAL_NEEDS 3
//-----------------
// Sorted View
#define PRIORITY_SORTED 1
#define FLIGHTNUMBER_SORTED 2
#define NAME_SORTED 3
//-------------------
// Modifications
#define MODIFY_NAME 1
#define MODIFY_FLIGHTNUMBER 2
#define MODIFY_PRIORITY 3
#define EXIT 4
// Regular expression for validating strings with letters and spaces only
regex checking_strings("[a-zA-Z ]+");

//########################## NODE STRUCTURE #####################
struct passenger {
    // DATA MEMBERS:
    //==============
    string name;
    int FlightNumber;
    int Priority;
    passenger* next;


    // CONSTRUCTORS:
    //==============
    //-Default Constructor (Used in merge sorting)
    passenger(): name(""), FlightNumber(0), Priority(-1), next(nullptr){}
    //-Parameterized Constructor
    passenger(const std::string& n, int fn, int p): name(n), FlightNumber(fn), Priority(p){}
    //** const std::string& instead of string to avoid copying the argument
};

//######################## LIST CLASS ############################
class passengerList {
private:
    // DATA MEMEBERS:
    //================
    passenger* head = nullptr; // Head pointer for the linked list of passengers
    int passengers_number = 0; // Total number of passengers
    int regular_passengers_number = 0; // Count of regular priority passengers
    int business_passengers_number = 0; // Count of business priority passengers
    int specialneeds_passengers_number = 0; // Count of special needs priority passengers
    vector<string>priorityLabels = {"Regular","Business","SpecialNeeds"};
    vector<string>loggingsystem; // Stores log messages for actions taken

public:
    // METHODS:
    //==========

    void add_remove(string name, int flight_number, int priority){
        // PRE-ACTIONS
        //=============
        int choice;
        // LOGIC STARTING POINT
        //=====================
        // ** The purpose of this loop is to prevent the user from having to re-enter all the information if they make an invalid choice (e.g., selecting something other than 1 or 2 for add/delete). Note: string input validation is not handled.
        while (true){

            cout<< "Would you like to add or remove a passenger [1.Add / 2.Delete]:";
            cin >> choice;
            if(choice == ADD){
                // Creating a Node
                passenger* newpassenger = new passenger(name, flight_number, priority);
                // - Checking if the added passenger is already in the list or not before doing any action
                passenger* checker = head;
                while(checker != nullptr){
                    if(checker->name == newpassenger->name && checker->FlightNumber == newpassenger->FlightNumber && checker->Priority == newpassenger->Priority){
                        cout << ">> This passenger already exists in the queue" << endl;
                        return;
                    }
                    checker = checker->next;
                }

                // - Handling Number of Passengers
                passengers_number++;
                switch(priority){
                case REGULAR: regular_passengers_number++; break;
                case BUSINESS: business_passengers_number++; break;
                case SPECIAL_NEEDS: specialneeds_passengers_number++; break;
                }

                //CASE1: Append first when it's first passenger
                if (head == nullptr){
                    head = newpassenger;
                    newpassenger->next = nullptr;

                }//CASE2: Append somewhere in the list
                else{
                    passenger* current = head;
                    while(current->next != nullptr){
                        current = current->next;
                    }
                    current->next = newpassenger;
                    newpassenger->next = nullptr;

                }
                // - Message to confirm the Action
                cout << ">> PASSENGER ADDED SUCCESSFULLY" << endl;
                // - Handling Logging System
                loggingsystem.push_back(">>> Passenger was added");
                cout << endl;
                return;


            }else if (choice == REMOVE){
                // ** The purpose of this loop so that if the use choose something wrong the program asks them again
                while(true){
                    // - Confirmation Message for Removing Passenger
                    int Approved;
                    cout << "Are you sure you want to to delete this passenger [1.Yes / 0.No]:" ;
                    cin >> Approved;
                    if(!Approved){
                        return;
                    }else if (Approved){

                        // - Checking if passengers list is empty
                        if(head == nullptr){
                            cout << ">> Passengers' list is empty" << endl;
                            return;
                        }

                        // - Handling Number of Passengers
                        passengers_number--;
                        switch(priority){
                            case REGULAR: regular_passengers_number--; break;
                            case BUSINESS: business_passengers_number--; break;
                            case SPECIAL_NEEDS: specialneeds_passengers_number--; break;
                        }

                        passenger* current = head;
                        passenger* previous = nullptr;

                        //CASE1: Deleting first node/passenger without remove all the linked list
                        if(head->name == name && head->FlightNumber == flight_number && head->Priority == priority){
                            // New head Assignment
                            head = current->next;
                            delete current;
                            // - Message to confirm the Action
                            cout << ">> PASSENGER REMOVED SUCCESSFULLY" << endl;
                            // - Handling Logging System
                            loggingsystem.push_back(">>> Passenger was removed");
                            return;
                        }
                        //CASE2: Deleting node/passenger which is somewhere in the list
                        else{
                            while(current != nullptr){
                                if(current->name == name && current->FlightNumber == flight_number && current->Priority == priority){
                                    previous->next = current->next;
                                    delete current;
                                    // - Message to confirm the Action
                                    cout << ">> PASSENGER REMOVED SUCCESSFULLY" << endl;
                                    // - Handling Logging System
                                    loggingsystem.push_back(">>> Passenger was removed");
                                    return;
                                }

                            previous = current;
                            current = current->next ;
                            }

                            cout << ">> Passenger is Not in Queue" << endl;
                            return;
                        }

                    }else{
                        cout << "Invalid option. choose from 0 / 1" << endl;
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }//############################## End of Approvement of Removing #####################################
                } //############################### End of Insurance Loop in Remove Case ##################################
            }else{
                cout << "Invalid input. choose from 1 / 2 " << endl; //add or delete
                cin.clear();
                cin.ignore(1000, '\n');
            }//######################## End of else (Third case beside add and remove) ####################################
        } //######################### End of Whole Logic Infinite Loop ####################################################
    } // ############################## End of ADD/REMOVE METHOD ##########################################################

//-------------------------------------------------------------------------------------------------

    void sorted_view (){
        int choice;
        // - Handling Wrong Input
        while(true){
            cout << "What would you like to queue sorted by[1.priority / 2.Flight number / 3.Name]:";
            if (!(cin >> choice) || choice > 3 || choice < 1){
                cout << "Invalid option. (choose from 1 / 2 / 3)" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }else
                break;
        }
        // LOGIC STARTING POINT
        //=====================
        if(choice == PRIORITY_SORTED){

            // INSERTION SORTING
            passenger* sortedHead = nullptr; // New head for sorted list (High priority)
            passenger* currentSelectedNode = head; // Current node we're on in the unsorted list

            while (currentSelectedNode != nullptr){
                passenger* nextUnsorted = currentSelectedNode->next; // Save next node so  when changing currentSelectedNode->next we don't lose the rest of unsorted list

                // CASE1: if the sortedHead is still null (Sorted list is empty) or Appending first (CurrentSelectedNode has higher priority than the head)
                //Ex on Appending on empty sorted list: unsorted list: 5 -> 6 ->.... , sorted list: null . That means new sorted list will be 5 -> null
                //EX on Appending first: unsorted list: 5 -> 6 -> ...... , sorted list: 3 -> null . That means the new sorted list will be 5 -> 3 -> null, so here we did 2 things we make 5->next is 3(sortedHead) and make 5 the new sortedHead
                if (sortedHead == nullptr || currentSelectedNode->Priority > sortedHead->Priority){
                    // To put the selected node (first node in the unsorted list) in the correct position in the sorted list, making it before sortedHead (Highest Priority in the sorted list)
                    currentSelectedNode->next = sortedHead;
                    // To assign new sortedHead (Highest priority) to have the greatest priority
                    sortedHead = currentSelectedNode;
                }else {
                    // CASE2: if Inserting in between two nodes or Append last
                    //EX on Appending last (first condition): unsorted list: 3 -> ..... , sorted list: 6 -> 5 -> 4 -> null . new sorted list: 6 -> 5 -> 4 -> 3 -> null , by making 3 (current) ->next = null and
                    //                                                                                                                                                    (2)  (1)
                    //Ex on inserting in between nodes (second condition): unsorted list: 4 -> 8 -> ..... , sorted list: 6 -> 5 -> 3 -> 2-> null . New sorted list: 6 -> 5 -> 4 -> 3 -> 2 -> null by 2 Actions:
                    //(1) making 4 -> next = 5 -> next , To put the currentSelectedNode in the correct position
                    //(2) making 5 -> next = 4 , To connect the sorted list again
                    passenger* sortedWalker = sortedHead;
                    // "insertion"
                    while (sortedWalker->next != nullptr && sortedWalker->next->Priority >= currentSelectedNode->Priority){
                        sortedWalker = sortedWalker->next;
                    }
                    currentSelectedNode->next = sortedWalker->next;
                    sortedWalker->next = currentSelectedNode;
                }

                currentSelectedNode = nextUnsorted;
            }
            head = sortedHead; // Update head to new sorted list
            // - Handling Logging System
            loggingsystem.push_back(">>> Queue viewed Sorted by Name");

        }else if (choice == FLIGHTNUMBER_SORTED){
            // SELECTION SORTING
            passenger* currentSelectedNode = head;

            while(currentSelectedNode != nullptr){
                //
                passenger* MinF_N = currentSelectedNode;
                passenger* minimumFN_picker = currentSelectedNode->next;

                while(minimumFN_picker != nullptr){
                    if(minimumFN_picker->FlightNumber < MinF_N->FlightNumber){ //all three sorting are the same just the if condition that does difference
                        // To assign new value for MinF_N if it's found that there's smaller number in the rest of the list
                        MinF_N = minimumFN_picker;
                    }

                    minimumFN_picker = minimumFN_picker->next;
               }
               // ** After this loop we have 3 things: 1. minimumFN_picker = nullptr, 2. MiniF_N has is a node that has the lowest priority which might be currentSelectedNode or got assigned by minimumFN_picker
               // - Swapping the data between the MinF_N and currentSelectedNode if they're not the same
               if(MinF_N != currentSelectedNode){
                    swap(currentSelectedNode->Priority, MinF_N->Priority);
                    swap(currentSelectedNode->FlightNumber, MinF_N->FlightNumber);
                    swap(currentSelectedNode->name, MinF_N->name);

                    // Swapping Manually:
                    /*
                    int temp_p = currentSelectedNode->Priority;
                    int temp_F_N = currentSelectedNode->FlightNumber;
                    string temp_N = currentSelectedNode->name;

                    currentSelectedNode->Priority = MinF_N->Priority;
                    currentSelectedNode->FlightNumber = MinF_N->FlightNumber;
                    currentSelectedNode->name = MinF_N->name;

                    MinF_N->Priority = temp_p;
                    MinF_N->FlightNumber = temp_F_N;
                    MinF_N->name = temp_N;
                    */
               }

               currentSelectedNode = currentSelectedNode->next;
            }
            // - Handling Logging System
            loggingsystem.push_back(">>> Queue viewed Sorted by Flight Number");

        }else if (choice == NAME_SORTED){
            if (head != nullptr && head->next != nullptr) {
                // Merge helper function
                auto merge = [](passenger* left, passenger* right) -> passenger* {
                passenger dummy;  // Uses default constructor
                passenger* tail = &dummy;

                while (left && right) {
                    if (left->name < right->name) {
                        tail->next = left;
                        left = left->next;
                    }else{
                        tail->next = right;
                        right = right->next;
                    }
                    tail = tail->next;
                }

                tail->next = left ? left : right;
                return dummy.next;
                };

            // Recursive sort
            std::function<passenger*(passenger*)> sort = [&](passenger* node) -> passenger* {
                if (!node || !node->next) return node;

                passenger* slow = node;
                passenger* fast = node->next;

                while (fast && fast->next) {
                    slow = slow->next;
                    fast = fast->next->next;
                }
                //** After this loop there are 2 possibilities:
                //(1) fast is pointing on null as number of nodes is odd and slow is pointing exactly at the exact mid of the list
                //(2) fast is pointing on the last node as number of nodes is even and slow is pointing at the node its number is number of elements/2
                passenger* right = slow->next;
                slow->next = nullptr;

                return merge(sort(node), sort(right));
            };

            // Sort and update head
            head = sort(head);
            }
            // - Handling Logging System
            loggingsystem.push_back(">>> Queue viewed Sorted by Name");
        }

        // - Handling Displaying Data after Sorting
        cout << endl;
        passenger* current = head;
        if(head==nullptr){
            cout << "Passenger's list is empty" << endl;
            return;
        }
        cout << "Passengers's List" << endl;
        cout << "=================" << endl;
        while (current != nullptr){
            cout << ">> Passenger's name: " << current->name << endl;
            cout << "     Flight Number: " << current->FlightNumber << endl;
            cout << "     Their priority: " << priorityLabels[current->Priority - 1] << endl;
            cout << "---------------------------------------"<< endl;
            current = current->next;
        }

    }

//----------------------------------------------------------------------------------------------------


    void searchingByname (string N){
        passenger* selector = head;
        bool isPassengerFound = false;
        //** Adds Space so that the line "passengers with name" is clear to be seen
        cout << endl;
        cout << "Passengers with name "<< N <<":" << endl;
        while(selector != nullptr){
            if(selector->name == N){
                cout << "Flight number: " << selector->FlightNumber << endl;
                cout << "Priority: " << priorityLabels[selector->Priority - 1] << endl;
                cout << "-----------------------------------" << endl;
                isPassengerFound = true;
            }
            selector = selector ->next;
        }
        // - Handling Logging System
        loggingsystem.push_back(">>> Search by name");

        if(isPassengerFound){
            return;
        }else{
            cout << "There's no passenger with the name" << N <<endl;
        }
    }

    void searchingByflightnumber(int F_N){

        passenger* current = head;

        bool passengers_found = false;

        cout << endl;
        cout << "Passengers with flight number " << F_N << ":" << endl;
        while(current != nullptr){
            if(current->FlightNumber == F_N){
                cout << "Name: " << current->name << endl;
                cout << "Priority: " << priorityLabels[current->Priority - 1] << endl;
                cout << "-----------------------------------" << endl;
                passengers_found = true;
            }
            current = current->next;
        }
        // - Handling Logging System
        loggingsystem.push_back(">>> Search by flight number");

        if(passengers_found){
            return;
        }else{
            cout << "There's no passenger with the flight number" << F_N <<endl;
        }

    }

    void searchingBypriority(int P){
        passenger* current = head;

        bool passengers_found = false;

        cout << endl;
        cout << "Passengers with priority " << priorityLabels[P - 1] << ":" << endl;
        while(current != nullptr){
            if(current->Priority == P){
                cout << "Name: " << current->name << endl;
                cout << "Flight number: " << current->FlightNumber << endl;
                cout << "-----------------------------------" << endl;
                passengers_found = true;
            }
            current = current->next;
        }
        // - Handling Logging System
        loggingsystem.push_back(">>> Search by priority");

        if(passengers_found){
            return;
        }else{
             cout << "There's no passenger with the priority" << priorityLabels[P - 1] <<endl;
        }

    }

    void search_position(string N , int F_N, int P){
        cout << endl;
        int position = 1;
        passenger* current = head;
        while(current != nullptr){
            if(current->name == N && current->FlightNumber == F_N && current->Priority == P){
                cout << "Passenger's position is " << position << " in the queue" << endl;
                cout << endl;
                return;
            }
            position++;
            current = current->next;
        }
        cout << "Passenger " << N << " with flight number:" << F_N << " ,and priority:" << priorityLabels[P-1] << " is not in the queue" << endl;
        cout << endl;

        // - Handling Logging System
        loggingsystem.push_back(">>> Search for position");
    }

//-------------------------------------------------------------------------------------------------------

    void statistics(){
        cout << endl;
        if (head == nullptr){
            cout << "Passengers' list is empty" << endl;
            cout << endl;
            return;
        }
        int sum = 0; //sum initialized as zero
        cout << "Total number of passengers: "<< passengers_number << endl;
        cout << "Passengers with regular priority: " << regular_passengers_number<< endl;
        cout << "Passengers with business priority: " << business_passengers_number<< endl;
        cout << "Passengers with special needs priority: " << specialneeds_passengers_number<< endl;

        for(int i = 1; i<= passengers_number;i++){
            sum+=i;
        }
        float average_waiting_time = static_cast<double>(sum) / passengers_number; //if you did sum/passengers_number directly will make the output always an integer
        cout << "Passengers average waiting number: " << average_waiting_time << endl;
        cout<< endl;

        // - Handling Logging System
        loggingsystem.push_back(">>> Queue statistics viewed");
    }

//-----------------------------------------------------------------------------------------------------------

    void modify_passengers(string old_N, int old_F_N, int old_P){

        if (head == nullptr) {
            cout << "Passengers' list is empty" << endl;
        }else{
            passenger* current = head;
            while (current != nullptr) {
                if (current->name == old_N && current->FlightNumber == old_F_N && current->Priority == old_P) {
                cout << ">> Passenger was found." << endl;
                break;
                }
                current = current->next; // Fixed: Missing increment in original
            }

            if (current == nullptr) {
                cout << "Passenger wasn't found" << endl;
                return;
            }

            // - validation for choose
            int choice;
            bool keepModifying = true;

            // Main modification loop
            while (keepModifying) {
                // - Input Validation
                while (true) {
                    cout << "What would you like to modify [1.Name / 2.Flight Number / 3.Priority] / 4.Exit:";
                    if (!(cin >> choice) || (choice < 1 || choice > 4)) {
                        cout << "Invalid option. choose between 1 / 2 / 3 / 4" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }else {
                        break;
                    }
                }
                cin.ignore(1000, '\n');

                if (choice == MODIFY_NAME) {
                    string new_name;

                    // - Input Validation
                    while (true) {
                        cout << "Enter new name:";
                        getline(cin, new_name);
                        if (new_name.empty() || !regex_match(new_name, checking_strings)) {
                            cout << "Invalid input name. [passenger's name can't contain any numbers or be empty]" << endl;
                        } else {
                            break;
                        }
                    }
                    // - Name Changing
                    current->name = new_name;

                    // - Handling Logging System
                    loggingsystem.push_back(">>> Name was modified");

                }else if (choice == MODIFY_FLIGHTNUMBER) {
                    int new_flight_num;

                    while (true) {
                        cout << "Enter new flight Number:";
                        if (!(cin >> new_flight_num) || new_flight_num <= 0) {
                            cout << "Invalid input. Flight number must a positive number" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }else {
                            break;
                        }
                    }
                    // - Flight Number Changing
                    current->FlightNumber = new_flight_num;

                    // - Handling Logging System
                    loggingsystem.push_back(">>> Flight number was modified");

                }else if (choice == MODIFY_PRIORITY) {
                    int new_priority;
                    bool validPriority = false;

                    // - Input Validation (replaces `priority_handling5` goto)
                    while (!validPriority) {
                        while (true) {
                            cout << "Enter new priority [1-Regular / 2-Business / 3-Special needs]:";
                            if (!(cin >> new_priority)) {
                                cout << "Invalid input. (priority must a number)" << endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }else {
                                break;
                            }
                        }
                        // - Input Validation
                        if (new_priority < 1 || new_priority > 3) {
                            cout << "Invalid option. Priority should be [1, 2, 3]" << endl;
                        }else {
                            validPriority = true;
                        }
                    }

                    // - Priority Changing
                    current->Priority = new_priority;

                    // Define passenger counts in an array (index 0 unused for clarity)
                    int passenger_counts[4] = {0, regular_passengers_number, business_passengers_number, specialneeds_passengers_number};

                    // Decrement old priority count
                    passenger_counts[old_P]--;

                    // Increment new priority count
                    passenger_counts[new_priority]++;

                    // Update the original variables
                    regular_passengers_number = passenger_counts[REGULAR];
                    business_passengers_number = passenger_counts[BUSINESS];
                    specialneeds_passengers_number = passenger_counts[SPECIAL_NEEDS];

                    // - Handling Logging System
                    loggingsystem.push_back(">>> Priority was modified");

                    }else if (choice == EXIT) {
                        cout << ">>> MODIFICATION DONE SUCCESSFULLY" << endl;
                        keepModifying = false; // Exit loop
                    }
            }
        }
}

//---------------------------------------------------------------------------------------------------------------
    void logging_system(){
        cout << endl;
        cout << "Logging System:" << endl;
        for(int i = 0; i < loggingsystem.size(); i++){
            cout << loggingsystem[i] << endl;
        }
        cout << endl;
    }

};

//################################################ END OF PASSENGERS CLASS #####################################################
int main()
{
    int choice;
    passengerList passenger;
    string passenger_N;
    int passenger_F_N;
    int passenger_P;
    cout << "\n========== Passenger Queue System ==========\n";
    do {

        cout << "=== Menu ===:" << endl;
        cout << "1.Add or Remove passenger" << endl;
        cout << "2.View the queue" << endl;
        cout << "3.Search for passenger" << endl;
        cout << "4.View queue statistics" << endl;
        cout << "5.Modify passenger's data" << endl;
        cout << "6.Logging system" << endl;
        cout << "7.Exit" << endl;
        cout << "============================\n";
        cout << ">>> Enter Desired Action [1-7]:" ;

        if(!(cin>>choice)){
            cin.clear();
            cin.ignore(1000, '\n'); //used to fix the problem of if the user did input a string so it ignore 1000 character if the user inputed wrong input (string) and the backslash at the end.
        }else{
            cin.ignore(); //that one fixes the problem of getline when i use it as an input way for passenger's name because when i used it the code skips the passenger's name and goes directly for their flight number
        }

        switch(choice){
        case 1:
            {
            //1- passenger's name validation if it's a number not a string
            while(true){
                cout << "Enter passenger's name:";
                getline(cin, passenger_N);
                if(!regex_match(passenger_N, checking_strings)){
                    cout << "Invalid input name. (passenger's name shouldn't contain any numbers)" << endl;
                }else
                break;
            }
            //2- passenger's flight number validation if it's a string or negative number instead of positive number
            while(true){
                cout << "Their Flight Number:";
                if(!(cin >> passenger_F_N) || passenger_F_N <= 0){
                cout << "Invalid input. (flight number must a positive number)" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }else
                break;
            }
            //3- passenger's priority validation for first if it's a string and if the number is valid or not
            priority_handling:
            while(true){
                cout << "Their priority [1-Regular / 2-Business / 3-Special needs]:";
                if(!(cin >> passenger_P)){
                cout << "Invalid input. (priority  must a number)" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }else
                break;
            }
                if (passenger_P < 1 || passenger_P > 3){
                    cout << "Invalid option. (choose from 1 , 2 , 3)" << endl;
                    goto priority_handling;
                }




            passenger.add_remove( passenger_N, passenger_F_N,passenger_P);
            break;
            }
            //####################################### END OF CASE 1 ###########################################
        case 2:
            cout << endl;
            passenger.sorted_view();
            break;
            //####################################### END OF CASE 2 ###########################################
        case 3:
            int search_choice;
            //validation for choice
            while(true){
               cout << "What do you want the search to be based on [1.Name / 2.Flight number / 3.Priority] / 4.Locate specific passenger:";
                //if the input is string the !cin will stop it, the only thing that the if condition is true is if the inputs is in correct range
                if(!(cin >> search_choice) || (search_choice < 1 || search_choice > 4)){
                    cout << "Invalid option. choose between 1 / 2 / 3 / 4" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }else {
                    break;
                }
            }

            if(search_choice == 1){

                while(true){
                cout << "Enter passenger's name:";
                cin.ignore();
                getline(cin, passenger_N);
                if(!regex_match(passenger_N, checking_strings)){
                    cout << "Invalid input name. (passenger's name shouldn't contain any numbers)" << endl;
                }else
                    break;
                }
                passenger.searchingByname(passenger_N);
            }
            else if(search_choice == 2){
                while(true){
                    cout << "Their Flight Number:";
                    if(!(cin >> passenger_F_N) || passenger_F_N < 0){
                        cout << "Invalid input. (flight number must a number)" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }else
                        break;
                    }
                passenger.searchingByflightnumber(passenger_F_N);
            }
            else if (search_choice == 3){
                priority_handling3:
                while(true){
                    cout << "Their priority [1-Regular / 2-Business / 3-Special needs]:";
                    if(!(cin >> passenger_P)){
                    cout << "Invalid input. (priority  must a number)" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }else
                    break;
                }
                if (passenger_P < 1 || passenger_P > 3){
                    cout << "Invalid option. (choose from 1 , 2 , 3)" << endl;
                    goto priority_handling3;
                }

                passenger.searchingBypriority(passenger_P);

            }else {

                 while(true){
                    cout << "Enter passenger's name:";
                    cin.ignore();
                    getline(cin, passenger_N);
                    if(!regex_match(passenger_N, checking_strings)){
                    cout << "Invalid input name. (passenger's name shouldn't contain any numbers)" << endl;
                    }else
                        break;
                }

                 while(true){
                    cout << "Their Flight Number:";
                    if(!(cin >> passenger_F_N) || passenger_F_N < 0){
                        cout << "Invalid input. (flight number must a number)" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }else
                        break;
                    }

                 priority_handling2:
                while(true){
                    cout << "Their priority [1-Regular / 2-Business / 3-Special needs]:";
                    if(!(cin >> passenger_P)){
                    cout << "Invalid input. (priority  must a number)" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }else
                    break;
                }
                if (passenger_P < 1 || passenger_P > 3){
                    cout << "Invalid option. (choose from 1 , 2 , 3)" << endl;
                    goto priority_handling2;
                }

                 passenger.search_position(passenger_N, passenger_F_N, passenger_P);

            }

            break;
            //####################################### END OF CASE 3 ###########################################
        case 4:
            passenger.statistics();
            break;
            //####################################### END OF CASE 4 ###########################################
        case 5:
            //in here we remove the cin.ignore that the function that modifies works
            cout << "Enter original info of the passenger:" << endl;
            while(true){
                cout << "Enter passenger's name:";
                getline(cin, passenger_N);
                if(!regex_match(passenger_N, checking_strings)){
                    cout << "Invalid input name. (passenger's name shouldn't contain any numbers)" << endl;
                }else
                    break;
            }

            while(true){
                    cout << "Enter their Flight Number:";
                    if(!(cin >> passenger_F_N) || passenger_F_N < 0){
                        cout << "Invalid input. (flight number must a number)" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }else
                        break;
            }

            priority_handling4:
                while(true){
                    cout << "Their priority [1-Regular / 2-Business / 3-Special needs]:";
                    if(!(cin >> passenger_P)){
                    cout << "Invalid input. (priority  must a number)" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }else
                    break;
                }
                if (passenger_P < 1 || passenger_P > 3){
                    cout << "Invalid option. Priority should be [1, 2, 3]" << endl;
                    goto priority_handling4;
                }


            passenger.modify_passengers(passenger_N, passenger_F_N, passenger_P);

            break;
            //####################################### END OF CASE 5 ###########################################
        case 6:
            passenger.logging_system();
            break;
            //####################################### END OF CASE 6 ###########################################
        case 7:
            cout << "Exiting..." << endl;
            break;
            //####################################### END OF CASE 7 ###########################################
        default:
            cout << "Invalid option. Choose between 1/2/3/4/5/6/7 ." << endl;
            break;
        }
    } while(choice != 7);
    return 0;
}

