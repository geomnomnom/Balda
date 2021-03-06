#include "graphicboard.h"
#include "logger.h"
#include <QInputDialog>
#include "gamemanager.h"

GraphicBoard::GraphicBoard(QWidget *parent) :
    QWidget(parent)
{
    tableLayout = new QGridLayout;
    for (int i = 0; i < 5; ++i) {
        buttons.push_back(QVector<ButtonCell*>(5));
        for (int j = 0; j < 5; ++j) {
            buttons[i][j] = new ButtonCell();
            buttons[i][j]->connectToPanel(this);
            tableLayout->addWidget(buttons[i][j], i, j);
        }
    }
    gamePanel = new QHBoxLayout(this);
    gameBoardPanel = new QVBoxLayout;
    gameBoardPanel->addLayout(tableLayout);
    wordPanel = new QHBoxLayout;
    currentWord = new QLabel("");
    commitButton = new QPushButton("Enter!");
    wordPanel->addWidget(currentWord);
    wordPanel->addWidget(commitButton);
    gameBoardPanel->addLayout(wordPanel);



    firstPlayerScore = new QLabel(tr("0"), this);
    firstPlayerWords = new QListWidget(this);
    firstPlayerPanel = new QVBoxLayout(this);
    firstPlayerPanel->addWidget(firstPlayerScore);
    firstPlayerPanel->addWidget(firstPlayerWords);

    secondPlayerScore = new QLabel(tr("0"), this);
    secondPlayerWords = new QListWidget(this);
    secondPlayerPanel = new QVBoxLayout(this);
    secondPlayerPanel->addWidget(secondPlayerScore);
    secondPlayerPanel->addWidget(secondPlayerWords);

    gamePanel->addLayout(secondPlayerPanel);
    gamePanel->addLayout(gameBoardPanel);
    gamePanel->addLayout(firstPlayerPanel);

    setLayout(gamePanel);

    int players = QInputDialog::getInt(this, tr("Enter number of players"), tr("Введите число игроков"), 1, 1, 2);
    Logger l;
    l.printLog(DEBUG, players);
    gameManager = new GameManager(players);
    connectToPlayers(gameManager->getFirstPlayer(), gameManager->getSecondPlayer());
    gameManager->getFirstPlayer()->connectToInterface(this);
    gameManager->getSecondPlayer()->connectToInterface(this);
    QString word = gameManager->getFirstWord();
    for (int i = 0; i < 5; ++i) {
        buttons[2][i]->setText(QString(word[i]));
    }

    for (int i = 0; i < 5; ++i) {
        buttons[2][i]->setMenu(NULL);
    }

    connect(commitButton, SIGNAL(clicked()), this, SLOT(onCommitButtonClicked()));
}

void GraphicBoard::connectToPlayers(Player *player1, Player* player2)
{
    connect(this, SIGNAL(chooseLetterFirst(QPair<QPair<int,int>, QChar>)),
            player1, SLOT(onLetterChosen(QPair<QPair<int,int>,QChar>)));
    connect(this, SIGNAL(chooseLetterSecond(QPair<QPair<int,int>, QChar>)),
            player2, SLOT(onLetterChosen(QPair<QPair<int,int>,QChar>)));
    connect(this, SIGNAL(pushLetterFirst(QPair<int,int>)),
            player1, SLOT(onLetterPushed(QPair<int,int>)));
    connect(this, SIGNAL(pushLetterSecond(QPair<int,int>)),
            player2, SLOT(onLetterPushed(QPair<int,int>)));
    connect(this, SIGNAL(commitWordFirst()), player1, SLOT(onWordCommited()));
    connect(this, SIGNAL(commitWordSecond()), player2, SLOT(onWordCommited()));
}


void GraphicBoard::onCellPushed()
{
    int xSender = 0;
    int ySender = 0;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (reinterpret_cast<ButtonCell*>(sender()) == buttons[i][j]) {
                xSender = i;
                ySender = j;
            }
        }
    }
    //  currentWord->setText(currentWord->text() + buttons[xSender][ySender]->text());
    if (gameManager->getCurrentPlayer() == 1) {
        emit pushLetterFirst(qMakePair(xSender, ySender));
    } else {
        emit pushLetterSecond(qMakePair(xSender, ySender));
    }
}

void GraphicBoard::onCellChosen(QChar letter)
{
    int xSender = 0;
    int ySender = 0;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (reinterpret_cast<ButtonCell*>(sender()) == buttons[i][j]) {
                xSender = i;
                ySender = j;
            }
        }
    }
    QPair<QPair<int,int>, QChar> sendLetter = qMakePair(qMakePair(xSender, ySender), letter);
    if (gameManager->getCurrentPlayer() == 1) {
        emit chooseLetterFirst(sendLetter);
    } else {
        emit chooseLetterSecond(sendLetter);
    }
}

void GraphicBoard::afterCellPushed(QPair<int, int>coordinates)
{
    currentWord->setText(currentWord->text() + buttons[coordinates.first][coordinates.second]->text());
}

void GraphicBoard::afterCellChoosen(QPair<QPair<int, int>, QChar> coordinates)
{
    buttons[coordinates.first.first][coordinates.first.second]->setMenu(NULL);
    buttons[coordinates.first.first][coordinates.first.second]->setText(QString(coordinates.second));
}

void GraphicBoard::afterWordCommited(QString word) {
    currentWord->setText(NULL);
    if (sender() == gameManager->getFirstPlayer()) {
        firstPlayerWords->addItem(word);
    } else {
        secondPlayerWords->addItem(word);
    }
    if (sender() == gameManager->getFirstPlayer()) {
        int score = gameManager->getFirstPlayer()->getScore();
        firstPlayerScore->setText(QString::number(score));
    } else {
        int score = gameManager->getSecondPlayer()->getScore();
        secondPlayerScore->setText(QString::number(score));
    }
}

void GraphicBoard::onPlayerResetWord(const QPair<int, int> &coordinates)
{
    buttons[coordinates.first][coordinates.second]->createMenu();
    buttons[coordinates.first][coordinates.second]->setText(QString(""));
    currentWord->setText(QString(""));
}

void GraphicBoard::onCommitButtonClicked()
{
    if (gameManager->getCurrentPlayer() == 1) {
        emit commitWordFirst();
    } else {
        emit commitWordSecond();
    }
}






