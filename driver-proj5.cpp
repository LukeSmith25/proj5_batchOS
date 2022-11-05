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
    int startTime = 0, prevStart = 0, sysClock = 0;
    int complete = 0, failed = 0;

    cin >> numProcess;

    while (batch.getNumItems() >= 0) {
        Process task(id++);
        if (numProcess >= 0) {
            cout << numProcess << endl;
            cin >> startTime;
            cin >> task;
        }

        // If the task can complete before the deadline
        /*
        if (batch.getNumItems() == 0) {
            cout << "current time is " << sysClock << ", the number of runnable processes is "
                 << batch.getNumItems() << endl;

            if (startTime > sysClock) {
                cout << "moving the clock forward to " << startTime <<
                " ticks since there are no processes to run" << endl;

                sysClock = startTime;
            }

            if (startTime < sysClock) {
                cout << "a new process has started at time " << startTime <<
                     "; we will give it id " << task.getId() << " and put it on the heap"
                     << endl;
            }
            else {
                cout << "a new process has started at time " << sysClock <<
                     "; we will give it id " << task.getId() << " and put it on the heap"
                     << endl;
            }

            batch.insert(task);

        }

        else {
            batch.insert(task);
            if (task.getId() != 0 && startTime == sysClock) {
                continue;
            }
        }
        */
        batch.insert(task);

        if (startTime == sysClock && task.getId() != 0) {
            numProcess--;
            continue;
        }
        /*
        if (task.getId() == 0) {
            prevStart = startTime;
        }
        else {
            if (startTime == sysClock) {
                continue;
            }
        }
        prevStart = startTime;
         */


        task = batch.getMinItem();

        if (task.canComplete(sysClock)) {
            if (startTime < sysClock) {
                cout << "running process id " << task.getId() << " at " <<
                     sysClock << endl;
                sysClock = task.run(sysClock);
                //cout << "SYS: " << sysClock << endl;
            }
            else {
                cout << "running process id " << task.getId() << " at " <<
                     startTime << endl;
                sysClock = task.run(startTime);
                //cout << "START: " << startTime << endl;
            }

            complete++;
        }
        else {
            if (startTime < sysClock) {
                cout << "skipping process id " << task.getId() << " at " <<
                     sysClock << endl;
            }
            else {
                cout << "skipping process id " << task.getId() << " at " <<
                     startTime << endl;
            }
            sysClock++;
            failed++;
        }
        batch.removeMinItem();
        numProcess--;
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
