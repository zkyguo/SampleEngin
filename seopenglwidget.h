#ifndef SEOPENGLWIDGET_H
#define SEOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QImage>

class seopenglwidget : public QOpenGLWidget, QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    enum Shape{None, Rect, Circle, Triangle};
    explicit seopenglwidget(QWidget *parent = nullptr);
    ~seopenglwidget();
    void drawShape(Shape sh);
    void setWireFrame(bool isWire);
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
signals:

public slots:
private:
    Shape m_shape;
    QOpenGLShaderProgram shaderProgram;
    QOpenGLTexture * texture;

};

#endif // SEOPENGLWIDGET_H
