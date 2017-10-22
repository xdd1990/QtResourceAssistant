#pragma once
#pragma execution_character_set("utf-8")

#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QtSvg/QSvgWidget> 

class QResourceItemWidget : public QWidget
{
	Q_OBJECT

public:
	QResourceItemWidget(QWidget *parent);
	~QResourceItemWidget();

	void setResourceUrl(QString strUrl);
	QString getResourceUrl();

	void setResourceName(QString strName);
	QString getResourceName();

	void setDescription(QString strDescription);
	QString getDescription();

	void setTags(QString strTags);
	QString getTags();

	void setDownloadTime(QString strTime);
	QString getDownloadTime();

	void setUploadTime(QString strTime);
	QString getUploadTime();

	void setNeedScore(QString strScore);
	QString getNeedScore();

signals:
	void downloadResource(QString strUrl);
	void deleteResource(QString strUrl);

private:
	void initUI();

	QString mResourceURL;

	QSvgWidget *mPreviewWidget;
	QLabel *mFileNameLabel;
	QLabel *mDescriptionLabel;
	QLabel *mTagLabel;
	QLabel *mDownloadTimeLabel;
	QLabel *mUploadTimeLabel;
	QLabel *mNeedScoreLabel;
	QPushButton *mDownloadResourceButton;
	QPushButton *mDeleteResourceButton;
};
