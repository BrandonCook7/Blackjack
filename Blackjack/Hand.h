#ifndef HAND_H
#pragma once
#include "Card.h"
#include <stack>
#include <vector>

class Hand {
    private:
        std::vector<Card> cardList;

    public:
        int getHandValue() {
            int totalValue = 0;
            int aceCount = 0;
            for(std::vector<Card>::iterator it = cardList.begin(); it != cardList.end(); ++it) {
                int cardNumber = it->getNumber();
                int cardValue = 0;
                // If statements below get the blackjack value of the currentCard
                if (cardNumber == 1) {
                    aceCount += 1;
                    cardValue = 1;
                } else if (cardNumber >= 10) {
                    cardValue = 10;
                } else {
                    cardValue = cardNumber;
                }

                totalValue += cardValue;
            }
            
            if (totalValue - 1 <= 10 && aceCount > 0) {
                totalValue -= 1;  // Removing inital ace that was coutned as 1
                totalValue += 11; // Counting that ace as an 11 isntead
                aceCount -= 1;
            }

            return totalValue;
        };

        int getNumberOfCards(){
            return cardList.size();
        };

        void addCard(Card inputCard){ 
            cardList.push_back(inputCard);
        };

        void clearHand(){
            cardList.clear();
        };

        std::vector<Card> getHandVector() {
            return cardList;
        }


};





#endif