#pragma once
#include "Employees.h"


class MedicineAndDosage {
private:
	const unsigned int MedicineID;
	const string MedicineName;

	int weekdays[7][3]; // row number would be the weekday, and each weekday usually has max 3 dosages
						// my approach with this is that each column of the weekday would store the sum of hours and minutes in the 24 hours format

public:
	MedicineAndDosage(const unsigned int id, const string name) : MedicineID(id), MedicineName(name) {

		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				weekdays[i][j] = -1;		//assigning -1 as initial value, so we can compare with -1 if at that day and time a dosage is to be given
			}
			
		}
	}
	

};