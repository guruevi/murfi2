#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <iostream>

#include "RtDataID.h"
#include "RtDataIDs.h"

//
#include"RtExperiment.h"

#include "PlotController.h"

using std::cout;
using std::endl;

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , plot_controller(NULL)
{
  ui->setupUi(this);
  plot_controller = new PlotController(ui->designPlotWidget,
                                       ui->roiPlotWidget,
                                       ui->motionPlotWidget);

  // register me to get the data
  getDataStore().addListener(this);
}

MainWindow::~MainWindow() {
  delete ui;
  delete plot_controller;
}

void MainWindow::notify(const RtDataID &id) {
  RtData *data = getDataStore().getData(id);

  ui->imageWidget->handleData(data);
  plot_controller->handleData(data);
}

void MainWindow::newExperiment() {
  initExperiment();
}

void MainWindow::newRun() {
}

void MainWindow::openRun() {
  string filename = QFileDialog::getOpenFileName(
    this, tr("Open run config"), "", tr("Files (*.xml)")).toStdString();

  if (filename.empty()) {
    return;
  }

  RtConfigFmriRun run_config;
  run_config.parseConfigFile(filename);

  ui->imageWidget->initRun(run_config);

  // TODO validation

  executeRun(run_config);
}
