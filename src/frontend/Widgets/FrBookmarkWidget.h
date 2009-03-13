// class for displaying bookmarks

#ifndef FR_BOOKMARKWIDGET
#define FR_BOOKMARKWIDGET

class QAction;
class QTabWidget;
class QToolButton;
class QVBoxLayout;

class FrBookmark;
class FrTabSettingsDocObj;

#include "Qt/qwidget.h"
#include <vector>
using namespace std;


class FrBookmarkWidget: public QWidget {
	Q_OBJECT
public:
	FrBookmarkWidget(QWidget *parent = 0);

    bool AddBookmark(FrTabSettingsDocObj* ts);
    bool RemoveBookmark(FrTabSettingsDocObj* ts);

    int GetBookmarkCount();

public slots:
    // Add slots here
    void OnCloseButtonClicked();
    void OnCurrentChanged(QWidget* page);

signals:
    void DeleteTab(unsigned long tabID);
    void CurrentChanged(unsigned long tabID);

private:
    QTabWidget*         m_tabWidget;
    QToolButton*        m_btnCloseTab;
	QVBoxLayout*        m_layout;
	
	FrBookmark*         m_defaultTab;
    vector<FrBookmark*> m_bookmarks;
};

#endif
