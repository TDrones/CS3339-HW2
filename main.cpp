#include <iostream> 
#include <bitset>
#include <string>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 3) {
        cout << "usage: " << endl;
        cout << "./fp_overflow_checker loop_bound loop_counter" << endl << endl;
        cout << "loop_bound is a positive floating-point value" << endl;
        cout << "loop_counter is a positive floating-point value" << endl;
        return 1;
    }

    float loopBound = stof(argv[1]);
    float loopCounter = stof(argv[2]);
    
    bitset<32> loopBoundBits(*reinterpret_cast<unsigned int*>(&loopBound));
    bitset<32> loopCounterBits(*reinterpret_cast<unsigned int*>(&loopCounter));

    string boundString = loopBoundBits.to_string();
    string counterString = loopCounterBits.to_string();

    cout << "Loop bound: " << boundString.substr(0,1) << " ";
    cout << boundString.substr(1,8) << " " << boundString.substr(9,23) << endl;
    cout << "Loop counter: " << counterString.substr(0,1) << " ";
    cout << counterString.substr(1,8) << " " << counterString.substr(9,23) << endl;

    //exponents 23-30
    int loopBoundExp = (loopBoundBits.to_ulong() >> 23) & 0xFF;
    int loopCounterExp = (loopCounterBits.to_ulong() >> 23) & 0xFF;

    int difference = loopBoundExp - loopCounterExp;

    if (difference >= 23) {
        cout << "Warning: Possible overflow!" << endl;
        cout << "Overflow threshold:" << endl;

        int thresholdExp = loopCounterExp + 24;
        unsigned int thresholdBitsInt = (unsigned int)(thresholdExp << 23);

        float threshold = *reinterpret_cast<float*>(&thresholdBitsInt);
        cout << threshold << endl;

        bitset<32> thresholdBits(thresholdBitsInt);
        string thresholdString = thresholdBits.to_string();
        cout << thresholdString.substr(0,1) << " ";
        cout << thresholdString.substr(1,8) << " ";
        cout << thresholdString.substr(9,23) << endl;
    }

    else {
        cout << "There is no overflow!" << endl;
    }

    return 0;
}
