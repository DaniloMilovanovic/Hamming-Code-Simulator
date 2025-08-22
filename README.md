# Hamming Code Simulator

A C++ console application that simulates the encoding, transmission with a single-bit error, and decoding of data using a Hamming code. This project was created as a homework assignment for the "Basics of Telecommunications" course.
Features

# How Hamming Code Works

The Hamming code is a linear error-correcting code that can detect and correct single-bit errors. The code works by adding multiple parity (control) bits to the original information word. 
These bits are calculated from and protect overlapping subsets of the data bits.
 - Information Bits: The original data to be transmitted.
 - Control Bits: Parity bits placed at positions that are powers of two (1, 2, 4, 8, ...).
 - Parity Bit (Optional): An additional overall parity bit for the entire code word, providing an extra layer of error detection.

When an error occurs, the calculated control sums form a syndrome that points directly to the position of the faulty bit, allowing for its correction.


# Core Logic Functions:

**encodeInformationWord()**: Encodes the information word into a Hamming code word.

**alterBit()**: Flips a bit at a given position to simulate an error.

**calculateControlSum()**, **calculateParitySum()**: Calculate the syndromes for error detection.

**decodeInformationWord()**: Extracts the original information word from the corrected code word.

# Getting Started
## Prerequisites

A C++ compiler (e.g., GCC, Clang, MSVC)

A terminal or command prompt to run the console application

## Compilation

To compile the program, navigate to the source directory and run:
bash

g++ -o HammingSimulator TelekomDomaci.cpp

This will create an executable named HammingSimulator.

## Usage

Run the executable:

./HammingSimulator

## Test the Simulation:

Follow the on-screen prompts:

Enter the length of the coded word: The total length of the Hamming code word (n), must be ≤ 31.

Do you want a parity bit? [y/n]: Type 'y' for yes or 'n' for no.

The program will then display the calculated information word length.

Enter the information word: Provide a binary string of the correct length (e.g., 1011).

Enter the changed bit position: Specify which bit (1 to n) should be flipped to simulate an error.

The program will output: The original sent information and code words, the received code word (with the error), the calculated control and parity sums and the corrected information and code words after error correction.

You can run this simulation multiple times with different information words and error positions without restarting the program.

# Example Run

Enter the length of the coded word: 7
Do you want a parity bit? [y/n]n
Coded word length:7
Information word length: 4

Enter the information word (in binary format): 1101
Enter the changed bit position: 3
Sent information word: 1101
Sent coded word: 1010101
Received coded word: 1000101
Control sum: 3
Parity sum: 0
Corrected information word: 1101
Corrected coded word: 1010101

# Limitations

The code word length is currently limited to a maximum of 31 bits as per the assignment requirements, though the code is written to potentially handle larger sizes.
Only single-bit errors are simulated and corrected. This simulator does not handle multi-bit errors.
