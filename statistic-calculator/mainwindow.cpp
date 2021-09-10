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
    importDataButton = MainWindow::findChild<QPushButton *>(QStringLiteral("importData_button"));
    displayDataButton = MainWindow::findChild<QPushButton *>(QStringLiteral("displayData_button"));
    showGraphicButton = MainWindow::findChild<QPushButton *>(QStringLiteral("showGraphic_button"));

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
    disable_output_buttons();

    // Connecting SIGNALS and SLOTS
    connect(saveDataButton, SIGNAL(clicked(bool)), this, SLOT(save_data()));
    connect(clearDataButton, SIGNAL(clicked(bool)), this, SLOT(clear_all_data()));
    connect(importDataButton, SIGNAL(clicked(bool)), this, SLOT(import_data_from_file()));
    connect(displayDataButton, SIGNAL(clicked(bool)), this, SLOT(display_selected_data()));
    connect(showGraphicButton, SIGNAL(clicked(bool)), this, SLOT(show_graphic()));

    importDataButton->setToolTip(QStringLiteral("Select a file with the numbers separated by spaces."));
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
        QMessageBox msgWarning(this);
        msgWarning.setText("WARNING!\nYou don't enter any value.");
        msgWarning.setIcon(QMessageBox::Warning);
        msgWarning.setWindowTitle("Caution");
        msgWarning.exec();
        inputDataLineEdit->clear();
        inputDataLineEdit->setFocus();
    } else {
        if(m_data->size() == 0) {
            enable_all_checkboxes();
            enable_output_buttons();
        }
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
    disable_output_buttons();
    update_lcd_outputs(ALL);
}

void MainWindow::import_data_from_file()
{
    clear_all_data();
    QString filename = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), "*");
    if(filename.isEmpty()) {
        QMessageBox msgWarning(this);
        msgWarning.setText("WARNING!\nYou don't open any file.");
        msgWarning.setIcon(QMessageBox::Warning);
        msgWarning.setWindowTitle("Caution");
        msgWarning.exec();
    } else{
        QFile file(filename);
        if(file.open(QFile::ReadWrite)) {
            QTextStream in(&file);
            QString line = "";
            QStringList myList;
            while(!in.atEnd()) {
                line = in.readLine();
                myList = line.split(" ");
                for(int i = 0; i < myList.size(); ++i) {
                    m_data->push_back(myList.at(i).toFloat());
                }
            }
            if(!m_data->empty()) {
                update_data_counter();
                enable_all_checkboxes();
                enable_output_buttons();
                std::sort(m_data->begin(), m_data->end());
            }
            file.close();
        } else {
            QMessageBox msgError(this);
            msgError.setText("ERROR!\nThe file could not be opened!");
            msgError.setIcon(QMessageBox::Warning);
            msgError.setWindowTitle("Error");
            msgError.exec();
        }
    }
}

void MainWindow::display_selected_data()
{
    reset_all_calculations();
    unsigned int outputMask = 0u;
    int dataSize = m_data->size();
    for(int i = 0; i < dataSize; ++i) {
        arithmeticMean += m_data->at(i);
    }
    arithmeticMean /= dataSize;

    if(dataSize % 2 == 0) {
        int firstPos = (dataSize/2)-1;
        int secondPos = dataSize/2;
        median = (m_data->at(firstPos) + m_data->at(secondPos))/2;
    } else {
        median = m_data->at(dataSize/2);
    }

    minimum = m_data->at(0);
    maximum = m_data->at(dataSize-1);

    variance = 0;
    for(int i = 0; i < dataSize; ++i) {
        variance += pow((m_data->at(i) - arithmeticMean), 2);
    }
    variance /= (dataSize - 1);

    standardDeviation = sqrt(variance);

    unsigned int mid = dataSize/2;
    unsigned int lower = mid/2;
    unsigned int upper = (dataSize+mid)/2;

    lowerQuartile = mid % 2 == 0 ? (m_data->at(lower) + m_data->at(lower-1))/2 : m_data->at(lower);
    upperQuartile = mid % 2 == 0 ? (m_data->at(upper) + m_data->at(upper-1))/2 : m_data->at(upper);

    // Arithmetic Mean
    if(arithmeticMeanCheckBox->isChecked())
        outputMask |= ARITHMETIC_MEAN;
    // Median
    if(medianCheckBox->isChecked())
        outputMask |= MEDIAN;
    // Minimum
    if(minimumCheckBox->isChecked())
        outputMask |= MINIMUM;
    // Maximum
    if(maximumCheckBox->isChecked())
        outputMask |= MAXIMUM;
    // Variance
    if(varianceCheckBox->isChecked())
        outputMask |= VARIANCE;
    // Standard Deviation
    if(standardDeviationCheckBox->isChecked())
        outputMask |= STANDARD_DEVIATION;
    // Lower Quartile
    if(lowerQuartileCheckBox->isChecked())
        outputMask |= LOWER_QUARTILE;
    // Upper Quartile
    if(upperQuartileCheckBox->isChecked())
        outputMask |= UPPER_QUARTILE;

    update_lcd_outputs(outputMask);
}

