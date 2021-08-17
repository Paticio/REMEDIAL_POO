#include "principal.h"
#include "ui_principal.h"
#include <QtDebug>
Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    m_numero2 = 0;
    //Colocar la cabecera de la tabla
    QStringList cabecera = {tr("Número"), tr("Nombre"), tr("Tipo"), tr("Fecha")};
    ui->outTareas->setColumnCount(4);
    ui->outTareas->setHorizontalHeaderLabels(cabecera);
    cargarTabla();
}

Principal::~Principal()
{
    delete ui;
}

void Principal::cargarTabla()
{
    QFile archivo("Tareas.txt");
    QTextStream io;
    archivo.open(QIODevice::ReadOnly | QIODevice::Text);
    io.setDevice(&archivo);
    while(!io.atEnd())
    {
        auto linea = io.readLine();
        m_tareas =linea.split(";");
        m_numero2++;
        if(m_tareas.at(5) == "0")
        {
            cargarColor(m_tareas.at(3));
            m_numero++;
            int fila = ui->outTareas->rowCount();
            QTableWidgetItem *numero = new QTableWidgetItem(QString::number(m_numero));
            numero->setTextColor(m_color);

            QTableWidgetItem *nombre = new QTableWidgetItem(m_tareas.at(1));
            nombre->setTextColor(m_color);

            QTableWidgetItem *tipo = new QTableWidgetItem(m_tareas.at(4));
            tipo->setTextColor(m_color);

            QTableWidgetItem *fecha = new QTableWidgetItem(m_tareas.at(2));
            fecha->setTextColor(m_color);

            ui->outTareas->insertRow(fila);
            ui->outTareas->setItem(fila,0, numero);
            ui->outTareas->setItem(fila,1,nombre);
            ui->outTareas->setItem(fila,2,tipo);
            ui->outTareas->setItem(fila,3,fecha);
        }
    }
    archivo.close();
}

void Principal::on_cmdAgregar_released()
{
    this->close();
    AgregarTarea *agregar = new AgregarTarea(NULL, m_numero2 + 1);
    agregar->show();
    m_numero = 0;
}

void Principal::on_cmdFinalizar_released()
{
    if(m_numero == 0)
    {
        ui->statusbar->setStyleSheet("color: rgb(255, 48, 48);");
        ui->statusbar->showMessage(tr("No existen Tareas!"), 5000);
    }
    else
    {
        m_numero = 0;
        this->close();
        FinalizarTarea *finalizar = new FinalizarTarea();
        finalizar->show();
    }
}

void Principal::cargarColor(QString prioridad)
{
    if(prioridad == "A")
        m_color = QColor(Qt::red);
    else if(prioridad == "M")
        m_color = QColor(225, 99, 44);
    else
        m_color = QColor(240, 247, 84);
}

void Principal::on_actionSalir_triggered()
{
    this->close();
}
