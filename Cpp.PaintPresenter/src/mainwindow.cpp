#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintwidget.h"

#include "PresentationDialog.hpp"

#include <QFileDialog>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , timer_(new QTimer(this))
{
    presentationDialog = new PresentationDialog(this);
    paintWidget = new PaintWidget(this);

    ui->setupUi(this);
    ui->menuBar->hide();
    ui->actionWindowsMenu->setMenu(ui->menuWindows);
    ui->menuWindows->addAction(ui->dockTimer->toggleViewAction());
    //ui->actionWindowsMenu->set
    //toolButton->setPopupMode(QToolButton::InstantPopup);

    this->setCentralWidget(paintWidget);

    //screen shot and clear
    connect(ui->actionScreenshot, SIGNAL(triggered()), paintWidget, SLOT(makeScreenshot()));
    connect(ui->actionScreenShotClear, SIGNAL(triggered()), paintWidget, SLOT(clearScreenshot()));
    connect(ui->actionClearDrawings, SIGNAL(triggered()), paintWidget, SLOT(clearDrawOverlay()));

    //choose color
    connect(ui->actionPenColorBlack, &QAction::triggered, [=]() { paintWidget->setPenColor(QColor::fromRgb(0,0,0)); }  );
    connect(ui->actionPenColorRed, &QAction::triggered, [=]() { paintWidget->setPenColor(QColor::fromRgb(255,0,0)); }  );
    connect(ui->actionPenColorGreen, &QAction::triggered, [=]() { paintWidget->setPenColor(QColor::fromRgb(0,255,0)); }  );
    connect(ui->actionPenColorBlue, &QAction::triggered, [=]() { paintWidget->setPenColor(QColor::fromRgb(0,0,255)); }  );
    connect(ui->actionPenColorYellow, &QAction::triggered, [=]() { paintWidget->setPenColor(QColor::fromRgb(255,255,0)); }  );

    //choose tools
    connect(ui->actionToolPen, &QAction::triggered, [=]() { paintWidget->setTool(PaintTool::Pen); }  );
    connect(ui->actionToolRectangle, &QAction::triggered, [=]() { paintWidget->setTool(PaintTool::Rectangle); }  );
    connect(ui->actionToolHighlight, &QAction::triggered, [=]() { paintWidget->setTool(PaintTool::Highlight); }  );
    connect(ui->actionToolText, &QAction::triggered, [=]() { paintWidget->setTool(PaintTool::Text); }  );
    connect(ui->actionToolErease, &QAction::triggered, [=]() { paintWidget->setTool(PaintTool::Erease);  }  );

    //handle timer stuff
    time_ = QTime(0,0);
    connect(timer_, &QTimer::timeout, this, &MainWindow::timerInterval);
    connect(ui->btnTimerStart, &QPushButton::clicked, [=]{std::cout << "start\n"; timer_->start(1000); } );
    connect(ui->btnTimerPause, &QPushButton::clicked, [=]{timer_->stop();} );
    connect(ui->btnTimerReset, &QPushButton::clicked, [=]{timer_->stop(); time_ = QTime(0,0); }  );

    connect(ui->actionOpenPDF, &QAction::triggered, this, &MainWindow::openPdfFile);
    connect(ui->actionPdfNextPage, &QAction::triggered, paintWidget, &PaintWidget::nextPdfPage);
    connect(ui->actionPdfPrevPage, &QAction::triggered, paintWidget, &PaintWidget::prevPdfPage);


    connect(ui->actionWindowsMenu, &QAction::triggered, [=]{ui->menuWindows->popup(QCursor::pos() ,ui->actionWindowsMenu);});

    //for presentationdialog: QDesktopWidget screenCountChanged(int newCount) isVirtualDesktop() const
}

MainWindow::~MainWindow()
{
    delete timer_;
    delete presentationDialog;
    delete paintWidget;
    delete ui;
}

void MainWindow::timerInterval()
{
        time_ = this->time_.addSecs(1);
        ui->lblTimer->setText(time_.toString("hh:mm:ss"));

        if(time_ == ui->timeTimerAlert->time())
        {
            //QSound::play("mysounds/bells.wav");
            std::cout << "beep" << std::endl;
        }
}

void MainWindow::openPdfFile()
{
    auto fileName = QFileDialog::getOpenFileName(this, tr("Open Pdf File"), nullptr, tr("Pdf Files (*.pdf)"));

    paintWidget->openPdfFile(fileName);
}

