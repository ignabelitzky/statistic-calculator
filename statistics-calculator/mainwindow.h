#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLCDNumber>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel *titleLabel;
    QLabel *inputDataLabel;
    QLabel *countDataLabel;
    QLineEdit *inputDataLineEdit;
    QPushButton *saveDataButton;
    QLCDNumber *countDataDisplay;
    std::vector<float> *m_data = nullptr;
    float m_arithmeticMean;
    float m_median;
    float m_maximum;
    float m_minimum;

};
#endif // MAINWINDOW_H
