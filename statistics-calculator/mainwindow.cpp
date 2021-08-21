#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setting the private variables
    m_data = new std::vector<float>(0);
    reset_all_calculations();

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
    arithmeticMeanDisplay = MainWindow::findChild<QLCDNumber *>(QStringLiteral("arithmeticMean_lcd"));
    medianDisplay = MainWindow::findChild<QLCDNumber *>(QStringLiteral("median_lcd"));
    minimumDisplay = MainWindow::findChild<QLCDNumber *>(QStringLiteral("minimum_lcd"));
    maximumDisplay = MainWindow::findChild<QLCDNumber *>(QStringLiteral("maximum_lcd"));
    varianceDisplay = MainWindow::findChild<QLCDNumber *>(QStringLiteral("variance_lcd"));
    standardDeviationDisplay = MainWindow::findChild<QLCDNumber *>(QStringLiteral("standardDeviation_lcd"));
    lowerQuartileDisplay = MainWindow::findChild<QLCDNumber *>(QStringLiteral("lowerQuartile_lcd"));
    upperQuartileDisplay = MainWindow::findChild<QLCDNumber *>(QStringLiteral("upperQuartile_lcd"));


    countDataDisplay->setMode(QLCDNumber::Dec);
    arithmeticMeanDisplay->setMode(QLCDNumber::Dec);
    medianDisplay->setMode(QLCDNumber::Dec);
    minimumDisplay->setMode(QLCDNumber::Dec);
    maximumDisplay->setMode(QLCDNumber::Dec);
    varianceDisplay->setMode(QLCDNumber::Dec);
    standardDeviationDisplay->setMode(QLCDNumber::Dec);
    lowerQuartileDisplay->setMode(QLCDNumber::Dec);
    upperQuartileDisplay->setMode(QLCDNumber::Dec);

    // Check Boxes
    arithmeticMeanCheckBox = MainWindow::findChild<QCheckBox *>(QStringLiteral("arithmeticMean_checkBox"));
    medianCheckBox = MainWindow::findChild<QCheckBox *>(QStringLiteral("median_checkBox"));
    minimumCheckBox = MainWindow::findChild<QCheckBox *>(QStringLiteral("minimum_checkBox"));
    maximumCheckBox = MainWindow::findChild<QCheckBox *>(QStringLiteral("maximum_checkBox"));
    varianceCheckBox = MainWindow::findChild<QCheckBox *>(QStringLiteral("variance_checkBox"));
    standardDeviationCheckBox = MainWindow::findChild<QCheckBox *>(QStringLiteral("standardDeviation_checkBox"));
    lowerQuartileCheckBox = MainWindow::findChild<QCheckBox *>(QStringLiteral("lowerQuartile_checkBox"));
    upperQuartileCheckBox = MainWindow::findChild<QCheckBox *>(QStringLiteral("upperQuartile_checkBox"));

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
    reset_all_calculations();
    update_data_counter();
    disable_all_checkboxes();
    reset_all_calculations();
    update_lcd_outputs();
}

void MainWindow::display_selected_data()
{
    int dataSize = m_data->size();
    for(int i = 0; i < dataSize; ++i) {
        arithmeticMean += m_data->at(i);
    }
    arithmeticMean /= dataSize;

    variance = 0;
    for(int i = 0; i < dataSize; ++i) {
        variance += pow((m_data->at(i) - arithmeticMean), 2);
    }
    variance /= (dataSize - 1);


    // Arithmetic Mean
    if(arithmeticMeanCheckBox->isChecked()) {
        // TODO: Set the mask for update_lcd_outputs() here
    }
    // Median
    if(medianCheckBox->isChecked()) {
        if(dataSize % 2 == 0) {
            int firstPos = (dataSize/2)-1;
            int secondPos = dataSize/2;
            median = (m_data->at(firstPos) + m_data->at(secondPos))/2;
        } else {
            median = m_data->at(dataSize/2);
        }
    }
    // Minimum
    if(minimumCheckBox->isChecked()) {
        minimum = m_data->at(0);
    }
    // Maximum
    if(maximumCheckBox->isChecked()) {
        maximum = m_data->at(dataSize-1);
    }
    // Variance
    if(varianceCheckBox->isChecked()) {
        // TODO: Set the mask for update_lcd_outputs() here
    }
    // Standard Deviation
    if(standardDeviationCheckBox->isChecked()) {
        standardDeviation = sqrt(variance);
    }
    update_lcd_outputs();
}

void MainWindow::update_data_counter()
{
    countDataDisplay->display(static_cast<int>(m_data->size()));
}

void MainWindow::set_input_display_to_default_value()
{
    inputDataLineEdit->setText(QString("0.0"));
    update_data_counter();
    reset_all_calculations();
    update_lcd_outputs();
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

    varianceCheckBox->setDisabled(true);
    varianceCheckBox->setChecked(false);

    standardDeviationCheckBox->setDisabled(true);
    standardDeviationCheckBox->setChecked(false);

    lowerQuartileCheckBox->setDisabled(true);
    lowerQuartileCheckBox->setChecked(false);

    upperQuartileCheckBox->setDisabled(true);
    upperQuartileCheckBox->setChecked(false);
}

void MainWindow::enable_all_checkboxes()
{
    arithmeticMeanCheckBox->setDisabled(false);
    medianCheckBox->setDisabled(false);
    minimumCheckBox->setDisabled(false);
    maximumCheckBox->setDisabled(false);
    varianceCheckBox->setDisabled(false);
    standardDeviationCheckBox->setDisabled(false);
    lowerQuartileCheckBox->setDisabled(false);
    upperQuartileCheckBox->setDisabled(false);
}

void MainWindow::reset_all_calculations()
{
    arithmeticMean = 0, median = 0, minimum = 0, maximum = 0;
    variance = 0, standardDeviation = 0, lowerQuartile = 0, upperQuartile = 0;
}

void MainWindow::update_lcd_outputs()
{
    arithmeticMeanDisplay->display(arithmeticMean);
    medianDisplay->display(median);
    minimumDisplay->display(minimum);
    maximumDisplay->display(maximum);
    varianceDisplay->display(variance);
    standardDeviationDisplay->display(standardDeviation);
    lowerQuartileDisplay->display(lowerQuartile);
    upperQuartileDisplay->display(upperQuartile);
}
