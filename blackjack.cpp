//Implement the game of Blackjack (21)
//Single player plays against the house.
//No splitting cards, aces are always worth 11

#include <iostream>
#include <ctime>

void shuffle(bool cardsDealt[]);
void printCard(int card);
void printHand(int hand [], const int cardCount);
int getNextCard(bool cardsDealt[]);
int scoreHand(int hand[], const int cardCount);
void printScoresAndHands(int houseHand[], const int houseCardCount, int playerHand[], const int playerCardCount);

void shuffle(bool cardsDealt[])
{
    for (int i = 0; i < 52; ++i)
    {
        cardsDealt[i] = false;
    }
}

void printCard(int card)
{
    const int rank = card % 13;

    if (rank == 0)
    {
        std::cout << "Ace";
    }
    else if (rank < 9)
    {
        std::cout << rank + 1;
    }
    else if (rank == 9)
    {
        std::cout << "Ten";
    }
    else if (rank == 10)
    {
        std::cout << "Jack";
    }
    else if (rank == 11)
    {
        std::cout << "Queen";
    }
    else
    {
        std::cout << "King";
    }

    std::cout << " of ";

    const int suit = card / 13;

    if (suit == 0)
    {
        std::cout << "Clubs";
    }
    else if (suit == 1)
    {
        std::cout << "Diamonds";
    }
    else if (suit == 2)
    {
        std::cout << "Hearts";
    }
    else
    {
        std::cout << "Spades";
    }
}
void printHand(int hand[], const int cardCount)
{
    for (int i = 0; i < cardCount; ++i)
    {
        const int nextCard = hand[i];
        printCard(nextCard);
        std::cout << ", ";
    }

    std::cout << std::endl;
}

int getNextCard(bool cardsDealt[])
{
    bool dealt = true;
    int newCard = -1;

    do
    {
        newCard = (rand() % 52);
        if (!cardsDealt[newCard])
        {
            dealt = false;
        }
    }
    while (dealt);

    return newCard;
}

int scoreHand(int hand [], const int cardCount)
{
   int aces = 0; //number of aces
   int score = 0; //numerical score of hand

   for (int i = 0; i < cardCount; ++i)
   {
       const int nextCard = hand[i];
       const int rank = nextCard % 13;

       if (rank == 0)
       {
           ++aces;
           ++score;
       }
       else if (rank < 9)
       {
           score += rank + 1;
       }
       else
       {
           score += 10;
       }
   }

   while (aces > 0 && score < 12)
   {
       --aces;
       score += 10;
   }

   return score;
}

void printScoresAndHands(int houseHand[], const int houseCardCount, int playerHand[], const int playerCardCount)
{
    std::cout << "House's Hand: ";
    printHand(houseHand, houseCardCount);
    //std::cout << std::endl;
    std::cout << "Score is: " << scoreHand(houseHand, houseCardCount) << std::endl;

    std::cout << "Your hand: ";
    printHand(playerHand, playerCardCount);
    //std::cout << std::endl;
    std::cout << "Score is: " << scoreHand(playerHand, playerCardCount) << std::endl;

    std::cout << std:: endl;
}

