#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->calcButton, &QPushButton::clicked, this, [this]() {
        // Получаем текст из полей ввода
        double num1 = ui->num1Input->text().toDouble();
        double num2 = ui->num2Input->text().toDouble();

        // Считаем сумму
        double sum = num1 + num2;

        // Выводим результат
        ui->resultLabel->setText("Результат: " + QString::number(sum));
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
