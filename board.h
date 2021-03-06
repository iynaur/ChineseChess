#ifndef BOARD_H
#define BOARD_H
#include <QWidget>
#include"stone.h"
#include<QPoint>
#include "step.h"
#include <QVector>

/**
 * @brief The Board class
 */
class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);

    QPoint& getRowCol(QPoint &pen);

    void drawStone(int id, QPainter &painter);
    bool isRegularMovement(int selectid ,int row,int col,int killid);
    bool maybeRegularMovement(int selectid ,int row,int col,int killid);

    bool isRegularMoveBoss(int selectid ,int row,int col);
    bool isRegularMoveCHE(int selectid ,int row,int col);
    bool isRegularMoveMa(int selectid ,int row,int col);
    bool isRegularMoveXiang(int selectid ,int row,int col);
    bool isRegularMoveShi(int selectid ,int row,int col);
    bool isRegularMoveSoldier(int selectid ,int row,int col);
    bool isRegularMovePao(int selectid ,int row,int col,int killid);
    int whoWinTheGame();
    void restartGame();

    //
    void click(QPoint pt);
    virtual void click(int id, int row, int col);
    int getStoneId(int row, int col);
    void trySelectStone(int id);
    void tryMoveStone(int killid, int row, int col);
    void moveStone(int moveid, int killid, int row, int col);
    void saveStep(int moveid, int killid, int row, int col);
    void killStone(int id);

    //
    virtual void back();
    void reliveStone(int id);
    void backOne();
    void back(std::shared_ptr<Step> step);
    void initCanMove();
    void fakeMove(std::shared_ptr<Step>);
    void unfakeMove(std::shared_ptr<Step>);

    bool bRedTurn ;
    Stone stone[32];
    int selected ;
    std::shared_ptr<Step> m_lastMove = nullptr;

    void getALLPossibleMove(QVector<std::shared_ptr<Step> > &steps);
    void saveAllPossibleMove(int moveid, int killid, int row, int col, QVector<std::shared_ptr<Step> > &steps);
protected:
    int d ;
    QVector<std::shared_ptr<Step>> steps ;

    std::vector<std::vector<bool>> m_canMove;
    bool m_bHasMoved = false;

private:
    void moveStone(int moveid, int row, int col);
    void drawPostion(int x , int y, int r, QPainter &painter);
    void initStone();

    bool isEXistPieceInLine(int selectid,int row,int col);
    int countPieceInLine(int selectid,int row,int col);
    bool isEXistPieceInPoint(int row ,int col);
signals:

public slots:
    void slotBack();
};

#endif // BOARD_H
