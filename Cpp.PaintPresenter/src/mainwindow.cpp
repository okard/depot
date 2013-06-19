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
    connect(ui->actionPenColorRed, &QAction::triggered, [=]() { paintWidget->setPenColor(QColor::fromRgb(255,0,0)); }  );
    connect(ui->actionPenColorGreen, &QAction::triggered, [=]() { paintWidget->setPenColor(QColor::fromRgb(0,255,0)); }  );
    connect(ui->actionPenColorBlue, &QAction::triggered, [=]() { paintWidget->setPenColor(QColor::fromRgb(0,0,255)); }  );
    connect(ui->actionPenColorYellow, &QAction::triggered, [=]() { paintWidget->setPenColor(QColor::fromRgb(255,255,0)); }  );
    //connect(ui->actionToolErease, &QAction::triggered, [=]() { paintWidget->setPenColor(QColor::fromRgb(0,0,0,0)); }  );

    connect(ui->actionToolPen, &QAction::triggered, [=]() { paintWidget->setTool(PaintTool::Pen); }  );
    connect(ui->actionToolRectangle, &QAction::triggered, [=]() { paintWidget->setTool(PaintTool::Rectangle); }  );
}

MainWindow::~MainWindow()
{
    delete ui;
    delete paintWidget;
}

