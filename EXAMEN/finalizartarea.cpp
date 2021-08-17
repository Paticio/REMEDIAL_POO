#include "finalizartarea.h"
#include "ui_finalizartarea.h"
#include <QtDebug>
FinalizarTarea::FinalizarTarea(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FinalizarTarea)
{
    ui->setupUi(this);
    QStringList cabecera = {tr("Número"), tr("Nombre"), tr("Tipo"), tr("Fecha"), tr("Prioridad"), tr("Finalizada")};
    ui->outTareas->setColumnCount(6);
    ui->outTareas->setHorizontalHeaderLabels(cabecera);
    cargarTabla();
}

FinalizarTarea::~FinalizarTarea()
{
    delete ui;
}

void FinalizarTarea::cargarTabla()
{
    QFile archivo("Tareas.txt");
    QTextStream io;
    archivo.open(QIODevice::ReadOnly | QIODevice::Text);
    io.setDevice(&archivo);
    while(!io.atEnd())
    {
        auto linea = io.readLine();
        m_tareas =linea.split(";");
        Principal::m_numero++;
        int fila = ui->outTareas->rowCount();
        ui->outTareas->insertRow(fila);
        ui->outTareas->setItem(fila,0,new QTableWidgetItem(QString::number(Principal::m_numero)));
        ui->outTareas->setItem(fila,1,new QTableWidgetItem(m_tareas.at(1)));
        ui->outTareas->setItem(fila,2,new QTableWidgetItem(m_tareas.at(4)));
        ui->outTareas->setItem(fila,3,new QTableWidgetItem(m_tareas.at(2)));
        ui->outTareas->setItem(fila,4,new QTableWidgetItem(prioridadToString(m_tareas.at(3))));
        ui->outTareas->setItem(fila,5,new QTableWidgetItem(finalizadaToString(m_tareas.at(5))));
    }
    archivo.close();
}

QString FinalizarTarea::prioridadToString(QString prioridad)
{
    if(prioridad == "A")
        return tr("Alta");
    else if(prioridad == "M")
        return tr("Media");
    else
        return tr("Baja");
}

QString FinalizarTarea::finalizadaToString(QString finalizado)
{
    if(finalizado == "0")
        return tr("No Finalizado");
    else
        return tr("Finalizado");
}

bool FinalizarTarea::finalizar()
{
    int numero = ui->inNumero->value();
    QFile archivo("Tareas.txt");
    QTextStream io;
    archivo.open(QIODevice::ReadWrite | QIODevice::Text);
    io.setDevice(&archivo);
    while(!io.atEnd())
    {
        auto linea = io.readLine();
        auto valores =linea.split(";");
        if(QString::number(numero) == valores.at(0))
        {
            io << valores.at(0) << ";" << valores.at(1) << ";" << valores.at(2) << ";" << valores.at(3) << ";" << valores.at(4) << ";1" << endl;
            return true;
        }
        else
            continue;
    }
    return false;
}

void FinalizarTarea::on_cmdFinalizar_released()
{
    if(!finalizar())
    {
        QMessageBox::warning(this, tr("Precaucion"), tr("No existe el número proporcionado"));
        return;
    }
    Principal::m_numero = 0;
    this->close();
    Principal *principal = new Principal();
    principal->show();
}
