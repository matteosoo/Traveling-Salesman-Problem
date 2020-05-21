// C++ program to solve Traveling Salesman Problem 
// using Branch and Bound. 
#include <bits/stdc++.h> 
#include <chrono> 
using namespace std::chrono;
using namespace std; 

int n;

// final_path[] stores the final solution ie, the 
// path of the salesman. 
vector<int> final_path; //[n+1]

// visited[] keeps track of the already visited nodes 
// in a particular path 
vector<bool> visited; //[n]

// Stores the final minimum weight of shortest tour. 
int final_res = INT_MAX; 

// Function to copy temporary solution to 
// the final solution 
void copyToFinal(int curr_path[]) 
{ 
    // reset final_path first 
    final_path.erase(final_path.begin(),final_path.end());
    // then update the current path to final path
	for (int i=0; i<n; i++)
		final_path.push_back(curr_path[i]); 
	final_path.push_back(curr_path[0]);
} 

// Function to find the minimum edge cost 
// having an end at the vertex i 
int firstMin(vector<vector<int>>& adj, int i) 
{ 
	int min = INT_MAX; 
	for (int k=0; k<n; k++) 
		if (adj[i][k]<min && i != k) 
			min = adj[i][k]; 
	return min; 
} 

// function to find the second minimum edge cost 
// having an end at the vertex i 
int secondMin(vector<vector<int>>& adj, int i) 
{ 
	int first = INT_MAX, second = INT_MAX; 
	for (int j=0; j<n; j++) 
	{ 
		if (i == j) 
			continue; 

		if (adj[i][j] <= first) 
		{ 
			second = first; 
			first = adj[i][j]; 
		} 
		else if (adj[i][j] <= second && 
				adj[i][j] != first) 
			second = adj[i][j]; 
	} 
	return second; 
} 

// function that takes as arguments: 
// curr_bound -> lower bound of the root node 
// curr_weight-> stores the weight of the path so far 
// level-> current level while moving in the search 
//		 space tree 
// curr_path[] -> where the solution is being stored which 
//			 would later be copied to final_path[] 
void TSPRec(vector<vector<int>>& adj, int curr_bound, int curr_weight, 
			int level, int curr_path[]) 
{ 
	// base case is when we have reached level N which 
	// means we have covered all the nodes once 
	if (level==n) 
	{
		// check if there is an edge from last vertex in 
		// path back to the first vertex 
		if (adj[curr_path[level-1]][curr_path[0]] != 0) 
		{ 
			// curr_res has the total weight of the 
			// solution we got 
			int curr_res = curr_weight + 
					adj[curr_path[level-1]][curr_path[0]]; 

			// Update final result and final path if 
			// current result is better. 
			if (curr_res < final_res) 
			{ 
				copyToFinal(curr_path); 
				final_res = curr_res; 
			} 
		} 
		return; 
	} 

	// for any other level iterate for all vertices to 
	// build the search space tree recursively 
	for (int i=0; i<n; i++) 
	{ 
		// Consider next vertex if it is not same (diagonal 
		// entry in adjacency matrix and not visited 
		// already) 
		if (adj[curr_path[level-1]][i] != 0 && 
			visited[i] == false) 
		{ 
			int temp = curr_bound; 
			curr_weight += adj[curr_path[level-1]][i]; 
            // cout << curr_weight << endl;

			// different computation of curr_bound for 
			// level 2 from the other levels 
			if (level==1) 
			curr_bound -= ((firstMin(adj, curr_path[level-1]) + 
							firstMin(adj, i))/2); 
			else
			curr_bound -= ((secondMin(adj, curr_path[level-1]) + 
							firstMin(adj, i))/2); 

			// curr_bound + curr_weight is the actual lower bound 
			// for the node that we have arrived on 
			// If current lower bound < final_res, we need to explore 
			// the node further 
			if (curr_bound + curr_weight < final_res) 
			{ 
				curr_path[level] = i; 
				// visited[i] = true;
                visited.at(i) = true;

				// call TSPRec for the next level 
				TSPRec(adj, curr_bound, curr_weight, level+1, 
					curr_path); 
			} 

			// Else we have to prune the node by resetting 
			// all changes to curr_weight and curr_bound 
			curr_weight -= adj[curr_path[level-1]][i]; 
			curr_bound = temp; 
            
			// Also reset the visited array 
			// memset(visited, false, sizeof(visited));
            visited.erase(visited.begin(), visited.end()); 
            for (int i = 0; i < n+1; i++)
                visited.push_back(0);
			for (int j=0; j<=level-1; j++) 
                visited.at(curr_path[j]) = true;
				// visited[curr_path[j]] = true;
		} 
	} 
} 

// This function sets up final_path[] 
void TSP(vector<vector<int>>& adj) 
{ 
	int curr_path[n+1]; 

	// Calculate initial lower bound for the root node 
	// using the formula 1/2 * (sum of first min + 
	// second min) for all edges. 
	// Also initialize the curr_path and visited array 
	int curr_bound = 0; 
	memset(curr_path, -1, sizeof(curr_path)); 
	// memset(visited, 0, sizeof(curr_path));
    // std::fill(visited.begin(), visited.begin()+n+1, 0);
    for (int i = 0; i < n+1; i++)
        visited.push_back(0);

	// Compute initial bound 
	for (int i=0; i<n; i++) 
		curr_bound += (firstMin(adj, i) + 
					secondMin(adj, i));

	// Rounding off the lower bound to an integer 
	curr_bound = (curr_bound&1)? curr_bound/2 + 1 : 
								curr_bound/2; 
    
	// We start at vertex 1 so the first vertex 
	// in curr_path[] is 0
    // visited[0] = true;  
    visited.at(0) = true;
	curr_path[0] = 0; 

	// Call to TSPRec for curr_weight equal to 
	// 0 and level 1 
	TSPRec(adj, curr_bound, 0, 1, curr_path); 
} 

// Driver code 
int main(int argc, char* argv[]) 
{ 
    freopen(argv[1], "r", stdin);
	// size_t n;
    std::cin >> n;

    vector<vector<int>> adj(n, vector<int>(n));

	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < n; j++)
			std::cin >> adj[i][j];

    auto start = high_resolution_clock::now();
	TSP(adj);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    // write file to BF.txt
    ofstream output_file("BB.txt");
    output_file << "Solution : " ; 
    for (int i=0; i<n; i++) 
	    output_file << final_path[i] << " - ";
    output_file << "0" << endl;
    output_file << "Cost     : " << final_res << endl;
    output_file << "Time     : " << (duration.count())/(1e+6) << " s" << endl;
    output_file.close(); 
	return 0; 
} 