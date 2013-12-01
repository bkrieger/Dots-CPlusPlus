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
  for(int i = 0; i < NUM_DOTS_HORIZONTAL; i++){
    for(int j = 0; j < NUM_DOTS_VERTICAL; j++){
        dot_board[i][j].color = getDotColor();
        dot_board[i][j].selected = false;
        dot_board[i][j].x = i*BALL_RADIUS*2.5 + 5;
        dot_board[i][j].y = j*BALL_RADIUS*2.5 + 5;        
    }
  }
  //set the initial line linked list to null
  line = NULL;
  numSelected = 0;
  hasSquare = false;
  squareXIndex = -1;
  squareYIndex = -1;
  isPaused = false;
  // update() forces a repaint of the canvas
  update();
}

void DotsGameWidget::setPaused(bool p){
  isPaused = p;
  // update canvas so we draw everything grey when paused
  update();
}

void DotsGameWidget::paintEvent(QPaintEvent*){
  // create painting context
  QPainter p(this);

  // draw a frame around the field:
  p.drawRect(0, 0, WIDTH-1, HEIGHT-1);

  //draw the dots
  for(int i = 0; i < NUM_DOTS_HORIZONTAL; i++){
    for(int j = 0; j < NUM_DOTS_VERTICAL; j++){
          // no fillEllipse... so we need to set the brush and use drawEllipse
          // if we're paused, draw everything gray.
          if (isPaused) {
            p.setBrush(Qt::darkGray);
          } else {
            p.setBrush(dot_board[i][j].color); // use implicit QBrush constructor
          }
          p.drawEllipse(dot_board[i][j].x, dot_board[i][j].y, BALL_RADIUS * 2, BALL_RADIUS * 2);

    }
  }
  //draw the lines in the LinkedList
  if(line){
    Line* curr = line;
    while(curr != NULL){
      QPen pen(curr->color);
      pen.setWidth(6);
      p.setPen(pen);
      p.drawLine(curr->start_X, curr->start_Y, curr->end_X, curr->end_Y);
      curr = curr->next;
    }
  }

}

void DotsGameWidget::mousePressEvent(QMouseEvent* event){
  if (!isPaused) {
    //index of clicked dot
      int x = returnIndexOfDot(event->x());
      int y = returnIndexOfDot(event->y());
    
    //set the current values
      curr_dot_x = x;
      curr_dot_y = y;
      curr_dot_color = dot_board[x][y].color;
      dot_board[x][y].selected = true;
      numSelected = 1;
      hasSquare = false;
      squareXIndex = -1;
      squareYIndex = -1;
    
    //force a repaint.
    update();
  }

}
void DotsGameWidget::mouseReleaseEvent(QMouseEvent*){
  //remove lines
  line = NULL;

  if (!isPaused) {

    if (hasSquare) {
      // select all dots of curr_dot_color
      for (int i = 0; i < NUM_DOTS_HORIZONTAL; i++) {
        for (int j = 0; j < NUM_DOTS_VERTICAL; j++) {
          // If the dot isn't already selected, and is of the right color, select it.
          if (dot_board[i][j].color == curr_dot_color && !dot_board[i][j].selected) {
            dot_board[i][j].selected = true;
            numSelected++;
          }
        }
      }
    }

    //handle the score and move dots down
    for(int i = 0; i < NUM_DOTS_HORIZONTAL; i++){
      for(int j = 0; j < NUM_DOTS_VERTICAL; j++){
        if(dot_board[i][j].selected) {
          // only do something if we have at least 2
          if (numSelected >= 2) {
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
                if (hasSquare) {
                  while (dot_board[i][k].color == curr_dot_color) {
                    dot_board[i][k].color = getDotColor();
                  }
                }
              }
            }
          } else {
            // we only want to unselect it
            dot_board[i][j].selected = false;
          }
        }
      }
    }
    if (numSelected >= 2) {
      needsScoreIncrease((numSelected-1)*2);
    }
  }
  numSelected = 0;
  update();
}

