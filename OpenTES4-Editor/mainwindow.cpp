#include "mainwindow.h"
#include "ui_mainwindow.h"

// std includes.
#include <fstream>
#include <iostream>

// Qt includes.
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    BSA::BSA bsa;
    std::ifstream bsaFile("Oblivion - Misc.bsa", std::ios::binary);

    if (bsaFile.is_open()) {
        bsaFile >> bsa;
        bsaFile.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
