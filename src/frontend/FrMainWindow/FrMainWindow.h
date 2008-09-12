#ifndef FR_MAIN_WINDOW
#define FR_MAIN_WINDOW

// Forward declaration
class QTabWidget;

class FrBaseView;
class FrView2D;
class FrMosaicView;
class FrOrthoView;
class FrMainDocument;
class FrMainController;
class FrLowPanel;
class FrToolsPanel;
class FrBookmarkWidget;
class QVTKWidget;

#include "ui_FrMainWindow.h"
#include "FrMacro.h"


class FrMainWindow: public QMainWindow, public Ui::MainWindow {
	Q_OBJECT
public:
	FrMainWindow();
    ~FrMainWindow();

    FrPropMacro(FrMainDocument*,MainDocument);
    FrPropMacro(FrMainController*,MainController);
    
    FrView2D* GetView2D(){ return m_view2D; }
    QVTKWidget* GetQVTKWidget(){ return m_qtView; }
	void UpdateTBCValues(double contrast, double brightness);

    void Initialize();

public slots:
	void brightnessValueChanged();
	void contrastValueChanged();
	void thresholdValueChanged();

	void tool1Triggered();
	void tool2Triggered();
	void tool3Triggered();
	void mode1Clicked();
	void mode2Clicked();
	void mode3Clicked();
	void tabChanged(int index);
	void bookmarkChanged(int index);
	void saveToTab();
    void openImage();

signals:

private:
    void InitializeWidgets();
    void InitializeSignals();

private:
    FrView2D* m_view2D;
    FrMosaicView* m_viewMosaic;
    FrOrthoView* m_viewOrtho;
    FrBaseView* m_currentView;

public:
    QVTKWidget* m_qtView;
    QTabWidget* m_tabWidget;
	QWidget*    m_slice2DWidget;
	QWidget*    m_graphWidget;

	FrToolsPanel*   m_toolsPanel;
	FrLowPanel*     m_lowPanel;
	FrBookmarkWidget* m_bookmarkWidget;
};

#endif
