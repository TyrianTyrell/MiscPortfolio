/*
 *  Airgead Banking App
 *
 *  Date: 2/8/2026
 *  Author: Terrie Banash
 */

#include <string>
#include "YearValues.cpp"
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

void roundToHundredth(double& value) { //QoL function
	value = round(value * 100.0) / 100;
}

vector<double> initializeInput() { //Take in the input variables
	vector<double> inputs = { 0.0, 0.0, 0.0, 0.0 }; //They're all doubles to cut on lines
	cout << "Initial investment amount: $";
	cin >> inputs.at(0);
	roundToHundredth(inputs.at(0)); //This is money, round to hundredths
	cout << endl << "Monthly deposit: $";
	cin >> inputs.at(1);
	roundToHundredth(inputs.at(1)); //This is money, round to hundredths
	cout << endl << "Annual interest: %";
	cin >> inputs.at(2);
	inputs.at(2) /= 100.0; //This is a percentage, divide by 100
	cout << endl << "Number of years: ";
	cin >> inputs.at(3);
	inputs.at(3) = floor(inputs.at(3)); //This is a whole number, ignore the decimal
	cout << endl;
	return inputs;
}

vector<YearValues> calculateResult(vector<double> args, int mode) {
	vector<YearValues> result; //define variables
	int years = args.at(3);
	double total;
	double interest;
	double totalInterest;
	YearValues myYearVals; //Trying to use a getter for an auto-type variable to put into the vector DOESN'T WORK GODDAMNIT
	switch (mode) {
		case 0: // with monthly deposits
			for (int i = 0; i < years; i++) {
				if (i == 0) {
					total = args.at(0) + args.at(1) * 12.0; //Get initial deposit and monthly deposits
					interest = total * args.at(2); //Multiply by interest as percentage
					roundToHundredth(interest);
					myYearVals = YearValues(total + interest, interest); //new pair for vector
				}
				else {
					total = result.at(i - 1).GetTotalBalance() + args.at(1) * 12.0; //Get previous value and add monthly deposits
					interest = total * args.at(2); //Multiply by interest as percentage
					roundToHundredth(interest);
					totalInterest = result.at(i - 1).GetInterest() + interest;  //Get previous amount of interest, add this year's interest
					myYearVals = YearValues(total + interest, totalInterest);  //new pair for vector
				}
				result.push_back(myYearVals); //Add to vector
			}
			break;
		case 1: // without monthly deposits
			for (int i = 0; i < years; i++) {
				if (i == 0) {
					total = args.at(0); //Get initial deposit
					interest = total * args.at(2); //Multiply by interest as percentage
					roundToHundredth(interest);
					myYearVals = YearValues(total + interest, interest); //new pair for vector
				}
				else {
					total = result.at(i - 1).GetTotalBalance(); //Get previous value
					interest = total * args.at(2); //Multiply by interest as percentage
					roundToHundredth(interest);
					totalInterest = result.at(i - 1).GetInterest() + interest; //Get previous amount of interest, add this year's interest
					myYearVals = YearValues(total + interest, totalInterest); //new pair for vector
				}
				result.push_back(myYearVals); //Add to vector
			}
			break;
		default: // otherwise just do fuckall
			break;
	}
	return result;
}

void printResults(vector<YearValues> values) { //Print out results, one by one
	int i = 1;
	for (YearValues pair : values) {
		cout << fixed << setprecision(2) << "Year: " << i << endl << "Balance: $" << pair.GetTotalBalance() << endl << "Total Interest: $" << pair.GetInterest() << endl << endl; 
		i++;
	}
}

void main()
{
	vector<double> values = initializeInput(); //Initialize all the variables
	vector<YearValues> withDeposits = calculateResult(values, 0); //Calculate WITH monthly deposits
	vector<YearValues> withoutDeposits = calculateResult(values, 1); //Calculate WITHOUT deposits
	system("pause"); //Wait for user input to present results
	cout << "Balance and Interest Without Additional Monthly Deposits" << endl << "--------------------------------------------------------" << endl;
	printResults(withoutDeposits); //Present results
	system("pause"); //Wait for user input to present more results
	cout << endl << "Balance and Interest With Additional Monthly Deposits" << endl << "-----------------------------------------------------" << endl;
	printResults(withDeposits); //Present more results
}