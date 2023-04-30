#pragma once
#include <string>
#include <fstream>
using namespace std;

//testing pull requests

class Person {
protected:
    string name;
    string contact;
    string gender;

    Person() {}
    Person(string name, string contact, string gender) : name(name), contact(contact), gender(gender) {}

    string getName() {
        return name;
    }

    virtual void addToFile() = 0;
};

class Employee : public Person {
protected:
    string id;
    string password;
    string designation;

    Employee() {}
    Employee(string id, string password, string designation, string name, string gender, string contact) :
        Person(name, contact, gender), id(id), password(password), designation(designation) {}

public:
    bool validate(string id, string pass) {
        return (this->id == id && password == pass);
    }
    void changePassword(string pass) {
        password = pass;
    }
    void addToFile() {

    }
};

class Admin : public Employee {
private:

public:
    Admin() {}
    Admin(string id, string password, string name, string gender, string contact) :
        Employee(id, password, "Admin", name, gender, contact) {}

    void addToFile() {
        ofstream outFile;
        string data;

        data = id + " " + password + " " + name + " " + gender + " " + contact;

        outFile.open("Admin.txt");
        if (!outFile) {
            //error message(depends if we are using forms or not) 
            return;
        }
        outFile << data << endl;
        outFile.close();
    }
};

class Patients :public Person {
private:
    string id;
    string age;
    int medicineCount;
    string* Medicine;

public:
    Patients() {}
    Patients(string name, string contact, string gender, string id, string age) :
        Person(name, contact, gender), id(id), age(age), medicineCount(0) {}

    string getID() {
        return id;
    }

    string getName() {
        return name;
    }

    void setMedicine(string medicine) {
        Medicine[medicineCount] = medicine;
        medicineCount++;
    }
    
    void addToFile() {
        ofstream outFile;
        string data;

        data = id + " " + name + " " + age + " " + gender + " " + contact;

        outFile.open("Patients.txt");
        if (!outFile) {
            //error message(depends if we are using forms or not) 
            return;
        }
        outFile << data << endl;
        outFile.close();
    }
};

class Nurse : public Employee {
private:
    int NoOfPatients;
    Patients* patients;
public:
    Nurse() { patients = new Patients[5]; } //assigning max 5 patients to each nurse
    Nurse(string id, string password, string name, string gender, string contact) :
        Employee(id, password, "Nurse", name, gender, contact), NoOfPatients(0) {
        patients = new Patients[5];
    }

    void addToFile() {
        ofstream outFile;
        string data;

        data = id + " " + password + " " + name + " " + gender + " " + contact;

        outFile.open("Nurse.txt");
        if (!outFile) {
            //error message(depends if we are using forms or not) 
            return;
        }
        outFile << data << endl;
        outFile.close();
    }
    //checks the workload on the nurse
    bool WorkLoad() {
        if (NoOfPatients > 5)
            return false;
        else
            return true;
    }

    void assignPatient(string name, string contact, string gender, string id, string age) {
        patients[NoOfPatients] = Patients(name, contact, gender, id, age);
        NoOfPatients++;
    }
    //Tells the name and id of assigned patients to a particular nurse
    void showAssignedPatients() {
        cout << "Assigned Patients:" << endl;
        for (int i = 0; i < NoOfPatients; i++) {
            cout << "ID: " << patients[i].getID() << ", Name: " << patients[i].getName() << endl;
        }
    }
    //assign medicine to patient
    void assignMedicine(string medName) {
        for (int i = 0; i < NoOfPatients; i++) {
            if (patients[i].getName() == name) {
                patients[i].setMedicine(medName);
                break;
            }
        }
    }
};

class Doctor : public Employee {
private:

public:
    Doctor() {}
    Doctor(string id, string password, string name, string gender, string contact) :
        Employee(id, password, "Doctor", ("Dr. " + name), gender, contact) {}

    void addToFile() {
        ofstream outFile;
        string data;

        data = id + " " + password + " " + name + " " + gender + " " + contact;

        outFile.open("Doctor.txt");
        if (!outFile) {
            //error message(depends if we are using forms or not) 
            return;
        }
        outFile << data << endl;
        outFile.close();
    }

    void assignNurse(Nurse& nurse, string name, string contact, string gender, string id, string age) {
        nurse.assignPatient(name, contact, gender, id, age);
    }

    void prescribeMedicine(Nurse& nurse, string medName) {
        nurse.assignMedicine(medName);
    }
};

bool initializeAll(Doctor* doctors, Nurse* nurses, Admin admin) {
    doctors = new Doctor[10];
    nurses = new Nurse[10];

    ifstream inFile;
    // inFile;
       //  while ();
    return true;
}