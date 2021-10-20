#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <set>

QT_BEGIN_NAMESPACE
namespace Ui { class MainMenu; }
QT_END_NAMESPACE

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();
    Q_INVOKABLE void closeProgram();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::MainMenu *ui;
    QVector<double> altitude;
    std::string utf8_text = "***";
    void delay(int);
    std::vector<std::string> splitpath(const std::string& str, const std::set<char> delimiters);
};
#endif // MAINMENU_H
