#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include "board.h"
#include <QMouseEvent>
#include <QVector>
#include "aiplayer.h"

class SingleGame : public Board
{
    Q_OBJECT
public:
    explicit SingleGame(QWidget *parent = 0);
    ~SingleGame();

    void back();
    void click(int id, int row, int col);
    void paintEvent(QPaintEvent *) override;

    void saveAllPossibleMove(int moveid,int killid,int row ,int col ,QVector<std::shared_ptr<Step>> &);

    bool isDumplicateStep(std::shared_ptr<Step> step);

protected:
    int level ;
    std::shared_ptr<Step> m_lastMove = nullptr;
    std::vector<std::shared_ptr<Step>> lastRedMove, lastBlackMove;
    aiPlayer* m_redAi, *m_blackAi;

signals:

public slots:
    void computerBlackMove();
};

#endif // SINGLEGAME_H