void DotsGameWidget::mouseMoveEvent(QMouseEvent* event){

  // We check to make sure that the left mouse button is pressed, 
  // otherwise we don't want to do anything
  if (!isPaused && (event->buttons() & Qt::LeftButton)) {
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
          selectDot(x, y, event);
        }
      }
    } else { // If we mouse over a dot that has already been selected
      // make sure we're going over an adjacent dot
      if (isAdjacent(curr_dot_x, x, curr_dot_y, y)) {
        // Check for backtrack
        Line *secondToLast = line;
        while (secondToLast->next->next != NULL) { secondToLast = secondToLast->next; }
        // When while loop is over, secondToLast is the second to last line.
        if (secondToLast->startXIndex == x && secondToLast->startYIndex == y) {
          // If we are going over the second to last dot, get rid of the last line
          // and deselect the current dot, and make the second to last dot the current.
          secondToLast->next = NULL;
          // If we are not backtracking over a square, deselect the dot
          if (!(curr_dot_x == squareXIndex && curr_dot_y == squareYIndex)) {
            dot_board[curr_dot_x][curr_dot_y].selected = false;
            numSelected--;
          } else {
            // we are backtracking over a square
            hasSquare = false;
            squareXIndex = -1;
            squareYIndex = -1;
          }
          //Make the dot we're over the current dot
          curr_dot_x = x;
          curr_dot_y = y;
        } else if (!hasSquare) {
          // If we haven't backtracked, and we don't already have a square, check for a square.
          Line *curr = line;
          // Only go up to the second to last element in while loop, otherwise it's a backtrack.
          while (curr->next->next != NULL) {
            // Check if the starting point of curr is what we're mousing over
            // If yes, we just made a square
            if (curr->startXIndex == x && curr->startYIndex == y) {
              // Square. Allow this connection to be made.
              selectDot(x, y, event);
              hasSquare = true;
              squareXIndex = x;
              squareYIndex = y;
              break;
            }
            curr = curr->next;
          }
        }
      }
    }
    //Line that's not connected to anything
    if(line){
      Line* curr = line;
      while(curr->next != NULL){ curr = curr->next; }
      curr->setEndPoint(event->x(), event->y());
    } else{
      line = new Line(
        curr_dot_x,
        curr_dot_y, 
        curr_dot_x*(BALL_RADIUS*2 + BALL_RADIUS/2) + BALL_RADIUS + 5, 
        curr_dot_y*(BALL_RADIUS*2 + BALL_RADIUS/2) + BALL_RADIUS + 5, 
        event->x(), 
        event->y(), 
        curr_dot_color);
    }

    update();
  }
}

void DotsGameWidget::selectDot(int x, int y, QMouseEvent *event) {
  curr_dot_x = x;
  curr_dot_y = y;
  if (!dot_board[x][y].selected) {
    dot_board[x][y].selected = true;
    numSelected++;
  }

  //create a new line
  Line* curr = line;
  while(curr->next != NULL){ curr = curr->next; }
  curr->setEndPoint(
    curr_dot_x*(BALL_RADIUS*2 + BALL_RADIUS/2) + BALL_RADIUS + 5,
    curr_dot_y*(BALL_RADIUS*2 + BALL_RADIUS/2) + BALL_RADIUS + 5);

  curr->next = new Line(
    x, 
    y, 
    curr_dot_x*(BALL_RADIUS*2 + BALL_RADIUS/2) + BALL_RADIUS + 5, 
    curr_dot_y*(BALL_RADIUS*2 + BALL_RADIUS/2) + BALL_RADIUS + 5, 
    event->x(), 
    event->y(), 
    curr_dot_color);
}

//sets a totally random dot color for a new dot
QColor DotsGameWidget::getDotColor(){
  int choose = rand() % 5;
  switch (choose) {
    case 0:
      return Qt::white;
    case 1:
      return Qt::darkRed;
    case 2:
      return Qt::darkBlue;
    case 3:
      return Qt::darkGreen;
    default:
      return Qt::darkYellow;
  }
}

//checks for adjacency, but not diagonally
bool DotsGameWidget::isAdjacent(int x1, int x2, int y1, int y2){
  int xdiff = abs(x1 - x2);
  int ydiff = abs(y1 - y2);
  if ((ydiff == 1 && xdiff == 0) || (xdiff == 1 && ydiff == 0)) return true;
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
  } else { //if (pos < 6*box_field)
    return 5;
  }
}