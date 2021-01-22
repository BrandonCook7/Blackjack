#ifndef GAME_H
#pragma once
#include "Hand.h"
#include "Deck.h"
#include <vector>

#define WIDTH 1600
#define HEIGHT 900

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//Used for sleep function, decides if OS is linux or windows
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

class Game {
    private:
        //Sprite Vectors
        std::vector<sf::Texture> clubTextures, diamondTextures, heartTextures, spadeTextures;
        sf::Texture backCard;
        Hand dealerHand;
        Hand playerHand;
        Deck gameDeck;
        Card hiddenCard;
        std::string whoWon;
        int playAgain = 1;
        int oldMousePosX = 0, oldMousePosY = 0;
        
        // We fill up a vector with a bunch of sprites (IN THE CONSTRUCTOR)
        // then we just go through and set the texture of each sprite
        // so then we know they like actually exist
    public:
        void testCase1() {
            std::cout << "TEST CASE 1" << std::endl;
            // TEST 1 Testing dealer blackjack with player blackjack
            // Give dealer ACE and KING
            // Give player ACE and KING
            // Expected result: DEALER WINS
            gameDeck.createDeck();
            dealerHand.addCard(*(new Card("King", 12)));
            dealerHand.addCard(*(new Card("Ace", 1)));

            playerHand.addCard(*(new Card("King", 12)));
            playerHand.addCard(*(new Card("Ace", 1)));

            
            if (dealerHand.getHandValue() == 21) {
                std::cout << "DEALER WINS" << std::endl;
            } 

            dealerHand.clearHand();
            playerHand.clearHand();
        }
        void testCase2() {
            std::cout << "TEST CASE 2" << std::endl;
            // TEST 2 Testing player blackjack w/o dealer blackjack
            // Give dealer Eight and Ace
            // Give player King and Ace
            // Expected result: PLAYER WINS
            gameDeck.createDeck();
            dealerHand.addCard(*(new Card("Eight", 8)));
            dealerHand.addCard(*(new Card("Ace", 1)));

            playerHand.addCard(*(new Card("King", 12)));
            playerHand.addCard(*(new Card("Ace", 1)));

            
            if (playerHand.getHandValue() == 21 && dealerHand.getHandValue() < 21) {
                std::cout << "PLAYER WINS" << std::endl;
            } 
            
            dealerHand.clearHand();
            playerHand.clearHand();
        }
        void testCase3() {
            std::cout << "TEST CASE 3" << std::endl;
            // TEST 3 Testing player and dealer have same hands
            // Give dealer Eight and Ace
            // Give player Eight and Ace
            // Expected result: DRAW (Hands are equal)
            gameDeck.createDeck();
            dealerHand.addCard(*(new Card("Eight", 8)));
            dealerHand.addCard(*(new Card("Ace", 1)));

            playerHand.addCard(*(new Card("Eight", 8)));
            playerHand.addCard(*(new Card("Ace", 1)));

            
            if (playerHand.getHandValue() == dealerHand.getHandValue()) {
                std::cout << "DRAW (Hands are equal)" << std::endl;
            } 
            
            dealerHand.clearHand();
            playerHand.clearHand();
        }

        void testCase4() {
            std::cout << "TEST CASE 4" << std::endl;
            // TEST 4 Testing player having better hand than dealer (by one)
            // Give dealer Eight and Eight
            // Give player Eight and Nine
            // Expected result: PLAYER WINS
            gameDeck.createDeck();
            dealerHand.addCard(*(new Card("Eight", 8)));
            dealerHand.addCard(*(new Card("Eight", 8)));

            playerHand.addCard(*(new Card("Eight", 8)));
            playerHand.addCard(*(new Card("Nine", 9)));

            
            if (playerHand.getHandValue() > dealerHand.getHandValue()) {
                std::cout << "PLAYER WINS" << std::endl;
            }
            
            dealerHand.clearHand();
            playerHand.clearHand();
        }

        void testCase5() {
            std::cout << "TEST CASE 5" << std::endl;
            // TEST 5 Testing dealer having better hand than player (by one)
            // Give dealer Eight and Nine
            // Give player Eight and Eight
            // Expected result: PLAYER WINS
            gameDeck.createDeck();
            dealerHand.addCard(*(new Card("Eight", 8)));
            dealerHand.addCard(*(new Card("Nine", 9)));

            playerHand.addCard(*(new Card("Eight", 8)));
            playerHand.addCard(*(new Card("Eight", 8)));

            
            if (dealerHand.getHandValue() > playerHand.getHandValue()) {
                std::cout << "DEALER WINS" << std::endl;
            } 
            
            dealerHand.clearHand();
            playerHand.clearHand();
        }

