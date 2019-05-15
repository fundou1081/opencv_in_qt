#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QWidget>

class MyGLWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = nullptr);

signals:

public slots:

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

#endif // MYGLWIDGET_H
