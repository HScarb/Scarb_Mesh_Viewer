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

void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open a file.");

    if(!filePath.isEmpty())
    {
        QFile file(filePath);
        if(file.open(QFile::ReadOnly | QFile::Text))
        {
            m_filePath = filePath;
            QTextStream in(&file);
            QString text = in.readAll();

            ui->textEdit->setPlainText(filePath);
            ui->widget->loadMesh("filePath");

            statusBar()->showMessage(tr("File loaded"), 2000);

            file.close();
        }
        else
        {
            QMessageBox::warning(this, tr("Application"),
                                 tr("Cannot read file %1:\n%2.")
                                 .arg(QDir::toNativeSeparators(filePath), file.errorString()));
            return;

        }
    }
}
