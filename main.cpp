#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

enum class State
{
	kEmpty,
	kObstacle
};

// * - - - Function Prototypes - - - *
void PrintBoard(const std::vector<std::vector<State>> &board);
vector<vector<State>> ReadBoardFile(std::string path);
vector<State> ParseLine(std::string points);
std::string CellString(State state);
vector<vector<State>> Search(vector<vector<State>> board, vector<int> start, vector<int> goal);
// - - - - - - - - - - - - - - - - - - 




// * - * - * M A I N * - * - *
int main()
{
	vector<vector<State>> board = ReadBoardFile("board1.txt");
	vector<int> start;
	vector<int> goal;
	vector<vector<State>> solution = Search(board, start, goal);
	PrintBoard(solution);
	
	return 0;
}




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
	if (cell == State::kObstacle)
	{
		return "X ";
	}
	else
	{
		return "0 ";
	}
}

// Search function will get a board, start and goal coordinates as input. 
vector<vector<State>> Search(vector<vector<State>> board, vector<int> start, vector<int> goal)
{
	std::cout << "No path found!\n";
	return {};
}
