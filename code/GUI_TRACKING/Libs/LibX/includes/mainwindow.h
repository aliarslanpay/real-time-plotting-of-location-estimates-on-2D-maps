#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
  
public:
    Ui::MainWindow *ui;
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
    void addGraph(std::string const &str1, const QPen &pen);
    void plot(int);
    void plot_array(QVector<double>, QVector<double>);
    void addPoint(double);
    void addPoint2(double);
    void newPlot(QVector<double>, QVector<double>);
  
private slots:
  void titleDoubleClick(QMouseEvent *event);
  void axisLabelDoubleClick(QCPAxis* axis, QCPAxis::SelectablePart part);
  void legendDoubleClick(QCPLegend* legend, QCPAbstractLegendItem* item);
  void selectionChanged();
  void mousePress();
  void mouseWheel();
  void contextMenuRequest(QPoint pos);
  void moveLegend();
  void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);
  void on_pushButton_clicked();
  void removeSelectedGraph();
  void removeAllGraphs();
  void on_pushButton_2_clicked();
  void on_pushButton_3_clicked();

private:
  QVector<double> qv_x, qv_y;
  QVector<double> rv_x, rv_y;
  double ax=0, bx=0;
  std::vector<double> xirtifa_m_ell, xirtifa_m_msl;
};

#endif // MAINWINDOW_H
