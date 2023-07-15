#include <iostream>
#include <string>
#include <vector>

using namespace std;

// prototype
class Position;
class ChessBoard;
class ChessPiece;

// --------------- ChessBoard Class ----------------------
class ChessBoard
{
    ChessPiece* board[8][8];

public:
    ChessBoard();
    void initialize();
    ChessPiece* getPiece(string position);
    bool placePiece(ChessPiece* piece, string position);
    bool move(string fromPosition, string toPosition);
    string toString();
};
//------------------------------------------------------


// --------------- ChessPiece Abstract Class -----------
class ChessPiece
{
public:
    enum Color { WHITE, BLACK }; //color of board
protected:
    // use of cheesBoard function to grab information from that function
    ChessBoard board;
    // used Color to declare the object color
    Color color;
    int row;
    int column;
public:
    // ChessPiece(get information from class ChessBoard all while also using board )
    ChessPiece(ChessBoard board, Color color);
    int getRow();
    int getColumn();
    void setRow(int i);
    void setColumn(int i);
    Color getColor();
    string getPosition();
    void setPosition(string position);
    virtual string toString() = 0;
    virtual vector<string>* legalMoves() = 0;
};


// --------------- Derived: "Pawn" - Base: "ChessPiece" --------------
class Pawn : public ChessPiece
{
public:
    Pawn(ChessBoard board, Color color):ChessPiece(board, color) {};
    string toString();
    vector<string>* legalMoves();
};

// --------------- Derived: "Bishop" - Base: "ChessPiece" --------------
class Bishop : public ChessPiece
{
public:
    Bishop(ChessBoard board, Color color) :ChessPiece(board, color) {};
    string toString();
    vector<string>* legalMoves();
};

// --------------- Derived: "Knight" - Base: "ChessPiece" --------------
class Knight : public ChessPiece
{
    
public:
    Knight(ChessBoard board, Color color) :ChessPiece(board, color) {};
    string toString();
    vector<string>* legalMoves();
};

// --------------- Derived: "Rook" - Base: "ChessPiece" --------------
class Rook : public ChessPiece
{
public:
    Rook(ChessBoard board, Color color) :ChessPiece(board, color) {};
    string toString();
    vector<string>* legalMoves();
};

// --------------- Derived: "Queen" - Base: "ChessPiece" --------------
class Queen : public ChessPiece
{
public:
    Queen(ChessBoard board, Color color) :ChessPiece(board, color) {};
    string toString();
    vector<string>* legalMoves();
};

// --------------- Derived: "King" - Base: "ChessPiece" --------------
class King : public ChessPiece
{
public:
    King(ChessBoard board, Color color) :ChessPiece(board, color) {};
    string toString();
    vector<string>* legalMoves();
};
//-----------------------------------------------------

// --------------- ChessBoard Functions ----------------------

ChessBoard::ChessBoard()
{
    //outer board
    for(int i = 0; i < 8; i++)
    {
        // inner board
        for(int j = 0; j < 8; j++)
        {
            board[i][j] = NULL;
        }
    }
}

