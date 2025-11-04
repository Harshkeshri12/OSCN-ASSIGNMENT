#include <iostream>
#include <string>
using namespace std;

string xor1(string a, string b) {
    string result = "";
    for (int i = 1; i < b.length(); i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

string mod2div(string dividend, string divisor) {
    int pick = divisor.length();
    string tmp = dividend.substr(0, pick);
    int n = dividend.length();

    while (pick < n) {
        if (tmp[0] == '1')
            tmp = xor1(divisor, tmp) + dividend[pick];
        else
            tmp = xor1(string(pick, '0'), tmp) + dividend[pick];
        pick++;
    }

    if (tmp[0] == '1')
        tmp = xor1(divisor, tmp);
    else
        tmp = xor1(string(pick, '0'), tmp);

    return tmp;
}

int main() {
    string data = "10011101";
    string divisor = "1001";  // x^3 + 1

    // Step 1: Append zeros
    string appended_data = data + string(divisor.length() - 1, '0');

    // Step 2: Get remainder
    string remainder = mod2div(appended_data, divisor);

    // Step 3: Form transmitted code
    string transmitted = data + remainder;

    cout << "Original Data:         " << data << endl;
    cout << "Generator:             " << divisor << endl;
    cout << "Appended Data:         " << appended_data << endl;
    cout << "CRC Remainder:         " << remainder << endl;
    cout << "Transmitted Codeword:  " << transmitted << endl;

    // Step 4: Simulate error (invert 3rd bit)
    string received = transmitted;
    received[2] = (received[2] == '0') ? '1' : '0'; // flip 3rd bit
    cout << "\nReceived (with error): " << received << endl;

    // Step 5: Check remainder at receiver
    string remainder_receiver = mod2div(received, divisor);
    cout << "Remainder at Receiver: " << remainder_receiver << endl;

    if (remainder_receiver.find('1') != string::npos)
        cout << "Error detected during transmission!" << endl;
    else
        cout << "No error detected." << endl;

    return 0;
}