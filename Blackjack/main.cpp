/*
Designed and Developed by Peter Wang, Cooper Lappenbusch, Brandon Cook and Khoa Bui
*/
#include <stack>
#include "Card.h"
#include "Deck.h"
#include "Game.h"
int main(){
    srand (time(NULL));
    Game g;
    //IMPORTANT <--------
    //If you want to build this project run run.sh and our executible is sfml-app
    //Uncomment these and comment playgame to run test cases
    // g.testCase1();
    // g.testCase2();
    // g.testCase3();
    // g.testCase4();
    // g.testCase5();
    g.playGame();
    return 0;
    
    /*
               GAME     
             /  |   \
        Decks  Hands Anything else
        /
      Cards
    */
}