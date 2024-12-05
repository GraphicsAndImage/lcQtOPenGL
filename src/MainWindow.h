#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class LCOpenGLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    LCOpenGLWidget      *mp_GLWidget;
};
#endif // MAINWINDOW_H
