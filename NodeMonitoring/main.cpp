#include "NodeMonitoring.h"
#include <QtWidgets/QApplication>
NodeMonitoring *g_w;
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	NodeMonitoring w;
	w.init();
	g_w = &w;
	w.show();

	return a.exec();
}
