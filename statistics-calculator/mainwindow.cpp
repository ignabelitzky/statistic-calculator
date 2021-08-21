#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_data = new std::vector<float>(0);

    // Labels
    titleLabel = MainWindow::findChild<QLabel *>(QStringLiteral("title_label"));
    inputDataLabel = MainWindow::findChild<QLabel *>(QStringLiteral("input_label"));
    countDataLabel = MainWindow::findChild<QLabel *>(QStringLiteral("count_label"));

    // Line Edits
    inputDataLineEdit = MainWindow::findChild<QLineEdit *>(QStringLiteral("input_lineEdit"));

    // Buttons
    saveDataButton = MainWindow::findChild<QPushButton *>(QStringLiteral("saveData_button"));
    clearDataButton = MainWindow::findChild<QPushButton *>(QStringLiteral("clearData_button"));
    displayDataButton = MainWindow::findChild<QPushButton *>(QStringLiteral("displayData_button"));

    // LCD Displays
    countDataDisplay = MainWindow::findChild<QLCDNumber *>(QStringLiteral("countDisplay_lcd"));
    countDataDisplay->setMode(QLCDNumber::Dec);
    arithmeticMeanDisplay = MainWindow::findChild<QLCDNumber *>(QStringLiteral("arithmeticMean_lcd"));
    arithmeticMeanDisplay->setMode(QLCDNumber::Dec);
    medianDisplay = MainWindow::findChild<QLCDNumber *>(QStringLiteral("median_lcd"));
    medianDisplay->setMode(QLCDNumber::Dec);
    minimumDisplay = MainWindow::findChild<QLCDNumber *>(QStringLiteral("minimum_lcd"));
    minimumDisplay->setMode(QLCDNumber::Dec);
    maximumDisplay = MainWindow::findChild<QLCDNumber *>(QStringLiteral("maximum_lcd"));
    maximumDisplay->setMode(QLCDNumber::Dec);

    // Check Boxes
    arithmeticMeanCheckBox = MainWindow::findChild<QCheckBox *>(QStringLiteral("arithmeticMean_checkBox"));
    medianCheckBox = MainWindow::findChild<QCheckBox *>(QStringLiteral("median_checkBox"));
    minimumCheckBox = MainWindow::findChild<QCheckBox *>(QStringLiteral("minimum_checkBox"));
    maximumCheckBox = MainWindow::findChild<QCheckBox *>(QStringLiteral("maximum_checkBox"));

    // Setting the objects to a default value
    update_data_counter();
    set_input_display_to_default_value();
    disable_all_checkboxes();

    // Connecting SIGNALS and SLOTS
    connect(saveDataButton, SIGNAL(clicked(bool)), this, SLOT(save_data()));
    connect(clearDataButton, SIGNAL(clicked(bool)), this, SLOT(clear_all_data()));
    connect(displayDataButton, SIGNAL(clicked(bool)), this, SLOT(display_selected_data()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_data;
}

void MainWindow::save_data()
{
    if(m_data->size() == 0) {
        enable_all_checkboxes();
    }
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

void MainWindow::clear_all_data()
{
    m_data->clear();
    update_data_counter();
    disable_all_checkboxes();
}

void MainWindow::display_selected_data()
{
    int dataSize = m_data->size();
    double arithmeticMean = 0.0;
    double median = 0.0;
    double minimum = 0.0;
    double maximum = 0.0;
    if(arithmeticMeanCheckBox->isChecked()) {
        float sum = 0;
        for(int i = 0; i < dataSize; ++i) {
            sum += m_data->at(i);
        }
        arithmeticMean = sum/dataSize;
    }
    if(medianCheckBox->isChecked()) {
        if(dataSize % 2 == 0) {
            int firstPos = (dataSize/2)-1;
            int secondPos = dataSize/2;
            median = (m_data->at(firstPos) + m_data->at(secondPos))/2;
        } else {
            median = m_data->at(dataSize/2);
        }
    }
    if(minimumCheckBox->isChecked()) {
        minimum = m_data->at(0);
    }
    if(maximumCheckBox->isChecked()) {
        maximum = m_data->at(dataSize-1);
    }
    update_lcd_outputs(arithmeticMean, median, minimum, maximum);
}

void MainWindow::update_data_counter()
{
    countDataDisplay->display(static_cast<int>(m_data->size()));
}

void MainWindow::set_input_display_to_default_value()
{
    inputDataLineEdit->setText(QString("0.0"));
    update_data_counter();
    update_lcd_outputs(0,0,0,0);
}

void MainWindow::disable_all_checkboxes()
{
    arithmeticMeanCheckBox->setDisabled(true);
    arithmeticMeanCheckBox->setChecked(false);

    medianCheckBox->setDisabled(true);
    medianCheckBox->setChecked(false);

    minimumCheckBox->setDisabled(true);
    minimumCheckBox->setChecked(false);

    maximumCheckBox->setDisabled(true);
    maximumCheckBox->setChecked(false);
}

void MainWindow::enable_all_checkboxes()
{
    arithmeticMeanCheckBox->setDisabled(false);
    medianCheckBox->setDisabled(false);
    minimumCheckBox->setDisabled(false);
    maximumCheckBox->setDisabled(false);
}

void MainWindow::update_lcd_outputs(double arithmeticMeanValue = 0.0, double medianValue = 0.0, double minValue = 0.0, double maxValue = 0.0)
{
    arithmeticMeanDisplay->display(static_cast<double>(arithmeticMeanValue));
    medianDisplay->display(static_cast<double>(medianValue));
    minimumDisplay->display(static_cast<double>(minValue));
    maximumDisplay->display(static_cast<double>(maxValue));
}

