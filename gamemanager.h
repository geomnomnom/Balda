#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "board.h"
#include "Dictionary.h"
#include "Player.h"
#include "wordcollector.h"
#include "bot/bot.h"

class GameManager : public QObject
{
    Q_OBJECT
    Board board;
    Dictionary dict;
    WordCollector wc;
    Player player1;
    Player player2;
    Bot bot;
    int numberOfSpareCells;
    QString firstWord;
    int playersNumber;
    Player* currentPlayer;
    const int FIRST_PLAYER = 1;
    const int SECOND_PLAYER = 2;
    int currentID;
    const int EASY = 14;
    const int HARD = 88;
    const int HARDEST = 228;

    bool isGameEnded();
public:
    explicit GameManager(int playersNumber, QObject *parent = 0);
    void runGame();
    Player* getFirstPlayer();
    Player* getSecondPlayer();
    int getCurrentPlayer();
    QString getFirstWord();
signals:
    void startMoveFirst();
    void startMoveSecond();
    void askForCells();

    /*
     * Signals to Board
     * */

    void showBoard();

public slots:
    void stepEnded();
    void getNumberOfCells(int value);
};

#endif // GAMEMANAGER_H
