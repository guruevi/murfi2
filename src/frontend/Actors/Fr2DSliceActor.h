// .NAME vtkpxImageSlice - create hierarchies of actors
// .SECTION Description
#ifndef FR_2DSLICE_ACTOR
#define FR_2DSLICE_ACTOR

#include "FrBaseActor.h"

// VTK stuff
#include "vtkImageData.h"
#include "vtkLookupTable.h"
#include "vtkPlaneSource.h"
#include "vtkTexture.h"
#include "vtkProperty.h"
#include "vtkExtractVOI.h"

class Fr2DSliceActor : public FrBaseActor
{
public:
	static Fr2DSliceActor *New();
	vtkTypeMacro(Fr2DSliceActor, FrBaseActor);

	// Description:
	// Add a part to the list of parts.
	virtual void SetInput(vtkImageData* image);
	virtual void SetLookupTable(vtkLookupTable* table);
	virtual void SetInterpolation(int on);
	virtual void SetOpacity(float opacity);

	// Description:
	// Set Key Location Parameters 
	virtual void SetLevel(int level);
	virtual void SetCurrentFrame(int CurrentFrame);
	virtual void SetCurrentPlane(int CurrentPlane);

	vtkGetMacro(CurrentFrame,int);
	vtkGetMacro(CurrentPlane,int);
	vtkGetMacro(Level,int);

	vtkGetMacro(Opacity,float);
	vtkGetMacro(Interpolation,int);

	vtkGetMacro(OwnsColorMap,int);

	vtkSetClampMacro(AutoUpdate,int,0,1);
	vtkGetMacro(AutoUpdate,int);
	vtkBooleanMacro(AutoUpdate,int);


	virtual void Update() { this->UpdateSlice();}
	virtual void UpdateTexture();

	vtkGetObjectMacro(CurrentImage,vtkImageData);

    // Returns Max number of slices
    int GetMaxSliceNumber();

protected:
	vtkActor*                    ImageSlice;
	vtkPlaneSource*              ImagePlane;
	vtkImageData*                CurrentImage;
	vtkTexture*                  ImageTexture;
	vtkExtractVOI*				 ImageVOI;
	int                          Level;

	float                        OutlineBounds[6];
	int                          CurrentPlane;
	int							 CurrentFrame;

	float                        Opacity;
	int                          Interpolation;
	int                          AutoUpdate;

	vtkLookupTable*              ColorMap;
	int                          OwnsColorMap;   

	Fr2DSliceActor();
	virtual ~Fr2DSliceActor();
	Fr2DSliceActor(const Fr2DSliceActor&) {};
	void operator=(const Fr2DSliceActor&) {};

	// Slice Stuff
	virtual void BuildImageSlice();
	virtual void UpdateSlice();

private:
	void AutoUpdateColormapRange(vtkLookupTable* cmap, vtkImageData* img);
	void SetStepColorMap(vtkLookupTable *cmap, float min, float max, float min_value, float max_value,
		int num_colors, int vol = 0);

};


#endif





