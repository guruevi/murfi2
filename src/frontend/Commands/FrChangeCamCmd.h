#ifndef FR_CHANGECAM_CMD
#define FR_CHANGECAM_CMD

class vtkRenderer;

#include "FrBaseCmd.h"
#include "FrMacro.h"

// This command changes settings of camera
// of current view and then update view.
class FrChangeCamCmd : public FrBaseCmd
{
public:
    // Constructor/destructor
    FrChangeCamCmd();
    
    // Modifiers
    void SetFocalPoint(double* value);
    void SetFocalPoint(double x, double y, double z);

    void SetPosition(double* value);
    void SetPosition(double x, double y, double z);

    void SetViewUp(double* value);
    void SetViewUp(double x, double y, double z);

    void SetScale(double value);

    // Property
    FrSetPropMacro(vtkRenderer*, Renderer);

    //
    // Overrides
    //
	virtual bool Execute();

    // Undo/redo section
	virtual bool CanUndo();
	virtual bool Undo();
	virtual bool Redo();

private:
    void SetupCameraSettings(void* settings);
    bool SetupOrthoViewCamSettings();

private:
    bool m_isPosition;
    double m_Position[3];

    bool m_isFocalPoint;
    double m_FocalPoint[3];

    bool m_isViewUp;
    double m_ViewUp[3];

    bool m_isScale;
    double m_Scale;
};

#endif // FR_CHANGECAM_CMD