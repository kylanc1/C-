#include <iostream>
#include <iomanip>
using namespace std;

void bubbleSort(double grades[], int numofgrades);

int main(void) {
	double *grades, //dynamically allocate array
		total = 0.0,
		average; // hold average of grades score
	int numofgrades, //hold the ammount of grades
		count; //Counter

	//Number of Grades
	cout << "How many Grades are there? " << endl;
	cin >> numofgrades;

	//Dynamically allocate array
	grades = new double[numofgrades];

	//Get Grades
	cout << "Enter the Grades below. (Non-Negative)" << endl;
	for (count = 0; count < numofgrades; count++) {
		cout << "Grade " << (count + 1) << ": ";
		cin >> grades[count];
	}

	//Total
	for (count = 0; count < numofgrades; count++) {
		total += grades[count];
	}

	//Average
	average = total / numofgrades;

	//Output Results to user
	cout << fixed << showpoint << setprecision(2);
	cout << "Average Grade: " << average << endl;

	cout << "Grades (Sorted in Ascending Order):" << endl;
	bubbleSort(grades, numofgrades);
	for (count = 0; count < numofgrades; count++) {
		cout << "Grade " << (count + 1) << ": " << grades[count] << endl;
	}


	//Free dynamically allocated memory
	delete[] grades;
	grades = 0; //Make grades point to null.
	cin.ignore(INT_MAX, '\n');
	cin.ignore(INT_MAX, '\n');

	return 0;
}


void bubbleSort(double grades[], int numofgrades) {
	bool exchanges;
	do {
		exchanges = false; // assume no exchanges
		for (int i = 0; i < numofgrades - 1; i++) {
			if (grades[i] > grades[i + 1]) {
				double temp = grades[i];
				grades[i] = grades[i + 1];
				grades[i + 1] = temp;
				exchanges = true; // after exchange
			}
		}
	} while (exchanges);
}