#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// OpenTES4 Core includes.
#include "bsa.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();
    void on_actionOpen_triggered();

private:
    Ui::MainWindow* ui;

    std::vector<BSA::BSA> filesBSA;
};

#endif // MAINWINDOW_H
