#ifndef AGREGARTAREA_H
#define AGREGARTAREA_H

#include <QDialog>
#include <QFile>
#include <QIODevice>
#include <QDate>
#include "principal.h"
namespace Ui {
class AgregarTarea;
}

class AgregarTarea : public QDialog
{
    Q_OBJECT

public:
    explicit AgregarTarea(QWidget *parent = nullptr, int numero = 0);
    ~AgregarTarea();
    void guardar();
    bool estaFinalizado();
    char prioridad() const;

private slots:
    void on_cmdAgregar_released();

private:
    Ui::AgregarTarea *ui;
    QFile archivo;
    int m_numero;
    QString m_nombre;
    QDate m_fecha;
    char m_prioridad;
    QString m_tipo;
    bool m_finalizado;

};

#endif // AGREGARTAREA_H
