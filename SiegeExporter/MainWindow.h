#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void convertToS2M(QDataStream& input, QDataStream& output);
    void convertToS2C(QDataStream& input, QDataStream& output);

public slots:
    void importSiege();
    void exportSiege();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
