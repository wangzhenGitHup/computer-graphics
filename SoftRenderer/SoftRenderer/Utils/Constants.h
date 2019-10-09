#ifndef  __CONSTANTS__H__
#define  __CONSTANTS__H__

#define  SCREEN_WIDTH  640
#define  SCREEN_HEIGHT 480
#define  MAX_X         SCREEN_WIDTH - 1
#define  MAX_Y         SCREEN_HEIGHT - 1
#define  MIN_X         0
#define  MIN_Y         0
#define  CULL_BACK     0
#define  CULL_FRONT    1
#define  CULL_NONE     2

// 1/255
#define  INV_SCALE     0.003921568627451  

#define  NONE          0
#define  LEFT          1
#define  RIGHT         2
#define  UP            3
#define  DOWN          4
#define  MNEAR         5
#define  MFAR          6
#define  D_ROTATION    4.0
#define  D_DISTANCE    1.0


#define ALL_VERTEX_AFTER_NEAR_CLIP             0x01  //3���㶼�ڽ����������
#define A_VERTEX_AFTER_NEAR_CLIP               0x02  //A���ڽ����������
#define B_VERTEX_AFTER_NEAR_CLIP               0x04  //B���ڽ����������
#define C_VERTEX_AFTER_NEAR_CLIP               0x08  //C���ڽ����������
#define AB_VERTEX_AFTER_NEAR_CLIP              0x0A  //AB���ڽ����������
#define AC_VERTEX_AFTER_NEAR_CLIP              0x0B  //AC���ڽ����������
#define BC_VERTEX_AFTER_NEAR_CLIP              0x0C  //BC���ڽ����������
#endif