        void fillVectors(){
            //sf::Sprite spriteCranberry;
            std::string cardDirectory;
                
                for(int i = 0; i < 13; i++){
                    int index = i + 1;
                    for(int j = 0; j < 4; j++){
                        switch(j){
                            case(0):
                                cardDirectory = "cardSpades";
                                break;
                            case(1):
                                cardDirectory = "cardHearts";
                                break;
                            case(2):
                                cardDirectory = "cardDiamonds";
                                break;
                            case(3):
                                cardDirectory = "cardClubs";
                                break;
                        }
                        sf::Texture texture;
                        std::string temp = "graphics/Cards/" + cardDirectory + std::to_string(index) + ".png";
                        if(!texture.loadFromFile(temp)){
                            std::cout << "Error loading card pictures"  << std::endl;
                            return;
                        }
                        switch(j){
                            case(0):
                                clubTextures.push_back(texture);
                                break;
                            case(1):
                                diamondTextures.emplace_back(texture);
                                break;
                            case(2):
                                heartTextures.emplace_back(texture);
                                break;
                            case(3):
                                spadeTextures.emplace_back(texture);
                                break;
                        }
                    }
                }
            backCard.loadFromFile("graphics/Cards/cardBack_red4.png");

        }

        void initializeHands(sf::RenderWindow& window) {

            playerHit(window);
            dealerHit(window);
            playerHit(window);
            dealerHit(window);
        };

        void playerHit(sf::RenderWindow& window){
            Card tempCard = gameDeck.getCard();//Grabs card off deck
            playerHand.addCard(tempCard);//Adds it to player
            int num = playerHand.getNumberOfCards();
            int xOffset = 650 + (40 * num);//Shifts cards down depending on amount;
            int yOffset = 700 - (40 * num);

            std::string suite = tempCard.getSuite();
            int suiteNum = 1;
            if(suite == "Clubs"){
                suiteNum = 1;
            } else if (suite == "Diamonds"){
                suiteNum = 2;
            } else if (suite == "Hearts"){
                suiteNum = 3;
            } else if (suite == "Spades"){
                suiteNum = 4;
            }
            placeCard(xOffset, yOffset, tempCard.getNumber()-1, suiteNum, false, window);
        }
    
        void dealerHit(sf::RenderWindow& window){
            Card tempCard = gameDeck.getCard();//Grabs card off deck
            dealerHand.addCard(tempCard);//Adds it to player
            int num = dealerHand.getNumberOfCards();
            int xOffset = 500 + (150 * num);//Shifts cards down depending on amount;

            std::string suite = tempCard.getSuite();
            int suiteNum = 1;
            if(suite == "Clubs"){
                suiteNum = 1;
            } else if (suite == "Diamonds"){
                suiteNum = 2;
            } else if (suite == "Hearts"){
                suiteNum = 3;
            } else if (suite == "Spades"){
                suiteNum = 4;
            }
            bool isHidden = false;
            if(dealerHand.getNumberOfCards() == 1){
                isHidden = true;
                hiddenCard = tempCard;
            }
            placeCard(xOffset, 50, tempCard.getNumber()-1, suiteNum, isHidden, window);
        }
        void showHiddenCard(sf::RenderWindow& window){
            std::string suite = hiddenCard.getSuite();
            int suiteNum = 0;
            if(suite == "Clubs"){
                suiteNum = 1;
            } else if (suite == "Diamonds"){
                suiteNum = 2;
            } else if (suite == "Hearts"){
                suiteNum = 3;
            } else if (suite == "Spades"){
                suiteNum = 4;
            }
            int xOffset = 500 + (150 * 1);
            placeCard(xOffset, 50, hiddenCard.getNumber()-1, suiteNum, false, window);
        }
        void placeCard(int x, int y, int cardNumber, int type, bool isHidden, sf::RenderWindow& window){
            sf::Sprite s;
            switch(type){
                case 1://1 for Clubs
                    s.setTexture(clubTextures[cardNumber]);
                    break;
                case 2://2 for Diamonds
                    s.setTexture(diamondTextures[cardNumber]);
                    break;
                case 3://3 for Hearts
                    s.setTexture(heartTextures[cardNumber]);
                    break;
                case 4://4 for Spades
                    s.setTexture(spadeTextures[cardNumber]);
                    break;
                default:
                    std::cout << "ERROR: No type of card within range, must choose from 1-4" << std::endl;
                    std::terminate;
            }
            if(isHidden){//Turns card upside
                s.setTexture(backCard);
            }
            if((x > WIDTH) && (y > HEIGHT)){
                std::cout << "ERROR: Cordinates out of range" << std::endl;
                std::terminate;
            } else {
                s.setPosition(x, y);
            }
            sf::Music music;
            if(!music.openFromFile("audio/cardPlace1.ogg")){
                std::terminate;
            }
            window.draw(s);
            music.play();//TODO DEBUG SOUND, NO AUDIO
            window.display();
        }
        void checkClosed(sf::RenderWindow& window){
            sf::Event event;
            while (window.pollEvent(event)) // Checks if key is pressed
            {
                // Close window: exit
                if (event.type == sf::Event::Closed){
                    window.close();
                    playAgain = 0;
                }
                if (event.type == sf::Event::KeyReleased)
                    if(event.key.code == sf::Keyboard::Escape){
                        window.close();
                        playAgain = 0;
                    }
            }
        }
        void playGame() {
            
            sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "BLACK JACK");

