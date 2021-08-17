#ifndef FINALIZARTAREA_H
#define FINALIZARTAREA_H

#include <QDialog>

#include "principal.h"

namespace Ui {
class FinalizarTarea;
}

class FinalizarTarea : public QDialog
{
    Q_OBJECT

public:
    explicit FinalizarTarea(QWidget *parent = nullptr);
    ~FinalizarTarea();
    void cargarTabla();
    QString prioridadToString(QString prioridad);
    QString finalizadaToString(QString finalizado);
    bool finalizar();

private slots:
    void on_cmdFinalizar_released();

private:
    Ui::FinalizarTarea *ui;
    QStringList m_tareas;
};

#endif // FINALIZARTAREA_H
