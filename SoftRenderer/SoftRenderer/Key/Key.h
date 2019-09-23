#ifndef  __KEY__H__
#define  __KEY__H__

#include "Tools.h"

#ifndef KEY_ESCAPE
#define KEY_ESCAPE  0X1B
#endif // VK_ESCAPE

#define KEY_SPACE  32
#define KEY_LEFT   37
#define KEY_UP     38
#define KEY_RIGHT  39
#define KEY_DOWN   40

extern bool* bTurn;
extern bool* bMove;
extern bool bWillExit;

void initKeys();
void releaseKeys();
void keyDown(int key);
void keyUp(int key);
 
#endif