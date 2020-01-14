#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "multigame.h"
#include <QImage>
#include <QPixmap>
#include "singlegame.h"
#include "zerogame.h"
#include <iostream>
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    m_board = new Board(this);
    resize(m_board->width() + 100, m_board->height() + 50);
    on_pushButton_4_clicked();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::initHuman(humanPlayer* &human, Stone::COLOR color){
  human = new humanPlayer(m_board, color);
}

void MainWidget::on_pushButton_clicked()//p vs p
{

}

void MainWidget::on_pushButton_2_clicked()
{

}

void MainWidget::on_pushButton_3_clicked()
{

}

void MainWidget::on_pushButton_4_clicked()
{

}

void MainWidget::initAi(aiPlayer* &ai, Stone::COLOR color){
  ai = new aiPlayer(m_board, color);
  connect(ai, &aiPlayer::move, this, [&](std::shared_ptr<Step> step)
  {
//    if (whoWinTheGame()) return;


      m_board->moveStone(step->_moveid, step->_killid, step->_rowTo, step->_colTo);
      m_board->restartGame();
      m_board->selected = -1;
      m_board->update();
  });
}

void MainWidget::on_pushButton_5_clicked()
{
  initAi(m_redAi, Stone::RED);
  initAi(m_blackAi, Stone::BLACK);
  if (m_board->bRedTurn)
  {
    m_redAi->acceptTurn();
  }
  else
  {
    m_blackAi->acceptTurn();
  }
}
