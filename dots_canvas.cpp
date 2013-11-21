
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

  layout = new QVBoxLayout(this);
  gameWidget = new DotsGameWidget(this);
  playButton = new QPushButton("Start", this);
  pauseButton = new QPushButton("Pause", this);
  resetButton = new QPushButton("Reset", this);
  scoreLabel = new QLabel(this);
  timeLabel = new QLabel(this);

  layout->addWidget(playButton);
}

void BreakoutCanvas::selectPlay() 
{
  boardShowing = true;
  layout->removeWidget(playButton);
  layout->addWidget(scoreLabel);
  layout->addWidget(timeLabel);
  layout->addWidget(gameWidget);
  layout->addWidget(pauseButton);
  layout->addWidget(resetButton);
  reset();
}

void BreakoutCanvas::reset()
{
  score = 0;
  isPaused = false;
  timeLeft = 60; //60seconds
  gameWidget.reset();

  pauseButton->setText("Pause");
  scoreLabel->setText("Score: 0");
  timeLabel->setText("Time Remaining: 60 seconds");
}

void BreakoutCanvas::pause()
{
  isPaused = !isPaused;
  gameWidget.setPaused(isPaused);
  pauseButton->setText(isPaused ? "Unpause" : "Pause");
}

void BreakoutCanvas::increaseScore(int value)
{
  score += value;
  scoreLabel->setText("Score: "+ score);
}

void BreakoutCanvas::timerTicked()
{
  // this will get called every second
  timeLeft--;
  timeLabel->setText("Time Reamining: " + timeLeft + " seconds");
  if (timeLeft == 0) {
    gameWidget.setPaused(true);
  }
}
