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
    FiveStarPlayerVS(QWidget* parent = nullptr);
    ~FiveStarPlayerVS();

private:
    Ui::FiveStarPlayerVSClass* ui; // ui ને પોઇન્ટર તરીકે જાહેર કર્યું

    // આપણા UI ઘટકો માટે વેરિએબલ
    QLineEdit* addressBar;
    QWebEngineView* webView;
};