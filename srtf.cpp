#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>

using namespace std;

class Process
{
public:
  int pid;
  int arrival_time;
  int burst_time;
  int original_burst_time; // New member to store the original burst time
  string name;
  int turnaround_time;
  int waiting_time;
  static Process read_next_process()
  {
    Process p;
    cout << "Enter the process id, arrival time and burst time: ";
    cin >> p.pid >> p.arrival_time >> p.burst_time;
    p.original_burst_time = p.burst_time; // Store the original burst time
    cout << "Enter the process name: ";
    cin.ignore();
    getline(cin, p.name);
    cout << "Loaded process "
         << "'" << p.name << "'" << endl;
    return p;
  }
};

class Schedule
{
public:
  vector<Process> *processes;
  Schedule(int process_count)
  {
    processes = new vector<Process>(process_count);
  }
  void read_processes()
  {
    for (int i = 0; i < processes->size(); i++)
    {
      processes->at(i) = Process::read_next_process();
    }
  }
  void sort_processes()
  {
    for (int i = 0; i < processes->size(); i++)
    {
      for (int j = i + 1; j < processes->size(); j++)
      {
        if (processes->at(i).arrival_time > processes->at(j).arrival_time)
        {
          Process temp = processes->at(i);
          processes->at(i) = processes->at(j);
          processes->at(j) = temp;
        }
      }
    }
  }
  void schedule_processes()
  {
    int current_time = 0;
    int completed_processes = 0;
    while (completed_processes < processes->size())
    {
      int min_burst_time = INT_MAX;
      int next_process = -1;
      for (int i = 0; i < processes->size(); i++)
      {
        if (processes->at(i).arrival_time <= current_time && processes->at(i).burst_time < min_burst_time && processes->at(i).burst_time > 0)
        {
          min_burst_time = processes->at(i).burst_time;
          next_process = i;
        }
      }
      if (next_process == -1)
      {
        current_time++;
      }
      else
      {
        processes->at(next_process).burst_time--;
        current_time++;
        if (processes->at(next_process).burst_time == 0)
        {
          completed_processes++;
          processes->at(next_process).turnaround_time = current_time - processes->at(next_process).arrival_time;
          processes->at(next_process).waiting_time = processes->at(next_process).turnaround_time - processes->at(next_process).original_burst_time;
        }
      }
    }
    /**
     * Pseudo code for SRTF
     * 1. Initialize the current time to 0 and completed processes to 0
     * 2. While the number of completed processes is less than the total number of processes
     *    a. Initialize the minimum burst time to INT_MAX and next process to -1
     *    b. For each process in the list of processes
     *      i. If the process has arrived and has a burst time less than the minimum burst time and the burst time is greater than 0
     *        a. Update the minimum burst time and next process
     *    c. If the next process is -1
     *      i. Increment the current time
     *    d. Else
     *      i. Decrement the burst time of the next process
     *      ii. Increment the current time
     *      iii. If the burst time of the current process is 0
     *        a. Increment the number of completed processes
     *        b. Calculate the turnaround time of the next process
     *        c. Calculate the waiting time of the next process
     * 3. End
     */
  }

  void tablular_schedule()
  {
    int x = 5;
    cout << std::left << std::setw(3 * x) << "Name"
         << std::setw(1 * x) << "PID"
         << std::setw(3 * x) << "Arrival Time"
         << std::setw(3 * x) << "Burst Time"
         << std::setw(4 * x) << "Turnaround Time"
         << std::setw(4 * x) << "Waiting Time" << endl;
    cout << string(18 * x, '-') << endl;
    for (int i = 0; i < processes->size(); i++)
    {
      cout << std::left << std::setw(3 * x) << processes->at(i).name
           << std::setw(1 * x) << processes->at(i).pid
           << std::setw(3 * x) << processes->at(i).arrival_time
           << std::setw(3 * x) << processes->at(i).original_burst_time
           << std::setw(4 * x) << processes->at(i).turnaround_time
           << std::setw(4 * x) << processes->at(i).waiting_time << endl;
    }
    cout << string(18 * x, '-') << endl;
  }
  int average_turnaround_time()
  {
    int sum = 0;
    for (int i = 0; i < processes->size(); i++)
    {
      sum += processes->at(i).turnaround_time;
    }
    return sum / processes->size();
  }
  int average_waiting_time()
  {
    int sum = 0;
    for (int i = 0; i < processes->size(); i++)
    {
      sum += processes->at(i).waiting_time;
    }
    return sum / processes->size();
  }
  void meta_data()
  {
    cout << "Average Turnaround Time: " << average_turnaround_time() << endl;
    cout << "Average Waiting Time: " << average_waiting_time() << endl;
  }
};

int main()
{
  int process_count;
  cout << "Enter the number of processes: ";
  cin >> process_count;
  Schedule s(process_count);
  s.read_processes();
  s.sort_processes();
  s.schedule_processes();
  s.tablular_schedule();
  s.meta_data();
  return 0;
}