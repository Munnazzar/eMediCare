#pragma once
#include "MedicineAndDosage.h"
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <chrono>
#include "ReminderFunction.h"

using namespace std;

void gotoline(int x, int y) {
    COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void printHeader() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 243);
    gotoline(0, 0);
    cout << char(220) << char(219) << char(220) << " e-MediCare";
    gotoline(1, 1);
    cout << char(223);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
}

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
    string getGender() {
        return gender;
    }
    virtual void addToFile() = 0;
};

class Patient :public Person {
private:
    int age;
    string assignedNurseId;
    string assignedDoctorId;
    int medicineCount;
    MedicineAndDosage medicine[5]; //max 5 medicines at a time

public:
    static int PatientsCount;
    Patient() { medicineCount = 0; age = 0; }
    Patient(string id, string name, string gender, string contact, int age, string doctorId) :
        Person(("P-" + id), name, contact, gender), age(age), medicineCount(0), assignedDoctorId(doctorId), assignedNurseId("default"){ 
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

    int getMedicineCount() {
        return medicineCount;
    }

    bool addMedicine(unsigned int id, string medicineName) {
        if (medicineCount >= 5)
            return false;
        medicine[medicineCount++] = MedicineAndDosage(id, medicineName);
        return true;
    }

    bool addDosage(string weekDay, int hours, int minutes, int medicineNumber) {
        if (medicineNumber > medicineCount)
            return false;
        return medicine[medicineNumber - 1].addDosage(weekDay, hours, minutes);
    }

    void addToFile() {
        ofstream outFile;
        outFile.open("Patients.txt", ios::app);
        if (!outFile) {
            //error message(depends if we are using forms or not) 
            return;
        }
        outFile << id << " " << name << " " << contact << " " << gender << " " << age << " " << assignedNurseId << " " << assignedDoctorId << " " << medicineCount;
        outFile << medicine[0];
        outFile << medicine[1];
        outFile << medicine[2];
       /* for (int i = 0; i < medicineCount; i++) {
            outFile << medicine[i];
        }*/
        outFile << endl;
        outFile.close();
    }

    void readFile(ifstream& inFile) {
        inFile >> id >> name >> contact >> gender >> age >> assignedNurseId >> assignedDoctorId >> medicineCount;
        inFile >> medicine[0];
        inFile >> medicine[1];
        inFile >> medicine[2];
        /*for (int i = 0; i < medicineCount;i++) {
            inFile >> medicine[i];
        }*/
    }

    static void incrementCount() {
        PatientsCount++;
    }

    void MedicineDetails() {
        for (int i = 0; i < getMedicineCount(); i++) {
            medicine[i].display();
        }
    }

    friend void notificationFunction(Patient* patients);

    //for testing purposes
    /*void display() {
        cout << "id" << id << endl;
        cout << "name" << name << endl;
        cout << "contact" << contact << endl;
        cout << "gender" << gender << endl;
        cout << "age" << age << endl;
        cout << "assignedNurseId" << assignedNurseId << endl;
        cout << "assignedDoctorId" << assignedDoctorId << endl;
        cout << "medicineCount" << medicineCount << endl;
        for (int i = 0; i < medicineCount; i++) {
            medicine[i].display();
        }
    }*/
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

    void PatientMedicineDetails(Patient patients[], string id) {
        for (int i = 0; i < Patient::PatientsCount; i++) {
            if (id == patients[i].getID()) {
                patients[i].MedicineDetails();
            }
        }
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
        Employee(("N-" + id), password, "Nurse", name, gender, contact), NoOfPatients(0) {
    }

    void display() {
        std::cout << "id" << id << " name: " << name << "contact: " << contact << " gender: " << gender << " password: " << password << " num:" << NoOfPatients << endl;
    }

    void setPatientId(string id) {
       PatientsId[NoOfPatients++] = id;
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
    void showAssignedPatients(Patient patients[]) {
        cout << "Assigned Patients:" << endl;
        for (int i = 0; i < NoOfPatients; i++) {
            for (int j = 0; j < Patient::PatientsCount; j++) {
                if (PatientsId[i] == patients[j].getID()) {
                    cout << "PATIENT NO " << i + 1 << ":" << endl << "\tName: " << patients[j].getID() << endl << "\tId: " << patients[j].getName() << endl;
                }
            }

        }
    }

    static void incrementCount() {
        NursesCount++;
    }

    static int printAvailableNurses(Nurse nurses[], int indexes[]) {
        system("cls");
        printHeader();
        int i = 4, count = 0;
        gotoline(48, i);
        cout << "AVAILABLE NURSES";
        gotoline(40, i + 2);
        cout << "   ID       Name           Gender";
        gotoline(39, i + 3);
        cout << "------------------------------------";
        for (int n = 0;n < NursesCount;n++) {
            if (nurses[n].NoOfPatients < 5) {
                gotoline(40, i + 4 + count);
                cout << count + 1;
                gotoline(43, i + 4 + count);
                cout << nurses[n].id;
                gotoline(52, i + 4 + count);
                cout << nurses[n].name;
                gotoline(67, i + 4 + count);
                cout << nurses[n].gender;
                indexes[count] = n;
                count++;
            }
        }
        if (count == 0) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            gotoline(45, i + 5);
            cout << "No Available Nurses";
            Sleep(1000);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 248);
        }
        return count;
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
        Employee(("D-"+id), password, "Doctor", ("Dr." + name), gender, contact), NoOfPatients(0) {
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
        nurse.setPatientId(patient.getID());
        patient.setNurseID(nurse.getID());
        return true;
    }

    bool AssignNurse(Patient patients[],Nurse nurses[]) {
        int patientIndexes[5] = { 0 };
        int i = 4, count = 0;
        gotoline(44, i);
        cout << "Patinets of " << this->name;
        gotoline(40, i + 2);
        cout << "   ID       Name           Gender";
        gotoline(39, i + 3);
        cout << "------------------------------------";
        if (NoOfPatients == 0) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            gotoline(45, i + 5);
            cout << "No Patients Assigned";
            Sleep(1000);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 248);
            return false;
        }

        for (int n = 0;n < DoctorsCount;n++) {
            if (patients[n].getDoctorID() == this->id) {
                gotoline(40, i + 4 + count);
                cout << count + 1;
                gotoline(43, i + 4 + count);
                cout << patients[n].getID();
                gotoline(52, i + 4 + count);
                cout << patients[n].getName();
                gotoline(67, i + 4 + count);
                cout << patients[n].getGender();
                patientIndexes[count] = n;
                count++;
            }
        }

        int choice;
        gotoline(40, 10 + NoOfPatients);
        cout << "Select a patient: ";
        cin >> choice;
        while (choice < 1 || choice > NoOfPatients) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
            gotoline(40, 11 + NoOfPatients);
            printf("Wrong Input!\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            gotoline(59, 10 + NoOfPatients);
            cout << "                      ";
            gotoline(59, 10 + NoOfPatients);
            cin >> choice;
        }

        int Patientindex = patientIndexes[choice - 1];

        int NursesIndex[10];
        int availableNurses = Nurse::printAvailableNurses(nurses, NursesIndex);
        
        if (availableNurses == 0)
            return false;

        gotoline(40, 10 + availableNurses);
        cout << "Select a nurse for the patient: ";
        cin >> choice;
        while (choice < 1 || choice > availableNurses) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
            gotoline(40, 11 + availableNurses);
            printf("Wrong Input!\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            gotoline(72, 10 + availableNurses);
            cout << "                      ";
            gotoline(72, 10 + availableNurses);
            cin >> choice;
        }

        int NurseIndex = NursesIndex[choice - 1];
        if (assignNurse(nurses[NurseIndex], patients[Patientindex])) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
            gotoline(50, 12 + availableNurses);
            cout << "NURSE ASSIGGNED!";
            Sleep(1000);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            return true;
        }
        return false;
    }

    static void incrementCount() {
        DoctorsCount++;
    }

    static int printAvailableDoctors(Doctor doctors[], int indexes[]) {
        system("cls");
        printHeader();
        int i = 4, count=0;
        gotoline(48, i);
        cout << "AVAILABLE DOCTORS";
        gotoline(40, i + 2);
        cout << "   ID       Name           Gender";
        gotoline(39, i + 3);
        cout << "------------------------------------";
        for (int n = 0;n < DoctorsCount;n++) {
            if (doctors[n].NoOfPatients < 5) {
                gotoline(40, i + 4 + count);
                cout << count+1;
                gotoline(43, i + 4+count);
                cout << doctors[n].id;
                gotoline(52, i + 4+count);
                cout << doctors[n].name;
                gotoline(67, i + 4+count);
                cout << doctors[n].gender;
                indexes[count] = n;
                count++;
            }
        }
        if (count == 0) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            gotoline(45, i + 5);
            cout << "No Available Doctors";
            Sleep(1000);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 248);
        }
        return count;
    }

    static int printOptions() {
        int i = 4;
        int choice;
        gotoline(50, i + 1);
        cout << "1) Assign Nurse to patient";
        gotoline(50, i + 2);
        cout << "2) Add Medcine for a patient";
        gotoline(50, i + 3);
        cout << "3) Add dosage for a patient";
        gotoline(50, i + 4);
        cout << "4) Return to Login page";

        gotoline(47, i + 6);
        cout << "Select an option: ";
        cin >> choice;

        while (choice < 1 || choice >4) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
            gotoline(47, i + 7);
            printf("Wrong Input!\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            gotoline(65, i + 6);
            cout << "                      ";
            gotoline(65, i + 6);
            cin >> choice;
        }
        return choice;
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

    bool addPatient(Patient patients[], Doctor doctors[]) {
        if (Patient::PatientsCount>= 10) {
            return false;
        }

        string id, name, gender, contact;
        int age;
        int i = 4;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        gotoline(50, i);
        cout << "FILL OUT THE FORM";
        gotoline(52, i + 1);
        cout << "Patient details";

        gotoline(42, i + 3);
        cout << "ID: ";
        gotoline(42, i + 4);
        cout << "Name: ";
        gotoline(42, i + 5);
        cout << "Age: ";
        gotoline(42, i + 6);
        cout << "Gender: ";
        gotoline(42, i + 7);
        cout << "Contact: ";

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 248);
        gotoline(46, i + 3);
        cout << "P-";
        cin >> id;
        gotoline(48, i + 4);
        cin >> name;
        gotoline(47, i + 5);
        cin >> age;
        gotoline(50, i + 6);
        cin >> gender;
        gotoline(51, i + 7);
        cin >> contact;

        int doctorsIndexes[10];
        int availableDoctors = Doctor::printAvailableDoctors(doctors, doctorsIndexes);
        
        if (availableDoctors == 0)
            return false;
        
        int choice, index;
        gotoline(40, 10 + availableDoctors);
        cout << "Select a doctor for the patient: ";
        cin >> choice;
        while (choice < 1 || choice > availableDoctors) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
            gotoline(40, 11+availableDoctors);
            printf("Wrong Input!\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            gotoline(73, 10 + availableDoctors);
            cout << "                      ";
            gotoline(73, 10 + availableDoctors);
            cin >> choice;
        }

        index = doctorsIndexes[choice-1];
        doctors[index].setPatientId("P-"+id);

        //adding patient to file and array
        patients[Patient::PatientsCount] = Patient(id, name, gender, contact, age, doctors[index].getID());
        patients[Patient::PatientsCount].addToFile();
        Patient::incrementCount();

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
        gotoline(50, 12+availableDoctors);
        cout << "RECORD ADDED!";
        Sleep(1000);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);

        return true;
    }

    bool addDoctor(Doctor* doctors) {
        if (Doctor::DoctorsCount >= 10) {
            return false;
        }

        string id, name, password, gender, contact;
        int i = 4;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        gotoline(50, i);
        cout << "FILL OUT THE FORM";
        gotoline(52, i + 1);
        cout << "Doctor details";

        gotoline(42, i + 3);
        cout << "ID: ";
        gotoline(42, i + 4);
        cout << "Name: ";
        gotoline(42, i + 5);
        cout << "Password: ";
        gotoline(42, i + 6);
        cout << "Gender: ";
        gotoline(42, i + 7);
        cout << "Contact: ";

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 248);
        gotoline(46, i + 3);
        cout << "D-";
        cin >> id;
        gotoline(48, i + 4);
        cout << "Dr.";
        cin >> name;
        gotoline(52, i + 5);
        cin >> password;
        gotoline(50, i + 6);
        cin >> gender;
        gotoline(51, i + 7);
        cin >> contact;

        doctors[Doctor::DoctorsCount] = Doctor(id, password, name, gender, contact);
        doctors[Doctor::DoctorsCount].addToFile();
        Doctor::incrementCount();

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
        gotoline(50, i + 9);
        cout << "RECORD ADDED!";
        Sleep(1000);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);

        return true;
    }

    bool addNurse(Nurse nurses[]) {
        if (Nurse::NursesCount >= 10)
            return false;

        string id, name, password, gender, contact;
        int i = 4;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        gotoline(50, i);
        cout << "FILL OUT THE FORM";
        gotoline(52, i + 1);
        cout << "Nurse details";

        gotoline(42, i + 3);
        cout << "ID: ";
        gotoline(42, i + 4);
        cout << "Name: ";
        gotoline(42, i + 5);
        cout << "Password: ";
        gotoline(42, i + 6);
        cout << "Gender: ";
        gotoline(42, i + 7);
        cout << "Contact: ";

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 248);
        gotoline(46, i + 3);
        cout << "N-";
        cin >> id;
        gotoline(48, i + 4);
        cin >> name;
        gotoline(52, i + 5);
        cin >> password;
        gotoline(50, i + 6);
        cin >> gender;
        gotoline(51, i + 7);
        cin >> contact;


        nurses[Nurse::NursesCount] = Nurse(id,password,name,gender,contact);
        nurses[Nurse::NursesCount].addToFile();
        Nurse::incrementCount();

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
        gotoline(50, i + 9);
        cout << "RECORD ADDED!";
        Sleep(1000);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        return true;
    }

    static void incrementCount() {
        AdminsCount++;
    }

    static int printOptions(){
        int i = 4;
        int choice;
        gotoline(50, i + 1);
        cout << "1) Add a doctor";
        gotoline(50, i + 2);
        cout << "2) Add a nurse";
        gotoline(50, i + 3);
        cout << "3) Add a patient";
        gotoline(50, i + 4);
        cout << "4) Return to Login page";

        gotoline(47, i + 6);
        cout << "Select an option: ";
        cin >> choice;

        while (choice < 1 || choice >4) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
            gotoline(47, i + 7);
            printf("Wrong Input!\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            gotoline(65, i + 6);
            cout << "                      ";
            gotoline(65, i + 6);
            cin >> choice;
        }
        return choice;
    }
};

