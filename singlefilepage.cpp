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

#include "singlefilepage.h"
#include "dsvgrenderer.h"
#include "utils.h"

#include <QFormLayout>
#include <QPushButton>
#include <QDebug>

SingleFilePage::SingleFilePage(QWidget *parent)
    : QWidget(parent),
      m_appNameLabel(new QLabel),
      m_versionLabel(new QLabel),
      m_infoLabel(new QLabel),
      m_installBtn(new DSuggestButton("Install")),
      m_spinner(new DSpinner)
{
    m_appNameLabel->setWordWrap(true);
    m_versionLabel->setWordWrap(true);
    m_infoLabel->setWordWrap(true);

    const qreal ratio = devicePixelRatioF();
    QLabel *iconLabel = new QLabel;
    QPixmap iconPixmap = DSvgRenderer::render(":/images/icon.svg", QSize(88, 88) * ratio);
    iconPixmap.setDevicePixelRatio(ratio);
    iconLabel->setPixmap(iconPixmap);
    iconLabel->setFixedSize(88, 88);

    QVBoxLayout *layout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout;

    m_installBtn->setFixedSize(100, 38);
    m_installBtn->setVisible(false);
    m_spinner->setVisible(false);

    formLayout->setLabelAlignment(Qt::AlignRight);
    formLayout->setHorizontalSpacing(10);
    formLayout->setVerticalSpacing(7);
    formLayout->setContentsMargins(20, 0, 20, 0);

    formLayout->addRow(new QLabel("Name:"), m_appNameLabel);
    formLayout->addRow(new QLabel("Version:"), m_versionLabel);
    formLayout->addRow(new QLabel("Description:"), m_infoLabel);

    m_spinner->setFixedSize(35, 35);

    layout->addWidget(iconLabel, 0, Qt::AlignHCenter);
    layout->addSpacing(20);
    layout->addLayout(formLayout);
    layout->addStretch();
    layout->addWidget(m_installBtn, 0, Qt::AlignHCenter);
    layout->addWidget(m_spinner, 0, Qt::AlignHCenter);
    layout->addSpacing(10);

    connect(m_installBtn, &DSuggestButton::clicked, this, [=] {
        m_installBtn->setVisible(false);
        m_spinner->setVisible(true);
        m_spinner->start();

        bool isInstall = Utils::install(m_filePath);

        if (isInstall) {
            qDebug() << "安装成功";
        } else {
            qDebug() << "安装失败";
        }

        m_installBtn->setVisible(true);
        m_spinner->setVisible(false);
        m_spinner->stop();
    });
}

SingleFilePage::~SingleFilePage()
{
}

void SingleFilePage::setFilePath(const QString &filePath)
{
    m_filePath = filePath;

    auto infos = Utils::getInfo(filePath);

    m_appNameLabel->setText(std::get<0>(infos));
    m_versionLabel->setText(std::get<1>(infos));
    m_infoLabel->setText(std::get<2>(infos));
    m_spinner->setVisible(false);
    m_installBtn->setVisible(true);
}
