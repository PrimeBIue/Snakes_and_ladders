#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>

using namespace std;

class Game {
     public:
        int rollDice(){
            return (rand() % 6 + 1);
        }
};

class Board : public Game{
    public:

        static int num_tiles;
        static int penalty;
        static int reward;
        static int maxTurns;
        static string gameType;
        static vector<string> tile_type;
        
        vector<string> setBoard(){
            cout << "Do you want to setup the game in automatic ('a') or manual ('m'): ";
            cin >> gameType;

            if(gameType == "m"){

                cout << "Please determine the maximum number of turns: ";
                cin >> maxTurns;
                cout << "Please determine the penalty if you land on a snake: ";
                cin >> penalty;
                cout << "Plese determine the reward of you land on a ladder: ";
                cin >> reward;
                
                cout << "Determine the amount of tiles in the board: ";
                cin >> num_tiles;
                
                for(int i = 0; i < num_tiles; i ++){
                    cout << "What type of tile will tile " << i+1 << " be? 'N' for normal, 'S' for snake or 'L' for ladder: ";
                    string input;
                    cin >> input;

                    if (input != "N" && input != "S" && input != "L"){
                        cout << "Sorry that is not a valid character try using 'N', 'S' or 'L'" << endl;
                        i--;
                    }
                    else{
                        tile_type.push_back(input);
                    }
                }  
            }
            else if(gameType == "a"){
                
                tile_type = {"N", "N", "L", "N", "L", "N", "N", "N", "N", "N",
                            "L", "N", "N", "N", "N", "N", "S", "N", "S", "L",
                            "S", "N", "N", "N", "N", "N", "S", "N", "N", "N"};
            }
            else {
                cout << "Sorry that is not a valid character please try again." << endl;
                setBoard();
            }
                return tile_type;
        }

};

int Board::num_tiles = 30;
int Board::maxTurns = 0;
int Board::penalty = 3;
int Board::reward = 3;
string Board::gameType;
vector<string> Board::tile_type;

class Player : public Board {
    private:
        int playerNum;
    public:
        Player(int _playerNum){
            playerNum = _playerNum;
        }

        int turn = 1;
        int currentTile = 1;

        void doTurn(){
            
            int diceValue = Game::rollDice();
            currentTile += diceValue;

            if (currentTile > Board::num_tiles) {
                cout << "\nCurrent turn number: " << turn << "\nPLayer " << playerNum << "\nCurrent tile: " << currentTile - diceValue << "\nYou rolled a " << diceValue << "\nTile type : " << Board::tile_type[Board::num_tiles - 1] << "\nFinal tile number: " << Board::num_tiles << "\n" <<endl;
            }

            else {
                cout << "\nCurrent turn number: " << turn << "\nPlayer " << playerNum << "\nCurrent tile: " << currentTile - diceValue << "\nYou rolled a " << diceValue << "\nTile type : " << Board::tile_type[currentTile-1] << "\nFinal tile number: ";

                if (Board::tile_type[currentTile-1] == "L") {
                    currentTile += Board::reward;
                    }
                else if (Board::tile_type[currentTile-1] == "S") {
                    currentTile -= Board::penalty;
                    
                    }
                if(currentTile <= 0) {currentTile = 0;}
                cout << currentTile << "\n" <<endl;
            }
        
            turn++;
        }
};

int main(){
    
    srand(time(NULL));

    Board b1;
    Player players[] = {1,2};
    string input;
    int i = 0;
    int a = 0;
    
    b1.setBoard();

    cout << "Welcome to Serpents and Ladders...";
    cout << "If you want to stop the game press 'e'" << endl;

    while (input != "e"){
        cout << "If you want to continue to the next turn press 'c': ";
        cin >> input;
        if (players[1].turn > players[0].maxTurns && players[0].maxTurns != 0){
            cout << "Sorry! You ran out of turns!";
            break;
            }
        if(input == "c"){
            players[i].doTurn();

            if(players[i].currentTile >= players[i].num_tiles){
                cout << "Player " << i + 1 << " is the winner!!!" << endl;
                break;
            }
            else if (i == 0){i++;}
            else{i = 0;}
        }
        else if (input != "c" && input != "e"){
            cout << "Invalid option please press 'c' to continue next turn or 'e' to end the game." << endl; 
        }
        
    }
    if (input == "e"){cout << "Thanks for playing!!!" << endl;}
    cout << "GAME OVER";
    return 0;
}
