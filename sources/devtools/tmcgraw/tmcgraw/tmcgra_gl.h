#ifndef _tmcgra_gl_h_
#define _tmcgra_gl_h_

void initialize (int width, int height) ;

// my callbacks
void display(void);
void mousefunc(int button, int state,int x, int y);
void keyboard (HWND hWnd, unsigned char key, int mousePositionX, int mousePositionY );
void reshape(int width, int height);

void _tmcglfinishgraph();
void _tmcglinitgraph();

void zoomStart();
void zoomFinish();
void zoomOff();



#endif
