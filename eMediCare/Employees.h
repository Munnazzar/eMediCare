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
    string assignedNurseId;
    string assignedDoctorId;
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
    string* PatientsId;
public:
    Nurse() { patients = new Patients[5]; } //assigning max 5 patients to each nurse
    Nurse(string id, string password, string name, string gender, string contact) :
        Employee(id, password, "Nurse", name, gender, contact), NoOfPatients(0) {
        patients = new Patients[5];
    }

    string getID() {
        return id;
    }

    void setPatientId(string id) {
        PatientsId[NoOfPatients++] = id;
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

    //Tells the name and id of assigned patients to a particular nurse
    void showAssignedPatients(Patients& patient) {
        //cout << "Assigned Patients:" << endl;
        for (int i = 0; i < NoOfPatients; i++) {
           // cout << "ID: " << patient[i].getID() << ", Name: " << patient[i].getName() << endl;
        }
    }
    //assign medicine to patient
    void assignMedicine(string medName, Patients* patient) {
        for (int i = 0; i < NoOfPatients; i++) {
            if (patient[i].getName() == name) {
                patient[i].setMedicine(medName);
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
    int NoOfPatients;
    string* patientsId;
public:
    Doctor() {}
    Doctor(string id, string password, string name, string gender, string contact) :
        Employee(id, password, "Doctor", ("Dr. " + name), gender, contact) {}

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
    void assignNurse(Nurse& nurse, Patients& patient, string id) {
        nurse.setPatientId(patient.getID());
        patient.setNurseID(nurse.getID());
    }
    //prescribes medicine to nurse
    void prescribeMedicine(Nurse& nurse, string medName, Patients& patient) {
        nurse.assignMedicine(medName, &patient);
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
    //assigns doctor to a particular patient
    void assignDoctor(Doctor& doctor, Patients& patient, string id) {
        doctor.setPatientId(patient.getID());
        patient.setDoctorID(doctor.getID());
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
    // inFile;
       //  while ();
    return true;
}