int Doctor::DoctorsCount = -1;
int Nurse::NursesCount = -1;
int Admin::AdminsCount = -1;
int Patient::PatientsCount = -1;

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
        patients[Patient::PatientsCount].readFile(inFile);
    }
    inFile.close();
    return true;
}


void storeData(Doctor doctors[], Nurse nurses[], Admin admins[], Patient patients[]) {
    ifstream outFile;
    outFile.open("Doctor.txt", ios::out | ios::trunc);
    outFile.close();
    outFile.open("Nurse.txt", ios::out | ios::trunc);
    outFile.close();
    outFile.open("Patients.txt", ios::out | ios::trunc);
    outFile.close();
    
    for (int i = 0; i < Doctor::DoctorsCount; i++) {
        doctors[i].addToFile();
    }
    outFile.close();

    for (int i = 0; i < Nurse::NursesCount; i++) {
        nurses[i].addToFile();
    }
    outFile.close();

    for (int i = 0; i < Patient::PatientsCount; i++) {
        patients[i].addToFile();
    }
}

void notificationFunction(Patient* patients)
{

    auto now = chrono::system_clock::now();                                // gets the current time from the system clock
    time_t current_time = chrono::system_clock::to_time_t(now);            /* This line converts the time stored in now to a time_t value, which is a C++ standard library type that represents
                                                                              a point in time uses the to_time_t function*/

    tm ltm;
    localtime_s(&ltm, &current_time);
    string weekdays[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday","Sunday" };
    string current_weekday = weekdays[ltm.tm_wday];


    // Find index of input weekday in weekdays array
    int weekday_index = -1;
    for (int i = 0; i < 7; i++)
    {
        if (weekdays[i].compare(current_weekday) == 0)
        {

            weekday_index = i;
            break;
        }
    }
    while (1)
    {
        for (int i = 0; i < Patient::PatientsCount; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    if (reminder(current_weekday, (patients + i)->medicine[j].dosageTimings[weekday_index][k]))
                    {
                        string name = patients[i].getName();
                        string medName = patients[i].medicine[j].getName();
                        string message = "Please Give" + medName + "To " + name;

                        wchar_t* wideMessage = new wchar_t[message.size() + 1];
                        size_t numCharsConverted = 0;
                        mbstowcs_s(&numCharsConverted, wideMessage, message.size() + 1, message.c_str(), message.size());

                        // Show the message box
                        MessageBox(NULL, wideMessage, L"Message Box", MB_OK);

                        delete[] wideMessage;

                    }
                }
            }
        }
    }


}