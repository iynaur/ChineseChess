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

    std::shared_ptr<Step> getBestMove();
    std::shared_ptr<Step> getBestRedMove();
    void getALLPossibleMove(QVector<std::shared_ptr<Step>> & );
    void saveAllPossibleMove(int moveid,int killid,int row ,int col ,QVector<std::shared_ptr<Step>> &);

    std::pair<int, int> calScore();
    std::pair<int, int> getMinScore(int level,int curMaxScore);
    std::pair<int, int> getMaxScore(int level,int curMinScore);
    bool isDumplicateStep(std::shared_ptr<Step> step);

protected:
    int level ;
    std::shared_ptr<Step> m_lastMove = nullptr;
    std::vector<std::shared_ptr<Step>> lastRedMove, lastBlackMove;


signals:

public slots:
    void computerBlackMove();
};

#endif // SINGLEGAME_H
