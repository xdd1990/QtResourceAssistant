#include "QAlipayDialog.h"
#include <QLabel>
#include <QGridLayout>

QAlipayDialog::QAlipayDialog(QWidget *parent)
	: QDialog(parent)
{
	setWindowTitle(tr("收钱码"));

	QLabel *TextLabel = new QLabel(this);
	QLabel *AlipayLabel = new QLabel(this);
	QLabel *WeChatLabel = new QLabel(this);

	TextLabel->setText(tr("如果此程序对你有所帮助,请慷慨解囊："));
	AlipayLabel->setPixmap(QPixmap(":/QtResourceAssistant/Resources/alipay.jpg").scaled(200, 300));
	WeChatLabel->setPixmap(QPixmap(":/QtResourceAssistant/Resources/wechat.png").scaled(200, 300));

	QGridLayout *GridLayput = new QGridLayout(this);
	GridLayput->addWidget(TextLabel, 0, 0, 1, 4);
	GridLayput->addWidget(AlipayLabel, 1, 0, 1, 2);
	GridLayput->addWidget(WeChatLabel, 1, 2, 1, 2);
}

QAlipayDialog::~QAlipayDialog()
{

}
