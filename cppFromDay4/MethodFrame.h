#ifndef METHODFRAME_H
#define METHODFRAME_H

#include <iostream>
using namespace std;

class MethodFrame {

    const string kProgramMethod;
    chrono::system_clock::time_point start;

public:
    MethodFrame(string kProgramMethod) : kProgramMethod(kProgramMethod) {}
    void printStart();
    void printEnd();

};

void MethodFrame::printStart() {
    this->start = chrono::system_clock::now();
    const time_t start_time = chrono::system_clock::to_time_t(start);
    const string start_time_str = ctime(&start_time);
    
    cout << endl << "----->  start of   " << this->kProgramMethod << "     at: " 
            << start_time_str.substr(0, start_time_str.length() - 1) << "  <-----" << endl << endl;
}

void MethodFrame::printEnd() {
    const chrono::system_clock::time_point end = chrono::system_clock::now();
    const time_t end_time = chrono::system_clock::to_time_t(end);
    const string end_time_str = ctime(&end_time);
    const chrono::duration<double> elapsed_seconds = end - start;

    cout << endl << "----->  end of     " << this->kProgramMethod << "     at: " 
            << end_time_str.substr(0, end_time_str.length() - 1) << "     elapsed time: " << elapsed_seconds.count() 
            << " seconds  <-----" << endl << endl;
}

#endif