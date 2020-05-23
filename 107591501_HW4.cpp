#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cstring>
#include <climits>
#include <chrono> 
#include <fstream>
#include <iomanip>
using namespace std::chrono;
using namespace std;

vector<int> bf_solution_list; 

// implementation of traveling Salesman Problem 
int travllingSalesmanProblem(vector<vector<int>>& graph, int n, int s) 
{ 
    vector<int> possible_solution_list; 

	// store all vertex apart from source vertex 
	vector<int> vertex; 
	for (int i = 0; i < n; i++) 
		if (i != s) 
			vertex.push_back(i); 

	// store minimum weight Hamiltonian Cycle. 
	int min_path = INT_MAX; 
	do { 

		// store current Path weight(cost) 
		int current_pathweight = 0; 

        // reset the possible solution list
        possible_solution_list.erase(possible_solution_list.begin(), possible_solution_list.end());
		
		// compute current path weight 
		int k = s; 
		for (int i = 0; i < vertex.size(); i++) { 
			current_pathweight += graph[k][vertex[i]]; 
			k = vertex[i];
            possible_solution_list.push_back(k);
		} 
		current_pathweight += graph[k][s]; 

        if (current_pathweight < min_path){
            bf_solution_list.erase(bf_solution_list.begin(), bf_solution_list.end());
            for (int i = 0; i < possible_solution_list.size(); i++) {
                bf_solution_list.push_back(possible_solution_list[i]);
            }
        }

		// update minimum 
		min_path = min(min_path, current_pathweight); 
		
	} while (next_permutation(vertex.begin(), vertex.end())); 

	return min_path; 
} 


int N;
// Sentinal value for representing infinity
#define INF INT_MAX

vector<int> bb_solution_list; 

// State Space Tree nodes
struct Node
{
	// stores edges of state space tree
	// helps in tracing path when answer is found
	vector<pair<int, int>> path;

	// stores the reduced matrix
	// int reducedMatrix[N][N];
	vector<vector<int>> reducedMatrix;

	// stores the lower bound
	int cost;

	//stores current city number
	int vertex;

	// stores number of cities visited so far
	int level;
};

// Function to allocate a new node (i, j) corresponds to visiting
// city j from city i
Node* newNode(vector<vector<int>>& parentMatrix, vector<pair<int, int>> const &path,
			int level, int i, int j)
{
	Node* node = new Node;

	// stores ancestors edges of state space tree
	node->path = path;
	// skip for root node
	if (level != 0)
		// add current edge to path
		node->path.push_back(make_pair(i, j));
	
	// copy data from parent node to current node
	// memcpy(node->reducedMatrix, parentMatrix,
	// 	sizeof node->reducedMatrix);
	node->reducedMatrix = parentMatrix;
	
	// Change all entries of row i and column j to infinity
	// skip for root node
	for (int k = 0; level != 0 && k < N; k++)
	{
		// set outgoing edges for city i to infinity
		node->reducedMatrix[i][k] = INF;

		// set incoming edges to city j to infinity
		node->reducedMatrix[k][j] = INF;
	}
	
	// Set (j, 0) to infinity
	// here start node is 0
	node->reducedMatrix[j].at(0) = INF;

	// set number of cities visited so far
	node->level = level;

	// assign current city number
	node->vertex = j;

	// return node
	return node;
}

// Function to reduce each row in such a way that
// there must be at least one zero in each row
void rowReduction(vector<vector<int>>& reducedMatrix, vector<int>& row)
{
	// initialize row array to INF
	// fill_n(row, N, INF);
	for (int i=0; i<N; i++)
		row.push_back(INF);

	// row[i] contains minimum in row i
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (reducedMatrix[i][j] < row[i])
				row.at(i) = reducedMatrix[i][j];

	// reduce the minimum value from each element in each row
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (reducedMatrix[i][j] != INF && row[i] != INF)
				reducedMatrix[i][j] -= row[i];
}

// Function to reduce each column in such a way that
// there must be at least one zero in each column
void columnReduction(vector<vector<int>>& reducedMatrix, vector<int>& col)
{
	// initialize col array to INF
	// fill_n(col, N, INF);
	for (int i=0; i<N; i++)
		col.push_back(INF);

	// col[j] contains minimum in col j
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (reducedMatrix[i][j] < col[j])
				col.at(j) = reducedMatrix[i][j];

	// reduce the minimum value from each element in each column
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (reducedMatrix[i][j] != INF && col[j] != INF)
				reducedMatrix[i][j] -= col[j];
}

