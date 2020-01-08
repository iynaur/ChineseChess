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
    widget = new MultiGame(this);
    resize(widget->width() + 100, widget->height() + 50);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_pushButton_clicked()
{
    if(widget != NULL)
        delete widget;
    widget = new MultiGame(this);
    widget->setVisible(true);
}

void MainWidget::on_pushButton_2_clicked()
{
    if(widget != NULL)
        delete widget;
    widget = new SingleGame(this);
    widget->setVisible(true);
}

void MainWidget::on_pushButton_3_clicked()
{
  on_pushButton_2_clicked();
  SingleGame* sin = dynamic_cast<SingleGame*>(widget);
  sin->bRedTurn = !sin->bRedTurn;
  sin->computerMove();
}

void MainWidget::on_pushButton_4_clicked()
{
  if(widget != NULL)
      delete widget;
  ZeroGame* zero = new ZeroGame(this);
  zero->start();
  widget = zero;
  widget->setVisible(true);
}
