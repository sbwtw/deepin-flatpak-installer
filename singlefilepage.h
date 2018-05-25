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

#ifndef SINGLEFILEPAGE_H
#define SINGLEFILEPAGE_H

#include <QWidget>
#include <QLabel>

class SingleFilePage : public QWidget
{
    Q_OBJECT

public:
    SingleFilePage(QWidget *parent = nullptr);
    ~SingleFilePage();

    void setFilePath(const QString &filePath);

private:
    QLabel *m_appNameLabel;
    QLabel *m_versionLabel;
    QLabel *m_infoLabel;
};

#endif