// Function to get the lower bound on
// on the path starting at current min node
int calculateCost(vector<vector<int>>& reducedMatrix)
{
	// initialize cost to 0
	int cost = 0;

	// Row Reduction
	// int row[N];
	vector<int> row;
	rowReduction(reducedMatrix, row);

	// Column Reduction
	// int col[N];
	vector<int> col;
	columnReduction(reducedMatrix, col);

	// the total expected cost
	// is the sum of all reductions
	for (int i = 0; i < N; i++)
		cost += (row[i] != INT_MAX) ? row[i] : 0,
			cost += (col[i] != INT_MAX) ? col[i] : 0;

	return cost;
}

// print list of cities visited following least cost
void printPath(vector<pair<int, int>> const &list)
{
	for (int i = 0; i < list.size(); i++)
		bb_solution_list.push_back(list[i].first);
		// cout << list[i].first << " - " << list[i].second << endl;
}

// Comparison object to be used to order the heap
struct comp {
	bool operator()(const Node* lhs, const Node* rhs) const
	{
		return lhs->cost > rhs->cost;
	}
};

// Function to solve Traveling Salesman Problem using Branch and Bound
int solve(vector<vector<int>>&  costMatrix)
{
	// Create a priority queue to store live nodes of search tree;
	priority_queue<Node*, std::vector<Node*>, comp> pq;

	vector<pair<int, int>> v;
	
	// create a root node and calculate its cost
	// The TSP starts from first city i.e. node 0
	Node* root = newNode(costMatrix, v, 0, -1, 0);
	
	// get the lower bound of the path starting at node 0
	root->cost = calculateCost(root->reducedMatrix);

	// Add root to list of live nodes;
	pq.push(root);

	// Finds a live node with least cost, add its children to list of
	// live nodes and finally deletes it from the list
	while (!pq.empty())
	{
		// Find a live node with least estimated cost
		Node* min = pq.top();

		// The found node is deleted from the list of live nodes
		pq.pop();

		// i stores current city number
		int i = min->vertex;

		// if all cities are visited
		if (min->level == N - 1)
		{
			// return to starting city
			min->path.push_back(make_pair(i, 0));

			// print list of cities visited;
			printPath(min->path);

			// return optimal cost
			return min->cost;
		}

		// do for each child of min
		// (i, j) forms an edge in space tree
		for (int j = 0; j < N; j++)
		{
			if (min->reducedMatrix[i][j] != INF)
			{
				// create a child node and calculate its cost
				Node* child = newNode(min->reducedMatrix, min->path,
					min->level + 1, i, j);

				/* Cost of the child =
					cost of parent node +
					cost of the edge(i, j) +
					lower bound of the path starting at node j
				*/
				child->cost = min->cost + min->reducedMatrix[i][j]
							+ calculateCost(child->reducedMatrix);

				// Add child to list of live nodes
				pq.push(child);
			}
		}

		// free node as we have already stored edges (i, j) in vector.
		// So no need for parent node while printing solution.
		delete min;
	}
	return 0;
}


int main() 
{	
	std::ifstream input_file("input.txt");

	size_t n;
	input_file >> n;

	vector<vector<int>> graph(n, vector<int>(n));

	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < n; j++)
			input_file >> graph[i][j];
	
	// brute force method
	int s = 0; 
    auto bf_start = high_resolution_clock::now();
	int bf_cost = travllingSalesmanProblem(graph, n, s);
	auto bf_stop = high_resolution_clock::now();
	auto bf_duration = duration_cast<nanoseconds>(bf_stop - bf_start);

    // write file to BF.txt
    ofstream bf_output_file("BF.txt");
    bf_output_file << "Solution : 0 - " ; 
    for (int i = 0; i < bf_solution_list.size(); i++) 
        bf_output_file << bf_solution_list[i] << " - "; 
    bf_output_file << "0" << endl;
	bf_output_file << "Cost     : " << bf_cost << endl;
	float bf_time = (bf_duration.count())/(1e+9); 
	bf_output_file << "Time     : " << std::fixed << std::setprecision(7) << bf_time << " s" << endl;
    bf_output_file.close(); 

	// branch & bound method
	N = n;
	auto bb_start = high_resolution_clock::now();
	int bb_cost = solve(graph);
	auto bb_stop = high_resolution_clock::now();
	auto bb_duration = duration_cast<nanoseconds>(bb_stop - bb_start);
	
	// write file to BB.txt
    ofstream bb_output_file("BB.txt");
    bb_output_file << "Solution : " ; 
    for (int i = 0; i < bb_solution_list.size(); i++) 
        bb_output_file << bb_solution_list[i] << " - "; 
    bb_output_file << "0" << endl;
	bb_output_file << "Cost     : " << bb_cost << endl;
	float bb_time = (bb_duration.count())/(1e+9);
	bb_output_file << "Time     : " << std::fixed << std::setprecision(7) << bb_time << " s" << endl;
    bb_output_file.close(); 

	return 0; 
}