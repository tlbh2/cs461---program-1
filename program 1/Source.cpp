#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <list>
#include <set>
#include <sstream>
#include <map>
#include <queue>
#include <math.h>
using namespace std;

int vertArr[46][46]; //the adjacency matrix initially 0

struct XYcoordinates
{
    XYcoordinates() :  x(0.0), y(0.0) {}
    XYcoordinates( double newX, double newY)
       : x(newX), y(newY) {}

    double x, y;
};


double distanceCalculate(double x1, double y1, double x2, double y2)
{
    double x = x1 - x2; //calculating number to square in next step
    double y = y1 - y2;
    double dist;

    dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
    dist = sqrt(dist);

    return dist;
}


void displayMatrix(int v) {
    int i, j;
    for (i = 0; i < v; i++) {
        for (j = 0; j < v; j++) {
            cout << vertArr[i][j] << " ";
        }
        cout << endl;
    }
}

//function to add edge into the matrix
void add_edge( int u, int v) {       
    vertArr[u][v] = 1;
    vertArr[v][u] = 1;
}

int GetIndex(set<string> S, string K)
{
    int Index = 1;

    // Traverse the Set
    for (auto &u : S) {
        if (u == K)
            return Index;
        Index++;
    }

    // If K is not present in the set
    return 0;
}

string GetElementName(set<string> D, int index)
{
    string d;

    set<string>::iterator setIt = D.begin();
    for (int i = 1; i < index; i++)
        setIt++;
    d = *setIt;

    return d;
}

bool IsGoalState(string x, string y) {
    if (x == y)
    {
        cout << " found the goal!! " << endl;
        return true;
    }
    return false;
}

int tracing(set<string>& exploredSet, string goal, set<string> out, string start)
{
    string tempName;
    //int nodeIndex = GetIndex(out, goal);
    cout << "The route is " << goal << " -> ";
    while (goal != start) {
        int nodeIndex = GetIndex(out, goal);
        for (int i = 0; i < out.size(); i++) {
            if (vertArr[i][nodeIndex] == 1)
            {
                tempName = GetElementName(out, i); //point out adjacent city which already explored
                if (exploredSet.find(tempName) != exploredSet.end())
                {
                    cout << tempName << " -> ";
                    exploredSet.erase(tempName);
                    goal = tempName;
                    //nodeIndex = GetIndex(out, goal);
                }
            }
        }
    }
    return 0;
}

