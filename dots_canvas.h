/* File: dots_canvas.h
*/

#ifndef DOTS_CANVAS_H_
#define DOTS_CANVAS_H_

#include <QtGui>

class DotsGameWidget;

class DotsCanvas : public QWidget
{
  Q_OBJECT

 public:
  DotsCanvas(QWidget* parent);

 public slots:
  void increaseScore(int value);

 private slots:
  void timerTicked();

 private:
  void selectPlay();
  void reset();
  void pause();

  bool boardShowing;
  bool isPaused;
  int score;

  QTimer* timer;
  int timeLeft;

  QVBoxLayout* layout;
  DotsGameWidget* gameWidget;
  QPushButton* playButton;
  QPushButton* pauseButton;
  QPushButton* resetButton;
  QLabel* scoreLabel;
  QLabel* timeLabel;

  static const int WIDTH = 400;
  static const int HEIGHT = 300;

};

#endif
