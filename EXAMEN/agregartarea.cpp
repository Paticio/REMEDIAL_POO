#include "agregartarea.h"
#include "ui_agregartarea.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QtDebug>
AgregarTarea::AgregarTarea(QWidget *parent, int numero) :
    QDialog(parent),
    ui(new Ui::AgregarTarea)
{
    m_numero = numero;
    ui->setupUi(this);
}

AgregarTarea::~AgregarTarea()
{
    delete ui;
}

void AgregarTarea::guardar()
{
    QFile f("Tareas.txt");
    QTextStream out(&f);
    f.open(QIODevice::WriteOnly | QIODevice::Append);

    //Guardar el contenido
    out << m_numero << ";" << m_nombre.mid(0,80) << ";" << m_fecha.toString("dd/MM/yyyy") << ";" << m_prioridad << ";" << m_tipo << ";" << m_finalizado << endl;
    f.close();
}

bool AgregarTarea::estaFinalizado()
{
    if(ui->inFinalizada->isChecked())
        return true;
    return false;
}

char AgregarTarea::prioridad() const
{
    if(ui->cmdAlta->isChecked())
        return 'A';
    else if(ui->cmdMedia->isChecked())
        return 'M';
    else if(ui->cmdBaja->isChecked())
        return 'B';
    else
        return 'n';
}

void AgregarTarea::on_cmdAgregar_released()
{
    m_nombre = ui->inTarea->text();
    if(m_nombre.isEmpty())
    {
        QMessageBox::warning(this, tr("Precaucion"), tr("Debe ingresar la tarea!"));
        return;
    }
    m_fecha = ui->inFecha->date();
    m_prioridad = prioridad();
    if(m_prioridad == 'n')
    {
        QMessageBox::warning(this, tr("Precaucion"), tr("Debe ingresar la prioridad de la tarea!"));
        return;
    }
    m_tipo = ui->inTipo->text();
    if(m_tipo.isEmpty())
    {
        QMessageBox::warning(this, tr("Precaucion"), tr("Debe ingresar el tipo de tarea!"));
        return;
    }
    m_finalizado = estaFinalizado();
    guardar();

    this->close();
    Principal *principal = new Principal();
    principal->show();
}
