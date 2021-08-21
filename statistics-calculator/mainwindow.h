#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLCDNumber>
#include <QCheckBox>
#include <QMessageBox>
#include <vector>
#include <algorithm>

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
    void display_selected_data();

private:
    Ui::MainWindow *ui;
    QLabel *titleLabel;
    QLabel *inputDataLabel;
    QLabel *countDataLabel;
    QLineEdit *inputDataLineEdit;
    QPushButton *saveDataButton;
    QPushButton *clearDataButton;
    QPushButton *displayDataButton;
    QLCDNumber *countDataDisplay;
    QLCDNumber *arithmeticMeanDisplay;
    QLCDNumber *medianDisplay;
    QLCDNumber *minimumDisplay;
    QLCDNumber *maximumDisplay;
    QCheckBox *arithmeticMeanCheckBox;
    QCheckBox *medianCheckBox;
    QCheckBox *minimumCheckBox;
    QCheckBox *maximumCheckBox;

    std::vector<float> *m_data = nullptr;

    void update_data_counter();
    void set_input_display_to_default_value();
    void disable_all_checkboxes();
    void enable_all_checkboxes();
    void update_lcd_outputs(double, double, double, double);

};
#endif // MAINWINDOW_H
