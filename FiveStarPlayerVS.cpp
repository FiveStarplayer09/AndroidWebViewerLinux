#include "FiveStarPlayerVS.h"
#include "ui_FiveStarPlayerVS.h"

// બધા જરૂરી ઘટકો માટે હેડર ફાઈલો
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWebEngineView>
#include <QWebEngineProfile>
#include <QWebEnginePage>
#include <QStandardPaths>
#include <QWebEngineScript>
#include <QWebEngineSettings>
#include <QWebEngineScriptCollection>
#include <QScroller> // ટચ-સ્ક્રોલિંગ માટેની નવી હેડર ફાઇલ

FiveStarPlayerVS::FiveStarPlayerVS(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::FiveStarPlayerVSClass)
{
    ui->setupUi(this);

    // વિન્ડોનું શીર્ષક અને Pixel 7 જેવું કદ સેટ કરો
    this->setWindowTitle("Android Web Viewer");
    this->resize(412, 915); // Pixel 7 નું વાસ્તવિક રિઝોલ્યુશન

    // કેન્દ્રીય વિજેટ અને લેઆઉટ બનાવો
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    // એડ્રેસ બાર અને વેબ વ્યુ બનાવો
    addressBar = new QLineEdit(this);
    addressBar->setFont(QFont("Segoe UI", 10));
    webView = new QWebEngineView(this);

    layout->addWidget(addressBar);
    layout->addWidget(webView);
    setCentralWidget(centralWidget);

    // --- વ્યાપક JavaScript ઇન્જેક્શનનો કોડ ---
    QWebEngineScript script;
    QString source = R"(
        Object.defineProperty(navigator, 'platform', { get: () => 'Linux armv8l' });
        Object.defineProperty(navigator, 'vendor', { get: () => 'Google Inc.' });
        Object.defineProperty(navigator, 'userAgent', {
            get: () => 'Mozilla/5.0 (Linux; Android 13; Pixel 7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Mobile Safari/537.36'
        });
        Object.defineProperty(navigator, 'maxTouchPoints', { get: () => 5 });
        Object.defineProperty(navigator, 'deviceMemory', { get: () => 8 });
        Object.defineProperty(navigator, 'hardwareConcurrency', { get: () => 8 });
        Object.defineProperty(navigator, 'webdriver', { get: () => undefined });
    )";

    script.setSourceCode(source);
    script.setInjectionPoint(QWebEngineScript::DocumentCreation);
    script.setRunsOnSubFrames(true);
    script.setWorldId(QWebEngineScript::MainWorld);

    // --- પ્રોફાઇલ અને પેજ સેટઅપ ---
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QWebEngineProfile* profile = QWebEngineProfile::defaultProfile();
    profile->setPersistentStoragePath(dataPath);
    profile->setHttpUserAgent("Mozilla/5.0 (Linux; Android 13; Pixel 7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Mobile Safari/537.36");
    profile->setHttpAcceptLanguage("en-US,en;q=0.9");

    QWebEnginePage* page = new QWebEnginePage(profile, webView);
    page->scripts().insert(script); // સ્ક્રિપ્ટને પેજ સાથે જોડો
    webView->setPage(page);

    // વેબ એન્જિન સેટિંગ્સને મોબાઇલ જેવી બનાવો
    QWebEngineSettings* settings = webView->settings();
    settings->setAttribute(QWebEngineSettings::TouchIconsEnabled, true);
    settings->setAttribute(QWebEngineSettings::FocusOnNavigationEnabled, true);

    // --- ટચ અને સ્ક્રોલિંગ સુવિધાઓને સક્ષમ કરવી ---
    QScroller::grabGesture(webView->view(), QScroller::TouchGesture);
    settings->setAttribute(QWebEngineSettings::ScrollAnimatorEnabled, true);

    // શરૂઆતનો URL સેટ કરો
    webView->setUrl(QUrl("https://www.google.com"));

    // સિગ્નલ અને સ્લોટ
    connect(addressBar, &QLineEdit::returnPressed, [this]() {
        webView->setUrl(QUrl::fromUserInput(addressBar->text()));
        });

    connect(webView, &QWebEngineView::urlChanged, [this](const QUrl& url) {
        addressBar->setText(url.toString());
        });
}

FiveStarPlayerVS::~FiveStarPlayerVS()
{
    delete ui;
}