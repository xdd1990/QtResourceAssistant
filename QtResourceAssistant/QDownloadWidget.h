#pragma once
#pragma execution_character_set("utf-8")

#include <QWidget>
#include <QLabel>
#include <QTabWidget>
#include <QTableWidget>
#include <QListWidget>
#include <QPushButton>

class QDownloadWidget : public QWidget
{
	Q_OBJECT

public:
	QDownloadWidget(QWidget *parent);
	~QDownloadWidget();

	void setAvatarImage(const QPixmap& image);
	void setLevelImage(const QPixmap& image);
	void setNickName(QString strNick);
	void parseDownloadInfo(QString strInfo);
protected:
	void initUi();
	void parseUploadResources(QString strInfo);
	QString parseTags(QString strInfo);

signals:
	void loadLevelImageSignal(QString strImage);
	void loadPageSignal(int PageNumber);
	void downloadResource(QString strUrl);
	void deleteResource(QString strUrl);

private:
	//QLabel *mAvatarLabel;
	QLabel *mNickNameLabel;
	QLabel *mDownloadSizeLabel;
	QLabel *mDownloadLevel;

	QLabel *mDownloadPointsLabel;
	QLabel *mRankLabel;
	QLabel *mDownloadResourceLabel;
	QLabel *mUploadResourceLabel;
	QLabel *mCreateAlbumLabel;

	QTabWidget *mTabWidget;
	QListWidget *mUploadResourceWidget;
	QListWidget *mDownloadResourceWidget;
	QListWidget *mStoreResourceWidget;
	QTableWidget *mDownloadScoreTable;

	int mCurrentPage = 1;
	QPushButton *mFirstPageButton;
	QPushButton *mNextPageButton;
	QPushButton *mPreviousPageButton;
};
