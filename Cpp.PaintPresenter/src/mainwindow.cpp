#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintwidget.h"

#include <QSignalMapper>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    paintWidget= new PaintWidget();

    this->setCentralWidget(paintWidget);

    connect(ui->actionScreenshot, SIGNAL(triggered()), paintWidget, SLOT(makeScreenshot()));
    connect(ui->actionScreenShotClear, SIGNAL(triggered()), paintWidget, SLOT(clearScreenshot()));
    connect(ui->actionClearDrawings, SIGNAL(triggered()), paintWidget, SLOT(clearDrawings()));

    connect(ui->actionPenColorBlack, &QAction::triggered, [=]() { paintWidget->setPenColor(QColor::fromRgb(0,0,0)); }  );

}

MainWindow::~MainWindow()
{
    delete ui;
    delete paintWidget;
}

