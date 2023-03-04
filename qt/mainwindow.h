#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <qcustomplot.h>
#include <QIcon>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    double xvalue;
public Q_SLOTS:
    void handleButton();
    void bmp_file_dialog();
    void selectDrawMode();
    void selectFileMode();
    void changeValueOfSlider();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
