#include "QtResourceAssistant.h"
#include <QMessageBox>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QEventLoop>
#include <QFileDialog>

QtResourceAssistant::QtResourceAssistant(QWidget *parent)
	: QMainWindow(parent), mLoginSuccess(false)
{
	initUi();
	initMenu();
	initLoginParameter();
}

QtResourceAssistant::~QtResourceAssistant()
{

}

void QtResourceAssistant::initUi()
{
	setWindowTitle(tr("CSDN资源管理助手"));

	mCentralWidget = new QWidget(this);
	setCentralWidget(mCentralWidget);

	mDownloadInfoWidget = new QDownloadWidget(mCentralWidget);

	QHBoxLayout* HBoxLayout = new QHBoxLayout(mCentralWidget);
	HBoxLayout->addWidget(mDownloadInfoWidget);

	connect(&mLoginDialog, &QLoginDialog::loginSignal, this, &QtResourceAssistant::loginRequest);
	connect(mDownloadInfoWidget, &QDownloadWidget::loadLevelImageSignal, this, &QtResourceAssistant::loadLevelImageSlot);
	connect(mDownloadInfoWidget, &QDownloadWidget::loadPageSignal, this, &QtResourceAssistant::downloadInfoRequest);
	connect(mDownloadInfoWidget, &QDownloadWidget::downloadResource, this, &QtResourceAssistant::downloadResourceSlot);
	connect(mDownloadInfoWidget, &QDownloadWidget::deleteResource, this, &QtResourceAssistant::deleteResourceSlot);
}

void QtResourceAssistant::initMenu()
{
	QMenuBar* MenuBar = menuBar();
	if (!MenuBar)
		return;
	mUserInfoAction = MenuBar->addAction(tr("账户信息"));
	connect(mUserInfoAction, &QAction::triggered, this, [&] {
		mUserInfoDialog.exec();
	});

	mPayAction = MenuBar->addAction(tr("捐助"));
	connect(mPayAction, &QAction::triggered, this, [&] {
		mPayDialog.exec();
	});

	mAboutAction = MenuBar->addAction(tr("关于"));
	connect(mAboutAction, &QAction::triggered, this, [&] {
		mAboutDialog.exec();
	});
}

void QtResourceAssistant::showLoginDialog()
{
	mLoginDialog.exec();
}

void QtResourceAssistant::showMainDialog()
{
	this->show();
	mPayAction->trigger();
}

void QtResourceAssistant::initLoginParameter()
{
	mNetworkAccessManager = new QNetworkAccessManager(this);
	connect(mNetworkAccessManager, &QNetworkAccessManager::finished, this, &QtResourceAssistant::initLoginReply);
	mNetworkAccessManager->get(QNetworkRequest(QUrl("http://passport.csdn.net/account/login?from=http://my.csdn.net/my/mycsdn")));
}

void QtResourceAssistant::initLoginReply(QNetworkReply *Reply)
{
	if (Reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() != 200)
	{
		QMessageBox::warning(this, tr("警告"), tr("获取网页信息失败，请检查网络并重启软件"),QMessageBox::StandardButton::Close);
		return;
	}

	QString strReply = Reply->readAll();
	Reply->deleteLater();

	//正则匹配
	QRegExp rep("LT-[\\w-]{1,100}");//LT-[A-Za-z0-9-]{1,100}也可以匹配
	rep.indexIn(strReply);
	mStringLT = rep.cap(0);

	rep.setPattern("name=\"execution\" value=\"[\\w]{4,4}");
	rep.indexIn(strReply);
	mStringExecution = rep.cap(0).remove("name=\"execution\" value=\"");

	mCookies = Reply->rawHeader("Set-Cookie");

	disconnect(mNetworkAccessManager, &QNetworkAccessManager::finished, this, &QtResourceAssistant::initLoginReply);
}

void QtResourceAssistant::loginRequest()
{
	QString Account = mLoginDialog.getAccount();
	QString Password = mLoginDialog.getPassword();
	if (Account.isEmpty() || Password.isEmpty())
		return;
	
	mWaitDialog.setText("正在登录，请稍后...");

	connect(mNetworkAccessManager, &QNetworkAccessManager::finished, this, &QtResourceAssistant::loginReply);

	QNetworkRequest NetworkRequest(QUrl("http://passport.csdn.net/account/login?ref=toolbar"));
	NetworkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	NetworkRequest.setRawHeader(QByteArray("Referer"), QByteArray("http://download.csdn.net/?ref=toolbar"));
	NetworkRequest.setRawHeader(QByteArray("Cookie"), mCookies.toLatin1());

	QString strPost = "username=" + Account + "&password=" + Password + "&lt=" + mStringLT + "&execution=" + mStringExecution + "&_eventId=submit";
	mNetworkAccessManager->post(NetworkRequest, strPost.toLatin1());
}

void QtResourceAssistant::loginReply(QNetworkReply *Reply)
{
	mWaitDialog.hide();

	QString strReply = Reply->readAll();
	Reply->deleteLater();

	QRegExp rep("var data = \\{.+(\"\\})");
	rep.indexIn(strReply);

	QString strJson = rep.cap(0);
	if (strJson.isEmpty())
	{
		QMessageBox::warning(this, tr("警告"), tr("登录失败，请检查网络并重启软件"), QMessageBox::StandardButton::Close);
		return;
	}
	strJson = strJson.remove("var data = {").remove("}");
	mUserInfoDialog.setUserInfo(strJson);

	mCookies = Reply->rawHeader("Set-Cookie");

	mLoginSuccess = true;

	disconnect(mNetworkAccessManager, &QNetworkAccessManager::finished, this, &QtResourceAssistant::loginReply);	
	
	downloadInfoRequest(1);
}

