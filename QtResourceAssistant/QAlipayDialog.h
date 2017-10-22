#pragma once
#pragma execution_character_set("utf-8")
#include <QDialog>

class QAlipayDialog : public QDialog
{
	Q_OBJECT

public:
	QAlipayDialog(QWidget *parent = 0);
	~QAlipayDialog();
};
