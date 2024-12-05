#include "MainWindow.h"
#include "LCOpenGLWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mp_GLWidget(new LCOpenGLWidget(this))
{
    setCentralWidget(mp_GLWidget);
}

MainWindow::~MainWindow() {}
