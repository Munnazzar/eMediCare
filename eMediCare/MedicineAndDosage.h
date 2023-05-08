#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <string.h>
using namespace std;

class MedicineAndDosage{
private:
	unsigned int MedicineID;
	char MedicineName[20];

	int dosageTimings[7][3]; // row number would be the weekday, and each weekday usually has max 3 dosages
	// my approach with this is that each column of the weekday would store the sum of hours and minutes in the 24 hours format
	bool flag[7][3];

public:
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

	void addToFile(ofstream& outfile) {
		outfile.write((char*)this, sizeof(MedicineAndDosage));
	}
	void readFile(ifstream& infile) {
		infile.read((char*)this, sizeof(MedicineAndDosage));
	}
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
				checkForMaxDosages = true;
				break;
			}
		}

		/*cant we set bool as the return type and return checkForMaxDosages instead of this if statement*/
		if (!checkForMaxDosages)
		{
			cout << "here i want a cout statement that says, max dosages in a day for this medicine reached already" << endl;
			return 0; 
		}
	}
};
