#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include <QLineEdit>

class QLoginDialog : public QDialog
{
	Q_OBJECT

public:
	QLoginDialog(QWidget *parent = 0);
	~QLoginDialog();

	QString getAccount();
	QString getPassword();
signals:
	void loginSignal();

protected:
	void initUi();

	QLineEdit *mAccountEdit;
	QLineEdit *mPasswordEdit;
};
