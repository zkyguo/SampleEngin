#include "seopenglwidget.h"
float vertices[] = {
//Position           Color
0.5f, 0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
-0.5f, 0.5f, 0.0f,   0.5f, 0.5f, 0.5f

};

unsigned int indices [] =
{
    0,1,3,
    1,2,3
};
unsigned int VBO, VAO, EBO;

seopenglwidget::seopenglwidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

seopenglwidget::~seopenglwidget()
{

    makeCurrent(); // call current state
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    doneCurrent();// quit current state
}

void seopenglwidget::drawShape(seopenglwidget::Shape sh)
{

    m_shape = sh;
    update();
}

void seopenglwidget::setWireFrame(bool isWire)
{
    makeCurrent();

    if(isWire)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    update();
    doneCurrent();
}

void seopenglwidget::initializeGL()
{
    initializeOpenGLFunctions();
    bool success;
    success = shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/Shaders/vertexShader.vert");
    success = shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/Shaders/fragShader.frag");
    success = shaderProgram.link();
    if(!success) qDebug()<<"ERROR : " << shaderProgram.log();

    //Create VAO VBO EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1,&EBO);

    //Bind VAO VBO EBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    //Bind data to GPU buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (indices), indices, GL_STATIC_DRAW);

    //Find attribute location in Shader
    GLint posLocation = shaderProgram.attributeLocation("aPos");
    //Tell GPU how to interpete buffer
    glVertexAttribPointer(posLocation,3, GL_FLOAT, GL_FALSE, 6*sizeof (float), 0);
    //Enable the firste value of VAO
    glEnableVertexAttribArray(posLocation);
    //color attribute
    glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, 6 *  sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

}

void seopenglwidget::resizeGL(int w, int h)
{

}

void seopenglwidget::paintGL()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shaderProgram.bind();
    switch(m_shape)
    {
        case Rect:
            glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        break;
    }
}
