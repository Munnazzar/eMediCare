#pragma once
#include <string>
#include <iostream>
#include <fstream>
//#include "MedicineAndDosage.h"
using namespace std;




class Person {
protected:
    string id;
    string name;
    string contact;
    string gender;

    Person() {}
    Person(string id, string name, string contact, string gender) : id(id), name(name), contact(contact), gender(gender) {}
public:
    string getName() {
        return name;
    }

    string getID() {
        return id;
    }

    virtual void addToFile() = 0;
};

class Employee : public Person {
protected:
    string password;
    string designation;

    Employee() {}
    Employee(string id, string password, string designation, string name, string gender, string contact) :
        Person(id, name, contact, gender), password(password), designation(designation) {}

public:
    bool validate(string id, string pass) {
        return (this->id == id && password == pass);
    }
    void changePassword(string pass) {
        password = pass;
    }
};

class Patients :public Person {
private:
    string age;
    string assignedNurseId;
    string assignedDoctorId;
    int medicineCount;
    MedicineAndDosage *medicine;

public:
    static int PateintsCount;
    Patients() { medicine = new MedicineAndDosage[5]; PateintsCount++; medicineCount = 0; } //max 5 medicines at a time
    Patients(string name, string contact, string gender, string id, string age) :
        Person(id, name, contact, gender), age(age), medicineCount(0) {
        PateintsCount++;
        medicine = new MedicineAndDosage[5];
    }

    void setNurseID(string id) {
        assignedNurseId = id;
    }

    void setDoctorID(string id) {
        assignedDoctorId = id;
    }

    string getNurseID() {
        return assignedNurseId;
    }

    string getDoctorID() {
        return assignedDoctorId;
    }

    void addToFile() {
        ofstream outFile;
        outFile.open("Patients.txt", ios::app);
        if (!outFile) {
            //error message(depends if we are using forms or not) 
            return;
        }
        outFile << id << " " << name << " " << contact << " " << gender << " " << age << " " << assignedNurseId << " " << assignedDoctorId << " " << medicineCount;
        outFile << endl;
        outFile.close();
    }

    void readFile(ifstream& inFile) {
        inFile >> id >> name >> contact >> gender >> age >> assignedNurseId >> assignedDoctorId >> medicineCount;
    }

    static void incrementCount() {
        PateintsCount++;
    }
};

class Nurse : public Employee {
private:
    int NoOfPatients;
    string PatientsId[5];//assigning max 5 patients to each nurse
public:
    static int NursesCount;
    Nurse() { NoOfPatients = 0; }
    Nurse(string id, string password, string name, string gender, string contact) :
        Employee(id, password, "Nurse", name, gender, contact), NoOfPatients(0) {
    }

    void display() {
        std::cout << "id" << id << " name: " << name << "contact: " << contact << " gender: " << gender << " password: " << password << " num:" << NoOfPatients << endl;
    }

    bool setPatientId(string id) {
        if (NoOfPatients >= 5) { //checking workload
            return false;
        }
        PatientsId[NoOfPatients++] = id;
        return true;
    }

    void addToFile() {
        ofstream outFile;
        outFile.open("Nurse.txt", ios::app);
        if (!outFile) {
            //error message(depends if we are using forms or not) 
            return;
        }
        outFile << id << " " << name << " " << contact << " " << gender << " " << password << " " << NoOfPatients;
        for (int i = 0; i < NoOfPatients; i++) {
            outFile << " " << PatientsId[i];
        }
        outFile << endl;
        outFile.close();
    }

    void readFile(ifstream& inFile) {
        inFile >> id >> name >> contact >> gender >> password >> NoOfPatients;
        for (int i = 0; i < NoOfPatients; i++) {
            inFile >> PatientsId[i];
        }
    }

    //Tells the name and id of assigned patients to a particular nurse
    void showAssignedPatients(Patients& patient) {
        //cout << "Assigned Patients:" << endl;
        for (int i = 0; i < NoOfPatients; i++) {
            // cout << "ID: " << patient[i].getID() << ", Name: " << patient[i].getName() << endl;
        }
    }

    static void incrementCount() {
        NursesCount++;
    }
    
};

class Doctor : public Employee {
private:
    int NoOfPatients;
    string patientsId[5];//The doctor will deal max 5 patients at a time

public:
    static int DoctorsCount;
    Doctor() { NoOfPatients = 0; }
    Doctor(string id, string password, string name, string gender, string contact) :
        Employee(id, password, "Doctor", ("Dr" + name), gender, contact), NoOfPatients(0) {
    }

