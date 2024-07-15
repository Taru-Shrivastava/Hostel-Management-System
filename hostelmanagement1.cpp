#include <iostream>
#include <string>
#include<fstream>
using namespace std;

class Student {
public:
    string name;
    int rollNumber;
    int roomNumber;
    double totalFees;
    double feesPaid;

    // Constructor
    Student(string n, int roll, int room, double fees){
        this->name = n;
        this->rollNumber = roll;
        this->roomNumber = room;
        this->totalFees = fees;
        this->feesPaid = 0.0;
    }
    // Display student information
    void display() {
        cout << "Name: " << name << "\tRoll Number: " << rollNumber << "\tRoom Number: " << roomNumber << "\tFees Paid: " << feesPaid << "\tRemaining Fees: " << calculateRemainingFees() << endl;
    }

    // Record fees payment
    void recordFees(double amount) {
        feesPaid += amount;
        cout << "Fees recorded successfully!" << endl;
    }

    // Calculate remaining fees
    double calculateRemainingFees() {
        return totalFees - feesPaid;
    }
};

class Node : public Student {
public:
    Node* next;

    // Constructor
    Node(Student s) : Student(s), next(NULL) {}

};

class HostelManager {
private:
    Node* head;

public:
    // Constructor
    HostelManager() : head(nullptr) {}

    // Add a new student to the hostel
    void addStudent(string name, int rollNumber, int roomNumber, double totalFees) {
        Student newStudent(name, rollNumber, roomNumber, totalFees);
        Node* newNode = new Node(newStudent);

        // If the list is empty, set the new node as the head
        if (!head) {
            head = newNode;
        } else {
            // Otherwise, add the new node to the end of the list
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }

        cout << "Student added successfully!" << endl;
    }

    // Display all students in the hostel
    void displayStudents() {
        Node* temp = head;

        // Traverse the list and display each student
        while (temp) {
            temp->display();
            temp = temp->next;
        }
    }

    // Record fees payment for a student
    void recordFees(int rollNumber, double amount) {
        Node* temp = head;

        // Find the student with the given roll number
        while (temp) {
            if (temp->rollNumber == rollNumber) {
                temp->recordFees(amount);
                return;
            }
            temp = temp->next;
        }

        cout << "Student with Roll Number " << rollNumber << " not found." << endl;
    }

     // Save student data to a file
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        Node* temp = head;
        while (temp) {
            file << temp->name << " " << temp->rollNumber << " " << temp->roomNumber << " " << temp->totalFees << " " << temp->feesPaid << endl;
            temp = temp->next;
        }

        file.close();
    }

    // Load student data from a file
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string name;
        int rollNumber, roomNumber;
        double totalFees, feesPaid;

        while (file >> name >> rollNumber >> roomNumber >> totalFees >> feesPaid) {
            addStudent(name, rollNumber, roomNumber, totalFees);
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->feesPaid = feesPaid;
        }

        file.close();
    }


    // Destructor to free allocated memory
    ~HostelManager() {
        Node* temp = head;
        while (temp) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }
};

int main() {
    HostelManager hostel;
    hostel.loadFromFile("student_data.txt");
    int n;
    cout<<"Enter no of students to be added"<<endl;
    cin>>n;

    string name;
    int rollNumber;
    int roomNumber;
    double fee;

    for(int i = 0;i<n;i++){
        cout<<"Enter name, rollno , room no and fee of the student to be enrolled"<<endl;
        cin>>name>>rollNumber>>roomNumber>>fee;
        hostel.addStudent(name,rollNumber,roomNumber,fee);

        
    }
     Student s1("taru",214,45,500.22);
     s1.display();
     s1.recordFees(100.22);
     s1.calculateRemainingFees();
     s1.display();
    
    // Display all students with fee-related information
    cout << "List of Students in the Hostel:" << endl;
    hostel.displayStudents();

    // Save student data to a file
    hostel.saveToFile("student_data.txt");
    
    

    

    return 0;
}
