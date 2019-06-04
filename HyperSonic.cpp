//============================================================================
// Name        : HyperSonic.cpp
// Author      : Chelsea Jaculina & Nick Dineros
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// Created on May 6, 2018

#include <iostream> // library for user input and output
#include <cstdlib> // c++ standard general utilities library
#include <string> // string library
#include <fstream> // file library
#include <sstream> // string streams
#include <ctype.h> // c standard library declares a set of function to classify and transforms individual characters
#include <stdio.h> // input and output operations
#include <limits.h> // determines various properties of the various variable types

using namespace std; // standard namespace. provides a scope to the identifiers

const int numOfCities = 30; // constant for the number of airport and cities to be tested

/*
 * minDistance
 * This function finds the vertex (airport) with the minimum distance
 * that has not yet been included in the shortest path tree
 * dist[] - array to check for distances
 * sptSet - spanning set tree. sets the particular value to be either true or false
 */
int minDistance(int dist[], bool sptSet[])
{

   int min = INT_MAX;
   int min_index; // initialize the min value

   	// iterative to find the airport with minimum distance
   for (int v = 0; v <  numOfCities; v++)
   {
	   if (sptSet[v] == false && dist[v] <= min)
       {
		   min = dist[v], min_index = v;
       }
   }
   return min_index;
}

/*
 * Print Path
 * Function that helps print out the flight path
 */
void printPath(int parent[], int j, string cities[numOfCities]){
	// Base case: if j is source
	if (parent[j] == -1){
		return;
	}
	printPath(parent, parent[j], cities);

	cout << " --> " << cities[j];
}

/*
 * PrintDijkstra
 * Function that prints out information for the Djikstra's algorithm
 */
void printDijkstra(int dist[], int n, string destination, string cities[numOfCities], int parent[])
{

    for (int i = 1; i <  numOfCities; i++)
    {
    	while(destination == cities[i]){
    		cout << "\t\tSFO to " << destination << "'s Flight Information:" << endl;
    		cout << "--------------------------------------------------------------------" << endl;
    		cout << "DEPARTURE Airport: SFO" << endl;
    		cout << "ARRIVAL Airport: " << destination << endl;
    		cout << "FLIGHT PATH......................... SFO";
    		printPath(parent, i, cities);
    		cout << endl;
    		cout << "MINIMUM DISTANCE FOR FLIGHT........................ " << dist[i] << " " << "miles" << endl;
    		cout << "MINIMUM COST FOR FLIGHT........................ $" << dist[i] * 0.20 << endl;
    		break;
    	}
    }
}
/*
 * Djikstra
 * Follows Djikstra's algorithm
 * Function that is implemented for Dijkstra's single source shortest path algorithm
 */
void dijkstra(int matrix[numOfCities][numOfCities], int src, string destination, string cities[30])
{
    int dist[numOfCities];  // The output array. dist[i] will hold
                  // the shortest distance from src to i

    // sptSet[i] will be true if vertex i is included / in shortest path tree or shortest distance from src to i is finalized
    bool sptSet[numOfCities];

    // Parent array to store shortest path tree
    int parent[numOfCities];

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i <  numOfCities; i++)
    {
        parent[0] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < numOfCities-1; count++)
    {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to src
        // in first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < numOfCities; v++)

            // Update dist[v] only if is not in sptSet, there is
            // an edge from u to v, and total weight of path from
            // src to v through u is smaller than current value of
            // dist[v]
            if (!sptSet[v] && matrix[u][v] &&
                dist[u] + matrix[u][v] < dist[v])
            {
                parent[v]  = u;
                dist[v] = dist[u] + matrix[u][v];
            }
    }

    // print the constructed distance array
    printDijkstra(dist, numOfCities, destination, cities, parent);
}

/*
 * Finds the shortest path from the departure airport to the arrival airport
 */
void find_path(int u, int v, int dist[][numOfCities], int pred[][numOfCities], string cities[])
{
    if(u != v){
    	find_path(u, pred[u][v], dist, pred, cities);
    }
    cout << " --> " << cities[v];
}


/*
 * Print Method
 * This functions prints for option #2: display the flight distances
 */
void printFlightDistances(string cities[numOfCities], int matrix[numOfCities][numOfCities])
{
	cout << "    ";
    for(int i = 0; i < numOfCities; i++) // top row
    {
	cout << cities[i]  << " ";
    }

    cout << "\n";

    for (int a = 0; a <  numOfCities; a++) {
    	cout << cities[a] << "\t";
        for (int b = 0; b <  numOfCities; b++) {
            cout << matrix[a][b] << "  ";
            if(matrix[a][b] == 0){
            	cout << "  ";
            }
        }
    cout << endl;
    }
}

