struct BoardState {
    string board;
    int depth;
};

class Solution {
public:
    int ctoi(char c) {
        return (int) c - '0';
    }

    char itoc(int i) {
        return (char) i + '0';
    }

    bool isFinished(string board) {
        return (ctoi(board[0]) == 1 && ctoi(board[1]) == 2 && ctoi(board[2]) == 3
            && ctoi(board[3]) == 4 && ctoi(board[4]) == 5 && ctoi(board[5]) == 0);
    }
    
    BoardState apply(BoardState state, int a, int b) {
        string newBoard = state.board;
        newBoard[a] = state.board[b];
        newBoard[b] = state.board[a];
        return {newBoard, state.depth + 1};
    }

    int slidingPuzzle(vector<vector<int>>& board) {
        queue<BoardState> queue;
        set<string> boardsDone;

        string startBoard;
        for(vector<int> row: board) {
            for(int col: row)
                startBoard += itoc(col);
        }

        queue.push({startBoard, 0});
        boardsDone.insert(startBoard);

        while(!queue.empty()) {
            BoardState state = queue.front();
            queue.pop();

            if(isFinished(state.board))
                return state.depth;

            int pos0 = state.board.find("0");
            vector<int> possibleMoves;
            
            if(pos0 != 0 && pos0 != 3)
                possibleMoves.push_back(pos0 - 1);
            
            if(pos0 != 2 && pos0 != 5)
                possibleMoves.push_back(pos0 + 1);
            
            if(pos0 / 3 < 1)
                possibleMoves.push_back(pos0 + 3);
            else
                possibleMoves.push_back(pos0 - 3);
            
            for(int move: possibleMoves) {
                BoardState newState = apply(state, pos0, move);

                if(boardsDone.insert(newState.board).second)
                    queue.push(newState);
            }
        }

        return -1;
    }
};