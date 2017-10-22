#include "QDownloadWidget.h"
#include <QGridLayout>
#include "QResourceItemWidget.h"

QDownloadWidget::QDownloadWidget(QWidget *parent)
	: QWidget(parent)
{
	initUi();
}

QDownloadWidget::~QDownloadWidget()
{

}

void QDownloadWidget::initUi()
{
	//mAvatarLabel = new QLabel(this);
	mNickNameLabel = new QLabel(this);
	mDownloadSizeLabel = new QLabel(this);
	mDownloadLevel = new QLabel(this);
	mDownloadPointsLabel = new QLabel(this);
	mRankLabel = new QLabel(this);
	mDownloadResourceLabel = new QLabel(this);
	mUploadResourceLabel = new QLabel(this);
	mCreateAlbumLabel = new QLabel(this);

	//mAvatarLabel->setText(tr("头像：\n403\nForbidden"));
	mDownloadPointsLabel->setAlignment(Qt::AlignCenter);
	mRankLabel->setAlignment(Qt::AlignCenter);
	mDownloadResourceLabel->setAlignment(Qt::AlignCenter);
	mUploadResourceLabel->setAlignment(Qt::AlignCenter);
	mCreateAlbumLabel->setAlignment(Qt::AlignCenter);

	mTabWidget = new QTabWidget(this);
	mTabWidget->setMinimumSize(QSize(860, 640));

	mUploadResourceWidget = new QListWidget(mTabWidget);
	mDownloadResourceWidget = new QListWidget(mTabWidget);
	mStoreResourceWidget = new QListWidget(mTabWidget);
	mDownloadScoreTable = new QTableWidget(mTabWidget);

	mTabWidget->addTab(mUploadResourceWidget, tr("上传资源"));
	mTabWidget->addTab(mDownloadResourceWidget, tr("下载资源"));
	mTabWidget->addTab(mStoreResourceWidget, tr("我的收藏"));
	mTabWidget->addTab(mDownloadScoreTable, tr("积分明细"));

	mFirstPageButton = new QPushButton(this);
	mNextPageButton = new QPushButton(this);
	mPreviousPageButton = new QPushButton(this);

	mFirstPageButton->setText(tr("首页"));
	mNextPageButton->setText(tr("下一页"));
	mPreviousPageButton->setText(tr("上一页"));

	QGridLayout *GridLayout = new QGridLayout(this);
	//GridLayout->addWidget(mAvatarLabel, 0, 0, 3, 3);
	GridLayout->addWidget(mNickNameLabel, 0, 0, 1, 3);
	GridLayout->addWidget(mDownloadLevel, 1, 0, 1, 3);
	GridLayout->addWidget(mDownloadSizeLabel, 2, 0, 1, 3);
	GridLayout->addWidget(mDownloadPointsLabel, 0, 3, 3, 2);
	GridLayout->addWidget(mRankLabel, 0, 5, 3, 2);
	GridLayout->addWidget(mDownloadResourceLabel, 0, 7, 3, 2);
	GridLayout->addWidget(mUploadResourceLabel, 0, 9, 3, 2);
	GridLayout->addWidget(mCreateAlbumLabel, 0, 11, 3, 2);
	GridLayout->addWidget(mTabWidget, 3, 0, 20, 26);
	GridLayout->addWidget(mFirstPageButton, 23, 11, 1, 1);
	GridLayout->addWidget(mNextPageButton, 23, 12, 1, 1);
	GridLayout->addWidget(mPreviousPageButton, 23, 13, 1, 1);

	connect(mFirstPageButton, &QPushButton::clicked, this, [&] {
		mCurrentPage = 1;
		emit loadPageSignal(mCurrentPage);
	});
	connect(mNextPageButton, &QPushButton::clicked, this, [&] {
		mCurrentPage += 1;
		emit loadPageSignal(mCurrentPage);
	});
	connect(mPreviousPageButton, &QPushButton::clicked, this, [&] {
		mCurrentPage -= 1;
		if (mCurrentPage == 0)
			mCurrentPage = 1;
		emit loadPageSignal(mCurrentPage);
	});
}

void QDownloadWidget::setAvatarImage(const QPixmap& image)
{
	//mAvatarLabel->setPixmap(image);
}

void QDownloadWidget::setLevelImage(const QPixmap& image)
{
	mDownloadLevel->setPixmap(image);
}

void QDownloadWidget::setNickName(QString strNick)
{
	mNickNameLabel->setText(strNick.remove("\""));
}

