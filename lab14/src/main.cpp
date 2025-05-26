#include <auroraapp.h>
#include <QtQuick>
#include "systemservice.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.template"));
    application->setApplicationName(QStringLiteral("laba14"));

    SystemService service;

    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    view->rootContext()->setContextProperty("systemService", &service);
    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/laba14.qml")));
    view->show();

    return application->exec();
}
