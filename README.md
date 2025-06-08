```markdown
# Airport Security Check Queue Management System

![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg) ![OOP](https://img.shields.io/badge/Object%20Oriented-Yes-green.svg) ![License](https://img.shields.io/badge/License-MIT-orange.svg)

## 📝 Project Description
A C++ queue management system for airport security that prioritizes passengers (Regular=1/Business=2/Special Needs=3) using linked lists. Features include:
- Add/remove passengers with validation
- Sort by priority/flight#/name
- Search by name/flight#/priority/position
- Real-time statistics (counts, average wait)
- Full passenger data modification
- Activity logging

## 🚀 Features
**Core Operations:**
- Priority handling with automatic counters
- Input validation for all entries
- Linked list memory management

**Sorting Algorithms:**
```cpp
// Insertion Sort (Priority)
if (sortedHead == nullptr || currentSelectedNode->Priority > sortedHead->Priority) {
    currentSelectedNode->next = sortedHead;
    sortedHead = currentSelectedNode;
}

// Selection Sort (Flight#)
if(minimumFN_picker->FlightNumber < MinF_N->FlightNumber) {
    MinF_N = minimumFN_picker;
}

// Merge Sort (Names)
auto merge = [](passenger* left, passenger* right) -> passenger* {
    passenger dummy;
    passenger* tail = &dummy;
    while (left && right) {
        if (left->name < right->name) {
            tail->next = left;
            left = left->next;
        } else {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }
    tail->next = left ? left : right;
    return dummy.next;
};
```

**Search System:**
- Name (regex validated)
- Flight number (numeric)
- Priority level (1-3)
- Queue position

**Statistics:**
- Priority distribution counts
- Average waiting position:
```cpp
float average_waiting_time = static_cast<double>(sum) / passengers_number;
```

**Modification:**
- Name (alphabetic only)
- Flight# (positive integers)
- Priority (with counter updates)

## 🛠️ Technical Implementation
**Validation:**
```cpp
// Name validation
regex checking_strings("[a-zA-Z ]+");
while(true) {
    getline(cin, passenger_N);
    if(!regex_match(passenger_N, checking_strings)) {
        cout << "Invalid name!" << endl;
    } else break;
}

// Numeric validation
while(true) {
    if(!(cin >> input) || input <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else break;
}
```

**Structure:**
```
CLASS: passengerList
├── head: passenger*
├── counters (regular/business/special)
├── loggingsystem: vector<string>
│
└── METHODS:
    ├── add_remove()
    ├── sorted_view()
    ├── search_*()
    ├── statistics()
    ├── modify_passenger()
    └── logging_system()

STRUCT: passenger
├── name: string
├── FlightNumber: int  
├── Priority: int
└── next: passenger*
```

## 🔧 Usage
1. Compile: `g++ -std=c++17 main.cpp -o AirportQueue`
2. Run: `./AirportQueue`
3. Menu Options:
   - 1: Add/Remove passenger
   - 2: View sorted queue
   - 3: Search passengers
   - 4: View statistics
   - 5: Modify passenger
   - 6: View logs
   - 7: Exit