void QtResourceAssistant::downloadInfoRequest(int Page)
{
	connect(mNetworkAccessManager, &QNetworkAccessManager::finished, this, &QtResourceAssistant::downloadInfoReply);

	QNetworkRequest NetworkRequest(QUrl("http://download.csdn.net/my/uploads/" + QString::number(Page)));
	NetworkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	NetworkRequest.setRawHeader(QByteArray("Referer"), QByteArray("http://download.csdn.net/"));
	NetworkRequest.setRawHeader(QByteArray("Cookie"), mCookies.toLatin1());

	mNetworkAccessManager->get(NetworkRequest);
}

QPixmap QtResourceAssistant::loadInternetImage(QString strUrl)
{
	QEventLoop EventLoop;
	connect(mNetworkAccessManager, &QNetworkAccessManager::finished, &EventLoop, &QEventLoop::quit);

	QUrl Url = QUrl(strUrl);
	QNetworkRequest NetworkRequest(Url);
	//NetworkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	//NetworkRequest.setRawHeader(QByteArray("Cookie"), mCookies.toLatin1());
	QNetworkReply *Reply = mNetworkAccessManager->get(NetworkRequest);
	EventLoop.exec();

	QByteArray ImageData = Reply->readAll();
	//QString data = QString::fromStdString(ImageData.toStdString());
	QPixmap Pixmap;
	Pixmap.loadFromData(ImageData);
	return Pixmap;
}

void QtResourceAssistant::loadLevelImageSlot(QString strImage)
{
	mDownloadInfoWidget->setLevelImage(loadInternetImage(strImage));
}

void QtResourceAssistant::downloadInfoReply(QNetworkReply *Reply)
{
	disconnect(mNetworkAccessManager, &QNetworkAccessManager::finished, this, &QtResourceAssistant::downloadInfoReply);

	QString strReply = Reply->readAll();
	Reply->deleteLater();
	if (strReply.isEmpty())
	{
		QMessageBox::warning(this, tr("警告"), tr("获取下载信息失败，请检查网络并重启软件"), QMessageBox::StandardButton::Close);
		return;
	}

	//mDownloadInfoWidget->setAvatarImage(loadInternetImage(mUserInfoDialog.getAvatar()));
	mDownloadInfoWidget->setNickName(mUserInfoDialog.getNickName());
	mDownloadInfoWidget->parseDownloadInfo(strReply);
}

bool QtResourceAssistant::isLoginSuccess()
{
	return mLoginSuccess;
}

void QtResourceAssistant::showWaitDialog()
{
	mWaitDialog.exec();
}

void QtResourceAssistant::downloadResourceSlot(QString strUrl)
{
	QString Directory = QFileDialog::getExistingDirectory(this, tr("目录"));
	if (Directory.isEmpty())
		return;
	QString FilePath = Directory + "/";
	mFile.setFileName(FilePath);
	if (!mFile.open(QIODevice::WriteOnly))
		return;
	mWaitDialog.setText(tr("正在下载..."));

	mFileReply = mNetworkAccessManager->get(QNetworkRequest(QUrl(strUrl)));
	connect(mFileReply, &QNetworkReply::readyRead, this, &QtResourceAssistant::readyReadSlot);
	connect(mFileReply, &QNetworkReply::finished, this, &QtResourceAssistant::downloadFileFinished);
}

void QtResourceAssistant::readyReadSlot()
{
	mFile.write(mFileReply->readAll());
}

void QtResourceAssistant::downloadFileFinished()
{
	mFile.flush();
	mFile.close();
	mFileReply->deleteLater();
}

void QtResourceAssistant::deleteResourceSlot(QString strUrl)
{
	QMessageBox::StandardButton Button = (QMessageBox::StandardButton)QMessageBox::question(this, tr("删除"), tr("确定要删除吗？"), QMessageBox::StandardButton::Yes ,QMessageBox::StandardButton::No);
	if (Button == QMessageBox::StandardButton::No)
		return;
	QEventLoop EventLoop;
	connect(mNetworkAccessManager, &QNetworkAccessManager::finished, &EventLoop, &QEventLoop::quit);

	strUrl = strUrl.right(strUrl.length() - strUrl.lastIndexOf("/") - 1);
	strUrl = "http://download.csdn.net/index.php/user_console/del_my_source/" + strUrl;

	QUrl Url = QUrl(strUrl);
	QNetworkRequest NetworkRequest(Url);
	QNetworkReply *Reply = mNetworkAccessManager->get(NetworkRequest);
	EventLoop.exec();

	QString strReply = Reply->readAll();
	strReply.remove("{\"succ\":");
	if (strReply.isEmpty())
		return;

	QRegExp rep("\\d");
	rep.indexIn(strReply);
	strReply = rep.cap();
	int bSuccess = strReply.toInt();
	if (bSuccess)
		QMessageBox::information(this, tr("删除"), tr("删除成功！"), QMessageBox::StandardButton::Close);
	else
		QMessageBox::information(this, tr("删除"), tr("删除失败！"), QMessageBox::StandardButton::Close);
}