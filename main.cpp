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
                return false;
            }
        }
    }
    return true;
}

// Sprawdzamy, czy gra się zakończyła i kto wygrał: X 1, O -1, REMIS 0, gramy dalej 2;
int isEnd(const vector<vector<string>> board)
{
    if(!canMove(board) == false)
    {
            for(int i = 0; i<3; i++)
        {
            if(board[i][0] != " " && board[i][0] == board[i][1] && board[i][1] == board[i][2]) //Sprawdza w poziomie
                if(board[i][0] == "X")
                    return 1;
                else if(board[0][i] == "O")
                    return -1;
            if(board[0][i] != " " && board[0][i] == board[1][i] && board[1][i] == board[2][i]) //Sprawdza w pionie
                if(board[0][i] == "X")
                    return 1;
                else if(board[0][i] == "O")
                    return -1;
                else
                    return 0;
        }

        // Sprawdzanie przekątnych
        if(board[0][0] != " " && board [0][0] == board[1][1] && board[1][1] == board[2][2])
        {
            if(board[0][0] == "X")
                return 1;
            else if(board[0][0] == "O")
                return -1;
        }
        if(board[2][2] != " " && board [2][2] == board[1][1] && board[1][1] == board[0][0])
        {
            if(board[2][2] == "X")
                return 1;
            else if(board[2][2] == "O")
                return -1;
        }
        return 0; // remis
    }
    else
        return 2; // można się ruszyć - gramy dalej



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

void basicType(vector<vector<string>> &board)
{
    char k;
    int counter = 0;
    string data = "x";
    system("CLS");
    printGameState(board);

    //-----------------TESTOWANIE-----------------
    // cout << "---Wygrana X---" << endl;
    // board[0][0] = "O";  board[0][1] = "O";  board[0][2] = "X";
    // board[1][0] = "X";  board[1][1] = "O";  board[1][2] = "X";
    // board[2][0] = "O";  board[2][1] = "X";  board[2][2] = "X";
    // printGameState(board);
    // cout << isEnd(board);

    // cout << endl << endl;
    // cout << "+++REMIS+++" << endl;
    // board[0][0] = "O";  board[0][1] = "O";  board[0][2] = "X";
    // board[1][0] = "X";  board[1][1] = "O";  board[1][2] = "O";
    // board[2][0] = "O";  board[2][1] = "X";  board[2][2] = "X";
    // printGameState(board);
    // cout << isEnd(board);

    // cout << endl << endl;
    // cout << "|||Wygrana O|||" << endl;
    // board[0][0] = "O";  board[0][1] = "O";  board[0][2] = "X";
    // board[1][0] = "X";  board[1][1] = "O";  board[1][2] = "O";
    // board[2][0] = "O";  board[2][1] = "X";  board[2][2] = "O";
    // printGameState(board);
    // cout << isEnd(board);

    // cout << endl << endl;
    // cout << " MOZNA GRAC DALEJ " << endl;
    // board[0][0] = "O";  board[0][1] = "O";  board[0][2] = "X";
    // board[1][0] = "X";  board[1][1] = "O";  board[1][2] = "O";
    // board[2][0] = "O";  board[2][1] = "X";  board[2][2] = " ";
    // printGameState(board);
    // cout << isEnd(board);

    cin >> k;
}

void expandedType()
{
    system("CLS");
}

// Zabezpieczenie przed wpisaniem typu danych innego niż int
int getInt()
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