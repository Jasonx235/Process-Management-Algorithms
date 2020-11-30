#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;
vector<class Job> setJob();
void FCFS(vector<Job> jobList);
void Priority(vector<Job> jobList);
void SJN(vector<Job> jobList);

class Job {
public:
    Job() {
        name = -1;
        BurstTime = -1;
        arrivalTime = -1;
        priority = -1;
        TAT = -1;
        start = -1;
        completion = -1;
        waiting = -1;
        remainingB = -1;
        status = false;
    }

    Job(int n, int arrival, int prior, int bur)
    {
        name = n; 
        arrivalTime = arrival; 
        priority = prior;
        BurstTime = bur;
        TAT = -1;
        start = -1;
        completion = -1;
        waiting = -1;
        remainingB = bur;
        status = false;
    }


    void setName(int n) {
        name = n;
    }
    void setBurst(int n) {
        BurstTime = n;
    }
    void setArrival(int n) {
        arrivalTime = n;
    }
    void setPriority(int n) {
        priority = n;
    }
    void setStatus(bool s) {
        status = s;
    }
    void setStart(int n) {
        start = n;
    }
    void setTAT(int n) {
        TAT = n;
    }
    void setComple(int n) {
        completion = n;
    }
    void setWaiting(int n) {
        waiting = n;
    }
    void setRemainB(int b) {
        remainingB = b;
    }


    int getName() {
        return name;
    }
    int getBurst() {
        return BurstTime;
    }
    int getArrival() {
        return arrivalTime;
    }
    int getPriority() {
        return priority;
    }
    bool getStatus() {
        return status;
    }
    int getStart() {
        return start;
    }
    int getTAT() {
        return TAT;
    }
    int getComple() {
        return completion;
    }
    int getWaiting() {
        return waiting;
    }
    int getReB() {
        return remainingB;
    }

private:
    int name;
    int BurstTime;
    int arrivalTime;
    int priority;
    int TAT;
    int start;
    int completion;
    int waiting;
    int remainingB;
    bool status = false;

};

int main()
{
    //Setting data
    vector<Job> jobList;
    jobList = setJob();

    /*
    * 1: 2, 3, 3
    * 2: 2, 2, 4
    * 3: 3, 1, 1
    * 4: 5, 3, 2
    */


    //Testing each Scheduling Alogorithm
    FCFS(jobList);
    Priority(jobList);
    SJN(jobList);

    return 0;
}

vector<Job> setJob()
{
    vector<Job> jobList;
    int numofJobs, arr, prior, bur;

    //Setting Up Jobs
    cout << "Enter the number of jobs: ";
    cin >> numofJobs;

    for (int i = 1; i <= numofJobs; i++)
    {
        cout << "Enter Arrival for process " << i << ": ";
        cin >> arr;
        cout << "Enter Priority for process " << i << ": ";
        cin >> prior;
        cout << "Enter Burst Time for process " << i << ": ";
        cin >> bur;

        jobList.push_back(Job(i, arr, prior, bur));
        cout << endl;
    }
    cout << endl;
    return jobList;
}

void print(vector<Job> jobList) {
    double totalTAT = 0;
    cout << left << setw(20) << "Process ID" << setw(20) << "Starting Time" << setw(20) << "Terminating Time" << setw(20) << "TAT" << endl;
    for (int i = 0; i < jobList.size(); i++) {
        cout << left << setw(25) << jobList[i].getName() << setw(22) << jobList[i].getStart() << setw(14) << jobList[i].getComple() << setw(10) << jobList[i].getTAT() << endl;
        totalTAT += jobList[i].getTAT();
    }

    //Ordering jobs to show order of execution
    for (int i = 0; i < jobList.size(); i++) {
        for (int j = 0; j < jobList.size(); j++) {
            if (jobList[i].getComple() < jobList[j].getComple()) {
                Job temp;
                temp = jobList[i];
                jobList[i] = jobList[j];
                jobList[j] = temp;
            }
        }
    }
    cout << "Average TAT: " << totalTAT / jobList.size() << endl;
    cout << "Order of Execution: ";
    for (int i = 0; i < jobList.size(); i++) {
        cout << " -> P" << jobList[i].getName();
    }
    cout << endl << endl;
}

