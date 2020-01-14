#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "aiplayer.h"
#include "humanplayer.h"

class Board;

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

  void initAi(aiPlayer *&ai, Stone::COLOR color);
  void initHuman(humanPlayer *&human, Stone::COLOR color);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

private:
    Ui::MainWidget *ui;
    Board* m_board;
    aiPlayer* m_redAi, *m_blackAi;
    humanPlayer* m_redHuman, *m_blackHuman;
};

#endif // MAINWIDGET_H
