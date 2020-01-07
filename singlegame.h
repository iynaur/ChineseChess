#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include "board.h"
#include <QMouseEvent>
#include <QVector>

class SingleGame : public Board
{
    Q_OBJECT
public:
    explicit SingleGame(QWidget *parent = 0);
    ~SingleGame();

    void back();
    void click(int id, int row, int col);
    void paintEvent(QPaintEvent *) override;

    Step* getBestMove();
    void getALLPossibleMove(QVector<Step *> & );
    void saveAllPossibleMove(int moveid,int killid,int row ,int col ,QVector<Step *> &);

    int calScore();
    int getMinScore(int level,int curMaxScore);
    int getMaxScore(int level,int curMinScore);

private:
    int level ;
    Step* m_lastMove = nullptr;

signals:

public slots:
    void computerMove();
};

#endif // SINGLEGAME_H
