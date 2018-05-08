#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMessageBox>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
    connect(ui.buttonBox->button(QDialogButtonBox::RestoreDefaults), &QPushButton::clicked, this, &MainWindow::onAutoSetButton_clicked);
    connect(ui.buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked, this, &MainWindow::onSaveCFGButton_clicked);
    connect(ui.buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &MainWindow::onCancelButton_clicked);

    // Product type is the system type, for example,
    //    macos, winrt, etc.
    //    This term is useful because the paths are
    //    different on each system.
    cfgp.productType = QSysInfo::productType();
    cfgp.productVersion = QSysInfo::productVersion();
    cfgp.CFGAppPath = QCoreApplication::applicationDirPath();

    // In MacOS, the application should end with .app, but the above
    //    function gives the path to the excutable file, which is
    //    the right path, but I prefer the one with .app.
    //    In this way, users are unlikely to chose a wrong path if
    //    not familiar with Mac application system.
    cfgp.CFGAppPath.remove(QRegularExpression("/Contents/MacOS$"));
    ui.cfgPathEdit->setText(cfgp.CFGAppPath);
}

QByteArray MainWindow::readJsonFile(const QString &filename)
{
    QFile f(filename);
    if (!f.open(QFile::ReadOnly | QFile::Text))
        return {};
    return f.readAll();
}

void MainWindow::writeJsonFile(const QString &filename, const QByteArray &contents)
{
    QFile f(filename);
    if (f.open(QFile::WriteOnly | QFile::Text))
        f.write(contents);
}

void MainWindow::readConfigFile()
{
    QByteArray var = readJsonFile(cfgp.cfgFilePath);
    QJsonDocument doc = QJsonDocument::fromJson(var);
    cfgp.setFromJsonObject(doc.object());
}

void MainWindow::writeConfigFile() const
{
    // Preserve the configuration file contents; only
    // update our configuration.
    QByteArray var = readJsonFile(cfgp.cfgFilePath);
    QJsonDocument doc = QJsonDocument::fromJson(var);
    QJsonObject obj = doc.object();
    cfgp.setToJsonObject(obj);
    doc.setObject(obj);
    writeJsonFile(cfgp.cfgFilePath, doc.toJson());
}

void MainWindow::dirAssert()
{
    if(QDir(cfgp.ResourcePath).exists())
    {
        ;
    }
    else
    {
        QDir().mkdir(cfgp.ResourcePath);
    }

    if(QDir(cfgp.mapImagePath).exists())
    {
        ;
    }
    else
    {
        QDir().mkdir(cfgp.mapImagePath);
    }

    if(QDir(cfgp.xbeeAddrPath).exists())
    {
        ;
    }
    else
    {
        QDir().mkdir(cfgp.xbeeAddrPath);
    }

    if(QDir(cfgp.logFilePath).exists())
    {
        ;
    }
    else
    {
        QDir().mkdir(cfgp.logFilePath);
    }
}

void MainWindow::onSaveCFGButton_clicked()
{
    cfgp.mapType = ui.mapTypeComboBox->currentText();
    dirAssert();
    writeConfigFile();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::information(this, "Saved", "Configuration file saved.",
                                    QMessageBox::Ok);
    QApplication::quit();
}

void MainWindow::setUI()
{
    ui.resourcePathEdit->setText(cfgp.ResourcePath);
    ui.mapResourceEdit->setText(cfgp.mapImagePath);
    ui.mapIndexPathEdit->setText(cfgp.mapIndexPath);
    ui.xbeeAddrEdit->setText(cfgp.xbeeAddrPath);
    ui.logPathEdit->setText(cfgp.logFilePath);

    ui.zoomLevelEdit->setText(cfgp.zoomLevel);
    ui.mapKeyEdit->setText(cfgp.mapKey);
}

void MainWindow::onCancelButton_clicked()
{
    return;
    QApplication::quit();
}

void MainWindow::on_mainPathBrowseButton_clicked()
{
    if (cfgp.productType == "osx")
    {
        QString fileName = QFileDialog::getOpenFileName(this, "Choose App File", "", "App Package (*.app);;All files (*.*)");
        if (fileName.length() > 0)
        {
            if (fileName.endsWith("QTGCS.app"))
            {
                //qDebug() << fileName;
                appPath = fileName;
                cfgp.GCSAppPath = fileName;
                ui.mainPathEdit->setText(cfgp.GCSAppPath);
                cfgFilePath = fileName + "/Contents/MacOS/config.json";
                cfgp.cfgFilePath = cfgFilePath;
                readConfigFile();
                setUI();
            }
            else
            {
                QMessageBox::StandardButton reply;
                reply = QMessageBox::critical(this, "Error", "Please choose the valid application.",
                                                QMessageBox::Ok);
            }
        }
    }
    else if (cfgp.productType == "macos")
    {;}
    else if (cfgp.productType == "ios")
    {;}
    else if (cfgp.productType == "tvos")
    {;}
    else if (cfgp.productType == "watchos")
    {;}
    else if (cfgp.productType == "darwin")
    {;}
    else if (cfgp.productType == "android")
    {;}
    else if (cfgp.productType == "debian")
    {;}
    else if (cfgp.productType == "winrt")
    {;}
    else if (cfgp.productType == "windows")
    {;}
    else if (cfgp.productType == "unknown")
    {;}
    else
    {;}
    /*
    QString fileName = QFileDialog::getOpenFileName(this, "Choose App File", "", "App Package (*.app);;All files (*.*)");
    if (fileName.length() > 0)
    {
        qDebug() << fileName;
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Cannot open file";
        }
    }*/
}

void MainWindow::on_cfgAppBrowseButton_clicked()
{

}

void MainWindow::on_resourceBrowseButton_clicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(this, "Choose Resource Directory", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (dirPath.length() > 0)
    {
        if (true)
        {
            //qDebug() << dirPath;
            cfgp.ResourcePath = dirPath + "/";
            ui.resourcePathEdit->setText(cfgp.ResourcePath);
            cfgp.mapImagePath = dirPath + "/mapscache/";
            ui.mapResourceEdit->setText(cfgp.mapImagePath);
            cfgp.mapIndexPath = dirPath + "/mapcache.txt";
            ui.mapIndexPathEdit->setText(cfgp.mapIndexPath);
        }
        else
        {
            // Not used now, check back later.
            QMessageBox::StandardButton reply;
            reply = QMessageBox::critical(this, "Error", "Please choose the valid application.",
                                            QMessageBox::Ok);
        }
    }
}

void MainWindow::onAutoSetButton_clicked()
{
    cfgp.mapImagePath = cfgp.ResourcePath + "mapscache/";
    cfgp.mapIndexPath = cfgp.ResourcePath + "mapcache.txt";
    cfgp.xbeeAddrPath = cfgp.ResourcePath + "xbeeaddr/";
    cfgp.logFilePath = cfgp.ResourcePath + "log/";
    setUI();
}
