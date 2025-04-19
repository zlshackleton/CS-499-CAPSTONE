// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iomanip>
#include <iostream>
#include <memory>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>

using namespace std;
using namespace CryptoPP;

// Function to hash our secret input using SHA-256 and salt it
string hashData(const string &data, const string &salt) {
	string digest;
	SHA256 hash;
	StringSource ss(data + salt, true, new HashFilter(hash, new HexEncoder(new StringSink(digest))));
	return digest;
}

int main()
{
	cout << "************************" << endl;
	cout << "* Secure Input Program *" << endl;
	cout << "************************" << endl;

	const unsigned int LIMIT = 20;

	// Smart pointer implementation for dynamic char buffer allocation
	unique_ptr<char[]> user_input(new char[LIMIT]);

	cout << "\nEnter secret input: ";
	cin.getline(user_input.get(), LIMIT); //getline() allows the a LIMIT of 20 therefore it will not run if user_input > 20

	// Check for overflow
	if (cin.fail()) {
		cout << "\nERROR: Buffer Overflow... Keep input below 20 characters." << endl;
		return 1;
	}

	string secret(user_input.get());
	cout << "\nYou Entered: " << secret << endl;

	// Generate random salt using Crypto++ library
	AutoSeededRandomPool prng;
	const size_t SALT_SIZE = 16;
	byte saltBytes[SALT_SIZE];
	prng.GenerateBlock(saltBytes, SALT_SIZE);

	// Convert salt to hexidecimal
	string salt;
	StringSource ss(saltBytes, SALT_SIZE, true, new HexEncoder(new StringSink(salt)));

	// Hash secret along with the salt
	string hashedSecret = hashData(secret, salt);

	cout << "\nSalt: " << salt << endl;
	cout << "Hashed Secret: " << hashedSecret << endl;

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Since getline expects and array passed to it we use user_input.get() since it returns a raw pointer to the char array.
// prng is named Pseudo Random Number Generator