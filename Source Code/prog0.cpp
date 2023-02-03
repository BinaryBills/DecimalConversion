/*Author: Binary Bills
*Creation Date: January 14, 2022
*Modification Date: January 16, 2022
*Purpose: This program converts decimal numbers into binary, hexadecimal, and Binary Coded decimals and outputs its result to a text file and the screen.
The user must provide an input text document named "input.txt" with a list of decimals in the range 0 - 255  they want to convert for the program to achieve its desired task. 
If the user does not provide this file, the program will automatically create its own.
*/

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <fstream>
#include<iomanip>
using namespace std;

void createInputFile();
void formatOutput(ofstream&);
string decToBinary(int);
string decToHex(int);
string decToBCD(int);
string encodeBinary(char[],vector<int>,int,int);

int main()
{
 /***********************************************************
 Creates Output File & begins the Decimal Conversion Process
 ***********************************************************/
	ofstream output("output.txt");
	createInputFile();
	formatOutput(output);
	output.close();
	system("pause");
	return 0;
}

void createInputFile()
{
/******************************************************************************
Checks if Input file exists. If not, it creates its own input of 0-255 decimals.
******************************************************************************/
	ifstream inputFile("input.txt");  
	if (!inputFile.is_open()) //If the user did not provide an input file, the program will create its own input.txt file.
	{
		ofstream inputFile("input.txt");
		for (int i = 0; i < 256; i++)
			inputFile << i << endl;
	}
	inputFile.close();
}


string decToBinary(int dec)
{
/******************************************************************************
 Converts decimal numbers from 0-255 into a 8-bit binary number(Division Method)
******************************************************************************/

//This char array ensures the converted decimal is formatted as a 8-bit binary number. 
	char binaryArr[10] = { '0', '0' , '0', '0' , ' ', '0' , '0' , '0', '0', '\0' };
	int i = 8;
	while (i != -1)
	{
		if (i != 4)
		{
			binaryArr[i] = '0' + dec % 2; //Converts the remainder to a char 
			dec = dec / 2;
		}
		i--;
	}
	return binaryArr; //Returns the charArray as a string 
}

string decToHex(int dec)
{
/*******************************************************************************
 Converts decimal numbers from 0-255 into a hexadecimal number (Division Method)
*******************************************************************************/

//This char array ensures the converted decimal is formatted as a two digit hexadecimal number. 
	char hexArr[3] = { '0', '0' , '\0' };
	int remainder;

	int i = 1;
	while (i != -1)
	{
		remainder = dec % 16;
		dec = dec / 16;

		//If the remainder after dividing the decimal by 16 is 10-15, we will replace the two-digit number with an alphabet.
		if (remainder == 10)
			hexArr[i] = 'A';

		else if (remainder == 11)
			hexArr[i] = 'B';

		else if (remainder == 12)
			hexArr[i] = 'C';

		else if (remainder == 13)
			hexArr[i] = 'D';

		else if (remainder == 14)
			hexArr[i] = 'E';

		else if (remainder == 15)
			hexArr[i] = 'F';
		else //If not, we will convert the number into a char and insert it into our charArray. 
			hexArr[i] = '0' + remainder;
		i--;
	}
	return hexArr; //Returns the charArray as a string 
}

string decToBCD(int dec)
{

/*************************************************************************
  Converts decimal numbers from 0-255 into a BCD Number (Division Method)
**************************************************************************/
	vector<int>decimalDigits; //Stores the extracted digits from each decimal place given a decimal number.
	int temp = dec; //Temp variable used to figure out the number of digits given a decimal number.
	string result;

//Each char array will store a binary encoded number of one of the digits in a given decimal.
	char BCDArr3[6] = { '0', '0' , '0', '0' , ' ', '\0' };
	char BCDArr2[6] = { '0', '0' , '0', '0' , ' ', '\0' };
	char BCDArr1[5] = { '0', '0' , '0', '0' , '\0' };


//This loop allows us to extract the digits from a decimal number left to right(meaning given the decimal "255", 2 is index 0)
	while (temp != 0)
	{
		decimalDigits.push_back(temp % 10);
		temp = temp / 10;
	}

	result = encodeBinary(BCDArr1, decimalDigits, 2, 2) + " " + encodeBinary(BCDArr2, decimalDigits, 1, 1) + encodeBinary(BCDArr3, decimalDigits, 0, 0);

	return result; //Returns the converted decimal as a string 

}

string encodeBinary(char BCDArr[], vector<int> decimalDigits, int index,int size)
{
/*************************************************************************
             Encodes decimal digits into binary numbers
**************************************************************************/

	int i = 3;
	
	if (decimalDigits.size() > size && decimalDigits.at(index) != 0)
	{
		i = 3;
		while (i != -1)
		{
			BCDArr[i] = '0' + decimalDigits.at(index) % 2; //Gets remainder and converts it into a char 
			decimalDigits.at(index) = decimalDigits.at(index) / 2;
			i--;
		}
	}
	return BCDArr;
}




void formatOutput(ofstream& output)
{

/*************************************************************************
 Formats the output to meet the criteria of the assignment's description
**************************************************************************/
	ifstream input("input.txt");
	int decimal;

	cout << setw(15) << "DECIMAL " << setw(15) << " BINARY " << setw(20) << " HEXDECIMAL " << setw(15) << " BCD\n";
	output << setw(15) << "DECIMAL " << setw(15) << " BINARY " << setw(20) << " HEXDECIMAL " << setw(15) << " BCD\n";

	while (input >> decimal)
	{
		cout << setw(11) << decimal << setw(21) << decToBinary(decimal) << setw(14) << decToHex(decimal) << setw(25) << decToBCD(decimal) << endl;
		output << setw(11) << decimal << setw(21) << decToBinary(decimal) << setw(14) << decToHex(decimal) << setw(25) << decToBCD(decimal) << endl;
	}
}