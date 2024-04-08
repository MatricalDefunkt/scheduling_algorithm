#include <iostream>
#include <vector>
#include <algorithm> // For std::sort
using namespace std;

struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
};

int main()
{
    int noOfProcesses;
    cout << "Enter number of processes: ";
    cin >> noOfProcesses;
    vector<Process> processes;
    vector<Process> completedProcesses;

    // Input processes
    for (int i = 0; i < noOfProcesses; i++)
    {
        Process p;
        cout << "Process " << i + 1 << " ====================\n";
        p.pid = i + 1;
        cout << "Enter arrival time: ";
        cin >> p.arrivalTime;
        cout << "Enter burst time: ";
        cin >> p.burstTime;
        processes.push_back(p);
    }

    // sorting the processes based on arrival time
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.arrivalTime < b.arrivalTime;
    });

    int currentTime = 0;
    while (!processes.empty())
    {
        // set current time if arrival time of first process is greater than current time
        if (processes[0].arrivalTime > currentTime)
        {
            currentTime = processes[0].arrivalTime;
        }

        vector<Process> filteredProcesses;

        // filter processes whose arrival time is less than or equal to current time
        for (const Process &p : processes)
        {
            if (p.arrivalTime <= currentTime)
            {
                filteredProcesses.push_back(p);
            }
            else
            {
                break; // no need to check further, as processes are sorted by arrival time
            }
        }

        // sort filtered processes by burst time
        sort(filteredProcesses.begin(), filteredProcesses.end(), [](const Process &a, const Process &b) {
            return a.burstTime < b.burstTime;
        });

        // process the shortest job
        Process shortestJob = filteredProcesses.front();
        shortestJob.completionTime = currentTime + shortestJob.burstTime;
        shortestJob.turnAroundTime = shortestJob.completionTime - shortestJob.arrivalTime;
        shortestJob.waitingTime = shortestJob.turnAroundTime - shortestJob.burstTime;
        completedProcesses.push_back(shortestJob);

        // remove processed job from the processes vector
        processes.erase(remove_if(processes.begin(), processes.end(), [&](const Process &p) {
            return p.pid == shortestJob.pid;
        }), processes.end());

        currentTime = shortestJob.completionTime;
    }

    cout << "Process\tAT\tBT\tET\tTAT\tWT\n";
    for (const Process &p : completedProcesses)
    {
        cout << p.pid << "\t"
             << p.arrivalTime << "\t"
             << p.burstTime << "\t"
             << p.completionTime << "\t"
             << p.turnAroundTime << "\t"
             << p.waitingTime << "\n";
    }

    float totalTAT = 0, totalWT = 0;
    for (const Process &p : completedProcesses)
    {
        totalTAT += p.turnAroundTime;
        totalWT += p.waitingTime;
    }
    cout << "Average Turnaround Time: " << totalTAT / noOfProcesses << "\n";
    cout << "Average Waiting Time: " << totalWT / noOfProcesses << "\n";

    return 0;
}
