#ifndef NEWMAINMENU_H
#define NEWMAINMENU_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class newMainMenu; }
QT_END_NAMESPACE

class newMainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit newMainMenu(QWidget *parent = nullptr);
    ~newMainMenu();
    Q_INVOKABLE void closeP();
/*
signals:
    void valueChanged();

public slots:
    void closeP();
*/
private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_2_clicked();

private:
    Ui::newMainMenu *ui;
};
#endif // NEWMAINMENU_H
