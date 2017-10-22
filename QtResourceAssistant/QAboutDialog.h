#pragma once
#pragma execution_character_set("utf-8")
#include <QDialog>

class QAboutDialog : public QDialog
{
	Q_OBJECT

public:
	QAboutDialog(QWidget *parent = 0);
	~QAboutDialog();
};
