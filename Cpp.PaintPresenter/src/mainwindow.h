#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class PaintWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void timerInterval();

private:
    Ui::MainWindow *ui;
    PaintWidget* paintWidget;
    //presenter window?

    QTime time_;
    QTimer* timer_;

};

#endif // MAINWINDOW_H
