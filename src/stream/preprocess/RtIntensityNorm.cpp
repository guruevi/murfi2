/******************************************************************************
 * RtIntensityNorm.cpp is the implementation of a class that normalizes the
 * intensity of subsequent images in a timeseries to match the global signal
 * of the first.
 *
 * Oliver Hinds <ohinds@mit.edu> 2008-03-15
 *
 *****************************************************************************/

#include"RtIntensityNorm.h"
#include"RtExperiment.h"
#include"RtConfigFmriExperiment.h"
#include"ace/Mutex.h"
#include"RtDataIDs.h"

string RtIntensityNorm::moduleString(ID_SPATIALINTENSITYNORM);

// default constructor
RtIntensityNorm::RtIntensityNorm() : RtStreamComponent() {
  componentID = moduleString;
}

// destructor
RtIntensityNorm::~RtIntensityNorm() {
  //cout << "destroyed" << endl;
}

// process a configuration option
//  in
//   name of the option to process
//   val  text of the option node
bool RtIntensityNorm::processOption(const string &name, const string &text,
				      const map<string,string> &attrMap) {

  // look for known options
  if(name == "maskRoiID") {
    maskRoiID = text;
    return true; 
  }

  return RtStreamComponent::processOption(name, text, attrMap);
}

// validate the configuration
bool RtIntensityNorm::validateComponentConfig() {
  bool result = true;

  if(maskRoiID == "") {
    cerr << "ERROR: maskRoiID must be set to do intensity normalization" << endl;
    result = false;
  }
  
  return result;
}

// process a single acquisition
int RtIntensityNorm::process(ACE_Message_Block *mb) {
  double sum = 0;
  
  ACE_TRACE(("RtIntensityNorm::process"));

  RtStreamMessage *msg = (RtStreamMessage*) mb->rd_ptr();

  // get the current image and mask to operate on
  RtMRIImage *img = (RtMRIImage*) msg->getCurrentData();
  RtMaskImage *mask = getMaskFromMessage(*msg);

  if(img == NULL) {
    cout << "RtIntensityNorm::process: image passed is NULL" << endl;

    ACE_DEBUG((LM_INFO, "RtIntensityNorm::process: image passed is NULL\n"));
    return 0;
  }

  if(mask == NULL) {
    cout << "RtIntensityNorm::process: mask is NULL" << endl;
    return 0;
  }

  // look for first image, compute mean intensity to norm further images by
  if(needsInit) {
    ACE_DEBUG((LM_DEBUG, "intensity normalization found first image\n"));
    
    // iterate over pixels accumulating intensity
    double sum = 0;
    for(unsigned int i = 0; i < img->getNumPix(); i++) {
      if(mask->getPixel(i)) {
	sum += img->getPixel(i);
      }
    }

    // store the average intensity in mask
    meanIntensity = sum/mask->getNumberOfOnVoxels();

    needsInit = false;
  }
  
//  ACE_DEBUG((LM_DEBUG, "intensity normalizing image %d\n", 
//	     img->getAcquisitionNum()));
  
  // compute the mean intensity in the mask for this image

  // iterate over pixels accumulating intensity
  sum = 0;
  for(unsigned int i = 0; i < img->getNumPix(); i++) {
    if(mask->getPixel(i)) {
      sum += img->getPixel(i);
    }
  }

  // norm factor
  short intensityDiff 
    = (short) rint(sum/mask->getNumberOfOnVoxels() - meanIntensity);
  
  // allocate a new data image for normalized image
  RtMRIImage *inorm = new RtMRIImage(*img);
  
  inorm->getDataID().setFromInputData(*img,*this);
  inorm->getDataID().setDataName(NAME_SPATIALINTENSITYNORM_IMG);

  // subtract the difference for each voxel
  for(unsigned int i = 0; i < img->getNumPix(); i++) {
    inorm->setPixel(i, (img->getPixel(i) - intensityDiff > 0)
		    ? (img->getPixel(i) - intensityDiff) : 0);
  }  

  // set the image id for handling
  //inorm->addToID("intensity-norm");
  setResult(msg,inorm);

  return 0;
}


/*****************************************************************************
 * $Source$
 * Local Variables:
 * mode: c++
 * fill-column: 76
 * comment-column: 0
 * End:
 *****************************************************************************/

