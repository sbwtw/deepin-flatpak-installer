#include "mainwindow.h"
#include "dtitlebar.h"
#include "utils.h"

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent),
      m_homePage(new HomePage),
      m_singleFilePage(new SingleFilePage)
{
    // titlebar()->setIcon(QIcon(":/images/icon.svg"));
    titlebar()->setTitle(QString());

    setWindowIcon(QIcon(":/images/icon.svg"));
    setFixedSize(480, 380);

    setCentralWidget(m_homePage);

    connect(m_homePage, &HomePage::onSelected, this, [=] (const QStringList &filePaths) {
        m_filePaths << filePaths;

        if (m_filePaths.size() == 1) {
            m_singleFilePage->setFilePath(m_filePaths.first());
            setCentralWidget(m_singleFilePage);
        }
    });
}

MainWindow::~MainWindow()
{

}