            // Moving speed of the cards
            // Did not implement animations but might later during break -Brandon
            //window.setFramerateLimit(300);
            
            //Initilizing a bunch of SFML variables
            sf::Text hitText, standText, quitText, winningText, playAgainText, yesText, noText;
            hitText.setCharacterSize(150);
            standText.setCharacterSize(150);
            sf::Font font;
            bool hitClicked = false, standClicked = false;
            font.loadFromFile("fonts/Caress.ttf");

            hitText.setFillColor(sf::Color::Black);
            hitText.setCharacterSize(50);
            hitText.setString("Hit");
            hitText.setFont(font);
            hitText.setPosition(1200,700);

            standText.setFillColor(sf::Color::Black);
            standText.setCharacterSize(50);
            standText.setString("Stand");
            standText.setFont(font);
            standText.setPosition(1400,700);

            quitText.setFillColor(sf::Color::Black);
            quitText.setCharacterSize(20);
            quitText.setString("Esc to quit");
            quitText.setFont(font);
            
            winningText.setFillColor(sf::Color::Black);
            winningText.setCharacterSize(75);
            winningText.setFont(font);
            winningText.setPosition(580, 300);

            playAgainText.setFillColor(sf::Color::Black);
            playAgainText.setCharacterSize(50);
            playAgainText.setString("Play Again?");
            playAgainText.setFont(font);
            playAgainText.setPosition(650, 400);
            
            yesText.setFillColor(sf::Color::Black);
            yesText.setCharacterSize(40);
            yesText.setString("Yes");
            yesText.setFont(font);
            yesText.setPosition(680, 480);

            noText.setFillColor(sf::Color::Black);
            noText.setCharacterSize(40);
            noText.setString("No");
            noText.setFont(font);
            noText.setPosition(800, 480);


