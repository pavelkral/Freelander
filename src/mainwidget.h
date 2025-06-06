#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "TokenManager.h"
#include "GoogleClient.h"
#include "clickabletextedit.h"
#include "freelandercalendar.h"
#include "calendartabledelegate.h"
#include <QWidget>
#include <QSet>
#include <QSystemTrayIcon>
#include <QSettings>
#include <QCloseEvent>
#include <QPainter>
#include <QDir>
#include <QNetworkReply>

class QCalendarWidget;
class QTextEdit;
class QLineEdit;
class QDateTimeEdit;
class QPushButton;
class QNetworkReply;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

class MainWidget : public QWidget {

    Q_OBJECT

public:
     MainWidget(QWidget *parent=nullptr);
    ~MainWidget();
    void onDeleteClickedId(QString id);
    int m_retryCount = 0;
    const int MAX_RETRIES = 3; 
    const int RETRY_DELAY_SECONDS = 5; 
    QSettings settings;
    QString settingsFilePath = QCoreApplication::applicationDirPath() + QDir::separator() + "settings.ini";

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *) override;
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onTokenReady(const QString &token);
	void onApiRequestFailed(const QString& errormessage, QNetworkReply::NetworkError errorType);
    void onApiRequestSuccess(const QString& message);
    void onEventsFetched(const QString &text, const QSet<QDate> &dates);
    void onEventDetailsFetched(const QString &sum, const QDateTime &st, const QDateTime &en,const QString &eventId);
    void onCalendarPageChanged(int y,int m);
    void onEventClicked();
    void onCalendarDateActivated(const QDate &date);
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void calendarContextMenuRequested(const QPoint &pos) ;
    void handleDateClicked(const QDate &date);
    void handleLineClick();
    void openSettings();

private:
    Ui::MainWidget *ui;
    FreelanderCalendar *calendar;
    CalendarTableDelegate *tableWiewDelegate;    // wDelegate *delegate;
    ClickableTextEdit *textEdit;
    TokenManager  *tokenManager;
    GoogleClient  *googleClient;
    QString        selectedLine;
    QSystemTrayIcon *trayIcon;
    QPoint dragPosition;
    QDate lastClickedDate;
};

#endif // MAINWIDGET_H
