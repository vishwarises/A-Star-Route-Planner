#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

enum class State
{
	kEmpty,
	kObstacle,
	kClosed,
	kPath
};

// * - - - - - - - - - - - - - Function Prototypes - - - - - - - - - - - - - - - - *
void PrintBoard(const std::vector<std::vector<State>> &board);
vector<vector<State>> ReadBoardFile(std::string path);
vector<State> ParseLine(std::string points);
std::string CellString(State state);
vector<vector<State>> Search(vector<vector<State>> board, vector<int> start, vector<int> goal);
int Heuristic(int x1, int y1, int x2, int y2);
void AddToOpen(int x, int y, int g, int h, vector<vector<int>>& open, vector<vector<State>>& grid);
bool Compare(std::vector<int> node1, std::vector<int> node2);
void CellSort(vector<vector<int>>* v);
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  



//  M A I N 
int main()
{
	vector<vector<State>> board = ReadBoardFile("board1.txt");
	vector<int> start;
	vector<int> goal;
	vector<vector<State>> solution = Search(board, start, goal);
	PrintBoard(solution);
	
	return 0;
}
// - - - - - - - - - - - - - - -



// * - - - FUNCTIONS - - - *
std::vector<State> ParseLine(std::string line)
{
	std::vector<State> result;
	std::istringstream stream(line);
	int n;
	char c;

	while (stream >> n >> c && c == ',') {
		if (n == 0) {
			result.push_back(State::kEmpty);
		}
		else {
			result.push_back(State::kObstacle);
		}
	}
	return result;
}

void PrintBoard(const std::vector<std::vector<State>> &board)
{
	for (const auto &i : board)
	{
		for (const auto& j : i)
		{
			std::cout << CellString(j);
		}
		std::cout << std::endl;
	}
}

vector<vector<State>> ReadBoardFile(std::string path)
{
	std::ifstream file(path);
	std::string line;
	vector<vector<State>> result;

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			if (!line.empty())
			{
				result.push_back(ParseLine(line));
			}
		}
		file.close();
	}
	else
	{
		std::cout << "Cannot open file!\n";
	}

	return result;
}

std::string CellString(State cell)
{
	switch (cell)
	{
	case State::kObstacle:
		return "X ";

	case State::kPath:
		return "- ";

	default:
		return "0 ";
	}
}

// Search function will get a board, start and goal coordinates as input. 
vector<vector<State>> Search(vector<vector<State>> board, vector<int> start, vector<int> goal)
{
	//Has all nodes from starting and its x, y, g, h. 
	std::vector<std::vector<int>> open;
	
	int x = start[0];
	int y = start[1];
	int goal_x = goal[0];
	int goal_y = goal[1];
	int g = 0;
	int h = Heuristic(x, y, goal_x, goal_y);

	AddToOpen(x, y, g, h, open, board);

	// Main while loop: process when open vector is non empty
	while (!open.empty())
	{
		// Sort the open list using CellSort, and get the current node.
		CellSort(&open);
		// Get the x and y values from the current node,
		// and set grid[x][y] to kPath.
		// Note:
		// The reason to sort from high to low:
		// It's easier to pop_back for c++ vectors:
		vector<int> cur_node = open.back();
		open.pop_back();

		x = cur_node[0];
		y = cur_node[1];
		board[x][y] = State::kPath;
		// Check if you've reached the goal. If so, return grid.
		if (x == goal[0] && y == goal[1]) return board;

		// If we're not done, expand search to current node's neighbors. This step will be completed in a later quiz.
		// ExpandNeighbors
	}

	std::cout << "No path found!\n";
	return {};
}


void CellSort(vector<vector<int>>* v)
{
	sort(v->begin(), v->end(), Compare);
}

// Finds the heuristic distance 
int Heuristic(int x1, int y1, int x2, int y2)
{
	return std::abs(x2 - x1) + std::abs(y2 - y1);
}


void AddToOpen(int x, int y, int g, int h, vector<vector<int>>& open, vector<vector<State>>& grid)
{
	//Creating a vector to add all nodes we come across
	std::vector<int> node = { x, y, g, h };
	open.push_back(node);

	//Marking the grids as visited 
	grid[x][y] = State::kClosed;
}

bool Compare(std::vector<int> node1, std::vector<int> node2)
{
	int f1 = node1[2] + node1[3];
	int f2 = node2[2] + node2[3];
	return f1 > f2;
}
