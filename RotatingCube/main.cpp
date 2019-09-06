/*
//  This file displays a rotating color cube.
//
//  Created by Tabitha Peck on 7/16/13.
//  Edited by Megan Feichtel: 8/26/2014
*/

#include <iostream>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <glut.h>
#endif


float win_width = 512;
float win_height = 512;

float x_angle, y_angle, z_angle;
bool x_rotate, y_rotate, z_rotate;

void init( void ){
    x_angle = 0;
    y_angle = 0;
    z_angle = 0;
    
    x_rotate = false;
    y_rotate = false;
    z_rotate = false;
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glClearColor (0.0, 0.0, 0.0, 0.0);
    
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
    
    glShadeModel (GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    // Enable blending
    
}

void idle( void ){
    if(x_rotate)
        x_angle += 0.4;
    if(y_rotate)
        y_angle += 0.4;
    if(z_rotate)
        z_angle += 0.4;
    
    
   // std::cout << "Hello World\n";
    
    glutPostRedisplay();
}

void cube( float size ){
    glPushMatrix();
    
    glRotatef(x_angle, 1, 0, 0);
    glRotatef(y_angle, 0, 1, 0);
    glRotatef(z_angle, 0, 0, 1);
    
    //draw the cube here
    glBegin(GL_QUADS);
    
    //front
    glColor3f(1, 0, 0); glVertex3f(-size, -size, size);
    glColor3f(1, 1, 1); glVertex3f(size, -size, size);
    glColor3f(0, 1, 0); glVertex3f(size, size, size);
    glColor3f(1, 1, 0); glVertex3f(-size, size, size);
    
    //right
    glColor3f(1, 1, 1); glVertex3f(size, -size, size);
    glColor3f(0, 0, 1); glVertex3f(size, -size, -size);
    glColor3f(0, 1, 1); glVertex3f(size, size, -size);
    glColor3f(0, 1, 0); glVertex3f(size, size, size);
    
    //back
    glColor3f(1, 0, 1); glVertex3f(-size, -size, -size);
    glColor3f(0, 0, 0); glVertex3f(-size, size, -size);
    glColor3f(0, 1, 1); glVertex3f(size, size, -size);
    glColor3f(0, 0, 1); glVertex3f(size, -size, -size);
   
    //left
    glColor3f(1, 0, 1); glVertex3f(-size, -size, -size);
    glColor3f(1, 0, 0); glVertex3f(-size, -size, size);
    glColor3f(1, 1, 0); glVertex3f(-size, size, size);
    glColor3f(0, 0, 0); glVertex3f(-size, size, -size);
    
    //top
    glColor3f(1, 1, 0); glVertex3f(-size, size, size);
    glColor3f(0, 1, 0); glVertex3f(size, size, size);
    glColor3f(0, 1, 1); glVertex3f(size, size, -size);
    glColor3f(0, 0, 0); glVertex3f(-size, size, -size);
    
    //bottom
    glColor3f(1, 0, 0); glVertex3f(-size, -size, size);
    glColor3f(1, 0, 1); glVertex3f(-size, -size, -size);
    glColor3f(0, 0, 1); glVertex3f(size, -size, -size);
    glColor3f(1, 1, 1); glVertex3f(size, -size, size);
    
    glEnd();
    glPopMatrix();
    
}

void display( void )
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(45.f, win_width/win_height, .1f, 500.f);
    //glOrtho(-2,2,-2,2,-.1,500);
    glMatrixMode(GL_MODELVIEW);
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT, GL_FILL);
    
    glPushMatrix();
    
    cube(0.5);
    
    glPopMatrix();
    
    glutSwapBuffers();
}

void reshape( int w, int h )
{
    win_width = w;
    win_height = h;
    glViewport( 0, 0, w, h );
    
    glutPostRedisplay();
 }


void keyboard( unsigned char key, int x, int y ) {
    switch(key) {
        case 27: // Escape key
            exit(0);
            break;
        case 'x':
            x_rotate = !x_rotate;
            break;
        case 'y':
            y_rotate = ! y_rotate;
            break;
        case 'z':
            z_rotate = ! z_rotate;
            break;
    }
}

int main(int argc, char * argv[])
{
    //std::cout << "Hello World\n";
    
    glutInit( &argc, argv );
    
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize( win_width, win_height );
    
    glutCreateWindow( "3D Cube" );
    
    init();
    
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );
    glutIdleFunc( idle );
    glutMainLoop();
    
    return 0;
}
