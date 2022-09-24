//Class: CS315-002 Spring 2022
//Date: 04/14/2022
//Assignment: PA2
//
//Program Name: pa2s22.cpp
//Author: Aaron Moseley
//SID: 9774
//Description:
//		-Takes in 4 numbers describing the size of a hiking trail and the positions of 3 people
//		-Uses BFS to find the shortest path that they could take to be at the same position
//		-Finds the total distance of that path and displays it
//Compilation g++ pa2s22.cpp -o pa2774
//Environment: 
//		-g++ -version: gcc version 9.3.0 (Ubuntu 9.3.0-17ubuntu1~20.04)
//		-uname -a: Linux ajmo276 5.4.0-92-generic #103-Ubuntu SMP Fri Nov 26 16:13:00 UTC 20    21 x86_64 x86_64 x86_64 GNU/Linux
//Synopsis: ./pa2774 < input.txt
//		
//		input.txt:
//		3 1 2 3
//		r g r
//		g g g
//		r g r
//
//		Output:
//		ajm9774
//		2
//
//		input.txt:
//		4 2 3 4
//		r b r g
//		b b r g
//		r r g b
//		g g b r
//
//		Output:
//		ajm9774
//		oo
//		
//
//Method: Breadth-First Search
//Running time: O(n^3) where n is the number of junctions
//Bugs: None
//Extras: None
//References:
//		-Practicum on 04/14/2022
//		For general information and learning about tuples/assert
//

#include <cassert>
#include <queue>
#include <tuple>
#include <string>
#include <iostream>
#include <climits>

using namespace std;

typedef tuple<int, int, int> itriple; //marks states
typedef queue<itriple> BFSqueue; //used for BFS, holds states

bool isEndState(itriple state)
{
	//Returns true if all the positions are equal
	return get<0>(state) == get<1>(state) && get<1>(state) == get<2>(state);
} //isEndState

int main()
{
	//Takes in n and the positions, makes the start state tuple to be used later
	int n;
	cin >> n;

	assert(n > 0 && n <= 50);

	int pos1, pos2, pos3;
	cin >> pos1 >> pos2 >> pos3;

	assert(pos1 <= n && pos1 > 0);
	pos1--;
	assert(pos2 <= n && pos2 > 0);
	pos2--;
	assert(pos3 <= n && pos3 > 0);
	pos3--;

	itriple startState = itriple(pos1, pos2, pos3);

	//Sets up arrays for the adjacency grid and the distances for all states
	itriple parent[n][n][n];
	char grid[n][n];
	int dist[n][n][n];

	//Takes in the grid and sets each distance to an unreachable value
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			char nextTile;
			cin >> nextTile;
			grid[i][j] = nextTile;

			for(int k = 0; k < n; k++)
			{
				dist[i][j][k] = n * n * n + 1;
				parent[i][j][k] = itriple(-1, -1, -1);
			}
		}
	}

	//Tests the grid input
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			assert(grid[i][j] == grid[j][i]);
		}
	}

	//Tests input
	/*cout << n << " " << get<0>(startState) << " " << get<1>(startState) << " " << get<2>(startState) << endl;

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			cout << grid[i][j] << " ";
		}

		cout << endl;
	}*/

	//Sets up for BFS
	BFSqueue searchQueue;
	itriple currState = startState;
	dist[get<0>(startState)][get<1>(startState)][get<2>(startState)] = 0;

	while(!isEndState(currState))
	{		
		//Adds all states where the third person can move, sets the distance
		char color12 = grid[get<0>(currState)][get<1>(currState)];
		for(int i = 0; i < n; i++)
		{
			if(i != get<2>(currState) && grid[get<2>(currState)][i] == color12)
			{
				itriple newState = itriple(get<0>(currState), get<1>(currState), i);
				if(dist[get<0>(currState)][get<1>(currState)][get<2>(currState)] + 1 < dist[get<0>(newState)][get<1>(newState)][get<2>(newState)])
				{
					dist[get<0>(newState)][get<1>(newState)][get<2>(newState)] = dist[get<0>(currState)][get<1>(currState)][get<2>(currState)] + 1;
					searchQueue.push(newState);
					
					if(get<0>(parent[get<0>(newState)][get<1>(newState)][get<2>(newState)]) == -1)
					parent[get<0>(newState)][get<1>(newState)][get<2>(newState)] = currState;
				}
			}
		}

		//Same thing but for second person
		char color13 = grid[get<0>(currState)][get<2>(currState)];
                for(int i = 0; i < n; i++)
                {
                        if(i != get<1>(currState) && grid[get<1>(currState)][i] == color13)
                        {
                                itriple newState = itriple(get<0>(currState), i, get<2>(currState));
                                if(dist[get<0>(currState)][get<1>(currState)][get<2>(currState)] + 1 < dist[get<0>(newState)][get<1>(newState)][get<2>(newState)])
                                {
                                        dist[get<0>(newState)][get<1>(newState)][get<2>(newState)] = dist[get<0>(currState)][get<1>(currState)][get<2>(currState)] + 1;
					searchQueue.push(newState);

					if(get<0>(parent[get<0>(newState)][get<1>(newState)][get<2>(newState)]) == -1)
					parent[get<0>(newState)][get<1>(newState)][get<2>(newState)] = currState;
                                }
                        }
                }

		//Same thing but for first person
		char color23 = grid[get<1>(currState)][get<2>(currState)];
		for(int i = 0; i < n; i++)
                {
                        if(i != get<0>(currState) && grid[get<0>(currState)][i] == color23)
                        {
                                itriple newState = itriple(i, get<1>(currState), get<2>(currState));
                                if(dist[get<0>(currState)][get<1>(currState)][get<2>(currState)] + 1 < dist[get<0>(newState)][get<1>(newState)][get<2>(newState)])
                                {
                                        dist[get<0>(newState)][get<1>(newState)][get<2>(newState)] = dist[get<0>(currState)][get<1>(currState)][get<2>(currState)] + 1;
					searchQueue.push(newState);

					if(get<0>(parent[get<0>(newState)][get<1>(newState)][get<2>(newState)]) == -1)
					parent[get<0>(newState)][get<1>(newState)][get<2>(newState)] = currState;
                                }
                        }
                }

		//Tests if the path is reachable, prints and returns if it isn't
		if(searchQueue.empty())
		{
			cout << endl << "ajm9774" << endl << "oo" << endl;
			return 0;
		}
	
		//Sets new current state
		currState = searchQueue.front();
		searchQueue.pop();
	}

	//Prints result if path is reachable
	cout << endl << "ajm9774" << endl;
	cout << dist[get<0>(currState)][get<1>(currState)][get<2>(currState)] << endl;

	while(currState != startState)
	{
		cout << get<0>(currState) + 1 << " " << get<1>(currState) + 1 << " " << get<2>(currState) + 1 << endl;
		currState = parent[get<0>(currState)][get<1>(currState)][get<2>(currState)];
	}

	cout << get<0>(startState) + 1 << " " << get<1>(startState) + 1 << " " << get<2>(startState) + 1 << endl;

	return 0;
} //main
