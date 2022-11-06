/**
 * file: process-proj5.h
 * author: Luke Smith
 * course: CSI 3334
 * assignment: project 5
 * due date: November 6, 2022
 *
 * Process file containing all operations for process class.
 */
#ifndef PROCESS_PROJ5_H
#define PROCESS_PROJ5_H

#include <iostream>
#include <string>

using namespace std;

/* A Process object represents a batch-executed computer process, which has a
 * hard real-time deadline before which it must finish. It also has an amount of
 * time that it requires to execute.
 *
 * A Process object has a (unique) id, which starts at 0 and should increment
 * whenever a new process is created. It is up to the operating system to assign
 * it an ID.
 *
 * Finally, a Process object has a data member "information", which is printed
 * when the run() method executes.
 *
 * The default constructor for the Process initializes all the data members to
 * reasonable defaults, and the id to the given ID (default is 0).
 *
 * The run method prints out the information contained in this process, and
 * then returns the system time plus the required time (which is the new system
 * time).
 *
 * The canComplete method returns true if the method would be able to complete
 * if it starts now, or false if it could not finish by its deadline.
 *
 * The getId method returns the id of this Process object.
 *
 * The operator< method is used to order Processes by:
 *  1. deadline (least to greatest)
 *  2. required time (least to greatest, if deadlines are equal)
 *  3. id (least to greatest, if deadlines & required times are equal)
 * The operator< method returns true if (*this) < p, false otherwise.
 *
 * The operator>> method is used to read in the deadline, requiredTime, and
 * information from an istream.
 *
 * The Process class does not allocate any of its own memory, so the
 * compiler-provided copy constructor, destructor, and operator= do not need to
 * be changed.
 */
class Process {
    public:
        Process(int theId = 0);

        int run(int currentSystemTime) const;
        bool canComplete(int currentSystemTime) const;
        int getId() const;

        bool operator<(const Process &p) const;

        friend istream &operator>>(istream &is, Process &p);

        //void print();

    private:
        int id;
        int deadline;
        int requiredTime;
        string information;
};

/**
 * Process Constructor
 *
 * This function is the default constructor for Process.
 *
 * Parameters:
 *      int: integer representing id
 *
 * Return value: None.
 */
Process::Process(int theId) {
    id = theId;
    deadline = 1;
    requiredTime = 1;
    information = "";
}

/**
 * run
 *
 * This function prints information and returns the result of the process
 * running.
 *
 * Parameters:
 *      int: integer representing current system time
 *
 * Return value: integer representing time after execution
 */
int Process::run(int currentSystemTime) const {
    cout << information << endl;
    return requiredTime + currentSystemTime;
}

/**
 * cancomplete
 *
 * This function returns a boolean representing if a function can complete
 * before a specified time.
 *
 * Parameters:
 *      int: integer representing current system time
 *
 * Return value: bool representing if process can run
 */
bool Process::canComplete(int currentSystemTime) const {
    if ((requiredTime + currentSystemTime) <= deadline) {
        return true;
    }
    return false;
}

/**
 * getId
 *
 * This function returns the id of a process
 *
 * Parameters: none
 *
 * Return value: integer value of id
 */
int Process::getId() const {
    return id;
}

/**
 * operator<
 *
 * This function determines if a process is less then a process passed.
 * First checks deadline, then required time, and finally id.
 *
 * Parameters:
 *      Process: process to be compared to
 *
 * Return value: boolean representing if current proc < passed proc
 */
bool Process::operator<(const Process &p) const {
    if (this->deadline < p.deadline) {
        return true;
    }
    if (this->deadline == p.deadline && this-> requiredTime < p.requiredTime) {
        return true;
    }
    if (this->deadline == p.deadline
    && this->requiredTime == p.requiredTime && this->id < p.id) {
        return true;
    }

    return false;
}

/**
 * operator>>
 *
 * This function reads in a process object.
 *
 * Parameters:
 *      istream: input stream containing information
 *      Process: process to be read into
 *
 * Return value: input stream modified after reading from it
 */
istream &operator>>(istream &is, Process &p) {
    is >> p.deadline >> p.requiredTime;
    cin.ignore();
    getline(is, p.information);
    return is;
}



#endif

