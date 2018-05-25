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

#include "homepage.h"
#include "dlinkbutton.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDebug>

DWIDGET_USE_NAMESPACE

HomePage::HomePage(QWidget *parent)
    : QWidget(parent)
{
	QVBoxLayout *layout = new QVBoxLayout(this);
    DLinkButton *openFileBtn = new DLinkButton("open file");

    layout->addWidget(openFileBtn);

    connect(openFileBtn, &DLinkButton::clicked, this, [=] {
        QFileDialog dialog;
        dialog.setFileMode(QFileDialog::ExistingFiles);
        dialog.setNameFilter("Flatpak files (*.flatpakref)");

        if (dialog.exec() == QDialog::Accepted) {
            qDebug() << dialog.selectedFiles();
            emit onSelected(dialog.selectedFiles());
        }
    });
}

HomePage::~HomePage()
{
}
