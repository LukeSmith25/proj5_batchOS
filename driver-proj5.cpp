/**
 * file: driver-proj5.cpp
 * author: Luke Smith
 * course: CSI 3334
 * assignment: project 5
 * due date: November 6, 2022
 *
 * Driver for implementing the real-time batch operating system.
 */

#include <iostream>
#include "process-proj5.h"
#include "arrayheap-student-proj5.h"
using namespace std;

int main() {
    ArrayHeap<Process> batch;
    int numProcess = 0;
    int id = 0;
    int startTime = 0, sysClock = 0;
    int complete = 0, failed = 0;

    cin >> numProcess;
    cin >> startTime;
    while(numProcess != 0) {
        Process task(id);

        if(startTime > sysClock && batch.getNumItems() == 0){
            sysClock = startTime;
        }

        if (id == 0) {

            cin >> task;
            batch.insert(task);
            id++;
            cin >> startTime;
        }

        if (startTime <= sysClock) {
            do {
                task = Process(id++);
                cin >> task;
                batch.insert(task);
//                cout << "inserted" << endl;
//                batch.checkOrder();

            } while (cin >> startTime && startTime <= sysClock);
        }

        while (batch.getNumItems() > 0 && ((cin.fail() && numProcess) || startTime > sysClock)) {
            if (batch.getMinItem().canComplete(sysClock)) {
                cout << "running process id " << batch.getMinItem().getId() << " at " << sysClock << endl;
                task = batch.getMinItem();
                sysClock = task.run(sysClock);
                complete++;
            }
            else {
                cout << "skipping process id " << batch.getMinItem().getId() << " at " << sysClock << endl;
                sysClock++;
                failed++;
            }
            batch.removeMinItem();
            //batch.checkOrder();
            numProcess--;
        }
    }

    cout << "final clock is                 " << sysClock << endl;
    cout << "number of processes run is     " << complete << endl;
    cout << "number of processes skipped is " << failed << endl;

    return 0;
}

/*
int main() {
    ArrayHeap<string> os;
    int numProcess = 0;
    int id = 0;
    int startTime = 0, sysClock = 0, totalTime = 0;
    int complete = 0, failed = 0;

    cin >> numProcess;

    while (numProcess != 0) {
        Process task(id++);
        cin >> startTime;
        cin >> task;

        // First run, add first time to system clock
        if (id - 1 == 0) {
            sysClock += startTime;
        }

        // If the task can complete before the deadline
        if (task.canComplete(startTime)) {
            if (startTime < sysClock) {
                cout << "running process id " << task.getId() << " at " <<
                     sysClock << endl;
            }
            else {
                cout << "running process id " << task.getId() << " at " <<
                     startTime << endl;
            }

            sysClock = task.run(startTime);
            totalTime = sysClock;

            complete++;
        }

            // Can't complete before the deadline, output error and inc sysClock
        else {
            if (startTime < sysClock) {
                cout << "skipping process id " << task.getId() << " at " <<
                     sysClock << endl;
            }
            else {
                cout << "skipping process id " << task.getId() << " at " <<
                     startTime << endl;
            }
            totalTime++;
            sysClock++;
            failed++;
        }

        numProcess--;
    }
    cout << "final clock is                 " << totalTime << endl;
    cout << "number of processes run is     " << complete << endl;
    cout << "number of processes skipped is " << failed << endl;

    return 0;
}
*/
