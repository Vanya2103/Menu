#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QSet>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Найти виджеты и кнопку в интерфейсе
    tableWidget1 = ui->tableWidget1;
    tableWidget2 = ui->tableWidget2;
    tableWidgetResult = ui->tableWidget;
    compareButton = ui->pushButton;

    // Связать кнопку с обработчиком кликов
    connect(compareButton, &QPushButton::clicked, this, &MainWindow::on_compareButton_clicked);

    // Связать действия меню с соответствующими слотами
    connect(ui->openTextAction, &QAction::triggered, this, &MainWindow::on_actionOpenFirstFile_triggered);
    connect(ui->openBinaryAction, &QAction::triggered, this, &MainWindow::on_actionOpenSecondFile_triggered);
    connect(ui->saveTextAction, &QAction::triggered, this, &MainWindow::on_actionSaveResult_triggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFileData(QTableWidget *tableWidget, const QString &fileName, int columnCount)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось открыть файл: %1").arg(fileName));
        return;
    }

    QTextStream in(&file);
    tableWidget->clear();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(columnCount);

    int row = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        tableWidget->insertRow(row);
        for (int col = 0; col < fields.size(); ++col) {
            tableWidget->setItem(row, col, new QTableWidgetItem(fields[col].trimmed()));
        }
        row++;
    }
    file.close();
}

void MainWindow::saveFileData(QTableWidget *tableWidget, const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось открыть файл для записи: %1").arg(fileName));
        return;
    }

    QTextStream out(&file);
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < tableWidget->columnCount(); ++col) {
            rowData << tableWidget->item(row, col)->text();
        }
        out << rowData.join(",") << "\n";
    }
    file.close();
}

void MainWindow::on_compareButton_clicked()
{
    tableWidgetResult->clear();
    tableWidgetResult->setRowCount(0);
    tableWidgetResult->setColumnCount(3); // Имя, адрес, стоимость книги

    QSet<QString> returnedNames;
    for (int i = 0; i < tableWidget2->rowCount(); ++i) {
        returnedNames.insert(tableWidget2->item(i, 0)->text().trimmed());
    }

    int resultRow = 0;
    for (int i = 0; i < tableWidget1->rowCount(); ++i) {
        QString name = tableWidget1->item(i, 0)->text().trimmed();
        if (!returnedNames.contains(name)) {
            tableWidgetResult->insertRow(resultRow);
            for (int col = 0; col < 3; ++col) {
                tableWidgetResult->setItem(resultRow, col, new QTableWidgetItem(tableWidget1->item(i, col)->text().trimmed()));
            }
            resultRow++;
        }
    }
}

void MainWindow::on_actionOpenFirstFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть первый файл"), "", tr("Текстовые файлы (*.txt);;Все файлы (*)"));
    if (!fileName.isEmpty()) {
        loadFileData(tableWidget1, fileName, 3);
    }
}

void MainWindow::on_actionOpenSecondFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть второй файл"), "", tr("Текстовые файлы (*.txt);;Все файлы (*)"));
    if (!fileName.isEmpty()) {
        loadFileData(tableWidget2, fileName, 1);
    }
}

void MainWindow::on_actionSaveResult_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить результат"), "", tr("Текстовые файлы (*.txt);;Все файлы (*)"));
    if (!fileName.isEmpty()) {
        saveFileData(tableWidgetResult, fileName);
    }
}

void MainWindow::on_action_2_triggered()
{

}

