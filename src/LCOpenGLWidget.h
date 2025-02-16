#ifndef LCOPENGLWIDGET_H
#define LCOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>

class Triangle;
class Triangle_1;

class LCOpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_4_5_Core
{
public:
    LCOpenGLWidget(QWidget *parent = nullptr);
    virtual ~LCOpenGLWidget();

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;

private:
    Triangle_1                    *mp_Triangle;
};

#endif // LCOPENGLWIDGET_H
