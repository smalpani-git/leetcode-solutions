// Solution to leetcode sudoku solver puzzle (hard)

// General approach - backtracking.
// Go from slot to slot and if it is empty, assign a feasible value in range (1-9),
// And then do the same for the next slot.
// If for any slot no value in the range is feasible, backtrack, to the previous
// slot to try the next value in the range for that slot and try to go forward
// again. 

// Time Complexity:
// Actual time complexity is O(1) because the board is constant size. 
// But let's try to solve assuming that the board is NxN.
// In the worst case, each recusive call makes

// T(N*N) = b + T(N*N - 1)  , when the value at the position r,c is fixed
// T(N*N) = c*N + N*T(N*N -1) , otherwise  (cN work is done in is valid call,
//                              maximum N recursive calls on the grid of size N*N-1
// This can't be solved by the master method, but we can reason about this in a different
// way. For every slot in the puzzle that doesn't have a pre-provisioned value we try
// all possible N values, and there can be maximum N*N empty slots, so we try:
// 9*9*9 .... N*N times (at max)
// So the time complexity is O( 9**(N*N) ) 
// Of course the number of empty slots is much lesser.
// Feasible improvements:

// 1. It is possible to scan the grid initially and create a reduced 
// set of candidates by eliminating values that are not possible. 
// E.g. For any cell [r,c] the values in the row r, col c, and the
// 3x3 grid to which the cell belongs are eliminated. This can
// significantly reduce the recursion depth at each level. 

// 2. Once we have created candidate sets per position, we can start with
// the slot that has least number of candidates and recurse in that order. 
// This way when we are backtracking, we only backtrack to the topmost level
// only a few times. This should guide us to the solution fast.

// 3. Solve in parallel (replicate the board at each recursion level)



class Solution {

// Function returns true if the value v is acceptable as a valid
// value for the board at co-ordindates [r,c]
bool isValid(vector<vector<char>>& board, int r, int c, char v) {

        // Check the row r at all columns that there is no existing v.
        for(int col=0; col<9; ++col) {
            if(board[r][col] == v) {
                return false;
            }
        }

        // Check the column c at all rows that there is no existing v.
        // One of the checks overlaps with a check above but we don't
        // care.
        for(int row=0; row<9; ++row) {
            if(board[row][c] == v) {
                return false;
            }
        }

        // Get the bounds of 3x3 grid to which board[r,c] belongs.
        int gridStartRow = r/3 * 3;
        int gridStartCol = c/3 * 3;
        int nextGridRow = gridStartRow + 3;
        int nextGridCol = gridStartCol + 3;

        // Check there is no value v in the 3x3 around board[r,c]
        // Some of these checks (exactly 5) are redundant with 
        // what was already checked earlier. However filtering out
        // the redundant check themselves is equally expensive as
        // brute comparison if not more.
        for(int row=gridStartRow; row<nextGridRow;  ++row) {
            for(int col=gridStartCol; col<nextGridCol; ++col) {
                if(board[row][col] == v) {
                    return false;
                }
            }
        }

        // The value is a valid for board[r,c]
        return true;
    }

    // Helper function that returns true when it solves the board. 
    // This specific invocation would select the right value for 
    // board[r,c] that solves the board. 
    // If it can't then it returns false and leaves board[r,c] to '.' 
    bool solveSudokuHelp(vector<vector<char>>& board, int row, int col) {
        if(row == 9) {
            // Reached row 9, nothing more to solve.
            return true;
        } else if(board[row][col] != '.') {
            // The value at the board[row,col] is fixed already, solve for
            // the next position.
            if(col==8) {
                // We are at the end of the current row, move to next column.
                return solveSudokuHelp(board,row+1,0);
            } else {
                // Next column, current row.
                return solveSudokuHelp(board,row,col+1);
            }
        } else {
            // Try value from 1 to 9 in order.
            for(char candidate='1';candidate <= '9'; ++ candidate) {
                if(isValid(board,row,col,candidate)) {
                    // If the value is valid for this position, set it. And
                    // kick the can down the road. 
                    board[row][col] = candidate;
                    if(col==8) {
                        // Puzzle was solved by using our candidate return true.
                        if(solveSudokuHelp(board,row+1,0)) {
                            return true;
                        }
                    } else {
                        // Puzzle was solved by using our candidate return true.
                        if(solveSudokuHelp(board,row,col+1)) {
                            return true;
                        }
                    }
                }
            }
            // Puzzle not solved by trying all the possible values 1-9, backtrack,
            // set the value back to '.' and return false.
            // If the caller has any more validate candidates for the position they 
            // would try it. Otherwise they would back track too.
            board[row][col] = '.';
            return false;
        }
        return false;
    }


public:
    void solveSudoku(vector<vector<char>>& board) {
        // Solve with the help of the helper function.
        // The problem assumes that there is a solution to the puzzle so 
        // ignore the return value.
        solveSudokuHelp(board,0,0);
    }
};
