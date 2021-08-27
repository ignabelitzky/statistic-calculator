#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLCDNumber>
#include <QCheckBox>
#include <QMessageBox>
#include <QFileDialog>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>
#include "param.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void save_data();
    void clear_all_data();
    void import_data_from_file();
    void display_selected_data();
    void show_graphic();
    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;

    // Labels
    QLabel *titleLabel;
    QLabel *inputDataLabel;
    QLabel *countDataLabel;

    // Line Edits
    QLineEdit *inputDataLineEdit;

    // Buttons
    QPushButton *saveDataButton;
    QPushButton *clearDataButton;
    QPushButton *importDataButton;
    QPushButton *displayDataButton;
    QPushButton *showGraphicButton;

    // LCD-Displays
    QLCDNumber *countDataDisplay;
    QLCDNumber *arithmeticMeanDisplay;
    QLCDNumber *medianDisplay;
    QLCDNumber *minimumDisplay;
    QLCDNumber *maximumDisplay;
    QLCDNumber *varianceDisplay;
    QLCDNumber *standardDeviationDisplay;
    QLCDNumber *lowerQuartileDisplay;
    QLCDNumber *upperQuartileDisplay;

    // Checkboxes
    QCheckBox *arithmeticMeanCheckBox;
    QCheckBox *medianCheckBox;
    QCheckBox *minimumCheckBox;
    QCheckBox *maximumCheckBox;
    QCheckBox *varianceCheckBox;
    QCheckBox *standardDeviationCheckBox;
    QCheckBox *lowerQuartileCheckBox;
    QCheckBox *upperQuartileCheckBox;

    // Data
    std::vector<float> *m_data = nullptr;
    double arithmeticMean, median, minimum, maximum;
    double variance, standardDeviation, lowerQuartile, upperQuartile;

    void update_data_counter();
    void set_input_display_to_default_value();
    void disable_all_checkboxes();
    void disable_output_buttons();
    void enable_output_buttons();
    void enable_all_checkboxes();
    void reset_all_calculations();
    void update_lcd_outputs(unsigned int outputMask);
    QString data_to_string();

};
#endif // MAINWINDOW_H
