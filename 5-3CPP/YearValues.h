#pragma once
class YearValues
{
	public:
		YearValues() {
			totalBalance = 0.0;
			yearsInterest = 0.0;
		}
		YearValues(double newBalance, double newInterest){
			totalBalance = newBalance;
			yearsInterest = newInterest;
		}
		double GetTotalBalance() {
			return totalBalance;
		}
		double GetInterest() {
			return yearsInterest;
		}
		void SetTotalBalance(double value) {
			totalBalance = value;
		}
		void SetInterest(double value) {
			yearsInterest = value;
		}
	private:
		double totalBalance;
		double yearsInterest;
};

