/*
 * AboutWindow.cpp
 *
 *  Created on: 13.08.2018
 *      Author: Felix Wohlfrom
 */

#include "AboutWindow.h"
#include "ui_AboutWindow.h"

#include <QDateTime>

#include "Version.h"
#include "Timestamp.h" // Auto generated by cmake

AboutWindow::AboutWindow(QWidget* parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint
        | Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint),
    ui(new Ui::AboutWindow)
{
    // Initialize window
    ui->setupUi(this);

    QString version =
            tr("Version %1.%2")
                .arg(QString::number(VERSION_MAJOR), QString::number(VERSION_MINOR));
    #ifdef VERSION_BETA
        version += " " + tr("beta");
    #endif
    #ifdef _DEBUG
        version += " " + tr("Debug");
    #endif
    ui->version->setText(version);

    // The build information
    ui->compiler->setText(getCompiler());
    ui->compilerFlags->setText(getCompilerFlags());
    ui->qtVersion->setText(QT_VERSION_STR);

    // The timestamp is generated on build time as UTC timestamp in ISO 8601
    // We convert this here to use the format
    QDateTime timestamp = QDateTime::fromString(_TIMESTAMP_, Qt::ISODate);
    ui->buildTimestamp->setText(timestamp.toString(Qt::SystemLocaleLongDate));

    this->layout();
}

AboutWindow::~AboutWindow()
{
    delete ui;
}

QString AboutWindow::getCompiler()
{
    #ifdef __GNUG__
        QString compiler = QString("GCC %1.%2.%3").arg(
                            QString::number(__GNUC__),
                            QString::number(__GNUC_MINOR__),
                            QString::number(__GNUC_PATCHLEVEL__));
        #ifdef __x86_64
            compiler += " (x64)";
        #endif
        return compiler;
    #elif defined _MSC_VER
        #if _MSC_VER == 1900
            QString compiler = "Visual Studio 2015";
        #elif _MSC_VER == 1800
            QString compiler = "Visual Studio 2013";
        #elif _MSC_VER == 1700
            QString compiler = "Visual Studio 2012";
        #elif _MSC_VER == 1600
            QString compiler = "Visual Studio 2010";
        #else
            QString compiler = QString("Visual C++ (%1)")
                .arg(QString::number(_MSC_VER));
        #endif
        #ifdef _WIN64
            compiler += " (x64)";
        #endif
        return compiler;
    #else
        return "Unknown compiler";
    #endif
}

QString AboutWindow::getCompilerFlags()
{
    #ifdef _DEBUG
        #ifdef USED_CXXFLAGS_DEBUG
            return QString(USED_CXXFLAGS_DEBUG);
        #else
            return "";
        #endif
    #elif defined USED_CXXFLAGS
        return QString(USED_CXXFLAGS);
    #else
        return "";
    #endif
}
