#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "logloader.h"
#include "gamewatcher.h"
#include "webuploader.h"
#include "Cards/deckcard.h"
#include "hscarddownloader.h"
#include "deckhandler.h"
#include "enemyhandhandler.h"
#include "arenahandler.h"
#include "secretshandler.h"
#include "drafthandler.h"
#include "Widgets/cardwindow.h"
#include <QMainWindow>
#include <QJsonObject>

#define DIVIDE_TABS_H 550//700 Rewards
#define DIVIDE_TABS_H2 850//1000 Rewards
#define DIVIDE_TABS_V 700


namespace Ui {
class Extended;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

//Constructor
public:
    explicit MainWindow(QWidget *parent = 0);
    MainWindow(QWidget *parent, MainWindow *primaryWindow);
    ~MainWindow();

private:
    enum WindowsFormation {H1, H2, H3, V2, None};

//Variables
private:
    Ui::Extended *ui;
    LogLoader *logLoader;
    GameWatcher *gameWatcher;
    WebUploader *webUploader;
    HSCardDownloader *cardDownloader;
    DeckHandler *deckHandler;
    EnemyHandHandler *enemyHandHandler;
    ArenaHandler *arenaHandler;
    SecretsHandler *secretsHandler;
    DraftHandler * draftHandler;
    CardWindow *cardWindow;
    QMap<QString, QJsonObject> cardsJson, enCardsJson;
    QPoint dragPosition;
    WindowsFormation windowsFormation;
    QFile* atLogFile;
    bool splitWindow;
    Transparency transparency;
    Theme theme;
    bool oneWindow;
    bool isMainWindow;
    MainWindow *otherWindow;
    int greyedHeight, cardHeight;
    int drawDisappear;
    bool showDraftOverlay;
    bool draftLearningMode;



//Metodos
public:
    void calculateMinimumWidth();

private:
    void createLogLoader();
    void createArenaHandler();
    void createGameWatcher();
    void createCardWindow();
    void createCardDownloader();
    void createDeckHandler();
    void createEnemyHandHandler();
    void createSecretsHandler();
    void createDraftHandler();
    void createWebUploader();
    void createVersionChecker();
    void readSettings();
    void writeSettings();
    void completeUI();
    void completeUIButtons();
    void completeConfigTab();
    void addDraftMenu(QPushButton *button);
    void spreadSplitWindow();
    void spreadTransparency();
    void updateOtherTabsTransparency();
    void spreadTheme();
    void updateMainUITheme();
    void updateButtonsTheme();
    void updateTabWidgetsTheme();
    void completeHeroButtons();
    QString getHSLanguage();
    void createCardsJsonMap(QMap<QString, QJsonObject> &cardsJson, QString lang);
    void resizeTabWidgets(QResizeEvent *event);
    void moveTabTo(QWidget *widget, QTabWidget *tabWidget);
    void resetSettings();
    void createLogFile();
    void closeLogFile();
    void createSecondaryWindow();
    void destroySecondaryWindow();
    void checkHSCardsDir();
    void calculateDeckWindowMinimumWidth();
    void initConfigTab(int tooltipScale);
    void moveInScreen(QPoint pos, QSize size);
    int getScreenHighest();
    void completeHighResConfigTab();
    void test();

//Override events
protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;

//Slots
public slots:
    //LogLoader
    void showLogLoadProgress(qint64 logSeek);
    void initCardsJson();

    //GameWatcher
    void showTabHeroOnNoArena();
    void resetDeck(bool deckRead=false);

    //WebUploader
    void resetDeckAlreadyRead();

    //Multi Handlers
    void checkCardImage(QString code);

    //HSCardDownloader
    void redrawDownloadedCardImage(QString code);

    //DraftHandler
    void uploadDeck();

    //Widgets
    void resizeSlot(QSize size);

    //MainWindow
    void pLog(QString line);
    void pDebug(QString line, DebugLevel debugLevel=Normal, QString file="MainWindow");
    void pDebug(QString line, qint64 numLine, DebugLevel debugLevel, QString file);

private slots:
    void synchronizedDone();
    void confirmNewArenaDraft(QString hero);
    void confirmClearDeck();
    void toggleSplitWindow();
    void transparentAlways();
    void transparentAuto();
    void transparentNever();
    void toggleDeckWindow();
    void updateTimeDraw(int value);
    void updateTamCard(int value);
    void toggleShowDraftOverlay();
    void toggleTheme();
    void toggleDraftLearningMode();
    void updateTooltipScale(int value);
};

#endif // MAINWINDOW_H
