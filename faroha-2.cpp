#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class University {
private:
    string name;
    string number;
    string address;
public:
    University() {}
    University(const string& name, const string& number, const string& address) : name(name), number(number), address(address) {}
    ~University() {}

    void enterInfo() {
        cout << "Enter university name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter university number: ";
        getline(cin, number);
        cout << "Enter university address: ";
        getline(cin, address);
    }

    void displayInfo() const {
        cout << "University name: " << name << "\nUniversity number: " << number << "\nUniversity address: " << address << endl;
    }

    friend ostream& operator<<(ostream& os, const University& uni) {
        os << "University name: " << uni.name << "\nUniversity number: " << uni.number << "\nUniversity address: " << uni.address << endl;
        return os;
    }
};

class Person {
protected:
    string name;
    int age;
    string gender;
    int id;
public:
    Person() : age(0), id(0) {}
    Person(const string& name, int age, const string& gender, int id) : name(name), age(age), gender(gender), id(id) {}
    virtual ~Person() {}

    void enterInfo() {
        cout << "Enter ID of student: ";
        cin >> id;
        cin.ignore();
        cout << "Enter name of student: ";
        getline(cin, name);

        while (true) {
            cout << "Enter age of student: ";
            cin >> age;
            if (age >= 17 && age <= 30) {
                cin.ignore();
                break;
            } else {
                cout << "Age must be between 17 and 30. Please re-enter.\n";
            }
        }

        cout << "Enter gender of student: ";
        getline(cin, gender);
    }

    virtual void displayInfo() const {
        cout << "ID: " << id << "\nName: " << name << "\nAge: " << age << "\nGender: " << gender << endl;
    }

    int getId() const {
        return id;
    }

    friend ostream& operator<<(ostream& os, const Person& person) {
        os << "ID: " << person.id << "\nName: " << person.name << "\nAge: " << person.age << "\nGender: " << person.gender << endl;
        return os;
    }

    bool operator==(const Person& other) const {
        return this->id == other.id;
    }

    bool operator!=(const Person& other) const {
        return !(*this == other);
    }
};

class Student : public Person {
private:
    string date_of_admission;
    string date_of_graduation;
    string major;
    string advisor;
    static int count;
    static const vector<string> validMajors;

    bool isValidMajor(const string& major) const {
        return find(validMajors.begin(), validMajors.end(), major) != validMajors.end();
    }
public:
    Student() {}
    Student(const string& name, int age, const string& gender, int id, const string& date_of_admission, const string& date_of_graduation, const string& major, const string& advisor)
        : Person(name, age, gender, id), date_of_admission(date_of_admission), date_of_graduation(date_of_graduation), major(major), advisor(advisor) {
        count++;
    }

    Student(const Student& other) : Person(other), date_of_admission(other.date_of_admission), date_of_graduation(other.date_of_graduation), major(other.major), advisor(other.advisor) {
        count++;
    }

    Student& operator=(const Student& other) {
        if (this != &other) {
            Person::operator=(other);
            date_of_admission = other.date_of_admission;
            date_of_graduation = other.date_of_graduation;
            major = other.major;
            advisor = other.advisor;
        }
        return *this;
    }

    ~Student() {
        ++count;
    }

    void enterInfo(map<int, Student>& students) {
        Person::enterInfo();


        while (students.find(this->id) != students.end()) {
            cout << "Student with ID " << this->id << " already exists. Please enter a unique ID.\n";
            cout << "Enter ID of student: ";
            cin >> this->id;
            cin.ignore();
        }

        while (true) {
            cout << "Enter date of admission (year): ";
            cin >> date_of_admission;
            if (stoi(date_of_admission) >= 2020) {
                break;
            } else {
                cout << "Date of admission must be greater than or equal to 2020. Please re-enter.\n";
            }
        }

        while (true) {
            cout << "Enter date of graduation (year): ";
            cin >> date_of_graduation;
            if (stoi(date_of_graduation) >= 2024) {
                break;
            } else {
                cout << "Date of graduation must be greater than or equal to 2024. Please re-enter.\n";
            }
        }

        cin.ignore();
        while (true) {
            cout << "Enter major (AI, CS, Data Science): ";
            getline(cin, major);
            if (isValidMajor(major)) {
                break;
            } else {
                cout << "Major must be one of AI, CS, or Data Science. Please re-enter.\n";
            }
        }

        cout << "Enter advisor: ";
        getline(cin, advisor);
    }

    static int getCount() {
        return count;
    }

    static void resetCount() {
        count = 0;
    }

    void displayInfo() const override {
        cout << "\nStudent Information\n";
        Person::displayInfo();
        cout << "Date of Admission: " << date_of_admission << "\nDate of Graduation: " << date_of_graduation << "\nMajor: " << major << "\nAdvisor Name: " << advisor << "\n";
        cout << "\nTotal number of students: " << count << endl;
    }

    friend ostream& operator<<(ostream& os, const Student& student) {
        os << static_cast<const Person&>(student);
        os << "Date of Admission: " << student.date_of_admission << "\nDate of Graduation: " << student.date_of_graduation << "\nMajor: " << student.major << "\nAdvisor Name: " << student.advisor << "\n";
        return os;
    }
};

int Student::count = 0;
const vector<string> Student::validMajors = {"AI", "CS", "Data Science"};

int main() {
    cout << "Welcome to Student Management System\n";
    cout << "---------------------------------------------------\n"; 

    University uni;
    uni.enterInfo();

    map<int, Student> students;
    bool loggedIn = true;

    while (loggedIn) {
        cout << "\nPress 1 to add new student\nPress 2 to display all students information\nPress 3 to search student by ID\nPress 4 to delete all information\nPress 5 to exit\n";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                Student newStudent;
                newStudent.enterInfo(students); // Pass the map to ensure unique ID
                students[newStudent.getId()] = newStudent;
                break;
            }
            case 2:
                if (!students.empty()) {
                    for (const auto& pair : students) {
                        pair.second.displayInfo();
                    }
                } else {
                    cout << "\nThere is no information available.\n";
                }
                break;
            case 3: {
                int searchId;
                cout << "\nEnter ID to search: ";
                cin >> searchId;
                auto it = students.find(searchId);
                if (it != students.end()) {
                    it->second.displayInfo();
                } else {
                    cout << "\nStudent with ID " << searchId << " not found.\n";
                }
                break;
            }
            case 4:
                if (!students.empty()) {
                    students.clear();
                    Student::resetCount();
                    cout << "\nAll information deleted successfully\n";
                } else {
                    cout << "\nThere is no information to delete.\n";
                }
                break;
            case 5:
                loggedIn = false;
                cout << "\nLogged out successfully.\n";
                break;
            default:
                cout << "\nInvalid choice. Please enter a valid option.\n";
                break;
        }

        cout << "-------------------------------------------------\n"; 
    }

    return 0;
}