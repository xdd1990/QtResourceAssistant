#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>

class QWaitDialog : public QDialog
{
	Q_OBJECT

public:
	QWaitDialog(QWidget *parent = 0);
	~QWaitDialog();

	void setText(QString strText);
protected:
	void paintEvent(QPaintEvent *Event);

private:
	QString mText;
};