    void display() {
        std::cout << "id" << id << " name: " << name << "contact: " << contact << " gender: " << gender << " password: " << password << " num:" << NoOfPatients << endl;
    }
    bool setPatientId(string id) {
        if (NoOfPatients >= 5) { //checking workload
            return false;
        }
        patientsId[NoOfPatients++] = id;
        return true;
    }

    void addToFile() {
        ofstream outFile;
        outFile.open("Doctor.txt", ios::app);
        if (!outFile) {
            //error message(depends if we are using forms or not) 
            return;
        }
        outFile << id << " " << name << " " << contact << " " << gender << " " << password << " " << NoOfPatients;
        for (int i = 0; i < NoOfPatients; i++) {
            outFile << " " << patientsId[i];
        }
        outFile << endl;
        outFile.close();
    }
    bool readFile(ifstream& inFile) {
        inFile >> id >> name >> contact >> gender >> password >> NoOfPatients;
        for (int i = 0; i < NoOfPatients; i++) {
            inFile >> patientsId[i];
        }
        return true;
    }

    //assigns nurse to a particular patient
    bool assignNurse(Nurse& nurse, Patients& patient) {
        if (nurse.setPatientId(patient.getID())) {
            //message indication that nurses has been assigned to the patient
            patient.setNurseID(nurse.getID());
            return true;
        }
        return false;
    }

    static void incrementCount() {
        DoctorsCount++;
    }
};

class Admin : public Employee {
private:

public:
    static int AdminsCount;
    Admin() {}
    Admin(string id, string password, string name, string gender, string contact) :
        Employee(id, password, "Admin", name, gender, contact) {}

    void addToFile() {
        ofstream outFile;
        outFile.open("Admin.txt", ios::app);
        if (!outFile) {
            //error message(depends if we are using forms or not) 
            return;
        }
        outFile << endl << id << " " << name << " " << contact << " " << gender << " " << password;
        outFile.close();
    }

    void readFile(ifstream& inFile) {
        inFile >> id >> name >> contact >> gender >> password;
    }

    //assigns doctor to a particular patient
    //ig this function is not needed
    /*void assignDoctor(Doctor& doctor, Patients& patient) {
        doctor.setPatientId(patient.getID());
        patient.setDoctorID(doctor.getID());
    }*/

    bool addPatient(Patients patients[], Doctor& doctor, string name, string gender, string contact, string age, string id) {
        if (doctor.setPatientId(id)) {
            patients[Patients::PateintsCount] = Patients(name, contact, gender, id, age);
            patients[Patients::PateintsCount].addToFile();
            Patients::incrementCount();
            return true;
        }
        return false;
    }

    bool addDoctor(Doctor* doctors, string id, string name, string password, string gender, string contact) {
        if (Doctor::DoctorsCount >= 10) {
            //error message
            return false;
        }

        doctors[Doctor::DoctorsCount] = Doctor(id, password, name, gender, contact);
        doctors[Doctor::DoctorsCount].addToFile();
        Doctor::incrementCount();
        return true;
    }

    bool addNurse(Nurse nurses[], string name, string gender, string contact, string age, string id) {
        if (Nurse::NursesCount >= 10) {
            //error message
            return false;
        }
        nurses[Nurse::NursesCount] = Nurse(name, contact, gender, id, age);
        nurses[Nurse::NursesCount].addToFile();
        Nurse::incrementCount();
        return true;
    }

    static void incrementCount() {
        AdminsCount++;
    }

};

int Doctor::DoctorsCount = -1;
int Nurse::NursesCount = -1;
int Admin::AdminsCount = -1;
int Patients::PateintsCount = -1;

//function called at the start of the program, loads all the data stored in files to arrays
bool initializeAll(Doctor doctors[], Nurse nurses[], Admin admins[], Patients patients[]) {
    ifstream inFile;
    inFile.open("Doctor.txt", ios::in);
    while (!inFile.eof()) {
        Doctor::incrementCount();
        doctors[Doctor::DoctorsCount].readFile(inFile);
    }
    inFile.close();

    inFile.open("Nurse.txt", ios::in);
    while (!inFile.eof()) {
        Nurse::incrementCount();
        nurses[Nurse::NursesCount].readFile(inFile);
    }
    inFile.close();

    inFile.open("Admin.txt", ios::in);
    while (!inFile.eof()) {
        Admin::incrementCount();
        admins[Admin::AdminsCount].readFile(inFile);
    }
    inFile.close();

    inFile.open("Patients.txt", ios::in);
    while (!inFile.eof()) {
        Patients::incrementCount();
        patients[Patients::PateintsCount].readFile(inFile);
    }
    inFile.close();
    return true;
}