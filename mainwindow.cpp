#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->rotXSlider, &QSlider::valueChanged, ui->widget, &GLWidget::setXRotation);
    connect(ui->widget, &GLWidget::xRotationChanged, ui->rotXSlider, &QSlider::setValue);
    connect(ui->rotYSlider, &QSlider::valueChanged, ui->widget, &GLWidget::setYRotation);
    connect(ui->widget, &GLWidget::yRotationChanged, ui->rotYSlider, &QSlider::setValue);
    connect(ui->rotZSlider, &QSlider::valueChanged, ui->widget, &GLWidget::setZRotation);
    connect(ui->widget, &GLWidget::zRotationChanged, ui->rotZSlider, &QSlider::setValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}
