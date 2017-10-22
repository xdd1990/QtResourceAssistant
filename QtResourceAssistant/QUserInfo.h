#pragma once
#pragma execution_character_set("utf-8")

#include <QDialog>
#include <QLabel>
#include <QLineEdit>

class QUserInfo : public QDialog
{
	Q_OBJECT

public:
	QUserInfo(QWidget *parent = 0);
	~QUserInfo();

	void setUserInfo(QString strInfo);
	QString getAvatar();
	QString getNickName();
private:
	QLabel *mUserIdLabel;
	QLineEdit *mUserIdEdit;

	QLabel *mMobileLabel;
	QLineEdit *mMobileEdit;

	QLabel *mUserNameLabel;
	QLineEdit *mUserNameEdit;

	QLabel *mEmailLabel;
	QLineEdit *mEmailEdit;

	QLabel *mPasswordLabel;
	QLineEdit *mPasswordEdit;

	QLabel *mRegisterIPLabel;
	QLineEdit *mRegisterIPEdit;

	QLabel *mRegisterTimeLabel;
	QLineEdit *mRegisterTimeEdit;

	QLabel *mLastLoginIPLabel;
	QLineEdit *mLastLoginIPEdit;

	QLabel *mLastLoginTimeLabel;
	QLineEdit *mLastLoginTimeEdit;

	QLabel *mLoginTimesLabel;
	QLineEdit *mLoginTimesEdit;

	QLabel *mNickNameLabel;
	QLineEdit *mNickNameEdit;

	QLabel *mAvatarLabel;
	QLineEdit *mAvatarEdit;
};
