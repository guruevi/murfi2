// class for graphs panel

#ifndef FR_GRAPHLIST_WIDGET
#define FR_GRAPHLIST_WIDGET

// Forward declarations
class FrGraphWidget;
class QScrollArea;
class QVBoxLayout;
class QWidget;

// Includes 
#include "FrMacro.h"
#include "FrSettings.h"

#include "Qt/qcolor.h"
#include "Qt/qstring.h"
#include "Qt/qscrollarea.h"

// This class represent list widget for graphs
class FrGraphListWidget : public QScrollArea {
	Q_OBJECT
public:
	FrGraphListWidget(QWidget *parent = 0);

    // Methods
    void AddGraphWidget(FrGraphWidget* widget);
    void AddGraphWidget(unsigned long id, QString& name, QColor& color, bool isVisible=true);
    
    bool RemoveGraphWidget(unsigned long id, bool doDelete = false);
    bool RemoveGraphWidget(FrGraphWidget* widget, bool doDelete = false);
    void RemoveAll();

    FrGraphWidget* GetGraphWidget(unsigned long id);
        
    // Here all signals
Q_SIGNALS:
    void GraphVisibilityChanged(unsigned long id);

private Q_SLOTS:
    void OnGraphVisibilityChanged(unsigned long id);

private:
    //QPushButton* m_btnUp;
    //QPushButton* m_btnDown;
    QVBoxLayout* m_layout;
    QWidget*     m_centralWidget;   
};

#endif