void ChessBoard::initialize()
{
    
    for(int i = 0; i < 8; i++)
    {
        // current column as a char
        char charPosition = i + 'a';

        //initialize pawns
        Pawn* whitePawn = new Pawn(*this, ChessPiece::WHITE);
        string positionWhite = "";
        positionWhite += charPosition;
        positionWhite += "2";
        placePiece(whitePawn, positionWhite);
        Pawn* blackPawn = new Pawn(*this, ChessPiece::BLACK);
        string positionBlack = "";
        positionBlack += charPosition;
        positionBlack += "7";
        placePiece(blackPawn, positionBlack);
        
        //initialize rooks
        if(i == 0 || i == 7)
        {
            Rook* whiteRook = new Rook(*this, ChessPiece::WHITE);
            positionWhite = "";
            positionWhite += charPosition;
            positionWhite += "1";
            placePiece(whiteRook, positionWhite);

            Rook* blackRook = new Rook(*this, ChessPiece::BLACK);
            positionBlack = "";
            positionBlack += charPosition;
            positionBlack += "8";
            placePiece(blackRook, positionBlack);
        }

        //initialize knights
        if(i == 1 || i == 6)
        {
            Knight* whiteKnight = new Knight(*this, ChessPiece::WHITE);
            positionWhite = "";
            positionWhite += charPosition;
            positionWhite += "1";
            placePiece(whiteKnight, positionWhite);

            Knight* blackKnight = new Knight(*this, ChessPiece::BLACK);
            positionBlack = "";
            positionBlack += charPosition;
            positionBlack += "8";
            placePiece(blackKnight, positionBlack);
        }

        //initialize bishops
        if(i == 2 || i == 5)
        {
            Bishop* whiteBishop = new Bishop(*this, ChessPiece::WHITE);
            positionWhite = "";
            positionWhite += charPosition;
            positionWhite += "1";
            placePiece(whiteBishop, positionWhite);

            Bishop* blackBishop = new Bishop(*this, ChessPiece::BLACK);
            positionBlack = "";
            positionBlack += charPosition;
            positionBlack += "8";
            placePiece(blackBishop, positionBlack);
        }

        //initialize queens
        if (i == 3)
        {
            Queen* whiteQueen = new Queen(*this, ChessPiece::WHITE);
            positionWhite = "";
            positionWhite += charPosition;
            positionWhite += "1";
            placePiece(whiteQueen, positionWhite);

            Queen* blackQueen = new Queen(*this, ChessPiece::BLACK);
            positionBlack = "";
            positionBlack += charPosition;
            positionBlack += "8";
            placePiece(blackQueen, positionBlack);
        }
        
        //initialize kings
        if (i == 4)
        {
            King* whiteKing = new King(*this, ChessPiece::WHITE);
            positionWhite = "";
            positionWhite += charPosition;
            positionWhite += "1";
            placePiece(whiteKing, positionWhite);

            King* blackKing = new King(*this, ChessPiece::BLACK);
            positionBlack = "";
            positionBlack += charPosition;
            positionBlack += "8";
            placePiece(blackKing, positionBlack);
        }
    }
}

ChessPiece* ChessBoard::getPiece(string position)
{
    //Check if position is 2 characters long
    if (position.length() == 2)
    {
        int row = position[1] - '0';
        char col = position[0];

        //Check if position is within the board
        if (row >= 0 && row <= 7)
        {
            if (col >= 'a' && col <= 'h')
            {
                // return piece at valid location on board
                return board[row][col];
            }
        }
    }

    // return NULL if invalid position
    return NULL;
}

// Need a error catcher for placePiece
bool ChessBoard::placePiece(ChessPiece* piece, string position) // <---- NEED TO IMPLEMENT ERROR CHECKING (FALSE BRANCH)
{
    //Check if position is 2 characters long
    if (position.length() == 2)
    {
        int row = position[1] - '0';
        char col = position[0];

        //Check if position is within the board
        if (row >= 1 && row <= 8)
        {
            if (col >= 'a' && col <= 'h')
            {
                //Update position of the piece
                piece->setPosition(position);
                board[piece->getRow()][piece->getColumn()] = piece;
                return true;
            }
        }
    }

    // return false if invalid position
    return false;
}

