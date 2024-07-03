#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>

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
    void on_compareButton_clicked();
    void on_actionOpenFirstFile_triggered();
    void on_actionOpenSecondFile_triggered();
    void on_actionSaveResult_triggered();

    void on_action_2_triggered();

private:
    Ui::MainWindow *ui;
    QTableWidget *tableWidget1;
    QTableWidget *tableWidget2;
    QTableWidget *tableWidgetResult;
    QPushButton *compareButton;
    void loadFileData(QTableWidget *tableWidget, const QString &fileName, int columnCount);
    void saveFileData(QTableWidget *tableWidget, const QString &fileName);
};

#endif // MAINWINDOW_H
