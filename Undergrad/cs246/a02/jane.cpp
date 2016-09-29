#include <iostream>
#include <iomanip>
using namespace std;


void printTitle(){ //prints the title row
	cout << "Table of Payments" << endl;
	cout << setw(10) << "Month";
	cout << setw(10) << "Charge";
	cout << setw(10) << "Interest";
	cout << setw(10) << "Payment";
	cout << setw(10) << "Principle" << endl;
}

void printLine(int month, double charge, double interest, double payment, double principle){
	//prints every line of the table using given input
	
	cout << setprecision(0); //nothing after decimal point for month
	cout << setw(10) << month;
	
	cout.setf(ios::fixed); //sets percision to two decimal places for everything else
	cout.setf(ios::showpoint);
	cout.precision(2);
	
	cout << setw(10) << charge;
	cout << setw(10) << interest;
	cout << setw(10) << payment;
	cout << setw(10) << principle << endl;		
}


int main(){
	
	// all the "magic numbers"
	int month = 1;
	const double charge = 0.76;
	const double interest = 0.03; //3% interest, principle * interest = new principle
	double payment = 104.11;
	double principle = 1456.21; //initial price goes here
	const double downPayment = 14.54;
	int nopay = 3; //3 non-payment months
	
	//temporary intermediate variables, makes code clearer
	double interestCharge = 0; //monthly interest charge
		
	printTitle(); //prints top row of the chart
	
	principle = principle-downPayment;
	
	//prints all of the non-payment months
	while (nopay > 0) {
		
		interestCharge = interest*principle;
		principle = principle + interestCharge + charge;
		
		printLine(month, charge, interestCharge, 0.00, principle);
				
		nopay-=1;
		month+=1;
	}
	
	//prints all the payment months
	while (payment <= principle){
		
		interestCharge = interest*principle;
		principle = principle + interestCharge - payment;
		
		printLine(month, 0.00, interestCharge, payment, principle);
		
		month+=1;
	}
	
	// prints the last line
	interestCharge = interest*principle;
	payment = principle + interestCharge;
	printLine(month, 0.00, interestCharge, payment, 0.00);
	
		
}
	
	
	
	
