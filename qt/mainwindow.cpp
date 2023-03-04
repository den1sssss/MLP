#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::handleButton()
{
    if (!(ui->widget->Pixels_draw.empty()) && ui->radioButton->isChecked())
    {
        //QMessageBox::about(this,"test output", QString::number(ui->widget->Pixels[1]));//здесь нужно вызвать функцию распознавания
        ui->label->setText("This is A");
        ui->widget->Pixels_draw.clear();
    }

    if (!(ui->widget->Pixels_file.empty()) && ui->radioButton_2->isChecked())
    {
        //QMessageBox::about(this,"test output", QString::number(ui->widget->Pixels[1]));//здесь нужно вызвать функцию распознавания
        ui->label->setText("This is B");
        ui->widget->Pixels_file.clear();
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/Perceptron-or-task.png"));
    ui->pushButton_2->setEnabled(false);
    connect(ui->pushButton, SIGNAL (clicked()), this, SLOT (handleButton()));
    connect(ui->pushButton_2, SIGNAL (clicked()), this, SLOT (bmp_file_dialog()));
    connect(ui->radioButton, SIGNAL (clicked()), this, SLOT (selectDrawMode()));
    connect(ui->radioButton_2, SIGNAL (clicked()), this, SLOT (selectFileMode()));
    connect(ui->horizontalSlider, SIGNAL (sliderMoved(int)), this, SLOT(changeValueOfSlider()));
    ui->horizontalSlider->setRange(0,101);
    xvalue = ui->horizontalSlider->value();
    //QLabel *label = new QLabel(this);
    ui->label_2->setText(QString::number(xvalue/100));
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    ui->widget_2->addGraph();
    ui->widget_2->graph(0)->addData(x,y);
    ui->widget_2->xAxis->setLabel("EPOCH");
    ui->widget_2->yAxis->setLabel("ERROR VALUE");
    ui->widget_2->yAxis->setRange(*std::min_element(y.begin(), y.end()),*std::max_element(y.begin(), y.end()));
    ui->widget_2->xAxis->setRange(0,*std::max_element(x.begin(), x.end()));
    ui->widget_2->setBackground(QColor(190, 251, 188));
    //ui->widget_2->replot();
    //ui->widget_2->setBackground(Color::yellow)
}

void MainWindow::changeValueOfSlider()
{
    xvalue = ui->horizontalSlider->value();
    ui->label_2->setText(QString::number(xvalue/100));
}

void MainWindow::bmp_file_dialog() {
    QImage img = QImage(
        QFileDialog::getOpenFileName(this, tr("Open File"), "/path/to/file/", tr("Object Files (*.bmp)")));
    if (img.isNull())
    {
        return;
    }
    if (img.size().width() != img.size().height() || img.size().width() > 512 || img.size().height() > 512 ||
        img.size().width() < 28 || img.size().height() < 28) {
        QMessageBox::about(this, "Ошибка",
                           "Выберите квадратное изображение .bmp не меньше "
                           "28x28 и не больше 512x512");
    } else {
        ui->widget->Pixels_file.clear();
        ui->widget->setEnabled(false);
        img = img.scaled(28, 28);
        img = img.transformed(QTransform().rotate(-90));

        ui->widget->Pixels_file.push_back(15);
        for (int i = img.size().width() - 1; i >= 0; i--) {
            for (int j = 0; j < img.size().height(); j++) {
                ui->widget->Pixels_file.push_back(img.pixelColor(j, i).black());
            }
        }
    }
}

void MainWindow::selectDrawMode()
{
    ui->widget->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
}

void MainWindow::selectFileMode()
{
    ui->widget->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

