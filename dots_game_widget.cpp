/* File: pong_canvas.cpp
   Author: Richard Eisenberg (eir@cis)
   Desc: Defines the behavior of the Pong game
*/

#include <QtGui>
#include "dots_game_widget.h"

DotsGameWidget::DotsGameWidget(QWidget* parent)
  : QWidget(parent) // This passes the constructor parameter to the superclass
{  
}


void DotsGameWidget::reset()
{
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 6; j++){
        dot_board[i][j].x = i*BALL_RADIUS*2 + 2;
        dot_board[i][j].y = j*BALL_RADIUS*2 + 2;        
    }
  }
  // update() forces a repaint of the canvas
  update();
}

void DotsGameWidget::setPaused(bool p){
  //if the game has changed state
  if(!(isPaused == p)){
    //if we need to pause
    if(p){

    } 
    //or if we need to resume
    else {

    }
  }
  isPaused = p;
}

void DotsGameWidget::paintEvent(QPaintEvent* event){
  // create painting context
  QPainter p(this);

  // draw a frame around the field:
  p.drawRect(0, 0, WIDTH-1, HEIGHT-1);

  //draw the dots
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 8; j++){
      // no fillEllipse... so we need to set the brush and use drawEllipse
      p.setBrush(Qt::red); // use implicit QBrush constructor
      p.drawEllipse(dot_board[i][j].x, dot_board[i][j].y, BALL_RADIUS * 2, BALL_RADIUS * 2);
    }
  }

}

void DotsGameWidget::mousePressEvent(QMouseEvent* event){}
void DotsGameWidget::mouseReleaseEvent(QMouseEvent* event){}
void DotsGameWidget::mouseMoveEvent(QMouseEvent* event){}
