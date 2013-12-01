/* File: dots_canvas.h
*/

#ifndef DOTS_CANVAS_H_
#define DOTS_CANVAS_H_

#include <sstream>
#include <QtGui>

using namespace std;

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
  void selectPlay();
  void reset();
  void pause();

 private:
  bool boardShowing;
  bool isPaused;
  int score;

  QTimer* timer;
  int timeLeft;

  QGridLayout* layout;
  DotsGameWidget* gameWidget;
  QPushButton* playButton;
  QPushButton* pauseButton;
  QPushButton* resetButton;
  QLabel* scoreLabel;
  QLabel* timeLabel;

  static const int WIDTH = 400;
  static const int HEIGHT = 600;

};

#endif
