/* File: dots.cpp
*/

#include <QtGui>
#include "dots.h"
#include "dots_canvas.h"

Dots::Dots()
{
  setWindowTitle("Dots");

  QVBoxLayout* layout = new QVBoxLayout(this);
  canvas = new DotsCanvas(this);
  layout->addWidget(canvas);

}
