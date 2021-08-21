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

    // Setting the objects to a default value
    update_data_counter();
    set_input_display_to_default_value();

    // Connecting SIGNALS and SLOTS
    connect(saveDataButton, SIGNAL(clicked(bool)), this, SLOT(save_data()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_data;
}

void MainWindow::save_data()
{
    QString inputData = inputDataLineEdit->text();
    if(inputData.isEmpty()) {
        QMessageBox msgWarning;
        msgWarning.setText("WARNING!\nYou don't enter any value.");
        msgWarning.setIcon(QMessageBox::Warning);
        msgWarning.setWindowTitle("Caution");
        msgWarning.exec();
    } else {
        float value = inputData.toFloat();
        m_data->push_back(value);
        std::sort(m_data->begin(), m_data->end());
        update_data_counter();
        set_input_display_to_default_value();
    }
}

void MainWindow::update_data_counter()
{
    countDataDisplay->display(static_cast<int>(m_data->size()));
}

void MainWindow::set_input_display_to_default_value()
{
    inputDataLineEdit->setText(QString("0.0"));
}

