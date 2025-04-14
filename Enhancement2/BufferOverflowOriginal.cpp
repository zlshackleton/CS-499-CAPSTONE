// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>

int main()
{
  std::cout << "Buffer Overflow Example" << std::endl;

  // TODO: The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
  //  even though it is a constant and the compiler buffer overflow checks are on.
  //  You need to modify this method to prevent buffer overflow without changing the account_number
  //  variable, and its position in the declaration. It must always be directly before the variable used for input.
  //  You must notify the user if they entered too much data.

  const std::string account_number = "CharlieBrown42";
  const unsigned int LIMIT = 20;

  char user_input[LIMIT];
  std::cout << "Enter a value: ";
  std::cin.getline(user_input, LIMIT); //getline() allows the a limit of 20 therefore it will not run if user_input > 20

  //Fail() returns true when the most recent cin does not run
  if (std::cin.fail()) {
	  std::cout << "\nERROR: Buffer Overflow caused by Invalid Input" << std::endl;
	  std::cout << "\nPlease reduce input to at most 19 characters!" << std::endl;
  }

  else {
	  std::cout << "\nSuccess: Account Created without overflow" << std::endl;
	  std::cout << "\nYou entered: " << user_input << std::endl;
	  std::cout << "\nAccount Number = " << account_number << std::endl;
  }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
