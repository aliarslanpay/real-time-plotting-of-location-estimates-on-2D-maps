#include "graphinfo.h"
#include "ui_graphinfo.h"
#include <QMouseEvent>

QPoint mpos;

GraphInfo::GraphInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphInfo)
{
    ui->setupUi(this);

}

GraphInfo::~GraphInfo()
{
    delete ui;
}

void GraphInfo::output(QString s, int a, double b)
{
    QString as = QString::number(a);
    QString bs = QString::number(b);
    ui->label_1->setText(s);
    ui->label_2->setText(as);
    ui->label_3->setText(bs);
}

void GraphInfo::mousePressEvent(QMouseEvent *event){
    mpos = event->pos();
}

void GraphInfo::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() & Qt::LeftButton) {
        QPoint diff = event->pos() - mpos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
    }
}
