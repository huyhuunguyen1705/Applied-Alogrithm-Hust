/*
Given a chess board N x N on which there are K being placed in some cells. Compute the number of solutions to place other
N - K queens in other cells such that among N queens on the board, no two queens attack each other.
A board is represented by a NxN matrix A in which A[i,j] = 1 if there is a queen placed in cell (i,j), and A[i,j] = 0, otherwise.
Input
Line 1: contains a positive integer N (1 <= N <= 12)
Line i+1 (i = 1, 2, . . ., N): contains the ith row of the matrix A
Output
Write the number of solutions
Example
Input 
4
0 1 0 0
0 0 0 0
0 0 0 0
0 0 1 0
Output
1
Input 
5
0 1 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
Output 
2
*/
#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 12;

int N, solutions = 0;
vector<vector<int>> board(MAX_N, vector<int>(MAX_N, 0));
vector<bool> col(MAX_N, false), diag1(2 * MAX_N, false), diag2(2 * MAX_N, false);

void backtrack(int row, int queens_left) {
    if (queens_left == 0) {
        solutions++;
        return;
    }
    if (row >= N) {
        return;
    }

    // Nếu hàng này đã có quân hậu sẵn, chuyển sang hàng tiếp theo
    bool has_queen = false;
    for (int col_index = 0; col_index < N; col_index++) {
        if (board[row][col_index] == 1) {
            has_queen = true;
            break;
        }
    }
    if (has_queen) {
        backtrack(row + 1, queens_left);
        return;
    }

    // Thử đặt quân hậu ở các cột còn trống
    for (int col_index = 0; col_index < N; col_index++) {
        if (!col[col_index] && !diag1[row - col_index + N - 1] && !diag2[row + col_index]) {
            // Đặt quân hậu
            col[col_index] = diag1[row - col_index + N - 1] = diag2[row + col_index] = true;
            backtrack(row + 1, queens_left - 1);
            // Gỡ quân hậu
            col[col_index] = diag1[row - col_index + N - 1] = diag2[row + col_index] = false;
        }
    }
}

int main() {
    cin >> N;

    int preplaced = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
            if (board[i][j] == 1) {
                preplaced++;
                col[j] = true;
                diag1[i - j + N - 1] = true;
                diag2[i + j] = true;
            }
        }
    }

    if (preplaced > N) {
        cout << 0 << endl;
        return 0;
    }

    backtrack(0, N - preplaced);
    cout << solutions << endl;

    return 0;
}
