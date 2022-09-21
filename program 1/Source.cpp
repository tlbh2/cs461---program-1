#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <list>
#include <set>
#include <sstream>
using namespace std;

int vertArr[47][47]; //the adjacency matrix initially 0

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
    int Index = 0;

    // Traverse the Set
    for (auto u : S) {
        if (u == K)
            return Index;
        Index++;
    }

    // If K is not present in the set
    return -1;
}

int main() {

    string line, substrings, firstWord;
    int uu = 0, vv = 0;
    const char delim = ' ';
    set<string> out; //use set to store non-duplicate values == unique values

    ifstream myfile("Adjacencies.txt");
    if (myfile.good())  
    {
        while (getline(myfile, line))
        {
            // X is an object of stringstream that references the 'line' string  
            stringstream X(line);
            //split string into substring using delimiter 
            while (getline(X, substrings, delim))
            {
                out.insert(substrings);
            }

        }
        myfile.close();
    }
    else cout << "There is no such file exists\n";

    //output set
    for (set<string>::iterator itr = out.begin(); itr != out.end(); itr++) {
        cout << *itr << " ";
    }
    cout << endl;
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
                if (substrings == " ") {
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

    displayMatrix(out.size());

    return 0;
}