int main() {


    //simulated starting point
    string startNode = "El_Dorado";
    double startNode_X = 37.8098997, startNode_Y = -96.8943313;
    //simulated goal state
    string endNode = "Mayfield";


    //min-heap for the priority queue
    priority_queue<double, vector<double>, greater<double>> minPQcost;

    string line, substrings, firstWord, townName, towns;
    int uu = 0, vv = 0;
    double X = 0.0, Y= 0.0, cost= 0.0 ;
    const char delim = ' ';
    set<string> out, explored, unexplored; //use set to store non-duplicate values == unique values
    map<string, XYcoordinates> townCoordinates;
    map<string, double> TnC; // town and its cost from starting point

    //read file coordinates.txt and store value to map for easy access
    ifstream coordinatesFile("coordinates.txt");
    if (coordinatesFile.good())
    {
        while (coordinatesFile >> townName >> X >> Y)
        {
            if (townName == startNode) {
                cost = distanceCalculate(startNode_X, startNode_Y, X, Y);
                out.insert(townName);
            }
            else
            {
                cost = distanceCalculate(startNode_X, startNode_Y, X, Y);
                TnC.insert(pair<string, double>(townName, cost));
                out.insert(townName);
            }
        }
        coordinatesFile.close();
    }

    //output set
    
    int count = 1;
    for (set<string>::iterator itr = out.begin(); itr != out.end(); itr++) {
        cout << count << "-" << * itr << endl;
        count++;
    }
    cout << "Total = " << out.size() << endl;
    cout << "=---------------------------=" << endl;
    

    //Adjacency matrix
    
    ifstream mySecondfile("Adjacencies.txt");
    if (mySecondfile.good())
    {
        while (mySecondfile >> firstWord and getline(mySecondfile, line))
        {
            // X is an object of stringstream that references the 'line' string  
            stringstream X(line);
            //split string into substring using delimiter 
            while (getline(X, substrings, delim))
            {
                if (substrings == " " or substrings == "") {
                    continue;
                }
                else {
                    uu = GetIndex(out, firstWord);
                    vv = GetIndex(out, substrings);
                    add_edge(uu , vv );
                }
            }
        }
        mySecondfile.close();
    }

    //displayMatrix(out.size());

    //print out coordinates map
    /*
    map<string, double>::iterator itr;
    cout << "\nThe map TnC is : \n";
    cout << "\tKEY\tELEMENT\n";
    for (itr = TnC.begin(); itr != TnC.end(); ++itr) {
        cout << '\t' << itr->first << '\t' << itr->second << '\n';
    }
    cout << endl;
    */
    

    //Best-First-Search
    // 1) Create an empty PriorityQueue -- minPQcost
    // 2) Insert "start" in pq.
    // 3) Until PriorityQueue is empty
   
    unexplored = out;
    unexplored.erase(startNode);
    explored.insert(startNode);

    int i, j, startNodeIndex;
    double tempVal = 0.0; 
    bool TFvalue = false;
    string targetName, tempName;
    startNodeIndex = GetIndex(out, startNode);
    for (i = 0; i < out.size(); i++) {
        if (vertArr[i][startNodeIndex] == 1)
        {
            targetName = GetElementName(out, i); //point out adjacent city
            if (explored.find(targetName) != explored.end())
            {
                continue;
            }
            else
            {
                TFvalue = IsGoalState(targetName, endNode);    //check if goal is reached
                unexplored.erase(targetName);        //update unexplored list of cities
                explored.insert(targetName);         //update explored list of cities
                auto it = TnC.find(targetName);      //locate its cost from target in TnC map
                if (it == TnC.end()) {
                    continue;
                }
                else {
                    minPQcost.push(it->second);
                }
            }
        
        }
    }

    while (!minPQcost.empty() and TFvalue == false)
    {
        tempVal = minPQcost.top();
        minPQcost.pop();

        for (auto &it : TnC) {
            if (it.second == tempVal) {
                targetName = it.first;
                break;
            }
        }

        startNodeIndex = GetIndex(out, targetName);

        for (i = 0; i < out.size(); i++) {
            if (vertArr[i][startNodeIndex] == 1)
            {
                targetName = GetElementName(out, i); //point out adjacent city
                if (explored.find(targetName) != explored.end())
                {
                    continue;
                }
                else
                {
                    TFvalue = IsGoalState(targetName, endNode);    //check if goal is reached
                    if (TFvalue == true)
                    {
                        cout << endl;
                        cout << "The route is " << endNode << " -> ";
                        while (endNode != startNode) {
                            int nodeIndex = GetIndex(out, endNode);
                            for (int i = 0; i < out.size(); i++) {
                                if (vertArr[i][nodeIndex] == 1)
                                {
                                    tempName = GetElementName(out, i); //point out adjacent city which already explored
                                    if (explored.find(tempName) != explored.end())
                                    {
                                        cout << tempName;
                                        explored.erase(tempName);
                                        endNode = tempName;
                                        if (endNode == startNode)
                                        {
                                            return 0;
                                        }
                                        cout << " -> ";
                                        
                                    }
                                }
                            }
                        }

                        return 0;
                    }
                    unexplored.erase(targetName);        //update unexplored list of cities
                    explored.insert(targetName);         //update explored list of cities
                    auto it = TnC.find(targetName);      //locate its cost from target in TnC map
                    if (it == TnC.end()) {
                        continue;
                    }
                    else {
                        minPQcost.push(it->second);
                    }
                    cout << targetName << endl;
                }
            }
        }
    }
    

    
    return 0;
}

