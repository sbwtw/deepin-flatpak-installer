/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "utils.h"
#include <QSettings>
#include <QProcess>

Utils::Utils(QObject *parent)
    : QObject(parent)
{

}

Utils::~Utils()
{
}

std::tuple<QString, QString, QString> Utils::getInfo(const QString &filePath)
{
    QSettings config(filePath, QSettings::IniFormat);
    config.beginGroup("Flatpak Ref");

    const QString appName = config.value("Name").toString();
    const QString branch = config.value("Branch").toString();
    const QString info = config.value("Title").toString();

    return std::make_tuple(appName, branch, info);
}

bool Utils::install(const QString &filePath)
{
    QProcess *process = new QProcess;
    bool failed = false;

    process->start("pkexec", QStringList() << "flatpak" << "install" << filePath);
    process->waitForFinished(-1);
    failed |= process->exitCode();
    process->deleteLater();

    return !failed;
}
