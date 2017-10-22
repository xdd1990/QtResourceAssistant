#include "QtResourceAssistant.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtResourceAssistant w;
	w.showLoginDialog();
	w.showWaitDialog();
	if (!w.isLoginSuccess())
		return 0;
	w.showMainDialog();
	return a.exec();
}
