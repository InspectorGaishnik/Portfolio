#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->num1Input->setText("0");
    ui->num2Input->setText("0");
    ui->resultLabel->setText("Rotate the dial to change the numbers");

    ui->dial_1->setRange(0, 100);
    ui->dial_2->setRange(0, 100);

    ui->dial_1->setValue(0);
    ui->dial_2->setValue(0);

    connect(ui->calcButton, &QPushButton::clicked, this, [this]() {
        calculateAndShow();
    });

    calculateAndShow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculateAndShow() {
    num1 = ui->num1Input->text().toDouble();
    num2 = ui->num2Input->text().toDouble();
    res = num1 * num2;

    ui->resultLabel->setText(
        QString::number(num1) + " * " +
        QString::number(num2) + " = " +
        QString::number(res)
        );
}

void MainWindow::on_dial_1_valueChanged(int value)
{
    ui->num1Input->setText(QString::number(value));
    ui->dial_1->setToolTip("Number 1: " + QString::number(value));
    calculateAndShow();
}


void MainWindow::on_dial_2_valueChanged(int value)
{
    ui->num2Input->setText(QString::number(value));
    ui->dial_2->setToolTip("Number 2: " + QString::number(value));
    calculateAndShow();
}

