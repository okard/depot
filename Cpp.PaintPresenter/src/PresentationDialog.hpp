#ifndef PRESENTATIONDIALOG_HPP
#define PRESENTATIONDIALOG_HPP

#include <QDialog>
#include <QAction>

class PaintWidget;

/**
 * @brief The PresentationDialog class
 * Show only the content of the paint widget
 */
class PresentationDialog : public QDialog
{
    Q_OBJECT
private:
    PaintWidget& widget_;
    QAction toggleViewAction_;

public:
    explicit PresentationDialog(PaintWidget& widget);
    virtual ~PresentationDialog();


    QAction* toggleViewAction() { return &toggleViewAction_; }
    
protected:
    void paintEvent(QPaintEvent *event);

signals:
    //resize signal?
    void showed();

public slots:
    void toggleVisibility();
};

#endif // PRESENTATIONDIALOG_HPP
