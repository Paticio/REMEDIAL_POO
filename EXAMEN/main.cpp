/***************************************************************************
 *                                                                         *
 *   Administrador de Tareas                                               *
 *                                                                         *
 *   Steven Borja                                                          *
 *   sborjac2@est.ups.edu.ec                                               *
 *                                                                         *
 ***************************************************************************/

#include "principal.h"
#include <QApplication>
#include <QTranslator>
#include <QInputDialog>

int Principal::m_numero = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Crea un objeto para manejar las traducciones
    QTranslator traduccion;

    //Crear lista de idiomas
    QStringList idiomas;
    idiomas << "Ingles" << "Español";
    //Soliticar al usuario que elija el usuario
    QString idiomaSel = QInputDialog::getItem(NULL, "Idioma", "Seleccione el idioma: ", idiomas);

    //Evaluar el idioma seleccionado
    if(idiomaSel == "Ingles")
        traduccion.load(":/traducciones/Traducciones/examen_borja_steven_en_US.qm");
    else
        traduccion.load(":/traducciones/Traducciones/examen_borja_steven_es_EC.qm");

    //Establecer un idioma a la aplicacion
    a.installTranslator(&traduccion);

    Principal w;
    w.show();
    return a.exec();
}
