#include "FiveStarPlayerVS.h"
#include <QtWidgets/QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("Five Star Player");
    QApplication::setApplicationVersion("1.0.0");

    // કમાન્ડ-લાઇન આર્ગ્યુમેન્ટ્સને સમજવા માટે પાર્સર બનાવો
    QCommandLineParser parser;
    parser.setApplicationDescription("Android Web Viewer with dynamic proxy support.");
    parser.addHelpOption();
    parser.addVersionOption();

    // "--proxy-server" નામનો વિકલ્પ ઉમેરો જેની આપણે કમાન્ડ લાઇનમાં અપેક્ષા રાખીએ છીએ
    QCommandLineOption proxyOption("proxy-server", "Set the application proxy server, e.g., socks5://127.0.0.1:9050", "address");
    parser.addOption(proxyOption);

    // એપ્લિકેશનના આર્ગ્યુમેન્ટ્સને પ્રોસેસ કરો
    parser.process(a);

    // તપાસો કે શું "--proxy-server" વિકલ્પ આપવામાં આવ્યો છે
    QString proxyString = parser.value(proxyOption);

    // મુખ્ય વિન્ડો બનાવો અને તેને પ્રોક્સીની માહિતી આપો
    FiveStarPlayerVS w(proxyString);
    w.show();

    return a.exec();
}