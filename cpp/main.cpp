#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <string>

using namespace std;


// ======================================================
// LANDWISE - INTELLIGENT LAND ACQUISITION DSA ENGINE
// ======================================================


// ======================================================
// LAND RECORD
// ======================================================

struct LandRecord {

    string surveyNumber;
    string owner;
    string location;

    double area;

    string status;

    int priority;
};


// ======================================================
// HASH TABLE
// Average Search: O(1)
// ======================================================

class LandHashTable {

private:

    unordered_map<string, LandRecord> records;


public:

    void insertRecord(
        LandRecord record
    ) {

        records[
            record.surveyNumber
        ] = record;
    }


    void searchRecord(
        string surveyNumber
    ) {

        auto it =
            records.find(
                surveyNumber
            );


        if (
            it == records.end()
        ) {

            cout
                << "\nLand Record Not Found.\n";

            return;
        }


        LandRecord r =
            it->second;


        cout
            << "\n========== LAND RECORD ==========\n";

        cout
            << "Survey Number : "
            << r.surveyNumber
            << endl;

        cout
            << "Owner         : "
            << r.owner
            << endl;

        cout
            << "Location      : "
            << r.location
            << endl;

        cout
            << "Area          : "
            << r.area
            << " acres"
            << endl;

        cout
            << "Status        : "
            << r.status
            << endl;

        cout
            << "Priority      : "
            << r.priority
            << endl;

        cout
            << "=================================\n";
    }


    void displayAll() {

        cout
            << "\n========== ALL LAND RECORDS ==========\n";


        for (
            auto &pair : records
        ) {

            LandRecord r =
                pair.second;


            cout
                << r.surveyNumber
                << " | "
                << r.owner
                << " | "
                << r.location
                << " | "
                << r.area
                << " acres"
                << " | "
                << r.status
                << endl;
        }


        cout
            << "======================================\n";
    }


    int size() {

        return records.size();
    }
};


// ======================================================
// PRIORITY QUEUE
// Highest Priority Case First
// ======================================================

struct PriorityCase {

    string surveyNumber;

    string project;

    int priority;


    bool operator<(
        const PriorityCase& other
    ) const {

        return priority <
               other.priority;
    }
};


class PriorityEngine {

private:

    priority_queue<PriorityCase> pq;


public:

    void addCase(
        string surveyNumber,
        string project,
        int priority
    ) {

        pq.push({

            surveyNumber,

            project,

            priority

        });
    }


    void processNextCase() {

        if (
            pq.empty()
        ) {

            cout
                << "\nNo pending cases.\n";

            return;
        }


        PriorityCase current =
            pq.top();


        pq.pop();


        cout
            << "\n========== NEXT PRIORITY CASE ==========\n";


        cout
            << "Survey Number : "
            << current.surveyNumber
            << endl;


        cout
            << "Project       : "
            << current.project
            << endl;


        cout
            << "Priority Score: "
            << current.priority
            << endl;


        cout
            << "========================================\n";
    }


    void displayQueue() {

        priority_queue<
            PriorityCase
        > temp = pq;


        cout
            << "\n========== PRIORITY QUEUE ==========\n";


        while (
            !temp.empty()
        ) {

            PriorityCase c =
                temp.top();


            temp.pop();


            cout
                << c.surveyNumber
                << " | "
                << c.project
                << " | Priority: "
                << c.priority
                << endl;
        }


        cout
            << "====================================\n";
    }
};


// ======================================================
// GRAPH + DIJKSTRA
// ======================================================

class Graph {

private:

    int vertices;

    vector<
        vector<
            pair<int, int>
        >
    > adjacency;


public:

    Graph(int v) {

        vertices = v;

        adjacency.resize(
            vertices
        );
    }


    void addEdge(
        int source,
        int destination,
        int distance
    ) {

        adjacency[source]
            .push_back({
                destination,
                distance
            });


        adjacency[destination]
            .push_back({
                source,
                distance
            });
    }


    void dijkstra(
        int source
    ) {

        vector<int> distance(
            vertices,
            INT_MAX
        );


        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;


        distance[source] = 0;


        pq.push({
            0,
            source
        });


        while (
            !pq.empty()
        ) {

            int currentDistance =
                pq.top().first;


            int currentVertex =
                pq.top().second;


            pq.pop();


            if (
                currentDistance >
                distance[currentVertex]
            ) {

                continue;
            }


            for (
                auto edge :
                adjacency[currentVertex]
            ) {

                int nextVertex =
                    edge.first;


                int edgeWeight =
                    edge.second;


                if (
                    distance[currentVertex]
                    + edgeWeight
                    <
                    distance[nextVertex]
                ) {

                    distance[nextVertex] =

                        distance[currentVertex]
                        + edgeWeight;


                    pq.push({

                        distance[nextVertex],

                        nextVertex

                    });
                }
            }
        }


        cout
            << "\n========== SHORTEST ROUTES ==========\n";


        for (
            int i = 0;
            i < vertices;
            i++
        ) {

            cout
                << "Location "
                << i
                << " -> ";


            if (
                distance[i] ==
                INT_MAX
            ) {

                cout
                    << "Unreachable";

            } else {

                cout
                    << distance[i]
                    << " km";
            }


            cout
                << endl;
        }


        cout
            << "=====================================\n";
    }
};


