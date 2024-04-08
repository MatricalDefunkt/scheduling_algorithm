#include <iostream>

using namespace std;

class Process
{
public:
  int pid;
  int arrival_time;
  int burst_time;
  static Process read_next_process()
  {
    Process p;
    cout << "Enter the process id, arrival time and burst time: ";
    cin >> p.pid >> p.arrival_time >> p.burst_time;
    return p;
  }
};

// Implementing shortest remaining time first
class Schedule
{

};

int
main()
{
  Process p = Process::read_next_process();
  cout << "Process id: " << p.pid << endl;
  return 0;
}