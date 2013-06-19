#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintwidget.h"

#include <QSignalMapper>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  , timer_(new QTimer(this))
{
    ui->setupUi(this);
    ui->menuBar->hide();
    ui->actionWindowsMenu->setMenu(ui->menuWindows);
    ui->menuWindows->addAction(ui->dockTimer->toggleViewAction());
    //ui->actionWindowsMenu->set
    //toolButton->setPopupMode(QToolButton::InstantPopup);

    paintWidget= new PaintWidget();

    this->setCentralWidget(paintWidget);

    //screen shot and clear
    connect(ui->actionScreenshot, SIGNAL(triggered()), paintWidget, SLOT(makeScreenshot()));
    connect(ui->actionScreenShotClear, SIGNAL(triggered()), paintWidget, SLOT(clearScreenshot()));
    connect(ui->actionClearDrawings, SIGNAL(triggered()), paintWidget, SLOT(clearDrawings()));

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
    //connect(ui->actionToolErease, &QAction::triggered, [=]() { paintWidget->setPenColor(QColor::fromRgb(0,0,0,0)); }  );

    //handle timer stuff
    connect(timer_, &QTimer::timeout, this, &MainWindow::timerInterval);
    connect(ui->btnTimerStart, &QPushButton::clicked, [=]{std::cout << "start\n"; timer_->start(1000); } );
    connect(ui->btnTimerPause, &QPushButton::clicked, [=]{timer_->stop();} );
    connect(ui->btnTimerReset, &QPushButton::clicked, [=]{timer_->stop(); time_ = QTime(0,0); }  );


    connect(ui->actionWindowsMenu, &QAction::triggered, [=]{ui->menuWindows->popup(QCursor::pos() ,ui->actionWindowsMenu);});

    this->showFullScreen();
}

MainWindow::~MainWindow()
{
    delete timer_;
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

