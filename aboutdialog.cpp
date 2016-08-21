#include "aboutdialog.h"
#include <QPaintEvent>
#include <QPixmap>
#include <QRect>
#include <QPainter>
#include <QLabel>
#include <QVBoxLayout>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent)
{
    resize(400,300);
    QVBoxLayout *layout=new QVBoxLayout();
    setLayout(layout);

    QLabel *label=new QLabel("<h2>About DoctorMario<br></h2><p>Version 1.0</p><p>Copyright &copy; 2012 Chen. All rights reserved.</p><p>Special thanks to A3,LLL,Ony.</p>");
    layout->addWidget(label);
    this->setWindowTitle(tr("About DoctorMario"));
}

void AboutDialog::paintEvent(QPaintEvent *event)
{
    QRect rect=QRect(QPoint(0,0),QPoint(480,300));
    QPainter painter;
    QPixmap *pic=new QPixmap(":/mylogo.JPG");
    *pic=pic->scaled(rect.width(),rect.height(),Qt::KeepAspectRatio);
    painter.drawPixmap(0,0,*pic);

}