/*
 * MAIN METHOD
 * The function displays an interface so that users can select a flight destination.
 * It displays the shortest path from the departure airport to the arrival airport.
 * In addition, it provides the user the minimum cost for the flight.
 */
int main()
{
        int x, y; // variables for the row and column

        int matrix[numOfCities][numOfCities]; // creates a 30 x 30 matrix

        int hold;

        int optionChoice = 0; // int variable for option choice

        string destination; // destination variable

        // an array of 30 cities of type string
        // this array contains the top 30 busiest airports in the world
        string cities[numOfCities] = {"SFO", "ATL", "PEK", "DXB", "HND",
       "LAX", "ORD", "LHR", "HKG", "PVG",
        "CDG","AMS", "DFW", "CAN", "FRA",
        "IST","DEL", "CGK", "SIN", "ICN",
        "DEN", "BKK", "JFK", "KUL", "MAD",
        "CTU", "LAS", "BCN", "BOM","YYZ"};

        ifstream in("input.txt");

        if (!in) {
            cout << "No file was found. Please make sure you have an input.txt file.\n";
            return 0;
        }

        for (y = 0; y <  numOfCities; y++) {
            for (x = 0; x < numOfCities; x++) {
                in >> matrix[y][x];
            }
        }
        in.close();

        while (optionChoice== 0)
        {
        	cout << "--------------------------------------------------------------------" << endl;
         	cout << "\t\tWELCOME TO HYPER SONIC - Flight Optimizer" << endl;
         	cout << "--------------------------------------------------------------------" << endl;
        	cout << "\t\t*HOME* Menu - Select an Option Number"<< endl;
        	cout << "--------------------------------------------------------------------" << endl;

        	cout << "0 - Terminate" << endl;
        	cout << "1 - Select a Destination" << endl;
        	cout << "2 - View Flight Distances (miles) "<< endl;
        	cout << "Option Choice: ";


        	cin >> optionChoice; // users's option choice

        	if (optionChoice == 1)
        	{
        		cout << "--------------------------------------------------------------------" << endl;
        		cout << "\t\t OPTION 1: SELECTING A DESTINATION" << endl;
        		cout << "--------------------------------------------------------------------" << endl;
        		cout <<"DEPARTURE: SFO";
        		cout << endl;
        		cout << "CURRENT AVAILABLE AIRPORTS:\n";
        			for(int k = 0; k <  numOfCities; k++){
        				cout << "\t" + cities[k] << " ";
        					if ((k+1) % 6 == 0){
        							cout << "\n";
        						}
        			}
        		cout << endl;
        		cout << "SELECT AN ARRIVAL AIRPORT: ";
            	cin >> destination;

            	for (int p = 0; p < destination.size(); p++){
            		destination.at(p) = toupper(destination.at(p));
            	}

            	bool valid = false;
            	int location;

            	for (int s = 1; s <  numOfCities; s++){
            		if(!destination.compare(cities[s])){
            			location = s;
            			valid = true;
            			hold = matrix[0][location];
            			matrix[0][location] = 99999;
            			cout << "--------------------------------------------------------------------" << endl;
            			dijkstra(matrix, 0, destination, cities); // prints out the minimum cost/shortest path using Djiikstra's algorithm
            			cout << endl;
                    	//floydWarshall(matrix, destination, cities); // prints out the minimum cost/shortest path using Floyd Warshall's algorithm
                    	matrix[0][location] = hold;
            			break;
            		}

            	}

            	optionChoice = 0;
        	}
        	else if(optionChoice == 2)
        	{
        		cout << "--------------------------------------------------------------------" << endl;
        		cout << "\t\t OPTION 2: VIEW FLIGHT DISTANCES (miles) " << endl;
        		printFlightDistances(cities, matrix);
        		optionChoice = 0;
        		cout << endl << endl << endl;
        	}
        	else if (optionChoice == 0)
        	{
        		cout << "--------------------------------------------------------------------" << endl;
        		cout << "\t\t OPTION 3: Program has terminated. " << endl;
        		cout << "\t\t Thank you for using Hyper Sonic! " << endl;
        		cout << "--------------------------------------------------------------------" << endl;
        		break;
        		return 0;
        	}
        }
 }

