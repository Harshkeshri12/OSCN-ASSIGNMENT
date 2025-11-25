#include <iostream>
#include <fstream>
#include <random>

using namespace std;

struct TCPReno {
    double cwnd;       // Congestion window (in MSS)
    double ssthresh;   // Slow start threshold
    double time;       // Simulation time
    double avgThroughput;
    double lossProb;
    int totalAcks;
    int totalLoss;

    TCPReno(double loss) {
        cwnd = 1.0;
        ssthresh = 64;
        time = 0.0;
        avgThroughput = 0;
        lossProb = loss;
        totalAcks = 0;
        totalLoss = 0;
    }

    bool lossHappens() {
        static random_device rd;
        static mt19937 gen(rd());
        uniform_real_distribution<> dis(0.0, 1.0);
        return dis(gen) < lossProb;
    }

    void simulate(const string &filename) {
        ofstream file(filename);

        int duration = 20; // seconds
        double rtt = 0.1;  // RTT = 100ms

        file << "time,cwnd\n";

        while (time < duration) {
            file << time << "," << cwnd << "\n";

            for (int i = 0; i < (int)cwnd; i++) {
                if (lossHappens()) {
                    totalLoss++;
                    ssthresh = cwnd / 2;
                    cwnd = max(1.0, cwnd / 2);  // Multiplicative Decrease
                    break;
                } else {
                    totalAcks++;
                    if (cwnd < ssthresh) {
                        cwnd += 1; // Slow start (exponential growth)
                    } else {
                        cwnd += 1 / cwnd; // Congestion avoidance (linear)
                    }
                }
            }
            time += rtt;
        }

        avgThroughput = totalAcks / duration;
        file.close();
    }
};

int main() {
    TCPReno sim1(0.001); // 0.1% loss
    TCPReno sim2(0.01);  // 1% loss
    TCPReno sim3(0.02);  // 2% loss

    sim1.simulate("loss_0.1.csv");
    sim2.simulate("loss_1.csv");
    sim3.simulate("loss_2.csv");

    cout << "===== TCP RENO SIMULATION RESULTS =====\n";
    cout << "Loss 0.1% Average Throughput (MSS/sec): " << sim1.avgThroughput << endl;
    cout << "Loss 1%   Average Throughput (MSS/sec): " << sim2.avgThroughput << endl;
    cout << "Loss 2%   Average Throughput (MSS/sec): " << sim3.avgThroughput << endl;

    cout << "\nGenerated CSV files: loss_0.1.csv, loss_1.csv, loss_2.csv\n";
    cout << "You can plot graphs in Excel, Python, or any tool.\n";
}