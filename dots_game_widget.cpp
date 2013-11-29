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
}

//reset the game
void DotsGameWidget::reset()
{
  //create the new dots
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 6; j++){
        dot_board[i][j].color = getDotColor();
        dot_board[i][j].selected = false;
        dot_board[i][j].x = i*BALL_RADIUS*2.5 + 5;
        dot_board[i][j].y = j*BALL_RADIUS*2.5 + 5;        
    }
  }
  //set the initial line linked list to null
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
  //index of clicked dot
    int x = returnIndexOfDot(event->x());
    int y = returnIndexOfDot(event->y());
  
  //set the current values
    curr_dot_x = x;
    curr_dot_y = y;
    curr_dot_color = dot_board[x][y].color;
    dot_board[x][y].selected = true;
  
  //force a repaint.
  update();
}
void DotsGameWidget::mouseReleaseEvent(QMouseEvent* event){
  //remove lines
  line = NULL;
  int score = 0;

  //handle the score and move dots down
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 6; j++){
      if(dot_board[i][j].selected){
        score++;
        for(int k = j; k >= 0; k--){
          //replace from above
          if(k > 0){
            dot_board[i][k].color = dot_board[i][k-1].color;
            dot_board[i][k].selected = false;
          }
          //create a new dot at top row
          else {
            dot_board[i][k].selected = false;
            dot_board[i][k].color = getDotColor();
          }
        }
      }
    }
  }

  //connect at some point?
  needsScoreIncrease(score);

  update();
}

void DotsGameWidget::mouseMoveEvent(QMouseEvent* event){
  //index of the dot you are currently looking at
  int x = returnIndexOfDot(event->x());
  int y = returnIndexOfDot(event->y());

  //if it hasn't already been selected
  if(dot_board[x][y].selected != true){
    //if the dot is of the same color
    if(dot_board[x][y].color == curr_dot_color){
      //if the dot is adjacent
      if(isAdjacent(curr_dot_x, x, curr_dot_y, y)){
        //select it
        curr_dot_x = x;
        curr_dot_y = y;
        dot_board[x][y].selected = true;

        //create a new line
        Line* curr = line;
        while(curr-> next != NULL){ curr = curr->next; }
        curr->setEndPoint(curr_dot_x*(BALL_RADIUS*2 + BALL_RADIUS/2) + BALL_RADIUS + 5,
          curr_dot_y*(BALL_RADIUS*2 + BALL_RADIUS/2) + BALL_RADIUS + 5);
        curr->next = new Line(curr_dot_x*(BALL_RADIUS*2 + BALL_RADIUS/2) + BALL_RADIUS + 5, 
          curr_dot_y*(BALL_RADIUS*2 + BALL_RADIUS/2) + BALL_RADIUS + 5, event->x(), event->y(), 
          curr_dot_color);
      }
    }
  }
  //Line that's not connected to anything
  if(line){
    Line* curr = line;
    while(curr->next != NULL){ curr = curr->next; }
    curr->setEndPoint(event->x(), event->y());
  } else{
    line = new Line(curr_dot_x*(BALL_RADIUS*2 + BALL_RADIUS/2) + BALL_RADIUS + 5, 
      curr_dot_y*(BALL_RADIUS*2 + BALL_RADIUS/2) + BALL_RADIUS + 5, event->x(), event->y(), 
      curr_dot_color);
  }

  update();
}

//sets a totally random dot color for a new dot
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

//checks for adjacency, but not diagonally
bool DotsGameWidget::isAdjacent(int x1, int x2, int y1, int y2){
  int xdiff = abs(x1 - x2);
  int ydiff = abs(y1 - y2);
  if ((ydiff < 2 && xdiff < 1) || (xdiff < 2 && ydiff < 1)) return true;
  else return false;
}

//freakishly hardcoding index selection from global position
//fix when less tired.  at least use a switch statement
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