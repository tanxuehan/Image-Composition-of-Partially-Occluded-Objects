#include "QtPastePic.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtPastePic w;
	w.show();
	return a.exec();
}
