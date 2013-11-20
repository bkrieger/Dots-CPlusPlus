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

 protected:
  void paintEvent(QPaintEvent* event);

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

  DotsGameWidget* gameWidget;

};

#endif
