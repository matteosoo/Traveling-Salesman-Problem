// CPP program to implement traveling salesman 
// problem using naive approach. 
#include <bits/stdc++.h> 
#include <chrono> 
#include <iomanip>
using namespace std::chrono;
using namespace std;

vector<int> solution_list; 

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
            solution_list.erase(solution_list.begin(), solution_list.end());
            for (int i = 0; i < possible_solution_list.size(); i++) {
                solution_list.push_back(possible_solution_list[i]);
            	}
	    }

		// update minimum 
		min_path = min(min_path, current_pathweight); 
		
	} while (next_permutation(vertex.begin(), vertex.end())); 

	// for (int i = 0; i < solution_list.size(); i++) { 
	//     cout << solution_list[i] << " " << endl ;
	// }

	return min_path; 
} 

// driver program to test above function 
int main(int argc, char* argv[]) 
{	
	freopen(argv[1], "r", stdin);
	size_t n;
	std::cin >> n;
	// std::cout << n <<std::endl;

	vector<vector<int>> graph(n, vector<int>(n));

	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < n; j++)
			std::cin >> graph[i][j];
	
	// for (size_t i = 0; i < n; i++)
	// 	for (size_t j = 0; j < n; j++)
	// 		std::cout << graph[i][j] <<std::endl;
		
	int s = 0; 

    	auto start = high_resolution_clock::now();
	int cost = travllingSalesmanProblem(graph, n, s);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start);

    	// write file to BF.txt
    	ofstream output_file("BF.txt");
    	output_file << "Solution : 0 - " ; 
	for (int i = 0; i < solution_list.size(); i++) 
		output_file << solution_list[i] << " - "; 
    	output_file << "0" << endl;
	output_file << "Cost     : " << cost << endl;
	float time = (duration.count())/(1e+9); 
	output_file << "Time     : " << std::fixed << std::setprecision(7) << time << " s" << endl;
    	output_file.close(); 
	return 0; 
}
