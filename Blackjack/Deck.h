#ifndef DECK_H

//#include "Card.h"
#include <stack>
#include <vector>
#pragma once
class Deck {
    private:
        std::stack<Card> stack;
    public:
        void createDeck(){
            while(!stack.empty()){//Clears deck for future use
                stack.pop();
            }
            std::string suiteTemp;

            for(int j = 0; j < 4; j++){//Looping through suites
                switch(j){
                    case 0:
                        suiteTemp = "Diamonds";
                        break;
                    case 1:
                        suiteTemp = "Hearts"; 
                        break;
                    case 2:
                        suiteTemp = "Spades"; 
                        break;
                    case 3:
                        suiteTemp = "Clubs";
                }
                for(int k = 0; k < 13; k++){//Looping through numbers
                    Card c(suiteTemp, k + 1);
                    stack.push(c);
                }
            }
        }
        std::string numToString(int n){
            std::string numStr;
            switch(n){
                case 1:
                    numStr = "Ace";
                    break;
                case 2:
                    numStr = "Two";
                    break;
                case 3:
                    numStr = "Three";
                    break;
                case 4:
                    numStr = "Four";
                    break;
                case 5:
                    numStr = "Five";
                    break;
                case 6:
                    numStr = "Six";
                    break;
                case 7:
                    numStr = "Seven";
                    break;
                case 8:
                    numStr = "Eight";
                    break;
                case 9:
                    numStr = "Nine";
                    break;
                case 10:
                    numStr = "Ten";
                    break;
                case 11:
                    numStr = "Jack";
                    break;
                case 12:
                    numStr = "Queen";
                    break;
                case 13:
                    numStr = "King";
            }
            return numStr;
        }
        
        void printDeck(){//Used for debugging
            for(int i = 0; i < 52; i++){
                //std::cout << em;
                std::cout << numToString(stack.top().getNumber()) << " of " << stack.top().getSuite() << std::endl;
                stack.pop();
            }
        }
        
        void shuffle(){
            std::vector<Card> shuffleDeck;

            while(!stack.empty()) {//Fills vector with stack values
                shuffleDeck.push_back(stack.top());
                stack.pop();
            }
            
            while (shuffleDeck.size() != 0) {
                int randomIndex = rand() % shuffleDeck.size();

                Card currentCard = shuffleDeck[randomIndex];

                stack.push(currentCard);
                shuffleDeck.erase(shuffleDeck.begin() + randomIndex);
            }

        }
        Card getCard(){//Returns card from top of stack and them removes it
            Card currentCard = stack.top();
            stack.pop();
            return currentCard;
        }


};
#endif