void QDownloadWidget::parseDownloadInfo(QString strInfo)
{
	if (strInfo.isEmpty())
		return;
	QRegExp rep("http://c.csdnimg.cn/jifen/images/xunzhang/jianzhang/(\\w+).png");
	rep.indexIn(strInfo);

	QString TempString = rep.cap();
	emit loadLevelImageSignal(TempString);

	rep.setPattern("</label>(.|\n)+MB");
	rep.indexIn(strInfo);
	TempString = rep.cap().remove("</label>").remove("\n").remove(" ");
	mDownloadSizeLabel->setText(tr(QString("上传权限：" + TempString).toStdString().c_str()));

	rep.setPattern("积分</label><span>(\\d+)");
	rep.indexIn(strInfo);
	TempString = rep.cap().remove("积分</label><span>");
	mDownloadPointsLabel->setText("<h6>积分</h6><h4><font color=orange>"+TempString+"</font></h4>");

	rep.setPattern("总排名</label><span>(\\d+)");
	rep.indexIn(strInfo);
	TempString = rep.cap().remove("总排名</label><span>");
	mRankLabel->setText("<h6>总排名</h6><h4><font color=\"orange\">" + TempString + "</font></h4>");

	rep.setPattern("上传资源</label><span>(\\d+)");
	rep.indexIn(strInfo);
	TempString = rep.cap().remove("上传资源</label><span>");
	mDownloadResourceLabel->setText("<h6>上传资源</h6><h4><font color=\"orange\">" + TempString + "</font></h4>");

	rep.setPattern("下载资源</label><span>(\\d+)");
	rep.indexIn(strInfo);
	TempString = rep.cap().remove("下载资源</label><span>");
	mUploadResourceLabel->setText("<h6>下载资源</h6><h4><font color=\"orange\">" + TempString + "</font></h4>");

	rep.setPattern("创建专辑</label><span>(\\d+)");
	rep.indexIn(strInfo);
	TempString = rep.cap().remove("创建专辑</label><span>");
	mCreateAlbumLabel->setText("<h6>创建专辑</h6><h4><font color=\"orange\">" + TempString + "</font></h4>");

	parseUploadResources(strInfo);
}

void QDownloadWidget::parseUploadResources(QString strInfo)
{
	if (strInfo.isEmpty())
		return;
	mUploadResourceWidget->clear();
	//每页5个
	for (int i = 0; i < 5; i++)
	{
		QRegExp rep("/download/(\\w+/\\w+)");
		rep.indexIn(strInfo);
		QString TempString = rep.cap();
		if (TempString.isEmpty())
			break;
		QListWidgetItem *Item = new QListWidgetItem(mUploadResourceWidget);
		QResourceItemWidget *ItemWidget = new QResourceItemWidget(mUploadResourceWidget);
		
		Item->setSizeHint(QSize(840, 120));

		connect(ItemWidget, &QResourceItemWidget::downloadResource, this, &QDownloadWidget::downloadResource);
		connect(ItemWidget, &QResourceItemWidget::deleteResource, this, &QDownloadWidget::deleteResource);

		mUploadResourceWidget->addItem(Item);
		mUploadResourceWidget->setItemWidget(Item, ItemWidget);

		ItemWidget->setResourceUrl(TempString);

		rep.setPattern("(.+)" + TempString + "\">");
		rep.indexIn(strInfo);
		TempString = rep.cap();
		strInfo.remove(TempString);

		TempString = strInfo.left(strInfo.indexOf("</a>"));
		ItemWidget->setResourceName("<h2>" + TempString + "</h2>");

		TempString = strInfo.left(strInfo.indexOf("brief\">"));
		strInfo.remove(TempString + "brief\">");

		TempString = strInfo.left(strInfo.indexOf("</p>")).remove("\n");
		ItemWidget->setDescription(TempString.left(45) + "...");

		//标签最多5个
		TempString = strInfo.left(strInfo.indexOf("下载个数：</label>")) + "下载个数：</label>";
		strInfo.remove(TempString);
		TempString = parseTags(TempString);
		ItemWidget->setTags(TempString);

		rep.setPattern("\\d+");
		rep.indexIn(strInfo);
		TempString = rep.cap();
		ItemWidget->setDownloadTime("下载个数：" + TempString);

		TempString = strInfo.left(strInfo.indexOf("上传时间：</label>")) + "上传时间：</label>";
		strInfo.remove(0, TempString.length());
		rep.setPattern("(\\d|-)+");
		rep.indexIn(strInfo);
		TempString = rep.cap();
		ItemWidget->setUploadTime("上传时间：" + TempString);

		TempString = strInfo.left(strInfo.indexOf("所需积分/C币：</label>")) + "所需积分/C币：</label>";
		strInfo.remove(0, TempString.length());
		rep.setPattern("\\d+");
		rep.indexIn(strInfo);
		TempString = rep.cap();
		ItemWidget->setNeedScore("所需积分：" + TempString);
	}
}

QString QDownloadWidget::parseTags(QString strInfo)
{
	QString TempTags = "";
	for (int i = 0; i < 5; i++)
	{
		QString TempString = strInfo.left(strInfo.indexOf("/tag/"));
		strInfo.remove(TempString);
		if (strInfo.isEmpty())
			break;
		TempString = strInfo.left(strInfo.indexOf(">"));
		strInfo.remove(TempString + ">");

		TempString = strInfo.left(strInfo.indexOf("</a>"));
		TempTags.append("<" + TempString + ">");
	}
	return TempTags;
}