#include "planetary.h"

Planetary * mainObject;

void resize(int w,int h){
    if(mainObject)
        mainObject->on_window_resize(w,h);
}

void display(){
    if(mainObject)
        mainObject->on_scene_render();
}

void idle(){
    if(mainObject)
        mainObject->on_idle();
}

void keyboard(unsigned char key,int x,int y){
    if(mainObject)
        mainObject->on_keyboard(key,x,y);
}
void special_keyboard(int key,int x,int y){
    if(mainObject)
        mainObject->on_special_keyboard(key,x,y);
}

void menu(int m){
    if(mainObject)
        mainObject->menu(m);
}

int main(int argc, char ** argv) {
    mainObject=new Planetary();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(300,300);
    glEnable(GL_DEPTH_TEST);

    glutCreateWindow("Planetary");
    glutFullScreen();
    mainObject->init_rendering();

    /* Register GLUT callbacks. */
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutSpecialFunc(special_keyboard);
    glutKeyboardFunc(keyboard);
    glutIgnoreKeyRepeat(false);
    glutIdleFunc(idle);

    glutCreateMenu(menu);
    glutAddMenuEntry("Turn on/off lighting",LIGHT_ON_OFF);
    glutAddMenuEntry("Start/stop self spinning",START_STOP_SELF_SPINNING);
    glutAddMenuEntry("Start/stop around sun spinning",START_STOP_AROUND_SUN_SPINNING);
    glutAddMenuEntry("Start/stop moving",START_STOP_MOVING);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
    /* Init the GL state */
    glLineWidth(1.0);

    /* Main loop */
    glutMainLoop();
    return 0;
}