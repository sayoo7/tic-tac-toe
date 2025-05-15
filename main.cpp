#include <iostream>
#include <vector>
#include <stdlib.h>
#include <limits>
#include <string>

using namespace std;

// Sprawdza, czy można jeszcze wykonać ruch
bool canMove(const vector<vector<string>> board)
{
    for(int i = 0; i<3; i++)
    {
        for(int j = 0; j<3; j++)
        {
            if(board[i][j] == " ")
            {
                return true;
            }
        }
    }
    return false;
}

// Sprawdzamy, czy gra się zakończyła i kto wygrał: X 1, O -1, REMIS 0, gramy dalej 2;
int isEnd(const vector<vector<string>> board)
{
   
    for(int i = 0; i<3; i++)
    {
        if(board[i][0] != " " && board[i][0] == board[i][1] && board[i][1] == board[i][2]) //Sprawdza w poziomie
            if(board[i][0] == "X")
                return 1;
            else if(board[i][0] == "O")
                return -1;
        if(board[0][i] != " " && board[0][i] == board[1][i] && board[1][i] == board[2][i]) //Sprawdza w pionie
            if(board[0][i] == "X")
                return 1;
            else if(board[0][i] == "O")
                return -1;
    }

    // Sprawdzanie przekątnych
    if(board[0][0] != " " && board [0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if(board[0][0] == "X")
            return 1;
        else if(board[0][0] == "O")
            return -1;
    }
    if(board[0][2] != " " && board [0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if(board[0][2] == "X")
            return 1;
        else if(board[0][2] == "O")
            return -1;
    }
    if(!canMove(board))
    {
        return 0; //remis
    }else
        return 2; // gra trwa dalej
}

//algorytm minimax w wersji podstawowej
int minimax(vector<vector<string>> board, bool aiMove)
{
    int score = isEnd(board);
    if(score != 2)
        return score;
    
    if(aiMove)  
    {
        int best = numeric_limits<int>::min(); // na początku ustaw najniższą możliwą wartość
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(board[i][j] == " ")
                {
                    board[i][j] = "X";
                    best = max(minimax(board, false), best);
                    board[i][j] = " ";
                }
            }
        }
        return best;
    }
    else // jeśli ruch gracza
    {
        int best = numeric_limits<int>::max();
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(board[i][j] == " ")
                {
                    board[i][j] = "O";
                    best = min(minimax(board, true), best);
                    board[i][j] = " ";
                }
            }
        }
        return best;
    }
}

// Szuka najlepszego ruchu jaki aktualnie można wykonać
pair<int, int> bestMove(vector<vector<string>> board)
{
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j<3; j++)
        {
            if(board[i][j] == " ")
            {
                board[i][j] = "X";
                int move = minimax(board, false);
                board[i][j] = " ";

                if(move > bestVal)
                {
                    bestMove = {i, j};
                    bestVal = move;
                }
            }
        }
    }
    return bestMove;
}

// Wyświetla aktualną planszę
void printGameState(const vector<vector<string>> board)
{
    cout << "PLANSZA: " << endl;
    cout << "\t " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "\t---+---+---" << endl;
    cout << "\t " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "\t---+---+---" << endl;
    cout << "\t " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
    cout << "\t---+---+---" << endl;
}

//zamienia liczbe pola na odpowiedni wiersz i kolumne
pair<int, int> getField(int number)
{
    int row = (number-1)/3;
    int col = (number-1)%3;
    return {row, col};
}


// Zabezpieczenie przed wpisaniem typu danych innego niż int
int getInt(bool playerMove = false, vector<vector<string>> board = {"0", "0"})
{
    if(playerMove)
    {
        int var;
        cin >> var;
        pair<int,int> field = getField(var);
        while(cin.fail() || var <1 || var > 9 || board[field.first][field.second] != " ")
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');    
            cout << "Podano nieprawidlowa wartosc, sproboj ponownie\n>> ";
            cin >> var;
            field = getField(var);
        }
        return var;
    }else
    {
        int var;
        cin >> var;
        while(cin.fail() || var <0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');    
            cout << "Podano nieprawidlowa wartosc, sproboj ponownie\n>> ";
            cin >> var;
        }
        return var;
    }
}


//tryb podstawowy
void basicType(vector<vector<string>> &board)
{
    bool playerTurn = false;
    while(isEnd(board) == 2)
    {
        system("CLS");
        printGameState(board);

        if(playerTurn)
        {
            cout << "Twoj ruch! Wybierz odpowiednie pole 1-9: ";
            int player_move = getInt(true, board);
            pair<int,int> field = getField(player_move);
            board[field.first][field.second] = "O";
        }else
        {
            pair<int,int> best = bestMove(board);
            board[best.first][best.second] = "X";
        }
        playerTurn = !playerTurn;
    }

    system("CLS");
    printGameState(board);
    int result = isEnd(board);
    if (result == 1) cout << "Wygral gracz (X)!" << endl;
    else if (result == -1) cout << "Wygral komputer (O)!" << endl;
    else cout << "Remis!" << endl;

    char pause;
    cout << "Wprowadz cokolwiek aby zakonczyc dzialanie programu" << endl;
    cin >> pause; //zeby program się od razu nie wyłączał
}

void expandedType()
{
    system("CLS");
}


void menu()
{
    int choice;
    bool rightVal = false;
    vector<vector<string>> board(3, vector<string>(3," "));
    cout << "Aby rozpoczac gre w kolko i krzyzyk, wybierz jaki wariant algorytmu chcesz uzyc:" << endl;
    cout << "1 - Podstawowy Algorytm minimax" << endl;
    cout << "2 - Rozszerzony Algorytm minimax" << endl;
    cout << "0 - Wyjdz" << endl;
    cout << ">> ";
    choice = getInt();

    while(!rightVal)
    {
        switch (choice)
        {
        case 0:
            cout << "Zegnaj" << endl;
            exit(0);
            break;
        case 1:
            basicType(board);
            rightVal = true;
            break;
        
        case 2:
            expandedType();
            rightVal = true;
            break;
        
        default:
            system("CLS");
            cout << "Podano nieprawidlowa wartosc!" << endl;
            cout << "Sprobuj ponownie\n>> ";
            choice = getInt();
            break;
        }
    }
}



int main()
{
    menu();
}