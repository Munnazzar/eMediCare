#pragma once
#include <string>
#include <fstream>
using namespace std;

class Person {
protected:
    string id;
    string name;
    string contact;
    string gender;

    Person() {}
    Person(string id, string name, string contact, string gender) : id(id),name(name), contact(contact), gender(gender) {}
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
    void addToFile() {

    }
};

class Patients :public Person {
private:
    string assignedNurseId;
    string assignedDoctorId;
    string age;
    int medicineCount;
    string* Medicine;

public:
    static int PateintsCount;
    Patients() { Medicine = new string[5]; PateintsCount++; medicineCount = 0; } //max 5 medicines at a time
    Patients(string name, string contact, string gender, string id, string age) :
        Person(id, name, contact, gender), age(age), medicineCount(0) {
        PateintsCount++;
        Medicine = new string[5];
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
    string PatientsId[5];//assigning max 5 patients to each nurse
public:
    static int NursesCount;
    Nurse() { NoOfPatients = 0; } 
    Nurse(string id, string password, string name, string gender, string contact) :
        Employee(id, password, "Nurse", name, gender, contact), NoOfPatients(0) {
    }

    bool setPatientId(string id) {
        if (NoOfPatients>=5) { //checking workload
            return false;
        }
        PatientsId[NoOfPatients++] = id;
        return true;
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
        Employee(id, password, "Doctor", ("Dr. " + name), gender, contact), NoOfPatients(0) {
    }

    bool setPatientId(string id) {
        if (NoOfPatients >= 5){ //checking workload
            return false;
        }
        patientsId[NoOfPatients++] = id;
        return true;
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
        outFile.open("Admin.dat", ios::app);
        if (!outFile) {
            //error message(depends if we are using forms or not) 
            return;
        }
        outFile.write((char*)this, sizeof(Admin));
        outFile.close();
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

    static void incrementCount() {
        AdminsCount++;
    }

};

int Doctor::DoctorsCount = 0;
int Nurse::NursesCount = 0;
int Admin::AdminsCount = 0;
int Patients::PateintsCount = 0;

//function called at the start of the program, loads all the data stored in files to arrays
bool initializeAll(Doctor* doctors, Nurse* nurses, Admin* admins, Patients* patients) {
    //can update later in someway to dynamically allocate memory to required size of arrays
    doctors = new Doctor[10];
    nurses = new Nurse[10];
    admins = new Admin[10];

    //Doctor::DoctorsCount = 0;
    //Nurse::NursesCount = 0;
    //Admin::AdminsCount = 0;
    //Patients::PateintsCount = 0;

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
    return true;
}



