/* File: main.cpp
*/

#include <QtGui>
#include "dots.h"

int main(int argc, char** argv) {
	QApplication app(argc, argv);

	Dots dots;
	dots.show();

	return app.exec();
}
