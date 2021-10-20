#ifndef GRAPHINFO_H
#define GRAPHINFO_H

#include <QWidget>

namespace Ui {
class GraphInfo;
}

class GraphInfo : public QWidget
{
    Q_OBJECT

public:
    explicit GraphInfo(QWidget *parent = nullptr);
    ~GraphInfo();
    void output(QString, int, double);

private:
    Ui::GraphInfo *ui;
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
};

#endif // GRAPHINFO_H
