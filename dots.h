/* File: dots.h
*/

#ifndef DOTS_H_
#define DOTS_H_

#include <QtGui>

class DotsCanvas;

// The Dots class manages the window, which is just a container for the
// DotsCanvas (where all the game logic lives) and the one control button.
class Dots : public QWidget
{
  Q_OBJECT

 public:
  Dots();

 private:
  DotsCanvas* canvas;
};

#endif
