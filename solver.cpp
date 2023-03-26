#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include "puzzle.h"

constexpr int N_DIR = 4;
constexpr int d_i[N_DIR] = {0, 0, +1, -1};
constexpr int d_j[N_DIR] = {+1, -1, 0, 0};
constexpr int direction[N_DIR] = {'R', 'L', 'D', 'U'};

constexpr int MAX_SEARCH_STEPS = 100;

bool dfs(int cur_steps, int prev_direction, int max_search_steps, std::string &path, Puzzle &puzzle)
{
    int limit = puzzle.h_val();
    // reaches exactly the target state
    if (limit == 0)
        return true;

    // pruning
    if (cur_steps + limit > max_search_steps)
        return false;

    for (int dir = 0; dir < N_DIR; dir++)
    {
        if (dir == (prev_direction ^ 1))
        {
            continue; // 如果是回头方向，放弃
        }

        int next_i = puzzle.epsilon_row + d_i[dir];
        int next_j = puzzle.epsilon_col + d_j[dir];
        if (puzzle.out_of_range(next_i, next_j))
        {
            continue;
        }

        path.push_back(direction[dir]);
        std::swap(puzzle.board[next_i][next_j], puzzle.epsilon_element());
        std::swap(next_i, puzzle.epsilon_row);
        std::swap(next_j, puzzle.epsilon_col);

        if (dfs(cur_steps + 1, dir, max_search_steps, path, puzzle))
            return true;

        std::swap(next_j, puzzle.epsilon_col);
        std::swap(next_i, puzzle.epsilon_row);
        std::swap(puzzle.board[next_i][next_j], puzzle.epsilon_element());
        path.pop_back();
    }

    return false;
}

bool ida_star(std::string &path, Puzzle &puzzle)
{
    for (int search_steps = puzzle.h_val(); search_steps <= MAX_SEARCH_STEPS; search_steps++)
    {
        if (dfs(0, -1, search_steps, path, puzzle))
            return true;
    }
    return false;
}

Puzzle setup_problem()
{
    const int n = 5;
    const int m = 4;

    // epsilon 使用 0 标注
    const int input_data[] = {
        5, 1, 12, 11,
        17, 6, 8, 4,
        3, 0, 2, 19,
        14, 9, 10, 7,
        18, 13, 15, 16};
    std::vector<std::vector<int>> board(n);
    for (int i = 0; i < n; i++)
    {
        board[i].reserve(m);
        for (int j = 0; j < m; j++)
        {
            board[i].push_back(input_data[i * m + j]);
        }
    }

    return Puzzle(board);
}

int main()
{
    Puzzle puzzle = setup_problem();

    std::string path;

    if (puzzle.solvable() == false)
    {
        printf("Unsolvable.\n");
        return 0;
    }

    if (ida_star(path, puzzle) == false)
    {
        printf("IDA-star search reaches maximum step!\n");
        return 0;
    }

    printf("Total %d steps:\n", path.length());
    for (int i = 0; i < path.length(); i++)
    {
        printf("%c ", path[i]);
        if ((i + 1) % 5 == 0)
        {
            printf("\n");
        }
    }
    return 0;
}