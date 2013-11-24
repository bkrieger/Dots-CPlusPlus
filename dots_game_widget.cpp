/* File: pong_canvas.cpp
   Author: Richard Eisenberg (eir@cis)
   Desc: Defines the behavior of the Pong game
*/

#include <QtGui>

DotsGameWidget::DotsGameWidget(QWidget* parent)
  : QWidget(parent) // This passes the constructor parameter to the superclass
{  
}


void DotsGameWidget::reset()
{
  // update() forces a repaint of the canvas
  update();
}

void DotsGameWidget::setPaused(bool isPaused){}
void DotsGameWidget::needsScoreIncrease(int value){}
void DotsGameWidget::paintEvent(QPaintEvent* event){}
void DotsGameWidget::mousePressEvent(QMouseEvent* event){}
void DotsGameWidget::mouseReleaseEvent(QMouseEvent* event){}
void DotsGameWidget::mouseMoveEvent(QMouseEvent* event){}
