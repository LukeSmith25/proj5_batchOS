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

    private:
        int id;
        int deadline;
        int requiredTime;
        string information;
};

Process::Process(int theId) {
    id = theId;
    deadline = 1;
    requiredTime = 1;
    information = "";
}

int Process::run(int currentSystemTime) const {
    cout << information << endl;
    return requiredTime + currentSystemTime;
}

bool Process::canComplete(int currentSystemTime) const {
    if ((requiredTime + currentSystemTime) <= deadline) {
        return true;
    }
    return false;
}

int Process::getId() const {
    return id;
}

bool Process::operator<(const Process &p) const {
    bool lessThan = false;
    // Case 1: d1 < d2
    if (deadline < p.deadline) {
        return true;
    }
    else {
        // Case 2: d1 = d2, check reqT1 < reqT2
        if (deadline == p.deadline && requiredTime < p.requiredTime) {
            return true;
        }
        else {
            // Case 3: d1 = d2, reqT1 = reqT2, check id < id2
            if ((deadline == p.deadline && requiredTime == p.requiredTime)
            && id < p.id) {
                return true;
            }
        }
    }

    // If not one of the 3 cases return false
    return false;
}

istream &operator>>(istream &is, Process &p) {
    is >> p.deadline >> p.requiredTime;
    cin.ignore();
    getline(is, p.information);
    return is;
}



#endif