void FCFS(vector<Job> jobList) {
    
    int totalTAT = 0;

    //Ordering job by arrival time
    for (int i = 0; i < jobList.size()-1; i++) {
        for (int j = 0; j < jobList.size()-1 -i; j++) {
            if (jobList[j].getArrival()  > jobList[j+1].getArrival()) {
                swap(jobList[j], jobList[j+1]);
            }
        }
    }
    
    //Calculating TAT, Completion time, and waiting time
    for (int i = 0; i < jobList.size(); i++) {
        if (i > 0) {
            jobList[i].setStart(jobList[i-1].getComple());
        }
        else
            jobList[i].setStart(jobList[i].getArrival());

        jobList[i].setWaiting(jobList[i].getStart() - jobList[i].getArrival());
        jobList[i].setComple(jobList[i].getStart() + jobList[i].getBurst());
        jobList[i].setTAT(jobList[i].getComple() - jobList[i].getArrival());
     
    }

    cout << "----------------------------------------First Come First Serve------------------------------------------------" << "\n\n";
    print(jobList);
}

void Priority(vector<Job> jobList) {

    int currentTime = 0;
    vector<Job> tempQueue;
    int jobsToBeProcessed = jobList.size();
  
    while (jobsToBeProcessed > 0) {


        //Adding into queue
        for (int i = 0; i < jobList.size(); i++) {
            if (jobList[i].getArrival() == currentTime) {
                tempQueue.push_back(jobList[i]);
            }
        }

        if (!tempQueue.empty()) {

            //Setting jobs by priority and swapping
            for (int i = 0; i < tempQueue.size(); i++) {
                for (int j = 0; j < tempQueue.size(); j++) {
                    if (tempQueue[i].getPriority() > tempQueue[j].getPriority()) {
                        Job temp;
                        temp = tempQueue[i];
                        tempQueue[i] = tempQueue[j];
                        tempQueue[j] = temp;
                    }
                }
            }
            //Begining of start time initiated
            if (tempQueue.back().getBurst() == tempQueue.back().getReB()) 
            {
                tempQueue[tempQueue.size() - 1].setStart(currentTime);
            }

            tempQueue.back().setRemainB(tempQueue.back().getReB() - 1);

            // Calculating start time, completion time, and TAT
            if (tempQueue.back().getReB() <= 0) 
            {

                for (int i = 0; i < jobList.size(); i++) {

                    if (jobList[i].getName() == tempQueue.back().getName())
                    {
                        jobList[i].setStart(tempQueue.back().getStart());
                        jobList[i].setComple(currentTime + 1);
                        jobList[i].setTAT(jobList[i].getComple() - jobList[i].getArrival());

                        tempQueue.pop_back();
                        break;
                    }
                }jobsToBeProcessed--;

            }

        }currentTime++;
    }
    //Sending data to print
    cout << "----------------------------------------Priority: Preemptive------------------------------------------------" << "\n\n";
    print(jobList);

}

void SJN(vector<Job> jobList) {
    int currentTime = 0;
    vector<Job> tempQueue;
    int jobsToBeProcessed = jobList.size();

    //Looping until no jobs are left to be processed
    while (jobsToBeProcessed > 0) 
    {
        //adding jobs to temp queue
        for (int i = 0; i < jobList.size(); i++) 
        {
            if (jobList[i].getArrival() <= currentTime && jobList[i].getStatus() == false) 
            {
                tempQueue.push_back(jobList[i]);
            }
        }

       
        if (!tempQueue.empty()) {

           //Ordering the jobs by burst time // the shortest job having highest priority
            for (int i = 0; i < tempQueue.size(); i++) 
            {
                for (int j = 0; j < tempQueue.size(); j++) 
                {
                    if (tempQueue[i].getBurst() > tempQueue[j].getBurst()) 
                    {
                        Job temp;
                        temp = tempQueue[i];
                        tempQueue[i] = tempQueue[j];
                        tempQueue[j] = temp;
                    }
                }
            }

            //Performing all the calculations that will be recorded e.g. start time, completion time, TAT, and status
            for (int i = 0; i < jobList.size(); i++) {

                if (jobList[i].getName() == tempQueue.back().getName()) 
                {
                    jobList[i].setStart(currentTime);
                    currentTime += jobList[i].getBurst();
                    jobList[i].setComple(currentTime);
                    jobList[i].setTAT(jobList[i].getComple() - jobList[i].getArrival());
                    jobList[i].setStatus(true);
                    tempQueue.clear();

                    break;
                }
            }
            jobsToBeProcessed--;

        }
        else currentTime++;
    }

    cout << "----------------------------------------Shortest Job Next------------------------------------------------" << "\n\n";
    print(jobList);
}
