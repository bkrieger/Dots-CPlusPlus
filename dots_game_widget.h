/* File: dots_game_widget.h
*/

#ifndef DOTS_GAME_WIDGET_H_
#define DOTS_GAME_WIDGET_H_

#include <QtGui>

class DotsGameWidget : public QWidget
{
  Q_OBJECT

 public:
  DotsGameWidget(QWidget* parent);

  void reset();
  void setPaused(bool isPaused);

 signals:
  void needsScoreIncrease(int value);

 protected:
  void paintEvent(QPaintEvent* event);
  void mousePressEvent(QMouseEvent* event);
  void mouseReleaseEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);

 private:

  bool isPaused;

};

#endif
