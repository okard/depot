#ifndef PRESENTATIONDIALOG_HPP
#define PRESENTATIONDIALOG_HPP

#include <QDialog>

class PresentationDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PresentationDialog(QWidget *parent = 0);
    
signals:
    //resize signal?
public slots:
    void toggleVisibility();
};

#endif // PRESENTATIONDIALOG_HPP
