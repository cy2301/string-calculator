#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout, std::endl, std::string;

unsigned int digit_to_decimal(char digit) {
	// char to int
	if (!isdigit(digit))
	{
		throw std::invalid_argument("Character entered is not a digit.");
	}
	return digit - '0';
}

char decimal_to_digit(unsigned int decimal) {
	if (decimal > 9)
	{
		throw std::invalid_argument("Decimal entered is greater than 9 or less than 0.");
	}
	return decimal + '0';
}

string trim_leading_zeros(string num) {
	bool wasNeg = false;
	string result = "";
	if (num.find("-") != string::npos) // Number represented is negative
	{
		wasNeg = true;
		num.erase(0,1); // initially delete the negative sign
	}
	size_t i = 0;
	while (num.at(i) == '0')
	{
		i++;
		if (i == num.length()) // if the number entered consists soley of 0's
		{	
			return "0";
		}
	}
	while (i != num.length())
	{
		result += num.at(i);
		i++;
	}
	if (wasNeg)
	{
		result.insert(0,"-");
	}
    return result;
}

string add(string lhs, string rhs) {
	// Important variables
	int carryOver = 0;
	int leftSide = 0;
	int rightSide = 0;
	int sumOfLeftAndRight = 0;
	string result = "";
	
	// Condition variables
	bool carryOverExists = true;
	bool negFound = false;
	
	// Iteration variables
	int leftIterate = lhs.length()-1;
	int rightIterate = rhs.length()-1;

	// Dealing with negatives

	if( (lhs.find('-') != string::npos && rhs.find('-') != string::npos) ||  // both are negative
		(rhs.find('-') != string::npos && lhs.find('0') == 0) ||  // right is negative, left is 0
		(lhs.find('-') != string::npos && rhs.find('0') == 0) // right is 0, left is negative
	  ) 
	{ 
		lhs.erase(0,1);  // deletes negative sign so digit to decimal will have no issues
		rhs.erase(0,1);
		negFound = true;  // marked as a negative number so it will be added back at the end
		leftIterate -= 1;  // accounts for deleted part, length has to be subtract 1 or be out of range
		rightIterate -= 1;
	}
	else if (lhs.find('-') != string::npos && rhs.find('-') == string::npos) // if left is neg and right is not
	{
		lhs.erase(0,1);
		result = subtract(lhs,rhs);
		if ((lhs.length() == rhs.length() && rhs > lhs) || lhs.length() < rhs.length())
			result.erase(0,1);
		else
			result.insert(0,"-");
		return trim_leading_zeros(result);
	}

	else if (lhs.find('-') == string::npos && rhs.find('-') != string::npos) // left is positive and right is negative, simply subtract
	{ 
		rhs.erase(0,1);
		result = subtract(lhs,rhs);
		if ((lhs.length() == rhs.length() && rhs < lhs) || lhs.length() > rhs.length()) // conditions for the result to be positive
		{
			if (result.find('-') != string::npos)
				result.erase(0,1);
		} 
		return result;
	}

	while (carryOverExists) {
		if (leftIterate >= 0) // if the left iteration is not negative (not out of range), then we grab the furthest right number available
		{  
			leftSide = digit_to_decimal(lhs.at(leftIterate));
		}
		if (rightIterate >= 0) 
		{
			rightSide = digit_to_decimal(rhs.at(rightIterate));
		}
		if (leftIterate < 0) // if left iteration goes below 0, left side will always be 0 (no numbers there)
		{
			leftSide = 0;
		} 
		if (rightIterate < 0) 
		{
			rightSide = 0;
		}
		sumOfLeftAndRight = leftSide + rightSide + carryOver; // carry over is 1, added on, if not then it is 0
		carryOver = 0; // resets carry over for next iteration
		
		if (sumOfLeftAndRight >= 10) // if the sum is greater than 10, then there is a carry over
		{
			sumOfLeftAndRight = sumOfLeftAndRight % 10;
			result += decimal_to_digit(sumOfLeftAndRight);
			carryOver = 1;
		} 
		else if (leftIterate < 0 && rightIterate < 0) // if both iterations are less than 0, there's nothing left in the strings
		{
			carryOverExists = false;  // ends the loop
			result += decimal_to_digit(sumOfLeftAndRight);
		} 
		else // only one is less than 0 or both still have some to go
		{
			result += decimal_to_digit(sumOfLeftAndRight);
		}
		leftIterate -= 1; // iterates through left string
		rightIterate -= 1;
	}
    string finalResult = "";
	int i = result.length() - 1; // result string is currently backwards due to push_back, this will mirror it
	while (i >= 0)
	{
		finalResult += result.at(i);
		i -= 1;
	}
	finalResult = trim_leading_zeros(finalResult);
	if (negFound) // if a negative existed before, we simply slap it back in 
	{
		finalResult.insert(0,"-");
	}
	return finalResult;
}

