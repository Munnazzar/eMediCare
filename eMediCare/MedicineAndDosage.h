#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <windows.h>
using namespace std;
void gotoline(int x, int y);

class MedicineAndDosage {
private:
	unsigned int MedicineID;
	char MedicineName[20];

	

public:
	int dosageTimings[7][3]; // row number would be the weekday, and each weekday usually has max 3 dosages
	// my approach with this is that each column of the weekday would store the sum of hours and minutes in the 24 hours format
	bool flag[7][3];

	MedicineAndDosage() {
		MedicineID = -1;
		strcpy_s(MedicineName, "default");
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				dosageTimings[i][j] = -1;		//assigning -1 as initial value, so we can compare with -1 if at that day and time a dosage is to be given
				flag[i][j] = false;			//assigning false as initial flags
			}

		}
	}

	unsigned int getID() {
		return MedicineID;
	}

	MedicineAndDosage(unsigned int id, string MedicineName) : MedicineID(id) {
		strcpy_s(this->MedicineName, 20, MedicineName.c_str());
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				dosageTimings[i][j] = -1;		//assigning -1 as initial value, so we can compare with -1 if at that day and time a dosage is to be given
				flag[i][j] = false;			//assigning false as initial flags
			}

		}
	}

	friend void operator << (ofstream& outfile, MedicineAndDosage& obj);
	friend void operator >> (ifstream& infile, MedicineAndDosage& obj);

	// void addToFile(ofstream& outfile) {
	// 	outfile<<" ";
	// 	outfile.write((char*)this, sizeof(MedicineAndDosage));
	// }


	// void readFile(ifstream& infile) {
	// 	infile.get();
	// 	infile.read((char*)this, sizeof(MedicineAndDosage));
	// }

	//return type conflicts
	bool addDosage(string weekday, int hours, int minute)
	{
		std::string weekdays[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday","Sunday" };

		int indexWeekDay;
		for (int i = 0; i < 7; i++) //checking for the given weekday in string and comparing it to the index of "weekdays" array 
		{
			if (weekday == weekdays[i])
			{
				indexWeekDay = i;		//once given weekday is found, the index for that weekday in the array is stored in "indexWeekDay"
				break;
			}
		}

		bool checkForMaxDosages = false;

		for (int i = 0; i < 3; i++)
		{
			if (dosageTimings[indexWeekDay][i] == -1)		//here it checks for all available slots for the current medicine in the dosages array
			{
				dosageTimings[indexWeekDay][i] = hours * 60 + minute;  //converts time into minutes and stores it in the respective array
				flag[indexWeekDay][i] = false;
				checkForMaxDosages = true;
				break;
			}
		}

		/*cant we set bool as the return type and return checkForMaxDosages instead of this if statement*/
//		if (!checkForMaxDosages)
//		{
//			return; // here i want a cout statement that says, max dosages in a day for this medicine reached already
//		}
		return checkForMaxDosages;
	}

	
	void display() {
		cout << "id: " << MedicineID;
		cout << ", Name: " << MedicineName << endl;
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				cout << dosageTimings[i][j] << " " << flag[i][j] << "\t";
			}
			cout << endl;
		}
	}

	void Display(string weekday) {
		int k = 4, j=0, l;
		string weekdays[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday","Sunday" };
		int indexWeekDay=0;
		for (int i = 0; i < 7; i++) //checking for the given weekday in string and comparing it to the index of "weekdays" array 
		{
			if (weekday == weekdays[i])
			{
				indexWeekDay = i;		//once given weekday is found, the index for that weekday in the array is stored in "indexWeekDay"
				break;
			}
		}

		if ((dosageTimings[indexWeekDay][0] == -1) && (dosageTimings[indexWeekDay][1] == -1) && (dosageTimings[indexWeekDay][2] == -1)) {
			gotoline(40, 6);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
			cout << "No dosages are assigned to this patient!";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
			Sleep(1000);
			return;
		}

		for (int i = 0; i < 7; i++)
		{
			if (i == indexWeekDay) {
				gotoline(57, k + 4);
				cout << weekdays[i];
				gotoline(43, k + 5 + j);
				cout << "-------------------------------------";
				gotoline(45, k + 7);
				cout << "Medicine Id: " << MedicineID;
				gotoline(45, k + 8);
				cout << "Medicine Name: " << MedicineName << endl;
				for (j = 0; j < 3; j++)
				{
					if (flag[i][j] != 0 && (dosageTimings[i][j] != -1)) {
						gotoline(45, k + 10 + j);
						cout << "SLOT " << j + 1 << ": " << (dosageTimings[i][j] / 60) << ":" << dosageTimings[i][j] - ((dosageTimings[i][j] / 60)*60) << "    Medicine Has Been Given";
					}
					else if (dosageTimings[i][j] == -1) {
						gotoline(45, k + 10 + j);
						cout << "SLOT " << j+1 << ": " << "Not Alloted" << "    Medicine Not Given";
					}
					else if (flag[i][j] == 0) {
						gotoline(45, k + 10 + j);
						cout << "SLOT " << j + 1 << ": " << (dosageTimings[i][j] / 60) << ":" << dosageTimings[i][j] - ((dosageTimings[i][j] / 60) * 60) << "    Medicine Not Given";
					}
				}
			}
			k += j;
			cout << endl;
		}
		gotoline(45, 17);
		cout << "Select Dosage: ";
		cin >> l;

		if (dosageTimings[indexWeekDay][l - 1] == -1)
		{
			gotoline(45, 18);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
			cout << "Dosage not allocated to the patient....\n";
			Sleep(1000);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
			return;
		}

		if (flag[indexWeekDay][l - 1] == true)
		{
			gotoline(45, 18);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
			cout << "Dosage already given to the patient....\n";
			Sleep(1000);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
			return;
		}
		else {
			flag[indexWeekDay][l - 1] = true;
			gotoline(45, 18);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
			cout << "You gave the medicine to patient....\n";
			Sleep(1000);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
		}
	}

	string getName(void) { return this->MedicineName; }
};

void operator << (ofstream& outfile, MedicineAndDosage& obj) {
	outfile << " ";
	outfile.write((char*)&obj, sizeof(MedicineAndDosage));
}


void operator >> (ifstream& infile, MedicineAndDosage& obj) {
	infile.get();
	infile.read((char*)&obj, sizeof(MedicineAndDosage));
}