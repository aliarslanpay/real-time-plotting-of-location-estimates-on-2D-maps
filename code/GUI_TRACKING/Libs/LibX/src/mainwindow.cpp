#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphinfo.h"
#include <iostream>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{

  std::srand(QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0);
  ui->setupUi(this);

  ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                  QCP::iSelectLegend | QCP::iSelectPlottables);
  /*ui->customPlot->addGraph();
  numberOfGraphs++;
  ui->customPlot->xAxis->setRange(0, 600);
  ui->customPlot->yAxis->setRange(100, 250);
  ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
  ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->customPlot->graph(0)->setPen(QPen(Qt::green));
  ui->customPlot->graph(0)->setName("receiver");*/
/*
  ui->customPlot->addGraph();
  numberOfGraphs++;
  ui->customPlot->xAxis->setRange(0, 600);
  ui->customPlot->yAxis->setRange(100, 250);
  ui->customPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssSquare);
  ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
  ui->customPlot->graph(1)->setPen(QPen(Qt::red));
  ui->customPlot->graph(1)->setName("receiver_2");*/

  ui->customPlot->plotLayout()->insertRow(0);
  QCPTextElement *title = new QCPTextElement(ui->customPlot, "Altitude Graphs", QFont("sans", 15, QFont::Bold));
  ui->customPlot->plotLayout()->addElement(0, 0, title);

  ui->customPlot->xAxis->setLabel("Time (s)");
  ui->customPlot->yAxis->setLabel("Altitude (m)");
  ui->customPlot->legend->setVisible(true);
  QFont legendFont = font();
  legendFont.setPointSize(10);
  ui->customPlot->legend->setFont(legendFont);
  ui->customPlot->legend->setSelectedFont(legendFont);
  ui->customPlot->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items

  ui->customPlot->rescaleAxes();


  connect(ui->customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
  connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
  connect(ui->customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

  connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

  connect(ui->customPlot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
  connect(ui->customPlot, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));
  connect(title, SIGNAL(doubleClicked(QMouseEvent*)), this, SLOT(titleDoubleClick(QMouseEvent*)));

  connect(ui->customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*,int)));

  ui->customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(ui->customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));

}
static int numberOfGraphs=0;
MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::addGraph(std::string const &str, const QPen &pen){
    ui->customPlot->addGraph();
    ui->customPlot->xAxis->setRange(0, 200);
    ui->customPlot->yAxis->setRange(0, 250);
    ui->customPlot->graph(numberOfGraphs)->setScatterStyle(QCPScatterStyle::ssDisc);
    //ui->customPlot->graph(numberOfGraphs)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(numberOfGraphs)->setPen(pen);
    ui->customPlot->graph(numberOfGraphs)->setName(QString::fromStdString(str));
    numberOfGraphs++;
}

void MainWindow::addPoint(double value){
    ax++;

    qv_x.append(ax);
    qv_y.append(value);
}

void MainWindow::addPoint2(double value){

    rv_x.append(ax);
    rv_y.append(value);
}

void MainWindow::plot(int i){
    if(i == 0){
        ui->customPlot->graph(i)->setData(qv_x, qv_y);
        ui->customPlot->replot();
    }
    else{
        ui->customPlot->graph(i)->setData(rv_x, rv_y);
        ui->customPlot->replot();
    }

    setWindowTitle("Altitude Graph - " + QString::number(1000.0 / ui->customPlot->replotTime(), 'f', 2) + " FPS");
    ui->customPlot->update();
    //ui->customPlot->rescaleAxes();
}

void MainWindow::plot_array(QVector<double> qv_x,  QVector<double> alt){
    ui->customPlot->graph(0)->setData(qv_x, alt);
    ui->customPlot->replot();
    setWindowTitle("Altitude Graph - " + QString::number(1000.0 / ui->customPlot->replotTime(), 'f', 2) + " FPS");
    ui->customPlot->update();
}

//Başlık değiştirme
void MainWindow::titleDoubleClick(QMouseEvent* event)
{
  Q_UNUSED(event)
  if (QCPTextElement *title = qobject_cast<QCPTextElement*>(sender())){
      bool ok;
    QString newTitle = QInputDialog::getText(this, "QCustomPlot example", "New plot title:", QLineEdit::Normal, title->text(), &ok);
    if (ok)
    {
      title->setText(newTitle);
      ui->customPlot->replot();
    }
  }
}

