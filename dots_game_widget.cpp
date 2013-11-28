/* File: pong_canvas.cpp
   Author: Richard Eisenberg (eir@cis)
   Desc: Defines the behavior of the Pong game
*/

#include <QtGui>
#include <stdlib.h>
#include "dots_game_widget.h"

DotsGameWidget::DotsGameWidget(QWidget* parent)
  : QWidget(parent) // This passes the constructor parameter to the superclass
{
  setFixedSize(WIDTH, HEIGHT);
  //QWidget::setMouseTracking(true);
}


void DotsGameWidget::reset()
{
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 6; j++){
        dot_board[i][j].color = getDotColor();
        dot_board[i][j].selected = false;
        dot_board[i][j].x = i*BALL_RADIUS*2.5 + 5;
        dot_board[i][j].y = j*BALL_RADIUS*2.5 + 5;        
    }
  }
  line = NULL;
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
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 6; j++){
      // no fillEllipse... so we need to set the brush and use drawEllipse
      p.setBrush(dot_board[i][j].color); // use implicit QBrush constructor
      p.drawEllipse(dot_board[i][j].x, dot_board[i][j].y, BALL_RADIUS * 2, BALL_RADIUS * 2);
    }
  }
  //draw the lines in the LinkedList
  if(line){
    Line* curr = line;
    while(curr != NULL){
      p.setBrush(curr->color);
      p.drawLine(curr->start_X, curr->start_Y, curr->end_X, curr->end_Y);
      curr = curr->next;
    }
  }

}

void DotsGameWidget::mousePressEvent(QMouseEvent* event){
  int x = event->x();
  int y = event->y();
  x = returnIndexOfDot(x);
  y = returnIndexOfDot(y);

  //set the current values
  currentDotX = x;
  currentDotY = y;
  currentDotColor = dot_board[x][y].color;

  //do we need selected? I figure, but haven't used it yet.
  dot_board[x][y].selected = true;
  //eventually take this out
  dot_board[x][y].color = Qt::red;
  line = NULL;

  //force a repaint.
  update();
}
void DotsGameWidget::mouseReleaseEvent(QMouseEvent* event){
  //remove last line for visual purposes (TEMPORARY)
  Line* curr = line;
  while (curr->next->next != NULL){
    curr = curr->next;
  }
  curr->next = NULL;
  update();
}

void DotsGameWidget::mouseMoveEvent(QMouseEvent* event){
  int x = event->x();
  int y = event->y();

  //index of the dot you are currently looking at
  int dot_x = returnIndexOfDot(x);
  int dot_y = returnIndexOfDot(y);
  //write a function or test for adjacency to last looked at dot
  bool is_adjacent = true;
  //if the dot is of the same color
  if(dot_board[dot_x][dot_y].color == currentDotColor){
    //if the dot is adjacent
    if(is_adjacent){
      currentDotX = dot_x;
      currentDotY = dot_y;

      dot_board[dot_x][dot_y].selected = true;
      dot_board[dot_x][dot_y].color = Qt::red;

      //create a new line
      Line* curr = line;
      while(curr-> next != NULL){ curr = curr->next; }
      curr->setEndPoint(currentDotX*(BALL_RADIUS*2 + BALL_RADIUS/2) + BALL_RADIUS + 5,
        currentDotY*(BALL_RADIUS*2 + BALL_RADIUS/2) + BALL_RADIUS + 5);
      curr->next = new Line(currentDotX*(BALL_RADIUS*2 + BALL_RADIUS/2) + BALL_RADIUS + 5, 
        currentDotY*(BALL_RADIUS*2 + BALL_RADIUS/2) + BALL_RADIUS + 5, x, y, 
        currentDotColor);
    }
  }

  //Line for first dot
  if(line){
    Line* curr = line;
    while(curr->next != NULL){ curr = curr->next; }
    curr->setEndPoint(x, y);
  } else{
    line = new Line(currentDotX*(BALL_RADIUS*2 + BALL_RADIUS/2) + BALL_RADIUS + 5, 
      currentDotY*(BALL_RADIUS*2 + BALL_RADIUS/2) + BALL_RADIUS + 5, x, y, 
      currentDotColor);
  }

  update();
}

QColor DotsGameWidget::getDotColor(){
  int choose = rand() % 4;
  if(choose == 0) {
    return Qt::white;
  } else if (choose == 1) {
    return Qt::darkCyan;
  } else if (choose == 2) {
    return Qt::darkMagenta;
  } else {
    return Qt::darkGray;
  }
}

//freakishly hardcoding index selection.
//fix when less tired.  at least a switch statement
int DotsGameWidget::returnIndexOfDot(int pos){
  int box_field = BALL_RADIUS*2+10; 
  if (pos < box_field) {
    return 0;
  } else if (pos < 2*box_field) {
    return 1;
  } else if (pos < 3*box_field) {
    return 2;
  } else if (pos < 4*box_field) {
    return 3;
  } else if (pos < 5*box_field) {
    return 4;
  } else if (pos < 6*box_field) {
    return 5;
  }
}