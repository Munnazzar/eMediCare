#pragma once
#include "MedicineAndDosage.h"
#include <string>
#include <iostream>
#include <fstream>
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

class Patient :public Person {
private:
    int age;
    string assignedNurseId;
    string assignedDoctorId;
    int medicineCount;
    MedicineAndDosage medicine[5]; //max 5 medicines at a time

public:
    static int PateintsCount;
    Patient() { medicineCount = 0; age = 0; } 
    Patient(string id, string name, string gender, string contact, int age, string doctorId ) :
        Person(id, name, contact, gender), age(age), medicineCount(0), assignedDoctorId(doctorId) {
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

    bool addMedicine(unsigned int id, string medicineName) {
        if (medicineCount >= 5)
            return false;
        medicine[medicineCount++] = MedicineAndDosage(id, medicineName);
        return true;
    }

    bool addDosage(string weekDay, int hours, int minutes, int medicineNumber) {
        return medicine[medicineNumber].addDosage(weekDay, hours, minutes);
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
    void showAssignedPatients(Patient& patient) {
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
        Employee(id, password, "Doctor", ("Dr." + name), gender, contact), NoOfPatients(0) {
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

    bool addMedicine(Patient &patient, int medicineId,string medicineName) {
        return patient.addMedicine(medicineId, medicineName);
    }

    bool addDosage(Patient& patient, string weekday, int hours, int minutes, int medicineNumber) {
        return patient.addDosage(weekday,hours,minutes, medicineNumber);
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
    bool assignNurse(Nurse& nurse, Patient& patient) {
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
        outFile << id << " " << name << " " << contact << " " << gender << " " << password;
        outFile << endl;
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

    bool addPatient(Patient patients[], Doctor& doctor, string id, string name, string gender, string contact, int age) {
        if (doctor.setPatientId(id)) {
            patients[Patient::PateintsCount] = Patient(id, name, gender, contact, age, doctor.getID());
            patients[Patient::PateintsCount].addToFile();
            Patient::incrementCount();
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

    bool addNurse(Nurse nurses[], string id, string name, string password, string gender, string contact) {
        if (Nurse::NursesCount >= 10) {
            //error message
            return false;
        }
        nurses[Nurse::NursesCount] = Nurse(id,password,name,gender,contact);
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
int Patient::PateintsCount = -1;

//function called at the start of the program, loads all the data stored in files to arrays
bool initializeAll(Doctor doctors[], Nurse nurses[], Admin admins[], Patient patients[]) {
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
        Patient::incrementCount();
        patients[Patient::PateintsCount].readFile(inFile);
    }
    inFile.close();
    return true;
}