// Need to impliment another error catcher for move
bool ChessBoard::move(string fromPosition, string toPosition)
{
    int fromRow, row, col;
    char fromCol;
    //Check if position is 2 characters long
    if (fromPosition.length() == 2)
    {
        fromRow = fromPosition[1] - '0';
        fromCol = fromPosition[0];

        //Check if position is within the board
        if (fromRow >= 1 && fromRow <= 8)
        {
            if (fromCol >= 'a' && fromCol <= 'h')
            {
                row = fromRow - 1;
                col = fromCol - 97;
            }
        }
    }

    if(board[row][col]) // Check if there is a piece to move
    {
        // Check if there are legal moves to make
        vector<string>* moves = board[row][col]->legalMoves();
        if(moves)
        {
            // Check if the requested movement is legal. If it is, execute the move
            int toRow, toCol;
            //Check if position is 2 characters long
            if (toPosition.length() == 2)
            {
                toRow = toPosition[1] - '0';
                toCol = toPosition[0];

                //Check if position is within the board
                if (toRow >= 1 && toRow <= 8)
                {
                    if (toCol >= 'a' && toCol <= 'h')
                    {
                        row = toRow - 1;
                        col = toCol - 97;
                    }
                }
            }

            // check if "to" position is within the legal moves list
            for(int i = 0; i < moves->size(); i++)
            {
                if((*moves)[i] == toPosition)
                {
                    if (board[row][col]) // Check if the "to" square has a piece that will be captured
                    {
                        // if a piece is there, delete it and replace it

                    }
                    else
                    {
                        // if no piece is there, move it and update its position
                        int frow = fromRow - 1;
                        int fcol = fromCol - 97;
                        board[row][col] = board[frow][fcol];
                        board[row][col]->setPosition(toPosition);
                        board[frow][fcol] = NULL;
                    }
                    return true;
                }
            }
        }

        //no legal moves
        cout << "no legal moves";
        return false;
    }
    else
    {
        // No piece in the "from" position
        cout << "no piece to move";
        return false;
    }
}

// I used this function to help design the chessboard
string ChessBoard::toString()
{
    string boardString = "  +---+---+---+---+---+---+---+---+\n";

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(j == 0)
            {
                string row = to_string(8 - i);
                boardString += row + " | ";
            }

            if (board[7 - i][j])
            {
                boardString += board[7 - i][j]->toString() + " | ";
            }
            else
            {
                boardString += "  | ";
            }
        }
        boardString += "\n";
        boardString += "  +---+---+---+---+---+---+---+---+\n";
    }

    boardString += "    A   B   C   D   E   F   G   H \n";
    return boardString;
};
//-----------------------------------------------------


// --------------- ChessPiece Abstract Class Functions ----------------------
ChessPiece::ChessPiece(ChessBoard board, Color color)
{
    this->board = board;
    this->color = color;
    row = -1;
    column = -1;
}

int ChessPiece::getRow()
{
    return row;
}

int ChessPiece::getColumn()
{
    return column;
}

void ChessPiece::setRow(int i)
{
    row = i;
}

void ChessPiece::setColumn(int i)
{
    column = i;
}

ChessPiece::Color ChessPiece::getColor()
{
    return color;
}

string ChessPiece::getPosition()
{
    char charPosition = column + 97;
    return charPosition + to_string(row);
}

void ChessPiece::setPosition(string position)
{
    //Check if position is 2 characters long
    if(position.length() == 2)
    {
        int tempRow = position[1] - '0';
        char tempCol = position[0];

        //Check if position is within the board
        if(tempRow >= 1 && tempRow <= 8)
        {
            if(tempCol >= 'a' && tempCol <= 'h')
            {
                // set position if valid
                row = tempRow - 1;
                column = tempCol - 97;
            }
        }
    }
}
//-----------------------------------------------------


// --------------- Derived: "Pawn" - Base: "ChessPiece" Functions --------------
string Pawn::toString()
{
    return color == WHITE ? "P" : "p";
}

