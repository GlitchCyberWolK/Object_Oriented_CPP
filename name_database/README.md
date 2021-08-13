# Person's history of surname and first name changes.

Consider that no more than **one surname change** and no more than **one name change** can occur each year. At the same time, more and more facts from a person's past may be discovered, therefore, the years in successive calls to the ChangeLastName and ChangeFirstName methods are **not required to increase**.

It is guaranteed that all first and last names are non-empty.

The string returned by the **GetFullName** method must contain the person's first and last name, separated by a single space, as of the end of the given year.

+ If **no first and last name changes** have occurred for the current year, the program returns the ***"Incognito"*** string.
+ If there was a last name change for the given year, but there was no name change, the program returns ***"last_name with unknown first name"***.
+ If there was a name change by the given year, but there was no last name change, the program returns ***"first_name with unknown last name"***.

## Example

### Code:

```cpp
int main() {
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullName(year) << endl;
  }
  
  return 0;
}
```

### Output:

```txt
Incognito
Polina with unknown last name
Polina Sergeeva
Polina Sergeeva
Appolinaria Sergeeva
Polina Volkova
Appolinaria Volkova
```

## Updates:

I added the **GetFullNameWithHistory** method to the class from the previous First and Last Name 1 task.

```cpp
    string GetFullNameWithHistory(int year) const {
        if(year < birthYear) return "No person";

        const string first_name = BuildJoinedName(FindFirstNamesHistory(year));
        const string last_name = BuildJoinedName(FindLastNamesHistory(year));

        return BuildFullName(first_name, last_name);
    }
```

Unlike the GetFullName method, the **GetFullNameWithHistory** method should return not only the first and last name by the end of a given year, but also all previous first and last names in reverse chronological order. If current facts indicate that a person has changed his last name or first name to the same last name or first name two times in a row, the second change in the formation of history should be ignored.

## Example:

## Code:

```cpp
int main() {
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1990, "Polina");
  person.ChangeLastName(1990, "Volkova-Sergeeva");
  cout << person.GetFullNameWithHistory(1990) << endl;
  
  person.ChangeFirstName(1966, "Pauline");
  cout << person.GetFullNameWithHistory(1966) << endl;
  
  person.ChangeLastName(1960, "Sergeeva");
  for (int year : {1960, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeLastName(1961, "Ivanova");
  cout << person.GetFullNameWithHistory(1967) << endl;
  
  return 0;
}
```

## Output:

```txt
Incognito
Polina with unknown last name
Polina Sergeeva
Polina Sergeeva
Appolinaria (Polina) Sergeeva
Polina Volkova (Sergeeva)
Appolinaria (Polina) Volkova (Sergeeva)
Polina (Appolinaria, Polina) Volkova-Sergeeva (Volkova, Sergeeva)
Pauline (Polina) with unknown last name
Sergeeva with unknown first name
Pauline (Polina) Sergeeva
Pauline (Polina) Sergeeva (Ivanova, Sergeeva)
```
