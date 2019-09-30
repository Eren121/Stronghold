#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QBuffer>

#include "System.h"
#include <format/Header.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionImport_Siege, SIGNAL(triggered()), this, SLOT(importSiege()));
    connect(ui->actionExport_Siege, SIGNAL(triggered()), this, SLOT(exportSiege()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::importSiege()
{
    const QString defaultDir(System::getS2hInstallFolder() + "/maps");
    QString fileName(QFileDialog::getOpenFileName(this, "Open Siege Map", defaultDir, "Siege file (*.s2c)"));

    if(fileName.isEmpty()) {
        return;
    }

    QString myMap = System::getSh2UserFolder();
    QFileInfo fileInfoIn(fileName);

    myMap += "/Maps/";
    myMap += fileInfoIn.fileName();

    QFileInfo fileInfo(myMap);
    QFile file(fileInfo.path() + "/" + fileInfo.completeBaseName() + ".s2m");

    if(file.open(QIODevice::WriteOnly)) {

        QFile fileIn(fileName);

        if(fileIn.open(QIODevice::ReadOnly)) {

            QDataStream input(&fileIn);
            input.setByteOrder(QDataStream::LittleEndian);
            QDataStream output(&file);
            output.setByteOrder(QDataStream::LittleEndian);

            convertToS2M(input, output);
            file.close();
            fileIn.close();
        }
        else {

            QMessageBox::critical(this, "Error", QString("Cannot open file '%1'").arg(fileName));
        }
    }
    else {

        QMessageBox::critical(this, "Error", QString("Cannot write to file '%1'").arg(myMap));
    }
}

void MainWindow::exportSiege()
{
    const QString defaultDir(System::getSh2UserFolder() + "/Maps");
    QString fileName(QFileDialog::getOpenFileName(this, "Open Siege Map", defaultDir, "Map file (*.s2m)"));

    if(fileName.isEmpty()) {
        return;
    }

    QString map = System::getS2hInstallFolder();
    QFileInfo fileInfoIn(fileName);


    map += "/maps/";
    map += fileInfoIn.fileName();

    QFileInfo fileInfo(map);
    QFile file(fileInfo.path() + "/" + fileInfo.completeBaseName() + ".s2c");

    if(file.open(QIODevice::WriteOnly)) {

        QFile fileIn(fileName);

        if(fileIn.open(QIODevice::ReadOnly)) {

            QDataStream input(&fileIn);
            input.setByteOrder(QDataStream::LittleEndian);
            QDataStream output(&file);
            output.setByteOrder(QDataStream::LittleEndian);

            convertToS2C(input, output);
            file.close();
            fileIn.close();
        }
        else {

            QMessageBox::critical(this, "Error", QString("Cannot open file '%1'").arg(fileName));
        }
    }
    else {

        QMessageBox::critical(this, "Error", QString("Cannot write to file '%1'").arg(map));
    }
}

void MainWindow::convertToS2M(QDataStream& input, QDataStream& output)
{
    Header header;
    header.readObject(input);
    header.loadIntoView(*ui->treeWidget);

    header.removeAuthor();
    header.set("type", "warcampaign");
    header.writeObject(output);

    // Read remaining data
    QByteArray raw = input.device()->readAll();
    output.writeRawData(raw, raw.size());
}

void MainWindow::convertToS2C(QDataStream &input, QDataStream &output)
{
    Header header;
    header.readObject(input);
    header.loadIntoView(*ui->treeWidget);



    header.set("type", "historical");
    //header.writeObject(output);

    // Read remaining data
    QByteArray raw = input.device()->readAll();
    output.writeRawData(raw, raw.size());
}
