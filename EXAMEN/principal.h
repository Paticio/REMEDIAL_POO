#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "agregartarea.h"
#include "finalizartarea.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();
    void cargarTabla();
    static int m_numero;

private slots:
    void on_cmdAgregar_released();
    void on_cmdFinalizar_released();
    void on_actionSalir_triggered();

private:
    Ui::Principal *ui;
    QStringList m_tareas;
    int m_numero2;
    QColor m_color;
    void cargarColor(QString prioridad);
};
#endif // PRINCIPAL_H
