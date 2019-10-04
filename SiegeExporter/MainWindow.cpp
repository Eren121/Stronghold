#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QBuffer>

#include "System.h"
#include "format/S2M.h"
#include <format/Header.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionImport_Siege, SIGNAL(triggered()), this, SLOT(importSiege()));
    connect(ui->actionExport_Siege, SIGNAL(triggered()), this, SLOT(exportSiege()));
    connect(ui->actionDezip, SIGNAL(triggered()), this, SLOT(dezipMap()));
    connect(ui->actionZip, SIGNAL(triggered()), this, SLOT(zipMap()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::importSiege()
{
    const QString defaultDir(System::getS2hInstallFolder() + "/maps");
    QString fileName(QFileDialog::getOpenFileName(this, "Open Siege Map", defaultDir, "Siege file (*.s2c);; Campaigns (*.s2m)"));

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

void MainWindow::dezipMap()
{
    const QString defaultDir(System::getSh2UserFolder() + "/Maps");
    QString fileName(QFileDialog::getOpenFileName(this, "Open Map", defaultDir, "Map file (*.s2m)"));

    if(fileName.isEmpty()) {
        return;
    }

    QFileInfo fileInfoIn(fileName);
    QFile fileIn(fileName);

    if(fileIn.open(QIODevice::ReadOnly)) {

        S2M s2m;
        QDataStream input(&fileIn);
        input.setByteOrder(QDataStream::LittleEndian);
        s2m.readObject(input);
        fileIn.close();

        {
            QFile fileOut(fileInfoIn.path() + "/" + fileInfoIn.completeBaseName() + "_head");

            if(fileOut.open(QIODevice::WriteOnly)) {

                QDataStream output(&fileOut);
                output.setByteOrder(QDataStream::LittleEndian);
                s2m.getHeader().writeObject(output);
                fileOut.close();
            }
            else {

                QMessageBox::critical(this, "Error", QString("Cannot open file '%1'").arg(fileOut.fileName()));
            }
        }

        for(int i = 0; i < 3; i++) {

            QFile fileOut(fileInfoIn.path() + "/" + fileInfoIn.completeBaseName() + "_" + QString('a' + i));

            if(fileOut.open(QIODevice::WriteOnly)) {

                QDataStream output(&fileOut);
                output.setByteOrder(QDataStream::LittleEndian);
                s2m.getData(i).setCompressed(false);
                s2m.getData(i).writeObject(output);
                fileOut.close();
            }
            else {

                QMessageBox::critical(this, "Error", QString("Cannot open file '%1'").arg(fileOut.fileName()));
            }
        }
    }
    else {

        QMessageBox::critical(this, "Error", QString("Cannot open file '%1'").arg(fileName));
    }
}

void MainWindow::zipMap()
{
    const QString defaultDir(System::getSh2UserFolder() + "/Maps");
    QString fileName(QFileDialog::getOpenFileName(this, "Open Map", defaultDir, "Data part (*_a; *_b; *_c)"));
    fileName.chop(2);

    if(fileName.isEmpty()) {
        return;
    }

    S2M s2m;

    {
        QFile fileIn(fileName + "_head");
        fileIn.open(QIODevice::ReadOnly);
        QDataStream input(&fileIn);
        input.setByteOrder(QDataStream::LittleEndian);
        s2m.getHeader().readObject(input);
        fileIn.close();

        s2m.getHeader().loadIntoView(*ui->treeWidget);
    }

    for(int i = 0; i < 3; i++) {

        QFile fileIn(fileName + "_" + QString('a' + i));
        fileIn.open(QIODevice::ReadOnly);

        QDataStream input(&fileIn);
        input.setByteOrder(QDataStream::LittleEndian);
        s2m.getData(i).setCompressed(false);
        s2m.getData(i).readObject(input);
        s2m.getData(i).setCompressed(true);
        fileIn.close();
    }

    QFile fileOut(fileName + ".s2m");
    fileOut.open(QIODevice::WriteOnly);
    QDataStream output(&fileOut);
    output.setByteOrder(QDataStream::LittleEndian);
    s2m.writeObject(output);
}

void MainWindow::convertToS2M(QDataStream& input, QDataStream& output)
{
    Header header;
    Primitive<QByteArray> raw;

    header.readObject(input);
    header.loadIntoView(*ui->treeWidget);

    header.removeAuthor();
    header.set("type", "kingmaker");
    header.writeObject(output);

    // Read remaining data
    raw.readObject(input);
    raw.writeObject(output);
}

void MainWindow::convertToS2C(QDataStream &input, QDataStream &output)
{
    Header header;
    Primitive<QByteArray> raw;

    header.readObject(input);
    header.loadIntoView(*ui->treeWidget);

    header.set("type", "historical");
    header.set("type", "kingmaker");
    header.writeObject(output);

    // Read remaining data
    raw.readObject(input);
    raw.writeObject(output);
}
