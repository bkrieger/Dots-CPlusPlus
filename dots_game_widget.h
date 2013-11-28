/* File: dots_game_widget.h
*/

#ifndef DOTS_GAME_WIDGET_H_
#define DOTS_GAME_WIDGET_H_

#include <QtGui>

using namespace std;

//LinkedList style class to draw lines
class Line {
public:
  int start_X;
  int start_Y;
  int end_X;
  int end_Y;
  Line* next;
  QColor color;

  Line(int x, int y, int x2, int y2, QColor qcolor){
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
  //these are the indices in the array of the current dot.
  int currentDotX, currentDotY;
  //track color for selection purposes
  QColor currentDotColor;
  static const int WIDTH = 375;
  static const int HEIGHT = 375;
  Line* line;
  struct dot 
  { 
    int x;
    int y;
    QColor color;
    bool selected;
  } dot_board[6][6]; 
  static const int BALL_RADIUS = 25;
};

#endif
