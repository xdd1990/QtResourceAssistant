#pragma once

#include <QtWidgets/QMainWindow>
#include "QLoginDialog.h"
#include "QWaitDialog.h"
#include "QUserInfo.h"
#include "QDownloadWidget.h"
#include "QAlipayDialog.h"
#include "QAboutDialog.h"
#include <QAction>
#include <QFile>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

class QtResourceAssistant : public QMainWindow
{
	Q_OBJECT

public:
	QtResourceAssistant(QWidget *parent = Q_NULLPTR);
	~QtResourceAssistant();

	void showLoginDialog();
	void showWaitDialog();
	bool isLoginSuccess();
	void showMainDialog();
protected:
	void initUi();
	void initMenu();
	void initLoginParameter();

	void loginRequest();
	void downloadInfoRequest(int Page);
	void loadLevelImageSlot(QString strImage);
	void downloadResourceSlot(QString strUrl);
	void deleteResourceSlot(QString strUrl);
	QPixmap loadInternetImage(QString strUrl);
	void initLoginReply(QNetworkReply *Reply);
	void loginReply(QNetworkReply *Reply);
	void downloadInfoReply(QNetworkReply *Reply);

	void readyReadSlot();
	void downloadFileFinished();
private:
	QWidget *mCentralWidget;

	bool mLoginSuccess;
	QString mStringLT;
	QString mStringExecution;
	QString mCookies;
	QLoginDialog mLoginDialog;
	QWaitDialog  mWaitDialog;
	QUserInfo    mUserInfoDialog;
	QAlipayDialog mPayDialog;
	QAboutDialog  mAboutDialog;
	QDownloadWidget*mDownloadInfoWidget;
	QNetworkAccessManager *mNetworkAccessManager;

	QAction *mUserInfoAction;
	QAction *mPayAction;
	QAction *mAboutAction;

	QFile mFile;
	QNetworkReply *mFileReply;
};