vector<string>* Pawn::legalMoves()
{
    vector<string> *moves = new vector<string>;
    int currentRow = row;
    char currentCol = column + 'a';

    // White movement (upwards relative to the board)
    if(color == WHITE)
    {
        int jumps = row == 1 ? 2 : 1;
        for(int i = 1; i <= jumps && currentRow < 7; i++)
        {
            currentRow += 1;
            string checkPosition = currentCol + to_string(currentRow);
            if (board.getPiece(checkPosition))
            {
                break;
            }
            else
            {
                moves->push_back(currentCol + to_string(currentRow + 1));
            }
        }
    }

    // Black movement (downwards relative to the board)
    if (color == BLACK)
    {
        int jumps = row == 6 ? 2 : 1;
        for (int i = 1; i <= jumps && currentRow > 0; i++)
        {
            currentRow -= 1;
            string checkPosition = currentCol + to_string(currentRow);
            if (board.getPiece(checkPosition))
            {
                break;
            }
            else
            {
                moves->push_back(currentCol + to_string(currentRow + 1));
            }
        }
    }

    return moves;
}

// --------------- Derived: "Bishop" - Base: "ChessPiece" Functions --------------
string Bishop::toString()
{
    return color == WHITE ? "B" : "b";
}

vector<string>* Bishop::legalMoves()
{
    return NULL;
}

// --------------- Derived: "Knight" - Base: "ChessPiece" Functions --------------
string Knight::toString()
{
    return color == WHITE ? "K" : "k";
}

vector<string>* Knight::legalMoves()
{
    // No legal moves
    return NULL;
}

// --------------- Derived: "Rook" - Base: "ChessPiece" Functions --------------
string Rook::toString()
{
    return color == WHITE ? "R" : "r";
}

vector<string>* Rook::legalMoves()
{
    vector<string>* moves = new vector<string>;
    int currentRow = row;
    char currentCol = column + 'a';

    // Check upwards movement
    int jumps = 7 - row;
    for (int i = 1; i <= jumps && currentRow < 7; i++)
    {
        currentRow += 1;
        string checkPosition = currentCol + to_string(currentRow);
        if (board.getPiece(checkPosition))
        {
            break;
        }
        else
        {
            moves->push_back(currentCol + to_string(currentRow + 1));
        }
    }

    // Check Downwards movement
    jumps = row;
    currentRow = row;
    for (int i = 1; i <= jumps && currentRow > 0; i++)
    {
        currentRow -= 1;
        string checkPosition = currentCol + to_string(currentRow);
        if (board.getPiece(checkPosition))
        {
            break;
        }
        else
        {
            moves->push_back(currentCol + to_string(currentRow + 1));
        }
    }

    //Check rightward movement
    jumps = 'h'- currentCol;
    for (int i = 1; i <= jumps && currentCol < 'h'; i++)
    {
        currentCol += 1;
        string checkPosition = currentCol + to_string(row);
        if (board.getPiece(checkPosition))
        {
            break;
        }
        else
        {
            moves->push_back(currentCol + to_string(currentRow + 1));
        }
    }

    //Check leftward movement
    jumps = column;
    currentCol = column + 'a';
    for (int i = 1; i <= jumps && currentCol > 'a'; i++)
    {
        currentCol -= 1;
        string checkPosition = currentCol + to_string(row);
        if (board.getPiece(checkPosition))
        {
            break;
        }
        else
        {
            moves->push_back(currentCol + to_string(currentRow + 1));
        }
    }

    return moves;
}

// --------------- Derived: "Queen" - Base: "ChessPiece" Functions --------------
string Queen::toString()
{
    return color == WHITE ? "Q" : "q";
}

vector<string>* Queen::legalMoves()
{
    // No legal moves
    return NULL;
}

// --------------- Derived: "King" - Base: "ChessPiece" Functions --------------
string King::toString()
{
    
    return color == WHITE ? "X" : "x";
}

vector<string>* King::legalMoves()
{
    // No legal moves
    return NULL;
}
//-----------------------------------------------------

// Main driver
int main()
{
    ChessBoard board;
    board.initialize();
    cout << board.toString() << endl;

    board.move("a2", "a4");

    cout << endl;

    cout << board.toString();

    board.move("a4", "a5");

    cout << endl;

    cout << board.toString();

    board.move("a1", "a3");

    cout << endl;

    cout << board.toString();

    board.move("a3", "b3");

    cout << endl;

    cout << board.toString();

    return 0;
}