            //FULL GAME LOOP
            while(window.isOpen() && playAgain == 1){
                // Reset variables for either start of game or another round
                playerHand.clearHand();
                dealerHand.clearHand();
                whoWon = "";
                window.clear(sf::Color(28, 119, 20));//Makes the background green

                gameDeck.createDeck();//Creates card deck
                gameDeck.shuffle();//Shuffles card deck
                fillVectors();//Fills vectors with textures

                int gameIsPlaying = 1;
                int continueRound = 1;
                int playerWon = 0;

                //Draws text for game
                window.draw(hitText);
                window.draw(standText); 
                window.draw(quitText);
                window.display();
                initializeHands(window);//Gives dealer and player each two cards


                //ROUND LOOP
                while (gameIsPlaying && window.isOpen()) {
                                        
                    sf::Event event;
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);



                    
                    // CHECK IF DEALER GOT INSTANT BLACKJACK
                    if (dealerHand.getHandValue() == 21) {
                        whoWon = "Dealer";
                        gameIsPlaying = 0;
                        showHiddenCard(window);
                    } else if (playerHand.getHandValue() == 21){
                        whoWon = "Player";
                        gameIsPlaying = 0;
                        showHiddenCard(window);
                    } else {
                        hitClicked = false;
                        standClicked = false;
                        //Checks if the user selected HIT or STAND
                        while(hitClicked == false && standClicked == false && window.isOpen()) {
                            checkClosed(window);
                            sf::Event eventMouse;

                            mousePos = sf::Mouse::getPosition(window);
                            window.pollEvent(eventMouse);
                            checkClosed(window);
                            if((mousePos.x >= 1195  && mousePos.x <= 1255) && (mousePos.y >=  695 && mousePos.y <= 755)){
                                if(eventMouse.type == sf::Event::MouseButtonReleased){
                                    if(oldMousePosX != mousePos.x && oldMousePosY != mousePos.y){
                                        hitClicked = true;
                                        oldMousePosX = mousePos.x;
                                        oldMousePosY = mousePos.y;
                                    }
                                }
                            }
                            
                            if((mousePos.x >= 1395 && mousePos.x <= 1515) && (mousePos.y >= 695 && mousePos.y <= 755)){
                                //standText.setFillColor(sf::Color::Red);
                                
                                if(eventMouse.type == sf::Event::MouseButtonReleased){
                                    if(oldMousePosX != mousePos.x && oldMousePosY != mousePos.y){
                                        standClicked = true;
                                        oldMousePosX = mousePos.x;
                                        oldMousePosY = mousePos.y;
                                    }
                                }
                            }
                            
                        }
                        

                        if (hitClicked == true) {
                            playerHit(window);
                            hitClicked = false;
                            if (playerHand.getHandValue() > 21) {
                                whoWon = "Dealer";
                                gameIsPlaying = 0;
                            }
                        } else if (standClicked == true) {
                            showHiddenCard(window);
                            while (dealerHand.getHandValue() < 17) {
                                standClicked = false;
                                sleep(1);
                                dealerHit(window);
                                if(dealerHand.getHandValue() > 21){
                                    whoWon = "Player";
                                }

                            }
                            gameIsPlaying = 0;
                        }
                    }
                }
                //Some basic logic to decide the winner if not decided already
                if(whoWon == ""){
                    if (dealerHand.getHandValue() > 21) {
                        whoWon = "Player";
                        gameIsPlaying = 0;
                    } else if (playerHand.getHandValue() > dealerHand.getHandValue()) {
                        whoWon = "Player";
                        gameIsPlaying = 0;
                    } else if (playerHand.getHandValue() == dealerHand.getHandValue()) {
                        whoWon = "Stalemate";
                        gameIsPlaying = 0;
                    } else {
                        whoWon = "Dealer";
                        gameIsPlaying = 0;
                    }
                }

                if(whoWon == "Player") {
                    winningText.setString("YOU WON");
                    std::cout << "PLAYER WON" << std::endl;
                } else if (whoWon == "Dealer") {
                    winningText.setString("DEALER WON");
                    std::cout << "DEALER WON" << std::endl;
                } else if (whoWon == "Stalemate") {
                    winningText.setString("DRAW");
                    std::cout << "DRAW" << std::endl;
                } else {
                    std::cout << "ERROR: Logic in the code is wrong one of 3 choices was not set" << std::endl;
                }

                showHiddenCard(window);
                window.draw(winningText);
                window.draw(playAgainText);
                window.draw(yesText);
                window.draw(noText);
                window.display();
                        
                
                //Used for Debugging
                //std::cout <<"Total Player Hand Value: " << playerHand.getHandValue() << std::endl;
                //std::cout <<"Total Dealer Hand Value: " << dealerHand.getHandValue() << std::endl;

                playAgain = -1;

                sf::Event event;
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                //Used to choose if the user wants to play again
                while(playAgain == -1 && window.isOpen()) {
                    sf::Event eventEnd;
                    mousePos = sf::Mouse::getPosition(window);
                    window.pollEvent(eventEnd);

                    if((mousePos.x >= 680  && mousePos.x <= 780) && (mousePos.y >=  480 && mousePos.y <= 550)){
                        if(eventEnd.type == sf::Event::MouseButtonReleased){
                            playAgain = 1;
                        }
                    }
                    if((mousePos.x >= 800 && mousePos.x <= 900) && (mousePos.y >= 480 && mousePos.y <= 550)){
                        if(eventEnd.type == sf::Event::MouseButtonReleased){
                            playAgain = 0;
                        }
                    }
                }
                
                
            }
    }
        
        

};
#endif