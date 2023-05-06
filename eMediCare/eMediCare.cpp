#include "Employees.h"
#include "MedicineAndDosage.h"
#include <fstream>
#include <iostream>

int main() {
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

	Admin admins[10];
	Doctor doctors[10];
	Nurse nurses[10];
	Patients patients[10];

	Admin admin("123", "pass", "admin", "other", "036581");
	initializeAll(doctors, nurses, admins, patients);

		//admin.addDoctor(doctors, "iid4", "mr.doc4", "pass4", "male4", "764");
		//admin.addNurse(nurses,"nurse2","gender3","0384","861","dsa2");
		//admin.addDoctor(doctors, "iid2", "mr.doc2", "pass2", "male2", "762");

	doctors[0].display();
	doctors[1].display();
	doctors[2].display();
	doctors[3].display();
	doctors[4].display();
	nurses[0].display();
	cout << endl << Doctor::DoctorsCount;
	return 0;
}