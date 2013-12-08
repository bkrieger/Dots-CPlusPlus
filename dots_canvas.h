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
  void selectPlayWithTime();
  void selectPlayWithMoves();
  void back();
  void reset();
  void pause();

 private:
  void startGame();
  void decrementTimeOrMoves();
  bool playingTimedGame;
  bool isPaused;
  int score;

  QTimer* timer;
  int timeOrMovesLeft;

  QGridLayout* layout;
  DotsGameWidget* gameWidget;
  QPushButton* playWithTimeButton;
  QPushButton* playWithMovesButton;
  QPushButton* backButton;
  QPushButton* pauseButton;
  QPushButton* resetButton;
  QLabel* scoreLabel;
  QLabel* timeOrMovesLabel;

  static const int WIDTH = 400;
  static const int HEIGHT = 600;

};

#endif
