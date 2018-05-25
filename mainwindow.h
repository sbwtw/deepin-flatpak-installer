#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include "homepage.h"
#include "singlefilepage.h"

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    HomePage *m_homePage;
    SingleFilePage *m_singleFilePage;

    QList<QString> m_filePaths;
};

#endif // MAINWINDOW_H