QString MainWindow::data_to_string() {
    std::vector<float>::iterator it;
    QString result = "";
    for(it = m_data->begin(); it < m_data->end(); ++it) {
        result += QString::number(*it);
        if(it != m_data->end()-1) {
            result += QString(",");
        }
    }
    return result;
}

void MainWindow::show_graphic()
{
    QString scriptPath = QFileDialog::getOpenFileName(this, tr("Select python script for graphic display"), "/home/", "*.py");
    if(scriptPath.isEmpty()) {
        QMessageBox msgWarning(this);
        msgWarning.setText("WARNING!\nYou don't select any file.");
        msgWarning.setIcon(QMessageBox::Warning);
        msgWarning.setWindowTitle("Caution");
        msgWarning.exec();
    } else {
        int rc = fork();
        if(rc == -1) {
            qDebug() << "Error forking!!!";
        } else if(rc == 0) {
            QString values = data_to_string();
            execl("/usr/bin/python", "python", scriptPath.toStdString().c_str(), values.toStdString().c_str(), NULL);
        }
    }
}

void MainWindow::update_data_counter()
{
    countDataDisplay->display(static_cast<int>(m_data->size()));
    // Clear and set focus to the Line Edit
    inputDataLineEdit->clear();
    inputDataLineEdit->setFocus();
}

void MainWindow::set_input_display_to_default_value()
{
    update_data_counter();
    reset_all_calculations();
    update_lcd_outputs(ALL);
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

void MainWindow::disable_output_buttons()
{
    displayDataButton->setDisabled(true);
    showGraphicButton->setDisabled(true);
}

void MainWindow::enable_output_buttons()
{
    displayDataButton->setEnabled(true);
    showGraphicButton->setEnabled(true);
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

void MainWindow::update_lcd_outputs(unsigned int outputMask)
{
    if(outputMask & ARITHMETIC_MEAN)
        arithmeticMeanDisplay->display(arithmeticMean);
    if(outputMask & MEDIAN)
        medianDisplay->display(median);
    if(outputMask & MINIMUM)
        minimumDisplay->display(minimum);
    if(outputMask & MAXIMUM)
        maximumDisplay->display(maximum);
    if(outputMask & VARIANCE)
        varianceDisplay->display(variance);
    if(outputMask & STANDARD_DEVIATION)
        standardDeviationDisplay->display(standardDeviation);
    if(outputMask & LOWER_QUARTILE)
        lowerQuartileDisplay->display(lowerQuartile);
    if(outputMask & UPPER_QUARTILE)
        upperQuartileDisplay->display(upperQuartile);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msgBox(this);
    QString information("<center><b>License</b><br>GNU General Public License v3.0<br><br><b>Created by</b><br>Ignacio Belitzky</center>");
    QString title("About Statistics Calculator");
    msgBox.setText(information);
    msgBox.setWindowTitle(title);
    msgBox.addButton(QMessageBox::Ok);
    msgBox.exec();
}
