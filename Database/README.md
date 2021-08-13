<body style="background-color:black;">

# CRUD Database 

> A C ++ program that implements work with a simple **database** (abbreviated as "DB"). 
> The program will communicate with the user via **standard input and output** (stdin and stdout streams).
>
> We will store pairs of the following type in our database: **date, event**.  Let's define the date as a string of the *Year-Month-Day* type, where Year, Month and Day are integers.
>
> The event is defined as a string of arbitrary printable characters without delimiters inside (spaces, tabs, etc.). 
 The event cannot be an empty string. Many different events can occur on the same date, the database must be able to save them all. 
 It is **not necessary** to save identical events that occurred on the same day: it is enough to save only one of them. 

 > Our database must understand **certain commands** in order to interact with it: 
 - **Adding an event: Add Date Event**
 - **Delete event: Del Date Event**
 - **Deleting all events for a specific date: Del Date**
 - **Search for events for a specific date: Find Date**
 - **Print all events for all dates: Print**

> All commands, dates and events are separated by spaces as you type. Commands are read from standard input. There can be exactly one command on one line, but you can enter multiple commands on multiple lines. Blank lines can also come in - ignore them and continue processing new commands on subsequent lines.

> ## Adding an event (Add Date Event)
> When adding an event, the database must remember it and then show it when searching (using the Find command) or printing (using the Print command). If the specified event already exists for the given date, re-adding it should be ignored. If the input is correct (see the section ***"Handling Input Errors"***), the program should not display anything on the screen.
> 
```cpp
void Database::AddEvent(const Date &date, const string &event) {
    database[date].insert(event);
}
```

> ## Deleting an event (Del Date Event)
> The command must **remove the previously added event with the specified name on the specified date, if it exists**. If the event is found and deleted, the program should print the string ***"Deleted successfully"*** (without quotes). If the event is not found on the specified date, the program should display the string ***"Event not found"*** (without quotes).

```cpp
bool Database::DeleteEvent(const Date &date, const string &event) {
        auto it = database.find(date);
        if(it != database.end() 
        && it->second.count(event)) {
            it->second.erase(event);
            return true;
        } return false;
    } 
} 
```

> ## Deleting multiple events (Del Date)
> The command removes all previously added events for the specified date. The program should always output a string like ***"Deleted N events"***, where **N** is the **number of all found and deleted events**. N can be zero if there were no events on the specified date.

```cpp 
unsigned long Database::DeleteDate(const Date &date) {
    unsigned long size_out = 0;
    if(database.count(date)) {
        size_out = database[date].size();
        database.erase(date);
    }
    return size_out;
}
```

> ## Event Searching (Find Date)
> Find and print previously added events on a specified date. The program should only print the events themselves, one per line. Events must be sorted in ascending order (in the order of comparing strings with each other).

```cpp
set<string> Database::Find(const Date &date) const {
    set<string> temp;
    if(database.count(date)) {
        temp = database.at(date);
    }
    return temp;
}
```

> ## Printing all events (Print)
> Using this command, we can show the complete content of our database. The program should print all Date Event pairs, one per line. All pairs must be sorted by date, and events within the same date must be sorted in ascending order. Dates must be formatted in a special way: YYYY-MM-DD, where Y, M, D are the year, month and day, respectively. If a number has fewer digits, then it must be padded with zeros, for example, 0001-01-01 - January 1st of the first year.

```cpp
void Database::Print() const {
    for(const auto &item : database) {
        for(const auto &event : item.second) {
            cout << item.first << " " << event << endl;
        }
    }
}
```

> ## Handling Input Errors
> The input **is not always correct**: the program must handle some input errors correctly.
>
> If the user entered an unknown command, then the program should report this by displaying the line ***"Unknown command: COMMAND"***, where **COMMAND** is the **command entered by the user**. The command is the first word in the line (up to a space).

```cpp
default: { // Everything other than the commands included in our database
cout << "Unknown command: " << userDemand << endl;
            }
```

> If the date does not correspond to the **Year-Month-Day** format, where **Year, Month and Day are arbitrary integers**, then the program should print ***"Wrong date format: DATE"***, where **DATE** is what the user entered instead of the date (before a space). Please note that the parts of the date are separated by exactly **one hyphen**, and the date itself should not contain extra characters either before the year or after the day. Date parts **cannot be empty**, but **can be zero or even negative**.

```cpp
Date getDateFromString(const string &dateString) {

    iss streamDate(dateString); 

    bool stringCheck = true;
    long long year,month, day;

    stringCheck = (stringCheck && streamDate >> year); 
    stringCheck = (stringCheck && (streamDate.peek() == '-'));
    streamDate.ignore(1);

    stringCheck = (stringCheck && streamDate >> month); 
    stringCheck = (stringCheck && streamDate.peek() == '-');
    streamDate.ignore(1);

    stringCheck = (stringCheck && streamDate >> day); 
    stringCheck = (stringCheck && streamDate.eof());

    if(!stringCheck) {
        throw logic_error("Wrong date format: " + dateString);
        }

    return {year, month, day};
}
```
> If the date format is correct, the database needs to **check the validity of the month and day**.

+ If the month number is not a number from **1 to 12**, the databse outputs ***"Month value is invalid: MONTH"***, where **MONTH** is an invalid month number, for example, 13 or -1.
  
+ If the month is correct and the day is not an integer **from 1 to 31**, the databse prints ***"Day value is invalid: DAY"***, where **DAY** is an invalid integer, for example, 39 or 0.

```cpp
Date::Date(const long long &y, const long long &m, const long long &d) {

    string error_message_month = "Month value is invalid: " + to_string(m);
    string error_message_day = "Day value is invalid: " + to_string(d);

    if(m < 1 || m > 12) throw invalid_argument(error_message_month);
    
    else if(d < 1 || d > 31) throw invalid_argument(error_message_day);

    year = y; month = m; day = d;
}
```

> ### Note that:
+ The databse **does not** check the year value separately.
+ The databse does not check the **correctness** of the calendar date: the number of days in each month is considered equal to 31, leap years are not being taken into account.
+ If both the month and the day are incorrect, then the database  displays one error message about the incorrectness of the given month.
  
> ### Examples:
+ 1-1-1 is a valid date;
+ -1-1-1 - correct date (year -1, month 1, day 1);
+ 1-1-1 - date in the correct format, but with an incorrect month -1;
+ 1 --- 1-1 - date in the wrong format: the month cannot start with two hyphens.
+ 1- + 1- + 1 is a valid date, since +1 is an integer
  
> After processing any of the described errors, entering and printing a message, the program should terminate its execution.


> ## Remarks
> ### **Uncaught exceptions**
> Since solving the problem requires a program that works correctly on a large number of different input data, it is inevitable that errors may be found in it. 
> One such error can be an uncaught exception: the error is that the exception, being thrown, does not fall under any of the catch block expressions up to the main function. In this case, the program will immediately terminate abnormally, and you will see "Unknown signal 6" as an error in the test.










