#include "QUserInfo.h"
#include <QGridLayout>

#define NEWITEM(ItemName,x,y,z,t) m##ItemName##Label = new QLabel(this);\
						  m##ItemName##Edit = new QLineEdit(this);\
						  m##ItemName##Label->setText(QString(#ItemName##":"));\
						  m##ItemName##Edit->setReadOnly(true);\
						  GridLayout->addWidget(m##ItemName##Label,x,y,z,t);\
					      GridLayout->addWidget(m##ItemName##Edit,x,y+1,z,t+2);

QUserInfo::QUserInfo(QWidget *parent)
	: QDialog(parent)
{
	QGridLayout *GridLayout = new QGridLayout(this);

	NEWITEM(UserId, 0, 0, 1, 1);
	NEWITEM(Mobile, 1, 0, 1, 1);
	NEWITEM(UserName, 2, 0, 1, 1);
	NEWITEM(Email, 3, 0, 1, 1);
	NEWITEM(Password, 4, 0, 1, 1);
	NEWITEM(RegisterIP, 5, 0, 1, 1);
	NEWITEM(RegisterTime, 6, 0, 1, 1);
	NEWITEM(LastLoginIP, 7, 0, 1, 1);
	NEWITEM(LastLoginTime, 8, 0, 1, 1);
	NEWITEM(LoginTimes, 9, 0, 1, 1);
	NEWITEM(NickName, 10, 0, 1, 1);
	NEWITEM(Avatar, 11, 0, 1, 1);
}

QUserInfo::~QUserInfo()
{

}

void QUserInfo::setUserInfo(QString strInfo)
{
	QStringList StringList = strInfo.split(",\"");
	for each (QString String in StringList)
	{
		QStringList TempStringList = String.split("\":");
		if (TempStringList.size() != 2)
			continue;
		if (TempStringList[0].contains("userId"))
			mUserIdEdit->setText(TempStringList[1]);
		else if (TempStringList[0] == "mobile")
			mMobileEdit->setText(TempStringList[1]);
		else if (TempStringList[0] == "userName")
			mUserNameEdit->setText(TempStringList[1]);
		else if (TempStringList[0] == "email")
			mEmailEdit->setText(TempStringList[1]);
		else if (TempStringList[0] == "password")
			mPasswordEdit->setText(TempStringList[1]);
		else if (TempStringList[0] == "registerIP")
			mRegisterIPEdit->setText(TempStringList[1]);
		else if (TempStringList[0] == "registerTime")
			mRegisterTimeEdit->setText(TempStringList[1]);
		else if (TempStringList[0] == "lastLoginIP")
			mLastLoginIPEdit->setText(TempStringList[1]);
		else if (TempStringList[0] == "lastLoginTime")
			mLastLoginTimeEdit->setText(TempStringList[1]);
		else if (TempStringList[0] == "loginTimes")
			mLoginTimesEdit->setText(TempStringList[1]);
		else if (TempStringList[0] == "nickName")
			mNickNameEdit->setText(TempStringList[1]);
		else if (TempStringList[0] == "avatar")
			mAvatarEdit->setText(TempStringList[1]);
	}
}

QString QUserInfo::getAvatar()
{
	return mAvatarEdit->text();
}

QString QUserInfo::getNickName()
{
	return mNickNameEdit->text();
}