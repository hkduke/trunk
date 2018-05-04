#include "qtenvtest.h"
#include <QApplication>
#include<QTextCodec>
#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif  
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtEnvTest w;
	w.show();
	return a.exec();
}
