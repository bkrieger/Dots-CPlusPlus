
/* File: dots_canvas.cpp
*/

#include <QtGui>
#include "dots_canvas.h"
#include "dots_game_widget.h"

DotsCanvas::DotsCanvas(QWidget* parent)
  : QWidget(parent) // This passes the constructor parameter to the superclass
{  
  timer = new QTimer(this);
  timer->setInterval(1000); // an interval of 1s to update clock
  timer->start();

  connect(timer, SIGNAL(timeout()), this, SLOT(timerTicked()));

  setFixedSize(WIDTH, HEIGHT);

  layout = new QGridLayout(this);
  playButton = new QPushButton("Start", this);
  pauseButton = new QPushButton("Pause", this);
  resetButton = new QPushButton("Reset", this);
  gameWidget = new DotsGameWidget(this);
  scoreLabel = new QLabel(this);
  timeLabel = new QLabel(this);

  playButton->setFixedSize(100, 100);
  pauseButton->setFixedSize(100, 100);
  resetButton->setFixedSize(100, 100);
  
  scoreLabel->setFixedSize(100, 100);
  timeLabel->setFixedSize(100, 100);

  connect(playButton, SIGNAL(clicked()), this, SLOT(selectPlay()));
  connect(pauseButton, SIGNAL(clicked()), this, SLOT(pause()));
  connect(resetButton, SIGNAL(clicked()), this, SLOT(reset()));

  layout->addWidget(playButton, 0, 0);

  scoreLabel->hide();
  timeLabel->hide();
  gameWidget->hide();
  pauseButton->hide();
  resetButton->hide();
}

void DotsCanvas::selectPlay() 
{
  boardShowing = true;

  layout->removeWidget(playButton);
  playButton->hide();

  layout->addWidget(scoreLabel, 0, 0);
  layout->addWidget(timeLabel, 0, 1);
  layout->addWidget(gameWidget, 1, 0, 1, 2);
  layout->addWidget(pauseButton, 2, 0);
  layout->addWidget(resetButton, 2, 1);

  scoreLabel->show();
  timeLabel->show();
  gameWidget->show();
  pauseButton->show();
  resetButton->show();

  reset();
}

void DotsCanvas::reset()
{
  score = 0;
  isPaused = false;
  timeLeft = 60; //60seconds
  gameWidget->reset();

  pauseButton->setText("Pause");
  scoreLabel->setText("Score: 0");
  timeLabel->setText("Time Remaining: 60 seconds");
}

void DotsCanvas::pause()
{
  isPaused = !isPaused;
  gameWidget->setPaused(isPaused);
  pauseButton->setText(isPaused ? "Unpause" : "Pause");
}

void DotsCanvas::increaseScore(int value)
{
  score += value;
  scoreLabel->setText(QString("Score: %1").arg(score));
}

void DotsCanvas::timerTicked()
{
  // this will get called every second
  if(!isPaused && boardShowing && timeLeft > 0) {
    timeLeft--;
    timeLabel->setText(QString("Time Remaining: %1 seconds").arg(timeLeft));
    if (timeLeft == 0) {
      gameWidget->setPaused(true);
    }
  }
}
