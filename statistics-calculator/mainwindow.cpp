#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_data = new std::vector<float>(0);
    m_arithmeticMean = 0.0;
    m_median = 0.0;
    m_maximum = 0.0;
    m_minimum = 0.0;

    titleLabel = MainWindow::findChild<QLabel *>(QString("title_label"));
    inputDataLabel = MainWindow::findChild<QLabel *>(QString("input_label"));
    inputDataLineEdit = MainWindow::findChild<QLineEdit *>(QString("input_lineEdit"));
    saveDataButton = MainWindow::findChild<QPushButton *>(QString("saveData_button"));
    countDataLabel = MainWindow::findChild<QLabel *>(QString("count_label"));
    countDataDisplay = MainWindow::findChild<QLCDNumber *>(QString("countDisplay_lcd"));

    inputDataLineEdit->setText(QString("0.0"));
    countDataDisplay->display(static_cast<int>(m_data->size()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_data;
}

