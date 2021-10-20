#include "newmainmenu.h"
#include "ui_newmainmenu.h"
#include "itemlist.h"
#include "itemmodel.h"
#include "mainwindow.h"
#include <set>
#include <iostream>
#include <fstream>
#include <QFileDialog>
#include <QMessageBox>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int selected = 0;
std::string utf8_text = "***";
std::vector<std::string> splitpath(const std::string& str, const std::set<char> delimiters);
void delay(int);

newMainMenu::newMainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::newMainMenu)
{
    ui->setupUi(this);
    setFixedSize(473,359);
    setWindowTitle("Main Menu");

    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->lineEdit->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);
}

newMainMenu::~newMainMenu()
{
    delete ui;
}

std::vector<std::string> splitpath(
  const std::string& str
  , const std::set<char> delimiters)
{
  std::vector<std::string> result;

  char const* pch = str.c_str();
  char const* start = pch;
  for(; *pch; ++pch)
  {
    if (delimiters.find(*pch) != delimiters.end())
    {
      if (start != pch)
      {
        std::string str(start, pch);
        result.push_back(str);
      }
      else
      {
        result.push_back("");
      }
      start = pch + 1;
    }
  }
  result.push_back(start);

  return result;
}

void newMainMenu::on_pushButton_clicked()
{
    QString filter = "Tab File (*.tab)";
    QString Filepath = QFileDialog::getOpenFileName(this, "Open a file", "C:\\Users\\PC_901_ADMIN\\Desktop\\New folder\\Realtime_Tracking", filter);

    std::set<char> delims{'/'};

    utf8_text = Filepath.toUtf8().constData();
    std::vector<std::string> path = splitpath(utf8_text, delims);
    QString qstr = QString::fromStdString(path.back());

    ui->label_3->setText(qstr);
}


void newMainMenu::on_comboBox_currentIndexChanged(int index)
{
    selected = index;
    if(index == 1){

        ui->label->setVisible(true);
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(false);
        ui->lineEdit->setVisible(true);
        ui->lineEdit_2->setVisible(true);
        ui->pushButton->setVisible(false);
        ui->pushButton_2->setVisible(true);
    }
    else if(index == 2){

        ui->label->setVisible(false);
        ui->label_2->setVisible(false);
        ui->label_3->setVisible(true);
        ui->lineEdit->setVisible(false);
        ui->lineEdit_2->setVisible(false);
        ui->pushButton->setVisible(true);
        ui->pushButton_2->setVisible(true);
    }
}


void newMainMenu::on_pushButton_2_clicked()
{
/*
    if (selected == 0){
        QMessageBox msgBox;
        msgBox.setText("Herhangi bir opsiyon seçmediniz!");
        msgBox.exec();
    }
    */
    if(selected == 1){
        this->hide();

    }
    else if(selected == 2){
        this->hide();
        ItemList model;
        MainWindow *altitude = new MainWindow;
        altitude->show();
        altitude->move(359,630);

        QGeoCoordinate center(41.108604, 29.030932);
        QGeoCoordinate center2(41.118604, 29.040932);
        QGeoCoordinate position{center};
        //QGeoCoordinate position2{center2};

        std::ifstream infile (utf8_text);
        double tmp1, tmp2, tmp1e=0, tmp2e=0;
        std::string tp;
        std::cout.precision(17);

        model.createAsset(center, "receiver");
        //model.createAsset(center2, "receiver_2");

        QQmlApplicationEngine engine;

        model.register_objects("assetmodel", "itemmodel", engine.rootContext());
        engine.rootContext()->setContextProperty("mainmenu",this);
        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

        altitude->addGraph("irtifa_m_msl", QPen(Qt::green));
        altitude->addGraph("irtifa_m_ell", QPen(Qt::blue));

        if (infile.is_open()) {
            getline(infile, tp);
            while (!infile.eof()) {
                for(int i=0; i<12; i++)
                    infile >> tmp1;
                infile >> tmp2;

                position = QGeoCoordinate{tmp1, tmp2};
                //position2 = QGeoCoordinate{tmp1+0.01, tmp2+0.01};
                double angle = atan2(tmp1 - tmp1e, tmp2 - tmp2e);
                angle *= (180.0/3.141592653589793238463);
                tmp1e = tmp1;
                tmp2e = tmp2;

                infile >> tmp1;
                altitude->addPoint(tmp1);
                altitude->plot(0);

                infile >> tmp1;
                altitude->addPoint2(tmp1);
                altitude->plot(1);

                model.addAsset(position, angle, "receiver");
                //model.addAsset(position2, "receiver_2");
                delay(150);
            }
        }
        else {
            QMessageBox msgBox;
            msgBox.setText("Error opening file!");
            msgBox.exec();
        }
    }
}

void delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);
    while(QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void newMainMenu::closeP() {
    exit(1);
}