int main ()
{
    std::time_t Time;
    std::time(&Time);
    srand(Time);

    bool cardsDealt[52];
    int houseCardCount = 0;
    int houseHand[12];
    int playerCardCount = 0;
    int playerHand[12];
    bool exit = false;

    std::cout << "Welcome to Blackjack!" << std::endl;
    std::cout << "--------------------" << std::endl;
    std::cout << "The primary objective of Blackjack is to get a hand of cards with a greater value than the" << std::endl;
    std::cout << "dealer's without the value of your hand exceeding 21, which is referred to as going bust." <<std::endl;
    std::cout << "Face cards are worth 10, aces are worth 11 or 1, and all other cards are worth their numeric value." << std::endl;
    std::cout << "After the initial deal, you can either hit (take another card) or stand (take no more cards" << std::endl;
    std::cout << "and keep your total)." << std::endl;
    std::cout << "The dealer must draw on 16 or less. There is no splitting cards in this version of Blackjack." << std::endl;
    std::cout << "--------------------" << std::endl;

    while (!exit)
    {
        //shuffle card deck and initialize all cards as not dealt
        shuffle(cardsDealt);
        //Deal the cards: player and house each get two cards
        playerHand[0] = getNextCard(cardsDealt);
        houseHand[0] = getNextCard(cardsDealt);
        playerHand[1] = getNextCard(cardsDealt);
        houseHand[1] = getNextCard(cardsDealt);
        houseCardCount = 2;
        playerCardCount = 2;

        std::cout << "Starting new hand..." << std::endl;
        std::cout << "--------------------" << std::endl;

        char choice;
        bool hit = true;
        int round = 1;
        bool blackjack = false;
        int playerScore = scoreHand(playerHand, playerCardCount);

        do
        {
            //Print the player's cards and one of the house's cards
            std::cout << "House's Hand:" << std::endl;
            printCard(houseHand[1]);
            std::cout << std::endl;
            std::cout << "Your Hand: " << std::endl;
            printHand(playerHand, playerCardCount);
            std::cout << "Score is " << scoreHand(playerHand, playerCardCount) << std::endl;

            if ( (scoreHand(playerHand,playerCardCount) == 21) && round == 1)
            {
                std::cout << "BLACKJACK! You win!" << std::endl;
                blackjack = true;
                break;
            }


            //Ask player to hit or stand
            std::cout << "Hit [h] or stand [s]? : ";
            std::cin >> choice;

            if (choice == 'h') //player hits
            {
                playerHand[playerCardCount] = getNextCard(cardsDealt);
                ++playerCardCount;
            }
            else if (choice == 's') //player stands
            {
                hit = false;
            }
            else
            {
                std::cout << "Invalid input! Press [h] to hit or [s] to stand." << std::endl;
            }

            std::cout << std::endl;
            playerScore = scoreHand(playerHand, playerCardCount);
        } while (hit && playerScore < 22);


        //Check if player busted

        if (!blackjack)
        {
            if (playerScore > 21)
            {
                printScoresAndHands(houseHand, houseCardCount, playerHand, playerCardCount);
                std::cout << "You bust! The House wins!" <<std::endl;
            }
            else
            {
                //If player does not bust, house hits below 17
                int houseScore = scoreHand(houseHand, houseCardCount);
                while (houseScore < 17)
                {
                    houseHand[houseCardCount] = getNextCard(cardsDealt);
                    ++houseCardCount;
                    houseScore = scoreHand(houseHand, houseCardCount);
                }

                bool houseBust = houseScore > 21;
                if (houseBust)
                {
                    printScoresAndHands(houseHand, houseCardCount, playerHand, playerCardCount);
                    std::cout << "The House bust! You win!" << std::endl;
                }
                else
                {
                    if (playerScore == houseScore)
                    {
                        printScoresAndHands(houseHand, houseCardCount, playerHand, playerCardCount);
                        std::cout << "Tie! You push." << std::endl;
                    }
                    else if (playerScore > houseScore)
                    {
                        printScoresAndHands(houseHand, houseCardCount, playerHand, playerCardCount);
                        std::cout << "You win!" << std::endl;
                    }
                    else
                    {
                        printScoresAndHands(houseHand, houseCardCount, playerHand, playerCardCount);
                        std::cout << "You lose! The House wins!" << std::endl;
                    }
                }
            }
        }



        std::cout << std::endl << "Would you like to play another round?" << std::endl;
        std::cout << "Yes [y] or No [n]: ";
        std:: cin >> choice;

        if (choice == 'n')
        {
            std::cout << std::endl << "Thanks for playing!";
            exit = true;
        }
        else if (choice == 'y')
        {
            exit = false;
        }
        else
        {
            std::cout << "Invalid input! Press [y] to play another round or [n] to exit." << std::endl;
        }

        std::cout << std::endl;

    }

    return 0;
}
