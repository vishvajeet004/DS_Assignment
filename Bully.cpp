#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class BullyAlgorithm
{
private:
    vector<int> processes;
    int leader;

public:
    BullyAlgorithm(const vector<int> &proc)
    {
        processes = proc;
        sort(processes.begin(), processes.end()); // Ensure highest ID wins
        leader = -1;
    }

    void startElection(int initiator)
    {
        cout << "Process " << initiator << " starts an election..." << endl;
        vector<int> higherProcesses;

        for (int process : processes)
        {
            if (process > initiator)
            {
                higherProcesses.push_back(process);
            }
        }

        if (higherProcesses.empty())
        {
            leader = initiator;
            cout << "Process " << initiator << " is the new leader!" << endl;
        }
        else
        {
            bool responseReceived = false;
            for (int process : higherProcesses)
            {
                cout << "Process " << initiator << " sends election message to " << process << endl;

                string response;
                cout << "Should process " << process << " respond? (yes/no): ";
                cin >> response;

                if (response == "yes")
                {
                    responseReceived = true;
                    cout << "Process " << process << " responds and starts its own election..." << endl;
                    startElection(process);
                    return;
                }
            }

            if (!responseReceived)
            {
                leader = initiator;
                cout << "No response from higher processes." << endl;
                cout << "Process " << initiator << " is the new leader!" << endl;
            }
        }
    }

    void detectCrash(int crashedLeader)
    {
        if (leader == -1)
        {
            cout << "No leader has been elected yet. Election needs to be initiated." << endl;
            return;
        }
        if (leader == crashedLeader)
        {
            cout << "Leader " << crashedLeader << " has crashed! Starting new election..." << endl;
            startElection(processes[0]); // Start election from the smallest ID
        }
    }

    int getLeader() const
    {
        return leader;
    }
};

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> processes;
    cout << "Enter process IDs: ";
    for (int i = 0; i < n; ++i)
    {
        int id;
        cin >> id;
        processes.push_back(id);
    }

    int initiator;
    cout << "Enter the initiator process ID: ";
    cin >> initiator;

    BullyAlgorithm bully(processes);
    bully.startElection(initiator);

    string crashInput;
    cout << "Do you want to simulate leader failure? (yes/no): ";
    cin >> crashInput;

    if (crashInput == "yes")
    {
        int crashedLeader;
        cout << "Enter the crashed leader ID: ";
        cin >> crashedLeader;
        bully.detectCrash(crashedLeader);
    }

    return 0;
}