// ======================================================
// SORTING
// ======================================================

void sortByPriority(
    vector<LandRecord>& records
) {

    sort(

        records.begin(),

        records.end(),

        [](
            const LandRecord& a,
            const LandRecord& b
        ) {

            return
                a.priority >
                b.priority;
        }
    );


    cout
        << "\n========== PRIORITY SORT ==========\n";


    for (
        auto &r : records
    ) {

        cout
            << r.surveyNumber
            << " | "
            << r.owner
            << " | Priority: "
            << r.priority
            << endl;
    }


    cout
        << "===================================\n";
}


// ======================================================
// MAIN
// ======================================================

int main() {

    cout << endl;

    cout
        << "=============================================\n";

    cout
        << "       LANDWISE DSA ENGINE v1.0\n";

    cout
        << " Intelligent Land Acquisition System\n";

    cout
        << "=============================================\n";


    // ==================================================
    // HASH TABLE
    // ==================================================

    LandHashTable landDB;


    landDB.insertRecord({

        "MH12-4821",

        "Rajesh Patil",

        "Pune",

        2.5,

        "Pending",

        96

    });


    landDB.insertRecord({

        "MH14-2187",

        "Amit Sharma",

        "Pimpri",

        4.2,

        "Under Verification",

        91

    });


    landDB.insertRecord({

        "MH09-7732",

        "Sneha Kulkarni",

        "Satara",

        3.7,

        "Acquired",

        87

    });


    landDB.insertRecord({

        "MH15-1049",

        "Rahul Deshmukh",

        "Nashik",

        5.1,

        "Pending",

        81

    });


    cout
        << "\nTotal Land Records: "
        << landDB.size()
        << endl;


    landDB.searchRecord(
        "MH12-4821"
    );


    // ==================================================
    // PRIORITY QUEUE
    // ==================================================

    PriorityEngine priorityEngine;


    priorityEngine.addCase(
        "MH12-4821",
        "National Highway 48",
        96
    );


    priorityEngine.addCase(
        "MH14-2187",
        "Industrial Corridor",
        91
    );


    priorityEngine.addCase(
        "MH09-7732",
        "Rail Infrastructure",
        87
    );


    priorityEngine.addCase(
        "MH15-1049",
        "Renewable Energy",
        81
    );


    priorityEngine.displayQueue();


    priorityEngine.processNextCase();


    // ==================================================
    // GRAPH
    // ==================================================

    Graph projectMap(6);


    projectMap.addEdge(
        0,
        1,
        5
    );


    projectMap.addEdge(
        0,
        2,
        9
    );


    projectMap.addEdge(
        1,
        2,
        3
    );


    projectMap.addEdge(
        1,
        3,
        7
    );


    projectMap.addEdge(
        2,
        4,
        4
    );


    projectMap.addEdge(
        3,
        5,
        6
    );


    projectMap.addEdge(
        4,
        5,
        2
    );


    cout
        << "\nRunning Dijkstra Algorithm...\n";


    projectMap.dijkstra(
        0
    );


    // ==================================================
    // SORTING
    // ==================================================

    vector<LandRecord> records = {

        {
            "MH12-4821",
            "Rajesh Patil",
            "Pune",
            2.5,
            "Pending",
            96
        },

        {
            "MH14-2187",
            "Amit Sharma",
            "Pimpri",
            4.2,
            "Verification",
            91
        },

        {
            "MH09-7732",
            "Sneha Kulkarni",
            "Satara",
            3.7,
            "Acquired",
            87
        },

        {
            "MH15-1049",
            "Rahul Deshmukh",
            "Nashik",
            5.1,
            "Pending",
            81
        }
    };


    sortByPriority(
        records
    );


    // ==================================================
    // FINAL
    // ==================================================

    cout
        << "\n=============================================\n";

    cout
        << "DSA ENGINE EXECUTION COMPLETED\n";


    cout
        << "Algorithms Used:\n";


    cout
        << "1. Hash Table       -> O(1) average search\n";


    cout
        << "2. Priority Queue   -> O(log n)\n";


    cout
        << "3. Dijkstra         -> O(E log V)\n";


    cout
        << "4. Sorting          -> O(n log n)\n";


    cout
        << "=============================================\n";


    return 0;
}