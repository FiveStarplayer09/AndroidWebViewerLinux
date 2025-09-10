#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FiveStarPlayerVS.h"

// આગળની ઘોષણાઓ (Forward declarations)
class QLineEdit;
class QWebEngineView;

class FiveStarPlayerVS : public QMainWindow
{
    Q_OBJECT

public:
    // કન્સ્ટ્રક્ટરને પ્રોક્સી સ્ટ્રિંગ મેળવવા માટે અપડેટ કર્યું
    FiveStarPlayerVS(const QString& proxyString = "", QWidget* parent = nullptr);
    ~FiveStarPlayerVS();

private:
    Ui::FiveStarPlayerVSClass* ui;

    // આપણા UI ઘટકો માટે વેરિએબલ
    QLineEdit* addressBar;
    QWebEngineView* webView;
};