string subtract(string lhs, string rhs) {
    // Important variables
	int negativeCarryOver = 0;
	int leftSide = 0;
	int rightSide = 0;
	int leftMinusRight = 0;
	string temp = "";
	string result = "";
	string addResult = "";
	
	// Condition variables
	bool carryOverExists = true;
	bool negFound = false;
	
	// Iteration variables
	int leftIterate = lhs.length()-1;
	int rightIterate = rhs.length()-1;

	// Dealing with negatives

	if (lhs.find('-') != string::npos && rhs.find('-') != string::npos) {  // if both are negative
		lhs.erase(0,1);  // delete the negative signs
		rhs.erase(0,1);
		leftIterate -= 1;  // iterate to account for deletion
		rightIterate -= 1;
		if ((lhs.length() == rhs.length() && rhs >= lhs) || rhs.length() > lhs.length()) 
		{  // if the right hand side is >= left hand side, then the result will be positive. Ex: -5 - (-10), note -5 > -1 when comparing strings
			lhs.swap(rhs);
			std::swap(leftIterate,rightIterate);
		}
		else // final result is negative
			negFound = true;
	}

	else if (lhs.find('-') == string::npos && rhs.find('-') == string::npos) // both are positive
	{
		if ((lhs.length() == rhs.length() && rhs > lhs) || rhs.length() > lhs.length()) // if the right hand side is > left hand side, the result will be negative
		{   // swap them and slap on the negative at the end. Otherwise, we don't have to do anything
			negFound = true;
			lhs.swap(rhs);
			std::swap(leftIterate,rightIterate);
		}
	}

	else if (lhs.find('-') != string::npos && rhs.find('-') == string::npos) // left is negative and right is not
	{
		lhs.erase(0,1);
		result = add(lhs,rhs);
		result.insert(0,"-");
		return result;
	} 
	else if (lhs.find('-') == string::npos && rhs.find('-') != string::npos) // right is negative, left is not
	{
		rhs.erase(0,1);
		result = add(lhs,rhs);
		return result;
	}
	
	while (carryOverExists) {
		if (leftIterate >= 0) // if the left iteration is not negative (not out of range)
		{
			leftSide = digit_to_decimal(lhs.at(leftIterate));
		}
		if (rightIterate >= 0) 
		{
			rightSide = digit_to_decimal(rhs.at(rightIterate));
		}
		if (leftIterate < 0) // if left iteration goes below 0, left side will always be 0 (no numbers there)
		{
			leftSide = 0;
		} 
		if (rightIterate < 0) 
		{
			rightSide = 0;
		}
		leftMinusRight = leftSide - rightSide - negativeCarryOver;
		if (leftMinusRight < 0) 
		{
			leftMinusRight = (leftSide + 10) - rightSide - negativeCarryOver;
			result += decimal_to_digit(leftMinusRight);
			negativeCarryOver = 1;
		} 
		else if (leftIterate < 0 && rightIterate < 0) // if both iterations are less than 0, there's nothing left in the strings
		{
			carryOverExists = false;  // ends the loop
			result += decimal_to_digit(leftMinusRight);
		} 
		else 
		{
			negativeCarryOver = 0;
			result += decimal_to_digit(leftMinusRight);
		}
		leftIterate -= 1;  // iterates through left string
		rightIterate -= 1;
	}
    string finalResult = "";
	int i = result.length() - 1;
	while (i >= 0) // reverses the appending
	{
		finalResult += result.at(i);
		i -= 1;
	}
	finalResult = trim_leading_zeros(finalResult);
	if (negFound) // if a negative existed before, we simply slap it back in
	{
		finalResult.insert(0,"-");
	}
	return finalResult;
}

