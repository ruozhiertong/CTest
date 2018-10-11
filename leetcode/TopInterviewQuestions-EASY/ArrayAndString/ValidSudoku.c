/*
 Valid Sudoku
  Go to Discuss
Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the 9 3x3 sub-boxes of the grid must contain the digits 1-9 without repetition.

A partially filled sudoku which is valid.

The Sudoku board could be partially filled, where empty cells are filled with the character '.'.

Example 1:

Input:
[
  ["5","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
Output: true
Example 2:

Input:
[
  ["8","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
Output: false
Explanation: Same as Example 1, except with the 5 in the top left corner being 
    modified to 8. Since there are two 8's in the top left 3x3 sub-box, it is invalid.
Note:

A Sudoku board (partially filled) could be valid but is not necessarily solvable.
Only the filled cells need to be validated according to the mentioned rules.
The given board contain only digits 1-9 and the character '.'.
The given board size is always 9x9.

*/

//just valid. A Sudoku board (partially filled) could be valid but is not necessarily solvable.
bool isValidSudoku(char** board, int boardRowSize, int boardColSize) 
{
 
	for(int i = 0; i < boardRowSize; i++)
	{
		for(int j = 0; j < boardColSize; j++)
		{
			if(board[i][j] == '.')
				continue;
			//check rule 1
			for(int col = 0; col < boardColSize; col++)
			{
				if(j == col)
					continue;
				if(board[i][j] == board[i][col])
					return 0;
			}

			//check rule 2
			for(int row = 0; row < boardRowSize; row++)
			{
				if(i == row)
					continue;
				if(board[i][j] == board[row][j])
					return 0;
			}
			//check rule 3
			int startRow = i / 3;
			int startCol = j / 3;

			for(int row = startRow*3 ; row < startRow*3 + 3; row++)
			{
				for(int col = startCol*3; col < startCol*3 + 3; col++)
				{
					if(i == row && j == col)
						continue;
					if(board[i][j] == board[row][col])
						return 0;
				}
			}
		}
	}

	return 1;
}