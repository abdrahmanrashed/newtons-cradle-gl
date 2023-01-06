#include "algo.hpp"

//determines the view angle of the camera.
double viewangle = 0;
//determines the current angle of the animation.
double animationangle = 0;
//determines if the direction of the animation.
int direction = 1;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);    
 
    glLoadIdentity(); 
    //set origin 
    glTranslated(0, -10, -50);
    //set camera viewing angle 
    glRotated(viewangle, 0, 1, 0);

    //sphere color
    glColor3d(point{165, 165, 165});
    //sphere array
    vector<point> spheres{{0, 0, 0}, {10, 0, 0}, {-10, 0, 0}, {20, 0, 0}, {-20, 0, 0}};
    for(int i = 0; i < spheres.size(); i++){
        moveTo(spheres[i]);
        glPushMatrix();
        if(i > 2){
            glTranslated(0, 20, 0);
            if((i == 3 && animationangle > 0)
            || (i == 4 && animationangle < 0))
            glRotated(animationangle, 0, 0, 1);
            glTranslated(0, -20, 0);
        }
        glutSolidSphere(5, 50, 50);
        glPopMatrix();
    }
    glTranslated(0, 4, 0);

    //cylinder color
    glColor3d(point{125, 125, 125});
    //cylinder array
    vector<point> cylinders{{25, 0, 25}, {-25, 0, 25}, {25, 0, -25}, {-25, 0, -25}, {0, 20, 25}, {0, 20, -25}};
    for(int i = 0, j[2] = {40, 50}; i < cylinders.size(); i++){
        moveTo(cylinders[i]);
        if(i > 3) glRotated(90, 0, 0, 1);
        cylinder(3, j[i > 3]);
        if(i > 3) glRotated(-90, 0, 0, 1);
    }
    //corners array
    spheres = {{25, 20, 25}, {-25, 20, 25}, {25, 20, -25}, {-25, 20, -25}};
    for(int i = 0; i < spheres.size(); i++){
        moveTo(spheres[i]);
        glutSolidSphere(3, 50, 50);
    }
    moveTo({0, 0, 0});
    glLineWidth(3);
    //ropes color
    glColor3d(point{230, 230, 230});
    //ropes array
    vector<array<point, 3>> ropes;
    ropes.push_back({point{10, 20, 25}, point{10, -4, 0}, point{10, 20, -25}});
    ropes.push_back({point{0, 20, 25}, point{0, -4, 0}, point{0, 20, -25}});
    ropes.push_back({point{-10, 20, 25}, point{-10, -4, 0}, point{-10, 20, -25}});
    ropes.push_back({point{20, 20, 25}, point{20, -4, 0}, point{20, 20, -25}});
    ropes.push_back({point{-20, 20, 25}, point{-20, -4, 0}, point{-20, 20, -25}});
    for(int i = 0; i < ropes.size(); i++){
        auto [point1, point2, point3] = ropes[i];
        glPushMatrix();
        if((i == 3 && animationangle > 0)
        || (i == 4 && animationangle < 0)){
            point p = {point2.x, point1.y, 0};
            moveTo(p);
            glRotated(animationangle, 0, 0, 1);
            moveTo({0, 0, 0});
        }
        glBegin(GL_LINE_STRIP);
        glVertex3d(point1);
        glVertex3d(point2);
        glVertex3d(point3);
        glEnd();
        glPopMatrix();
    }
    //change animation angle position;
    if(animationangle > 40) direction = -1; 
    else if(animationangle < -40) direction = 1;
    animationangle += ((40 - abs(animationangle)) / 38 + 0.01) * direction * 3.7;
    glutSwapBuffers();  
}
void timer(int value) {
    glutPostRedisplay();      
    glutTimerFunc(17, timer, 0);
}
void reshape(GLsizei width, GLsizei height) {   
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
    glViewport(0, 0, width, height);
 
    glMatrixMode(GL_PROJECTION);  

    glLoadIdentity();   
    gluPerspective(90.0, aspect, 0.1, 100.0);
}
void keybd(unsigned char key, int x, int y){
    switch(key){
        case 'a':
            viewangle -= 2.5;
            break;
        case 'd':
            viewangle += 2.5;
            break;
    }
}
void keybd2(int key, int x, int y){
    switch(key){
        case GLUT_KEY_LEFT:
            viewangle--;
            break;
        case GLUT_KEY_RIGHT:
            viewangle++;
            break;
    }
}
void initGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClearDepth(1.0);                     
    glEnable(GL_DEPTH_TEST);  
    glDepthFunc(GL_LEQUAL);    
    glShadeModel(GL_SMOOTH); 
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);         
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(1600, 900);    
    glutInitWindowPosition(50, 50); 
    glutCreateWindow("newton's cradle"); 
    glutDisplayFunc(display);     
    glutReshapeFunc(reshape);   
    glutKeyboardFunc(keybd);
    glutSpecialFunc(keybd2);  
    initGL();                     
    glutTimerFunc(0, timer, 0);  
    glutMainLoop();                
    return 0;
}