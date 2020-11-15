#pragma once

#include <QMainWindow>

#include "CTimeLineView.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    CTimeLineView *view;

private slots:
    void on_actionRemove_triggered();

private:

    Ui::MainWindow *ui;


};

