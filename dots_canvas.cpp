
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

  connect(timer, SIGNAL(timeout()), this, SLOT(timerTicked()));

  setFixedSize(WIDTH, HEIGHT);

  layout = new QGridLayout(this);
  playWithTimeButton = new QPushButton("Timed Game", this);
  playWithMovesButton = new QPushButton("Moves Game", this);
  backButton = new QPushButton("Back", this);
  pauseButton = new QPushButton("Pause", this);
  resetButton = new QPushButton("Reset", this);
  gameWidget = new DotsGameWidget(this);
  scoreLabel = new QLabel(this);
  timeOrMovesLabel = new QLabel(this);

  playWithTimeButton->setFixedSize(200, 100);
  playWithMovesButton->setFixedSize(200, 100);
  backButton->setFixedSize(100, 50);
  pauseButton->setFixedSize(150, 50);
  resetButton->setFixedSize(150, 50);

  scoreLabel->setFixedSize(100, 50);
  timeOrMovesLabel->setFixedSize(250, 50);

  connect(playWithTimeButton, SIGNAL(clicked()), this, SLOT(selectPlayWithTime()));
  connect(playWithMovesButton, SIGNAL(clicked()), this, SLOT(selectPlayWithMoves()));
  connect(backButton, SIGNAL(clicked()), this, SLOT(back()));
  connect(pauseButton, SIGNAL(clicked()), this, SLOT(pause()));
  connect(resetButton, SIGNAL(clicked()), this, SLOT(reset()));
  connect(gameWidget, SIGNAL(needsScoreIncrease(int)), this, SLOT(increaseScore(int)));

  layout->addWidget(playWithTimeButton, 0, 0);
  layout->addWidget(playWithMovesButton, 1, 0);

  scoreLabel->hide();
  timeOrMovesLabel->hide();
  backButton->hide();
  gameWidget->hide();
  pauseButton->hide();
  resetButton->hide();
}

void DotsCanvas::selectPlayWithTime()
{
  playingTimedGame = true;
  timer->start();
  startGame();
}

void DotsCanvas::selectPlayWithMoves()
{
  playingTimedGame = false;
  startGame();
}

void DotsCanvas::startGame() 
{
  layout->removeWidget(playWithTimeButton);
  layout->removeWidget(playWithMovesButton);
  playWithTimeButton->hide();
  playWithMovesButton->hide();

  layout->addWidget(backButton, 0, 0);
  layout->addWidget(scoreLabel, 1, 0);
  layout->addWidget(timeOrMovesLabel, 1, 1);
  layout->addWidget(gameWidget, 2, 0, 1, 3);
  layout->addWidget(pauseButton, 3, 0);
  layout->addWidget(resetButton, 3, 1);

  backButton->show();
  scoreLabel->show();
  timeOrMovesLabel->show();
  gameWidget->show();
  pauseButton->show();
  resetButton->show();

  reset();
}

void DotsCanvas::back()
{
  timer->stop();

  layout->removeWidget(backButton);
  layout->removeWidget(scoreLabel);
  layout->removeWidget(timeOrMovesLabel);
  layout->removeWidget(gameWidget);
  layout->removeWidget(pauseButton);
  layout->removeWidget(resetButton);

  resetButton->hide();
  pauseButton->hide();
  gameWidget->hide();
  timeOrMovesLabel->hide();
  scoreLabel->hide();
  backButton->hide();

  layout->addWidget(playWithTimeButton, 0, 0);
  layout->addWidget(playWithMovesButton, 1, 0);
  playWithTimeButton->show();
  playWithMovesButton->show();
}

void DotsCanvas::reset()
{
  score = 0;
  isPaused = false;
  if (playingTimedGame) {
    timeOrMovesLeft = 60; //60seconds
    timeOrMovesLabel->setText("Time Remaining: 60 seconds");
  } else {
    timeOrMovesLeft = 30; //30 moves
    timeOrMovesLabel->setText("Moves Remaining: 30");
  }
  gameWidget->reset();

  pauseButton->setText("Pause");
  scoreLabel->setText("Score: 0");
}

void DotsCanvas::pause()
{
  if (timeOrMovesLeft > 0) {
    isPaused = !isPaused;
    gameWidget->setPaused(isPaused);
    pauseButton->setText(isPaused ? "Unpause" : "Pause");
  }
}

void DotsCanvas::increaseScore(int value)
{
  if (!playingTimedGame) {
    decrementTimeOrMoves();
  }
  score += value;
  scoreLabel->setText(QString("Score: %1").arg(score));
}

void DotsCanvas::timerTicked()
{
  // this will get called every second
  if(playingTimedGame && !isPaused && timeOrMovesLeft > 0) {
    decrementTimeOrMoves();
  }
}

void DotsCanvas::decrementTimeOrMoves()
{
    timeOrMovesLeft--;
    timeOrMovesLabel->setText(QString("%1 Remaining: %2 %3")
      .arg(playingTimedGame ? "Time" : "Moves")
      .arg(timeOrMovesLeft)
      .arg(playingTimedGame ? "seconds" : ""));
    if (timeOrMovesLeft == 0) {
      gameWidget->reset();
      gameWidget->setPaused(true);
      timeOrMovesLabel->setText(QString("Game Over! Reset to try again."));
    }

}
