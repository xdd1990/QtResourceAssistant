#include "QResourceItemWidget.h"
#include <QGridLayout>
#include <QtSvg/QSvgRenderer>

QResourceItemWidget::QResourceItemWidget(QWidget *parent)
	: QWidget(parent)
{
	initUI();
}

QResourceItemWidget::~QResourceItemWidget()
{

}

void QResourceItemWidget::initUI()
{
	mPreviewWidget = new QSvgWidget(this);
	mFileNameLabel = new QLabel(this);
	mDescriptionLabel = new QLabel(this);
	mTagLabel = new QLabel(this);
	mDownloadTimeLabel = new QLabel(this);
	mUploadTimeLabel = new QLabel(this);
	mNeedScoreLabel = new QLabel(this);

	mDeleteResourceButton = new QPushButton(this);
	mDownloadResourceButton = new QPushButton(this);
	mDownloadResourceButton->setText(tr("ÏÂÔØ"));
	mDeleteResourceButton->setText(tr("É¾³ý"));

	QGridLayout *GridLayout = new QGridLayout(this);
	GridLayout->addWidget(mPreviewWidget, 0, 0, 4, 1);
	GridLayout->addWidget(mFileNameLabel, 0, 1, 1, 6);
	GridLayout->addWidget(mDescriptionLabel, 1, 1, 1, 6);
	GridLayout->addWidget(mTagLabel, 2, 1, 1, 6);
	GridLayout->addWidget(mDownloadTimeLabel, 3, 1, 1, 2);
	GridLayout->addWidget(mUploadTimeLabel, 3, 3, 1, 2);
	GridLayout->addWidget(mNeedScoreLabel, 3, 5, 1, 2);
	GridLayout->addWidget(mDownloadResourceButton, 0, 7, 1, 1);
	GridLayout->addWidget(mDeleteResourceButton, 1, 7, 1, 1);

	mPreviewWidget->load(QString(":/QtResourceAssistant/Resources/zip.svg"));
	mPreviewWidget->resize(mPreviewWidget->renderer()->defaultSize());

	connect(mDownloadResourceButton, &QPushButton::clicked, this, [&] {
		emit downloadResource(mResourceURL);
	});
	connect(mDeleteResourceButton, &QPushButton::clicked, this, [&] {
		emit deleteResource(mResourceURL);
	});
}

void QResourceItemWidget::setResourceUrl(QString strUrl)
{
	mResourceURL = "http://download.csdn.net" + strUrl;
}

QString QResourceItemWidget::getResourceUrl()
{
	return mResourceURL;
}

void QResourceItemWidget::setResourceName(QString strName)
{
	mFileNameLabel->setText(strName);
}

QString QResourceItemWidget::getResourceName()
{
	return mFileNameLabel->text();
}

void QResourceItemWidget::setDescription(QString strDescription)
{
	mDescriptionLabel->setText(strDescription);
}

QString QResourceItemWidget::getDescription()
{
	return mDescriptionLabel->text();
}

void QResourceItemWidget::setTags(QString strTags)
{
	mTagLabel->setText(strTags);
}

QString QResourceItemWidget::getTags()
{
	return mTagLabel->text();
}

void QResourceItemWidget::setDownloadTime(QString strTime)
{
	mDownloadTimeLabel->setText(strTime);
}

QString QResourceItemWidget::getDownloadTime()
{
	return mDownloadTimeLabel->text();
}

void QResourceItemWidget::setUploadTime(QString strTime)
{
	mUploadTimeLabel->setText(strTime);
}

QString QResourceItemWidget::getUploadTime()
{
	return mUploadTimeLabel->text();
}

void QResourceItemWidget::setNeedScore(QString strScore)
{
	mNeedScoreLabel->setText(strScore);
}

QString QResourceItemWidget::getNeedScore()
{
	return mNeedScoreLabel->text();
}