#include "NodeDiscoverTest.h"
#include <QtWidgets/QApplication>
#include <QString>

//#pragma comment(lib, "qtpropertybrowser.lib")

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	NodeDiscoverTest w;
	w.show();
	return a.exec();
}
