//Fedchuk Sofiia k-26, variant 22
#include <iostream>
#include <string>
#include <future>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

mutex coutMutex;

void compute(const string& name, int seconds) {
    this_thread::sleep_for(chrono::seconds(seconds));
    lock_guard<mutex> lock(coutMutex);
    cout << name << " done" << endl;
}

void quick(const string& name) { compute(name, 1); }
void slow(const string& name)  { compute(name, 7); }

void work() {
    cout << "Starting computations..." << endl;
    auto start = chrono::high_resolution_clock::now();

    future<void> fExtra = async(launch::async, [] {
        slow("C2");
        quick("D2");
    });

    quick("A");
    slow("B");
    quick("C1");

    fExtra.wait();

    quick("D1");
    quick("F");

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Total Time: " << elapsed.count() << " s\n";
}

int main() {
    work();
    cout << "Work is done!" << endl;
    return 0;
}