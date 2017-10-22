#include "QWaitDialog.h"
#include <QPainter>

QWaitDialog::QWaitDialog(QWidget *parent)
	: QDialog(parent)
{
	this->resize(150, 50);
	this->setWindowTitle(tr("µÈ´ý"));
}

QWaitDialog::~QWaitDialog()
{

}

void QWaitDialog::setText(QString strText)
{
	mText = strText;
}

void QWaitDialog::paintEvent(QPaintEvent *Event)
{
	QDialog::paintEvent(Event);
	QPainter Painter(this);
	Painter.drawText(20, 20, mText);
}
