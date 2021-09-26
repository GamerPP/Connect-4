#include <iostream>

using namespace std;

void initGrid();
void chooseSymbols();
int checkWin();

int** grid = nullptr;
int width = 7;
int height = 6;
bool currPlayer = 0;
char pOneID = ' ';
char pTwoID = ' ';

int main(int, char**) {
    initGrid();
    chooseSymbols();
    
    while (true){
        cout << "\033[2J\033[1;1H";
        for (int y = 0; y < height+1; y++){
            if (!y){
                cout << "  ";
                for (int x = 0; x < width; x++){
                    cout << x+1 << " ";
                }
                cout << "\n";
            }
            else{
                cout << "| ";
                for (int x = 0; x < width; x++){
                    if (grid[x][y-1] == 1) cout << pOneID << " ";
                    else if (grid[x][y-1] == 2) cout << pTwoID << " ";
                    else cout << "  ";
                }
                cout << "|\n";
            }
        }

        int playerWon = checkWin();
        if (playerWon && playerWon < 3){
            cout << "WOOOO PLAYER " << playerWon << " WON!!!!";
            return 1;
        }

        int choice = 0;
        bool valid = 0;
        while (!valid){
            cout << "Player " << currPlayer + 1 << ", where would you like to place your token?: ";
            cin >> choice;
            choice -= 1;
            if (choice > width || choice < 0 || grid[choice][0])
                cout << "Invalid choice!\n";
            else valid = true;
        }

        for (int y2 = 0; y2 < height; y2++){
            if (grid[choice][y2+1] > 0){
                grid[choice][y2] = currPlayer + 1;
                y2 = height;
            }
            else if (y2+1 == height) grid[choice][y2] = currPlayer + 1;
        }
        currPlayer = !currPlayer;
    }
}

void initGrid() {
    grid = new int * [width];

    for (int i = 0; i < width; i++){
        grid [i] = new int [height];
    }
}

void chooseSymbols(){
    bool valid = false;
    while (!valid){
        cout << "Player one token symbol: ";
        cin >> pOneID;

        if (pOneID == '0') cout << "Invalid symbol.\n";
        else valid = true;
    }
    valid = false;
    while (!valid){
        cout << "Player two token symbol: ";
        cin >> pTwoID;

        if (pTwoID == '0') cout << "Invalid symbol.\n";
        else valid = true;
    }
}

int checkWin(){
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            if (grid[x][y] && grid[x][y]){
                bool possibleWin = true;
                for (int i = 0; i < 4; i++){
                    if (x+i > width-1){
                        possibleWin = false;
                        continue;
                    }
                    if (grid[x+i][y] != grid[x][y]) possibleWin = false;
                } if (possibleWin) return grid[x][y];
                possibleWin = true;
                for (int i = 0; i < 4; i++){
                    if (x+i > width-1 || y+i > height-1){
                        possibleWin = false;
                        continue;
                    }
                    if (grid[x+i][y+i] != grid[x][y]) possibleWin = false;
                } if (possibleWin) return grid[x][y];
                possibleWin = true;
                for (int i = 0; i < 4; i++){
                    if (x+i > width-1 || y-i < 0){
                        possibleWin = false;
                        continue;
                    }
                    if (grid[x+i][y-i] != grid[x][y]) possibleWin = false;
                } if (possibleWin) return grid[x][y];
                possibleWin = true;
                for (int i = 0; i < 4; i++){
                    if (y+i > height-1){
                        possibleWin = false;
                        continue;
                    }
                    if (grid[x][y+i] != grid[x][y]) possibleWin = false;
                } if (possibleWin) return grid[x][y];
            }
        }
    }
    return 0;
}
