/* File: dots_game_widget.h
*/

#ifndef DOTS_GAME_WIDGET_H_
#define DOTS_GAME_WIDGET_H_

#include <QtGui>

using namespace std;

//LinkedList style class to draw lines
class Line {
public:
  // These indexes are used to know which dot the line comes from
  // They are not to be used for drawing.
  int startXIndex;
  int startYIndex;
  // These following values are to be used for drawing.
  int start_X;
  int start_Y;
  int end_X;
  int end_Y;
  Line* next;
  QColor color;

  Line(int xIndex, int yIndex, int x, int y, int x2, int y2, QColor qcolor){
    startXIndex = xIndex;
    startYIndex = yIndex;
    start_X = x;
    start_Y = y;
    end_X = x2;
    end_Y = y2;
    next = NULL;
    color = qcolor;
  }

  void setEndPoint(int x, int y){
    end_X = x;
    end_Y = y;
  }

  void setNext(Line* nextLine){
    next = nextLine;
  }
};

class DotsGameWidget : public QWidget
{
  Q_OBJECT

 public:
  DotsGameWidget(QWidget* parent);

  void reset();
  void setPaused(bool p);

 signals:
  void needsScoreIncrease(int value);

 protected:
  void paintEvent(QPaintEvent* event);
  void mousePressEvent(QMouseEvent* event);
  void mouseReleaseEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);

 private:
  bool isPaused;
  QColor getDotColor();
  int returnIndexOfDot(int pos);
  bool isAdjacent(int x1, int x2, int y1, int y2);
  void selectDot(int x, int y, QMouseEvent *event);
  //these are the indices in the array of the current dot.
  int curr_dot_x, curr_dot_y;
  //track color for selection purposes
  QColor curr_dot_color;
  static const int WIDTH = 375;
  static const int HEIGHT = 375;
  static const int NUM_DOTS_HORIZONTAL = 6;
  static const int NUM_DOTS_VERTICAL = 6;
  Line* line;
  int numSelected;
  bool hasSquare;
  int squareXIndex;
  int squareYIndex;

  struct Dot 
  { 
    int x;
    int y;
    QColor color;
    bool selected;
  } dot_board[6][6]; 
  static const int BALL_RADIUS = 25;
};

#endif