//Eksen adı değiştirme
void MainWindow::axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
{
  if (part == QCPAxis::spAxisLabel)
  {
    bool ok;
    QString newLabel = QInputDialog::getText(this, "QCustomPlot example", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
    if (ok)
    {
      axis->setLabel(newLabel);
      ui->customPlot->replot();
    }
  }
}

//Lejantta tıklanan grafiğin adını değiştirme
void MainWindow::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item) {
  Q_UNUSED(legend)
  if (item)
  {
    QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
    bool ok;
    QString newName = QInputDialog::getText(this, "QCustomPlot example", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
    if (ok)
    {
      plItem->plottable()->setName(newName);
      ui->customPlot->replot();
    }
  }
}

//kullanıcının grafikteki tıklamaları senkronize edilir
void MainWindow::selectionChanged()
{
    // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
            ui->customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        ui->customPlot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        ui->customPlot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }

    // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
            ui->customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        ui->customPlot->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        ui->customPlot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }

    // synchronize selection of graphs with selection of corresponding legend items:
    for (int i=0; i<ui->customPlot->graphCount(); ++i) {
        QCPGraph *graph = ui->customPlot->graph(i);
        QCPPlottableLegendItem *item = ui->customPlot->legend->itemWithPlottable(graph);
        if (item->selected() || graph->selected()) {
            item->setSelected(true);
            graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
        }
    }
}

//sürükleme için eksen seçimi, tıklanan eksen seçilir
void MainWindow::mousePress()
{

  if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeDrag(ui->customPlot->xAxis->orientation());
  else if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeDrag(ui->customPlot->yAxis->orientation());
  else
    ui->customPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

//seçilen eksende sürükleme (zoom +-)
void MainWindow::mouseWheel()
{
  if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeZoom(ui->customPlot->xAxis->orientation());
  else if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeZoom(ui->customPlot->yAxis->orientation());
  else
    ui->customPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void MainWindow::removeSelectedGraph()
{
  if (ui->customPlot->selectedGraphs().size() > 0)
  {
    //ui->customPlot->removeGraph(ui->customPlot->selectedGraphs().first());
    ui->customPlot->selectedGraphs().first()->setVisible(false);
    ui->customPlot->selectedGraphs().first()->removeFromLegend();
    ui->customPlot->replot();
  }
}
void MainWindow::on_pushButton_2_clicked()
{
    for(int i=0; i<numberOfGraphs; i++){
        ui->customPlot->graph(i)->setVisible(true);
        ui->customPlot->graph(i)->addToLegend();
         ui->customPlot->replot();
    }

}

void MainWindow::removeAllGraphs()
{
  //ui->customPlot->clearGraphs();
  //ui->customPlot->replot();
  for(int i=0; i<numberOfGraphs; i++){
      ui->customPlot->graph(i)->setVisible(false);
      ui->customPlot->graph(i)->removeFromLegend();
      ui->customPlot->replot();
  }
}

//Lejantın potansiyel konumlarını gösteren context menu
void MainWindow::contextMenuRequest(QPoint pos) {
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    if (ui->customPlot->legend->selectTest(pos, false) >= 0) {
        menu->addAction("Move to top left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
        menu->addAction("Move to top center", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
        menu->addAction("Move to top right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
        menu->addAction("Move to bottom right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
        menu->addAction("Move to bottom left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
    } else  // general context menu on graphs requested
    {
      //menu->addAction("Add random graph", this, SLOT(addRandomGraph()));
      if (ui->customPlot->selectedGraphs().size() > 0)
        menu->addAction("Hide selected graph", this, SLOT(removeSelectedGraph()));
      if (ui->customPlot->graphCount() > 0)
        menu->addAction("Hide all graphs", this, SLOT(removeAllGraphs()));
    }
    menu->popup(ui->customPlot->mapToGlobal(pos));
}

//Lejantın konumu değiştirilir
void MainWindow::moveLegend()
{
  if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
  {
    bool ok;
    int dataInt = contextAction->data().toInt(&ok);
    if (ok)
    {
      ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
      ui->customPlot->replot();
    }
  }
}

//grafikte tıklanan ilgili nokta hakkındaki bilgi, status bar'da gösterilir
void MainWindow::graphClicked(QCPAbstractPlottable *plottable, int dataIndex) {
  double dataValue = plottable->interface1D()->dataMainValue(dataIndex);

  //QString message = QString("Clicked on graph '%1' at data point #%2 with value %3.").arg(plottable->name()).arg(dataIndex).arg(dataValue);
  //ui->statusBar->showMessage(message, 2500);
/*
  GraphInfo *g = new GraphInfo;
  g->setWindowTitle("Altitude Graph");
  g->show();
  //g->move(460,650);
    g->output(plottable->name(), dataIndex, dataValue);*/

}

//grafikleri ekrana sığdırır
void MainWindow::on_pushButton_clicked() {
    //ui->plot->xAxis->setRange(*std::min_element(qv_x.begin(), qv_x.end()), *std::max_element(qv_x.begin(), qv_x.end()));
    //ui->plot->yAxis->setRange(*std::min_element(qv_y.begin(), qv_y.end()) -1, *std::max_element(qv_y.begin(), qv_y.end()) + 1);
    ui->customPlot->rescaleAxes();
}

//pencerenin ekran görüntüsünü alır
void MainWindow::on_pushButton_3_clicked()
{
    QPixmap pixmap(this->size());
    this->render(&pixmap);

    QString file = "graph_";
    file += QDateTime::currentDateTime().toString("yyyy-MM-dd_hhmmss");
    file += ".png";

    pixmap.save(file);
}
