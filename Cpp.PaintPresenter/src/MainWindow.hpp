#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class PaintWidget;
class PresentationDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void timerInterval();

    void openPdfFile();

    //void togglePresentationWindow?

private:
    Ui::MainWindow *ui;
    PaintWidget* paintWidget;
    PresentationDialog* presentationDialog;
    //presenter window?

    QTime time_;
    QTimer* timer_;

};

#endif // MAINWINDOW_H
