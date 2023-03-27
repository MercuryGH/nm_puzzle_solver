#pragma once
#include <vector>

struct Puzzle
{
    std::vector<std::vector<int>> board;

    int epsilon_row{-1};
    int epsilon_col{-1};

    constexpr static auto EPSILON_MARK = 0;

    Puzzle(std::vector<std::vector<int>> &board) : board(board)
    {
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[0].size(); j++)
            {
                if (board[i][j] == EPSILON_MARK)
                {
                    epsilon_row = i;
                    epsilon_col = j;
                    break;
                }
            }
        }
    }

    bool solvable() const
    {
        int n_inversion = 0;
        std::vector<bool> occurs(n_rows() * n_cols(), false);

        // 朴素求逆序对数目，可用归并排序法优化
        for (int i = 0; i < n_rows(); i++)
        {
            for (int j = 0; j < n_cols(); j++)
            {
                const int cur_element = board[i][j];
                if (cur_element == EPSILON_MARK)
                {
                    continue;
                }

                n_inversion += std::count(occurs.begin() + 1, occurs.begin() + cur_element, false);
                occurs[cur_element] = true;
            }
        }
        if (n_cols() % 2 == 1)
        {
            return (n_inversion % 2) == 0;
        }
        else
        {
            return ((n_inversion + (n_rows() - 1 - epsilon_row)) % 2) == 0;
        }
    }

    // 最优解下界
    int h_val() const
    {
        int ret = 0;
        for (int i = 0; i < n_rows(); i++)
        {
            for (int j = 0; j < n_cols(); j++)
            {
                const int cur_element = board[i][j];
                if (cur_element == EPSILON_MARK)
                    continue;

                int goal_i = (cur_element - 1) / n_cols();
                int goal_j = (cur_element - 1) % n_cols();
                ret += std::abs(goal_i - i) + std::abs(goal_j - j); // 曼哈顿距离
            }
        }
        return ret;
    }

    int &epsilon_element() { return board[epsilon_row][epsilon_col]; }
    int n_rows() const { return board.size(); }
    int n_cols() const { return board[0].size(); }
    bool out_of_range(int i, int j) const { return i < 0 || i >= n_rows() || j < 0 || j >= n_cols(); }
};