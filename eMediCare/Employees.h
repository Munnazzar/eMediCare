#pragma once
#include <string>
#include <fstream>
using namespace std;

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
    static int AdminsCount;
    Admin() {}
    Admin(string id, string password, string name, string gender, string contact) :
        Employee(id, password, "Admin", name, gender, contact) {
        AdminsCount++;
    }

    void addToFile() {
        ofstream outFile;
        outFile.open("Admin.dat", ios::app);
        if (!outFile) {
            //error message(depends if we are using forms or not) 
            return;
        }
        outFile.write((char*)this, sizeof(Admin));
        outFile.close();
    }

    static void incrementCount() {
        AdminsCount++;
    }
};

class Patients :public Person {
private:
    string id;
    string age;
    int medicineCount;
    string* Medicine;

public:
    static int PateintsCount;
    Patients() {}
    Patients(string name, string contact, string gender, string id, string age) :
        Person(name, contact, gender), id(id), age(age), medicineCount(0) {
        PateintsCount++;
    }

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
        outFile.open("Patients.dat", ios::app);
        if (!outFile) {
            //error message(depends if we are using forms or not) 
            return;
        }
        outFile.write((char*)this, sizeof(Patients));
        outFile.close();
    }

    static void incrementCount() {
        PateintsCount++;
    }
};

class Nurse : public Employee {
private:
    int NoOfPatients;
    Patients* patients;
public:
    static int NursesCount;
    Nurse() { patients = new Patients[5]; } //assigning max 5 patients to each nurse
    Nurse(string id, string password, string name, string gender, string contact) :
        Employee(id, password, "Nurse", name, gender, contact), NoOfPatients(0) {
        patients = new Patients[5];
        NursesCount++;
    }

    void addToFile() {
        ofstream outFile;
        outFile.open("Nurse.dat", ios::app);
        if (!outFile) {
            //error message(depends if we are using forms or not) 
            return;
        }
        outFile.write((char*)this, sizeof(Nurse));
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

    static void incrementCount() {
        NursesCount++;
    }
};

class Doctor : public Employee {
private:

public:
    static int DoctorsCount;
    Doctor() {}
    Doctor(string id, string password, string name, string gender, string contact) :
        Employee(id, password, "Doctor", ("Dr. " + name), gender, contact) {
        DoctorsCount++;
    }

    void addToFile() {
        ofstream outFile;
        outFile.open("Doctor.dat", ios::app);
        if (!outFile) {
            //error message(depends if we are using forms or not) 
            return;
        }
        outFile.write((char*)this, sizeof(Doctor));
        outFile.close();
    }

    void assignNurse(Nurse& nurse, string name, string contact, string gender, string id, string age) {
        nurse.assignPatient(name, contact, gender, id, age);
    }

    void prescribeMedicine(Nurse& nurse, string medName) {
        nurse.assignMedicine(medName);
    }

    static void incrementCount() {
        DoctorsCount++;
    }
};

//function called at the start of the program, loads all the data stored in files to arrays
bool initializeAll(Doctor* doctors, Nurse* nurses, Admin* admins, Patients* patients) {
    //can update later in someway to dynamically allocate memory to required size of arrays
    doctors = new Doctor[10];
    nurses = new Nurse[10];
    admins = new Admin[10];

    Doctor::DoctorsCount = 0;
    Nurse::NursesCount = 0;
    Admin::AdminsCount = 0;
    Patients::PateintsCount = 0;

    ifstream inFile;
    inFile.open("Doctor.dat", ios::in);
    while (inFile.read((char*)(&doctors[Doctor::DoctorsCount]), sizeof(Doctor))) {
        Doctor::incrementCount;
    }

    inFile.open("Nurse.dat", ios::in);
    while (inFile.read((char*)(&nurses[Nurse::NursesCount]), sizeof(Nurse))) {
        Nurse::incrementCount;
    }

    inFile.open("Admin.dat", ios::in);
    while (inFile.read((char*)(&admins[Admin::AdminsCount]), sizeof(Admin))) {
        Admin::incrementCount;
    }

    inFile.open("Patients.dat", ios::in);
    while (inFile.read((char*)(&patients[Patients::PateintsCount]), sizeof(Patients))) {
        Patients::incrementCount;
    }
}