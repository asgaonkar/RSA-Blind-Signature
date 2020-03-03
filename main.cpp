/*

Project Members: 

1. Jaswant Pakki - 1208755310
2. Atit Gaonkar	 - 1217031322

*/

#include <stdio.h> 
#include <stdlib.h> 
#include <array>
#include <iostream>
#include <random>
#include <cmath>

#include "RSA.h"
#include "BigInt.h"

#define RAND_LIMIT32 0x7FFFFFFF

using namespace RSAUtil;
using namespace std;

int main(int argc, char *argv[])
{
	
	cout<<"Blind Signature";

	/*
	Step 01: Alice obtains the public key and Modulus N of the person (Bob) who is to sign the message
	*/
	RSA Bob;

	//cout<<"\nPublic Key (N): "<<Bob.getModulus().toHexString();
	//cout<<"\nPublic Key (E): "<<Bob.getPublicKey().toHexString();

	/*
	Step 02: Obtain a random number and its inverse with respect to the Modulus [Not phi] of Bob
	*/
	srand(time(0));
	BigInt rand = std::rand();
	//printf("\nRandom: %x",rand);
	cout<<"\nRandom Number: "<<rand.toHexString();

	//Step 03: Alice obtains/generates a message to be signed. 

	BigInt message = (random()%RAND_LIMIT32);

	//printf("\nMessage: %x",message);
	cout<<"\nMessage: "<<message.toHexString();

	/*
	Step 04: Alice encrypts the random number with the public key. 
	Step 05: Alice multiplies this value by the message.
	Step 06: Alice then takes a modulus over N
	*/
	
	RSA *rsa_bob = &Bob;
	BigInt after_mul = (rsa_bob->encrypt(rand) * message) % rsa_bob->getModulus();

	//printf("\nAfter Multiplied: %x",after_mul);
	cout<<"\nAfter Multiplied: "<<after_mul.toHexString();

	/*
	Step 07: Alice sends it to Bob
	Step 08: Bob simply decrypts the received value with the private key
	*/
	BigInt blind_sig = Bob.decrypt(after_mul);
	//printf("\nBlind Signature: %x",blind_sig);
	cout<<"\nBlind signature: "<<blind_sig.toHexString();


	/*
	Step 09: Bob sends it back to Alice
	Step 10: Alice then multiplied the received value with the inverse and takes a modulus over N.
	*/
	BigInt sig = (blind_sig * modInverse(rand, Bob.getModulus())) % Bob.getModulus();
	//printf("\nSignature: %x",sig);
	cout<<"\nSignature: "<<sig.toHexString();


	/*
	Step 11: To obtain the original message from it, again encrypt it with Bob’s Public Key.
	*/
	cout<<"\nVerify: "<<message.toHexString()<<" & "<<Bob.encrypt(sig).toHexString();
	//printf("\nVerify: %x & %x",message,sig);
	
	cout<<"\n";
	return 0;
}
