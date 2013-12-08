#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QComboBox>

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
    void timerInterval(); //move to timer widget

    void openPdfFile();


    void togglePresentationDialog();

private:
    Ui::MainWindow *ui;
    PaintWidget* paintWidget;
    PresentationDialog* presentationDialog;

    QComboBox views_;
    QComboBox overlays_;
    QComboBox presentationSize_;


    QTime time_;
    QTimer* timer_;

};

#endif // MAINWINDOW_H
