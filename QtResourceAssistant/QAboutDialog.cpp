#include "QAboutDialog.h"
#include <QLabel>
#include <QHBoxLayout>

QAboutDialog::QAboutDialog(QWidget *parent)
	: QDialog(parent)
{
	setWindowTitle(tr("关于"));

	QLabel *AboutLabel = new QLabel(this);
	AboutLabel->setText(tr("本软件用于学习和交流,版权属于作者,请不要用于商业用途。\n如果有问题,请加QQ：1245178753交流。\n软件只实现了自己上传资源的显示和删除,其他几个页面的功能以及下载并没有实现。\n下载的有点麻烦,没有仔细研究。"));

	QHBoxLayout *HBoxLayout = new QHBoxLayout(this);
	HBoxLayout->addWidget(AboutLabel);
}

QAboutDialog::~QAboutDialog()
{

}
