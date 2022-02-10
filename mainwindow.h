#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graf.h"
#include<QPushButton>
#include <QRadioButton>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void paintEvent(QPaintEvent *event);
    ~MainWindow();
private slots:
    void handleButton();
    void on_SaveGraf_released();
    void on_Orientat_clicked();
    void on_Neorientat_clicked();
    void on_pushButton_clicked();
private:
    Ui::MainWindow *ui;
    Graf g;
    Node firstNode, secondNode;
    bool drawNode, drawArc, isOriented;
    QPushButton *m_button;

};
#endif // MAINWINDOW_H
