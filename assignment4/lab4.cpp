#include <iostream>
#include <vector>
using namespace std;

// Function to calculate number of redundant bits required
int calculateRedundantBits(int m) {
    int r = 0;
    while ((1 << r) < (m + r + 1)) { // use bit shift instead of pow()
        r++;
    }
    return r;
}

// Function to generate Hamming Code (even parity)
vector<int> generateHammingCode(const string &data) {
    int m = data.length();
    int r = calculateRedundantBits(m);
    int totalLength = m + r;

    vector<int> hamming(totalLength + 1); // 1-indexed
    int j = 0;

    // Insert data bits and leave parity positions empty (1,2,4,8,...)
    for (int i = 1; i <= totalLength; i++) {
        if ((i & (i - 1)) == 0) {    // parity positions
            hamming[i] = 0;
        } else {
            hamming[i] = data[j++] - '0';
        }
    }

    // Calculate parity bits using even parity
    for (int i = 0; i < r; i++) {
        int parityPos = (1 << i);
        int parity = 0;

        for (int k = 1; k <= totalLength; k++) {
            if (k & parityPos) {
                parity ^= hamming[k];
            }
        }
        hamming[parityPos] = parity;
    }

    return hamming;
}

// Function to detect error bit position
int detectError(const vector<int> &received) {
    int n = received.size() - 1;
    int r = 0;

    while ((1 << r) <= n) r++; // count parity bits

    int errorPos = 0;

    for (int i = 0; i < r; i++) {
        int parityPos = (1 << i);
        int parity = 0;

        for (int k = 1; k <= n; k++) {
            if (k & parityPos)
                parity ^= received[k];
        }
        if (parity != 0)
            errorPos += parityPos;
    }

    return errorPos;
}

int main() {
    string data;
    cout << "Enter binary data: ";
    cin >> data;

    vector<int> hamming = generateHammingCode(data);

    cout << "\nGenerated Hamming Code (to be transmitted): ";
    for (int i = 1; i < hamming.size(); i++)
        cout << hamming[i] << " ";
    cout << endl;

    // Simulating receiver
    vector<int> received = hamming;

    // Uncomment to simulate error:
    // received[3] ^= 1;

    int errorPos = detectError(received);

    if (errorPos == 0) {
        cout << "\nReceived Data has NO ERROR." << endl;
    } else {
        cout << "\nError detected at bit position: " << errorPos << endl;
        received[errorPos] ^= 1;

        cout << "Corrected Hamming Code: ";
        for (int i = 1; i < received.size(); i++)
            cout << received[i] << " ";
        cout << endl;
    }

    return 0;
}
