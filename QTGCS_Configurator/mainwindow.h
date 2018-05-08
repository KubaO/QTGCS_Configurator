#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

#include "configureproperty.h"
#include "ui_mainwindow.h"

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QString appPath;
    QString currentWorkingPath;
    QString cfgFilePath;
    ConfigureProperty cfgp;
    static QByteArray readJsonFile(const QString &filename);
    static void writeJsonFile(const QString &filename, const QByteArray &contents);
    void readConfigFile();
    void writeConfigFile() const;
    void setUI();
    void dirAssert();

private slots:
    void onAutoSetButton_clicked();
    void onSaveCFGButton_clicked();
    void onCancelButton_clicked();
    void on_mainPathBrowseButton_clicked();
    void on_cfgAppBrowseButton_clicked();
    void on_resourceBrowseButton_clicked();

private:
    Ui::MainWindow ui;
};

#endif // MAINWINDOW_H
