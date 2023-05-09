#include "EmployeesAndPatients.h"
#include "MedicineAndDosage.h"
#include <fstream>
#include <iostream>
#include <windows.h>


void printHeader() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 243);
	gotoline(0, 0);
	cout << char(220) << char(219) << char(220) << " e-MediCare";
	gotoline(1, 1);
	cout << char(223);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
}

void intro() {
	gotoline(40, 5);
	cout << "OBJECT ORIENTED PROGRAMMING PROJECT";
	gotoline(52, 7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 243);
	cout << char(220) << char(219) << char(220) << " e-MediCare";
	gotoline(53, 8);
	cout << char(223);
	gotoline(40, 10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 248);
	cout << "Group members: ";
	gotoline(40, 11);
	cout << "- Asfandyar Khanzada (22K-4626)";
	gotoline(40, 12);
	cout << "- Syed Abdullah Bin Tariq (22K-4253)";
	gotoline(40, 13);
	cout << "- Munnazzar Shahzad (22K-4231)";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	cout << endl<< "\npress any key to continue......";
	getchar();
}

class Login {
private:
	int opt;
	Doctor *doctors;
	Nurse *nurses;
	Admin *admins;
	Patient *patients;
	string id;
	string pass;

	bool validAccount() {
		switch (opt) {
		case 1:
			for (int i=0; i < Admin::AdminsCount; i++)
				if (admins[i].validate(id, pass))
					return true;
			return false;
		case 2:
			cout << "DOCTOR LOGIN";
			break;
		case 3:
			cout << "NURSE LOGIN";
			break;
		}
		return false;
	}

	void loginPage() {
		int i = 4;
		system("cls");
		printHeader();
		while (1) {
			gotoline(49, i);
			switch (opt) {
			case 1:
				cout << "ADMIN LOGIN";
				break;
			case 2:
				cout << "DOCTOR LOGIN";
				break;
			case 3:
				cout << "NURSE LOGIN";
				break;
			}
			gotoline(49, i + 1);
			cout << "ID: ";
			cin >> id;
			gotoline(49, i + 2);
			cout << "Password: ";
			cin >> pass;

			if (validAccount()) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
				gotoline(49, i + 3);
				cout << "Login successful";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
				Sleep(1000);
				break;
			}
			system("cls");
			printHeader();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
			i = 5;
			gotoline(49, i-1);
			cout << "Invalid account details\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
		}
	}
public:
	Login(Doctor doctors[], Nurse nurses[], Admin admins[], Patient patients[]): opt(0), id("id"), pass("pass") {
		this->doctors = doctors;
		this->nurses = nurses;
		this->admins = admins;
		this->patients = patients;
	}

	void Initiate(string &id , string &pass) {
		int i = 4;
		gotoline(49, i);
		cout << "You are a: ";
		gotoline(50, i + 1);
		cout << "1) admin";
		gotoline(50, i + 2);
		cout << "2) doctor";
		gotoline(50, i + 3);
		cout << "3) nurse";

		gotoline(47, i + 5);
		cout << "Select an option: ";
		cin >> opt;

		while (opt < 1 || opt >3) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
			gotoline(52, i + 6);
			printf("Wrong Input!\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
			gotoline(64, i + 5);
			cout << "                      ";
			gotoline(65, i + 5);
			cin >> opt;
		}
		this->loginPage();
		id = this->id;
		pass = this->pass;
	}
};

//int loginPage(string id, string pass) {
//	int i = 4, opt;
//	gotoline(49, i);
//	cout << "You are a: ";
//	gotoline(50, i + 1);
//	cout << "1) admin";
//	gotoline(50, i + 2);
//	cout << "2) doctor";
//	gotoline(50, i + 3);
//	cout << "3) nurse";
//
//	gotoline(47, i + 5);
//	cout << "Select an option: ";
//	cin >> opt;
//
//	while (opt < 1 || opt >3) {
//		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
//		gotoline(52, i + 6);
//		printf("Wrong Input!\n");
//		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
//		gotoline(64, i + 5);
//		cout << "                      ";
//		gotoline(65, i + 5);
//		cin >> opt;
//	}
//
//	while (1) {
//
//		system("cls");
//		printHeader();
//		gotoline(49, i);
//		switch (opt) {
//		case 1:
//			cout << "ADMIN LOGIN";
//			break;
//		case 2:
//			cout << "DOCTOR LOGIN";
//			break;
//		case 3:
//			cout << "NURSE LOGIN";
//			break;
//		}
//		gotoline(49, i + 1);
//		cout << "ID: ";
//		cin >> id;
//		gotoline(49, i + 2);
//		cout << "Password: ";
//		cin >> pass;
//
//		if (validAccount()) {
//			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
//			gotoline(49, i + 3);
//			cout << "Login successful";
//			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
//			Sleep(1000);
//			break;
//		}
//		system("cls");
//		printHeader();
//		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
//		gotoline(49, 2);
//		cout << "Invalid account details\n";
//		i = 5;
//		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
//	}
//	return opt;
//}


int main() {
	HANDLE  hConsole;
	system("COLOR F0");
	intro();
	system("cls");
	printHeader();


	Admin admins[10];
	Doctor doctors[10];
	Nurse nurses[10];
	Patient patients[10];

	initializeAll(doctors, nurses, admins, patients);
	string id, pass;

	Login login(doctors, nurses, admins, patients);
	login.Initiate(id,pass);
}


/*fstream file;
	file.open("Admin.txt",  ios::out);
	file.close();
	file.open("Doctor.txt", ios::out);
	file.close();
	file.open("Nurse.txt", ios::out);
	file.close();
	file.open("Patients.txt",ios::out);
	file.close();*/

	//MedicineAndDosage medicine;

	/*Admin admins[10];
	Doctor doctors[10];
	Nurse nurses[10];
	Patient patients[10];

	Admin admin("123", "pass", "admin", "other", "036581");
	initializeAll(doctors, nurses, admins, patients);*/

	//admin.addDoctor(doctors, "iid4", "mr.doc4", "pass4", "male4", "764");
	//admin.addNurse(nurses,"nurse2","gender3","0384","861","dsa2");
	//admin.addDoctor(doctors, "iid2", "mr.doc2", "pass2", "male2", "762");

	//reminder("Sunday", 13, 48);
	//return 0;

	//Admin admins[10];
	//Doctor doctors[10];
	//Nurse nurses[10];
	//Patients patients[10];

	//Admin admin("123", "pass", "admin", "other", "036581");
	//initializeAll(doctors, nurses, admins, patients);




