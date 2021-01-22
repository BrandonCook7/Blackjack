
#ifndef CARD_H
#pragma once
#include <iostream>

class Card {
    private:
        std::string suite;//Diamonds, Spades, Clubs or Hearts
        int number;// Ace is 1 or 11, Jack, Queen, and King is 10, Everything else is it's value

    public:
        Card(){
            
        }
        Card(std::string s, int n){
            suite = s; number = n;
        }
        ~Card(){
            // delete(&suite);
            // delete(&color);
            // delete(&number);
        }
        std::string getSuite(){
            return suite;
        }
        int getNumber(){
            return number;
        }
        void setSuite(std::string s){
            suite = s;
        }
        void setNumber(int n){
            number = n;
        }
};
#endif