#include <iostream>
#include <string>
using namespace std;

// Function to perform XOR division and find remainder
string xorDivision(string data, string generator) {
    int n = generator.length();
    string temp = data.substr(0, n);

    while (n <= data.length()) {
        if (temp[0] == '1') {
            for (int i = 1; i < generator.length(); i++)
                temp[i] = (temp[i] == generator[i]) ? '0' : '1';
        }
        temp.erase(0, 1);
        if (n < data.length())
            temp += data[n];
        n++;
    }
    return temp;
}

int main() {
    string data = "1101011011";
    string generator = "10011"; // x^4 + x + 1

    // Append zeros equal to degree of generator
    int m = generator.length() - 1;
    string appendedData = data + string(m, '0');

    // Get remainder using XOR division
    string remainder = xorDivision(appendedData, generator);

    // Transmitted message = data + remainder
    string transmitted = data + remainder;

    cout << "Original Data: " << data << endl;
    cout << "Generator: " << generator << endl;
    cout << "Remainder: " << remainder << endl;
    cout << "Transmitted Data: " << transmitted << endl;

    return 0;
}