string multiply(string lhs, string rhs) {
	int topSide = 0;
	int bottomSide = 0;
	int product = 0;
	int carryOver = 0;
	string result = "";
	bool negFound = false;
	
	if (rhs.length() < lhs.length())  // swap them so the bigger number is on top
	{
		swap(lhs,rhs);
	}
	if (lhs.find('-') != string::npos && rhs.find('-') != string::npos) // if both are negative, it's ok because result is pos
	{
		rhs.erase(0,1);  // deletes the negative
		lhs.erase(0,1);
	}
	else if (rhs.find('-') != string::npos && lhs.find('-') == string::npos) // right is negative left positive
	{
		rhs.erase(0,1);
		negFound = true;  // negFound is so we can slap a negative on at the end
	}
	else if (lhs.find('-') != string::npos && rhs.find('-') == string::npos) // left is negative, right positive
	{
		lhs.erase(0,1);
		negFound = true;
	}
    string sum = "0";
	int counter = 1;
	for (int i = lhs.length() - 1; i >= 0; i--)  // nested for loop, one for the bigger number (top number) and one for the smaller number (bottom)
	{
		for (int j = rhs.length() - 1; j >= 0; j--)
		{
			topSide = digit_to_decimal(rhs.at(j));
			bottomSide = digit_to_decimal(lhs.at(i));
			
			product = topSide * bottomSide + carryOver;
			carryOver = 0;  // resets carryOver so we don't get same carry over each iteration
			
			if (product >= 10)  // carry over exists
			{
				if (j == 0) 
				{  
				// if we're at the end of the big number, then there's nothing to add carry over to, so we append the entire thing
					int loopProduct = product;
					while (loopProduct != 0) 
					{
						result += decimal_to_digit(loopProduct % 10);  // append last digit then the next digit
						loopProduct /= 10;
					}
				}
				else 
				{
					carryOver = product / 10;  // only append last digit and add the next digit as carry over
					result += decimal_to_digit(product % 10);
				}
			}
			else 
			{
				result += decimal_to_digit(product);  // no carry over, simply append it
			}
		}
		int j = result.length()-1;  // reverses the result since it's currently backwards
		string newResult = "";
		while (j >= 0)
		{
			newResult += result.at(j);
			j--;
		}
		sum = add(sum,newResult);  // add the sum to the normal result (not the reversed one) each time
		result = "";
		for (int k = 0; k < counter; k++)  // number of zeroes to add is equal to the outer loop (add one zero after first iteration (first row))
			result += "0";
		counter++;  // increments the counter so we know the next iteration will need 2 zeroes (second row)
	}
	if (negFound) 
	{
		sum.insert(0,"-");
	}
	return sum;
}

string numTimes(string lhs, string result) {
	if (lhs == result)
		return "1";
	if (result == "0" || compare(lhs,result)) // if lhs > result, ie: 5 and 2, then return 0
		return "0";
	string i = "1";
 	string product = multiply(lhs,i);
	while (!compare(product,result)) // while (product is less than the result)
	{
		i = add(i,"1");
		product = multiply(lhs,i);
	}
	if (product == result) // bandaid solution (i is 1 too much i product > result at the end)
		return i;
	return subtract(i,"1");
}

bool compare (string lhs, string rhs) { // true if lhs > rhs
	if (lhs.length() > rhs.length()) // if they're different lengths
		return true;
	if (rhs.length() > lhs.length())
		return false;
	string a = "";
	string b = "";
	for (size_t i = 0; i < lhs.length(); i++) // compares digit by digit
	{
		a = lhs.at(i);
		b = rhs.at(i);
		if (stoi(a) < stoi(b))
			return false;
		if (stoi(a) > stoi(b))
			return true;
	}
	return true;
}

string division(string dividend, string divisor) {
	if (divisor == "0")
		throw std::invalid_argument("Error: Division by 0.");
	if (dividend == "0")
		return "0";
	string quotient = ""; // result
	string factorTimes = "0";
	string dividendParse = "";
	bool negFound = false;
	if (dividend.find("-") != string::npos && divisor.find("-") != string::npos) // both are negative, result will be positive
	{
		dividend.erase(0,1);
		divisor.erase(0,1);
	}
	else if (dividend.find("-") != string::npos && divisor.find("-") == string::npos) // dividend is negative, result will be negative
	{
		dividend.erase(0,1);
		negFound = true;
	}
	else if (dividend.find("-") == string::npos && divisor.find("-") != string::npos)
	{
		divisor.erase(0,1);
		negFound = true;
	}
	size_t origLength = dividend.length();
	for (size_t i = 0; i < origLength; i++)
	{
		dividendParse.push_back(dividend.at(i)); // essentially dragging down the next number
		//cout << "dividendParse: " << dividendParse << endl;
		factorTimes = numTimes(divisor,dividendParse); // how many times divisor goes into that part of the dividend
		//cout << "numTimes: " << factorTimes << endl;
		//cout << "divisor * numTimes: " << multiply(divisor,factorTimes) << endl;
		if (factorTimes == "0") // not factorable
		{
			quotient.append("0");
			continue;
		}
		quotient.append(factorTimes);
		dividendParse = subtract(dividendParse,multiply(divisor,factorTimes));
		//cout << "dividendParse after subtract: " << dividendParse << endl << endl;
		if (dividendParse == "0")
		{
			dividendParse = ""; // resets dividendParse
		}
	}
	if (negFound)
		quotient.insert(0,"-");
	return trim_leading_zeros(quotient);
}

string modulus(string dividend, string divisor) {
	return subtract(dividend,multiply(division(dividend,divisor),divisor));
}
