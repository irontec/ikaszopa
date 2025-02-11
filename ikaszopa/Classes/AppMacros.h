#ifndef __APPMACROS_H__
#define __APPMACROS_H__

#include "cocos2d.h"

/* For demonstrating using one design resolution to match different resources,
 or one resource to match different design resolutions.
 
 [Situation 1] Using one design resolution to match different resources.
 Please look into Appdelegate::applicationDidFinishLaunching.
 We check current device frame size to decide which resource need to be selected.
 So if you want to test this situation which said in title '[Situation 1]',
 you should change ios simulator to different device(e.g. iphone, iphone-retina3.5, iphone-retina4.0, ipad, ipad-retina),
 or change the window size in "proj.XXX/main.cpp" by "CCEGLView::setFrameSize" if you are using win32 or linux plaform
 and modify "proj.mac/AppController.mm" by changing the window rectangle.
 
 [Situation 2] Using one resource to match different design resolutions.
 The coordinates in your codes is based on your current design resolution rather than resource size.
 Therefore, your design resolution could be very large and your resource size could be small.
 To test this, just define the marco 'TARGET_DESIGN_RESOLUTION_SIZE' to 'DESIGN_RESOLUTION_2048X1536'
 and open iphone simulator or create a window of 480x320 size.
 
 [Note] Normally, developer just need to define one design resolution(e.g. 960x640) with one or more resources.
 */

#define DESIGN_RESOLUTION_480X320    0
#define DESIGN_RESOLUTION_1024X768   1
#define DESIGN_RESOLUTION_2048X1536  2

/* If you want to switch design resolution, change next line */
#define TARGET_DESIGN_RESOLUTION_SIZE DESIGN_RESOLUTION_2048X1536

typedef struct tagResource
{
    cocos2d::Size size;
    char directory[100];
}Resource;
//Horizontal
//static Resource smallResource  =    { cocos2d::Size(960, 480),    "images/iphone"         };//14.65%
//static Resource mediumResource =    { cocos2d::Size(1136, 640),   "images/ipad"           };//23%
//static Resource largeResource =     { cocos2d::Size(2048, 1536),  "images/ipadhd"         };//100%
static Resource smallResource  =    { cocos2d::Size(2048, 1536),  "images/ipadhd"         };
static Resource mediumResource =    { cocos2d::Size(2048, 1536),  "images/ipadhd"           };
static Resource largeResource =     { cocos2d::Size(2048, 1536),  "images/ipadhd"         };

 //static Resource smallResource  =    { cocos2d::Size(480, 960),    "images"         };
//static Resource mediumResource =    { cocos2d::Size(640, 1136),   "images"         };
//static Resource largeResource =     { cocos2d::Size(1536, 2040),  "images"         };

// static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(480, 960);

#if (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_320X480)
static cocos2d::Size designResolutionSize = smallResource.size;
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_640X1136)
static cocos2d::Size designResolutionSize = mediumResource.size;
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_2048X1536)
static cocos2d::Size designResolutionSize = largeResource.size;
#else
#error unknown target design resolution!
#endif

// The font size 24 is designed for small resolution, so we should change it to fit for current design resolution
#define TITLE_FONT_SIZE  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / smallResource.size.width * 24)

#endif /* __APPMACROS_H__ */
