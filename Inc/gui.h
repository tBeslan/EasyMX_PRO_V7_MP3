#ifndef _GUI_H_
#define _GUI_H_

#include "gfx.h"

// GListeners
extern GListener glistener;

// GHandles
extern GHandle ghContainerMainPage;
extern GHandle GW1;

// Function Prototypes
void guiCreate(void);
void guiShowPage(unsigned pageIndex);
void guiEventLoop(void);

#endif /* _GUI_H_ */

