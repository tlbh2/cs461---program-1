#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <list>
#include <set>
#include <sstream>
#include <map>
using namespace std;

int vertArr[46][46]; //the adjacency matrix initially 0

struct XYcoordinates
{
    XYcoordinates() :  x(0.0), y(0.0) {}
    XYcoordinates( float newX, float newY)
       : x(newX), y(newY) {}

    float x, y;
};

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
    return 0;
}

int main() {

    string line, substrings, firstWord, townName;
    int uu = 0, vv = 0;
    float X = 0.0, Y= 0.0 ;
    const char delim = ' ';
    set<string> out; //use set to store non-duplicate values == unique values
    map<string, XYcoordinates> townCoordinates;

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
    int count = 0;
    for (set<string>::iterator itr = out.begin(); itr != out.end(); itr++) {
        cout << count << "-" << * itr << endl;
        count++;
    }
    cout << out.size() << endl;
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

    displayMatrix(out.size());

    //read file coordinates.txt and store value to map for easy access
    ifstream coordinatesFile("coordinates.txt");
    if (coordinatesFile.good())
    {
        while (coordinatesFile >> townName >> X >> Y)
        {
            XYcoordinates tempObject(X,Y);
            townCoordinates.insert(pair<string, XYcoordinates>(townName, tempObject));
        }
        coordinatesFile.close();
    }

    //print out coordinates map
    map<string, XYcoordinates>::iterator itr;
    cout << "\nThe map gquiz1 is : \n";
    cout << "\tKEY\tELEMENT\n";
    for (itr = townCoordinates.begin(); itr != townCoordinates.end(); ++itr) {
        cout << '\t' << itr->first << '\t' << itr->second.x << '\t' << itr->second.y
            << '\n';
    }
    cout << endl;

    
    return 0;
}

