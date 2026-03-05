#include <iostream> 
#include <bitset>
#include <string>
#include <cstdlib>
using namespace std;

// Programs checks for floating-point overflow in a loop comparing exponents of loop bound and loop counter
int main(int argc, char* argv[]) {

    // Checks for correct number of arguments!
    if (argc != 3) {
        cout << "usage: " << endl;
        cout << "./fp_overflow_checker loop_bound loop_counter" << endl << endl;
        cout << "loop_bound is a positive floating-point value" << endl;
        cout << "loop_counter is a positive floating-point value" << endl;
        return 1;   // Exits
    }

    float loopBound = stof(argv[1]);    // Initializes loopBound as a float from the first arg
    float loopCounter = stof(argv[2]);  // Initializes loopCounter as a float from the second arg
    
    bitset<32> loopBoundBits(*reinterpret_cast<unsigned int*>(&loopBound)); // Gives 32-bit IEEE as unsigned int, converts to bitset
    bitset<32> loopCounterBits(*reinterpret_cast<unsigned int*>(&loopCounter)); // Gives 32-bit IEEE as unsigned int, converts to bitset

    string boundString = loopBoundBits.to_string(); // Converts bitset to string
    string counterString = loopCounterBits.to_string(); //Converts bitset to string

    // Output sign, exponent, and mantissa for loop bound and loop counter
    cout << "Loop bound: " << boundString.substr(0,1) << " ";
    cout << boundString.substr(1,8) << " " << boundString.substr(9,23) << endl;
    cout << "Loop counter: " << counterString.substr(0,1) << " ";
    cout << counterString.substr(1,8) << " " << counterString.substr(9,23) << endl;

    // Exponent bits shifted to the right
    int loopBoundExp = (loopBoundBits.to_ulong() >> 23) & 0xFF;
    int loopCounterExp = (loopCounterBits.to_ulong() >> 23) & 0xFF;

    int difference = loopBoundExp - loopCounterExp; // Difference between exp

    // Checks if difference is greater or equal to 23, if so possible overflow
    if (difference >= 23) {
        cout << "Warning: Possible overflow!" << endl;
        cout << "Overflow threshold:" << endl;

        int thresholdExp = loopCounterExp + 24; // Threshold exp
        unsigned int thresholdBitsInt = (unsigned int)(thresholdExp << 23); // Shifts exp left by 23 to get threshold bits

        float threshold = *reinterpret_cast<float*>(&thresholdBitsInt); // Threshold bits reinterpreted as float
        cout << threshold << endl; // Output threshold value

        
        bitset<32> thresholdBits(thresholdBitsInt); // Stores in bitset to output
        string thresholdString = thresholdBits.to_string(); // Converts bitset to string
        cout << thresholdString.substr(0,1) << " "; // Output sign bit
        cout << thresholdString.substr(1,8) << " "; // Output exponent bits
        cout << thresholdString.substr(9,23) << endl; // Output mantissa bits
    }

    else {
        cout << "There is no overflow!" << endl; // Less than 23, no overflow
    }

    return 0;  // Exits
}
