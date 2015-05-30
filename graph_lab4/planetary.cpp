//
// Created by root on 25.04.15.
//


#include "planetary.h"

void Planetary::on_window_resize(int w, int h) {
    if (h == 0)
        h = 1;
    float ratio = (float) (w * 1.0 / h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Planetary::on_scene_render() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    draw_info();
    glPushMatrix();
    draw_cube();
    glTranslated(x,y,-z-5);
    draw_sun();
    draw_planet();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D,0);
    glutSwapBuffers();
}


void Planetary::draw_planet() {
    glColor4d(1,1,1,0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glPushMatrix();
         glRotatef(planet_sun_angle, 0, 1, 0 );
         glTranslatef( 0,0,0 );
         glPushMatrix();
            glTranslatef(-0.5f,0,0);
            glRotatef( planet_self_angle, 0, 0, 1 );
            gluQuadricTexture(quadrics[0],1);
         gluSphere(quadrics[0],planet_radius,20,20);
         glPopMatrix();
    glPopMatrix();

}

void Planetary::draw_sun() {
    glColor4d(1,1,1,0);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    if(is_lighting()){
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0,GL_AMBIENT ,LIGHT_AMBIENCE);
        glLightfv(GL_LIGHT0,GL_DIFFUSE,LIGHT_DIFFUSION);
        glLightfv(GL_LIGHT0,GL_SPECULAR,LIGHT_SPECULAR);
        glLightfv(GL_LIGHT0,GL_POSITION,LIGHT_POSITION);
    }
    else{
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);
    }
    gluQuadricTexture(quadrics[1],1);
    gluSphere(quadrics[1],sun_radius,20,20);
}



void Planetary::on_idle() {
    if(is_planet_sun_spinning())
    add_planet_sun_angle(0.5f);

    if(is_planet_self_spinning())
    add_planet_self_angle(1.0f);

    if(planet_sun_angle>360) planet_sun_angle=0;
    if(planet_self_angle>360) planet_self_angle=0;


    if(scene_moving) {

        if(x < -1 || x > 1)
            dx*=-1;
        if(y < -1 || y > 1)
            dy*=-1;
        if(z < -4 || z > 5)
            dz*=-1;

        x += dx;
        y += dy;
        z += dz;
    }
    glutPostRedisplay();
}


void Planetary::init_rendering() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);

    quadrics[0] = gluNewQuadric();
    quadrics[1] = gluNewQuadric();
    textures[0] = SOIL_load_OGL_texture("/home/andriypuhach/moon.jpg",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);
    textures[1] = SOIL_load_OGL_texture("/home/andriypuhach/sun.jpg",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS);
}

void Planetary::on_keyboard(unsigned char key,int x, int w) {
    int mod = glutGetModifiers();
    switch(key){
        case 0:
            if(mod==GLUT_ACTIVE_CTRL)
                planet_sun_spinning=!planet_sun_spinning;
            break;
        case 'p':
            if(mod==GLUT_ACTIVE_ALT)
                planet_radius-=0.01;
            else if (mod==0)
                planet_radius+=0.01;
            break;
        case 's':
            if(mod==GLUT_ACTIVE_ALT)
                sun_radius-=0.01;
            else if (mod==0)
                sun_radius+=0.01;
            break;
        case 27:
            exit(0);
        case 32:
            planet_self_spinning=!planet_self_spinning;
            break;
    }
}

void Planetary::draw_info() {
    if(info_drawing){
        glPushMatrix();
        glRasterPos2d(-glutGet(GLUT_WINDOW_WIDTH)/2.0f + 0.2,glutGet(GLUT_WINDOW_HEIGHT)/2.0-0.4);
        glutBitmapString(GLUT_BITMAP_HELVETICA_10,(unsigned char *)"P - Enlarge planet");
        glRasterPos2d(-0.8,0.45);
        glutBitmapString(GLUT_BITMAP_HELVETICA_10,(unsigned char *)"Alt+P - Smallen planet");
        glRasterPos2d(-0.8,0.3);
        glutBitmapString(GLUT_BITMAP_HELVETICA_10,(unsigned char *)"S - Enlarge sun");
        glRasterPos2d(-0.8,0.15);
        glutBitmapString(GLUT_BITMAP_HELVETICA_10,(unsigned char *)"Alt+S - Smallen sun");
        glRasterPos2d(-0.8,0.0);
        glutBitmapString(GLUT_BITMAP_HELVETICA_10,(unsigned char *)"Space - Stop/Resume self rotating");
        glRasterPos2d(-0.8,-0.15);
        glutBitmapString(GLUT_BITMAP_HELVETICA_10,(unsigned char *)"Ctrl Space - Stop/Resume around sun rotating");
        glPopMatrix();
    }
}

void Planetary::on_special_keyboard(int key, int i1, int i2) {
    if(key==GLUT_KEY_F1){
        info_drawing=!info_drawing;
    }
}

void Planetary::menu(int item) {
    switch (item)
    {
        case LIGHT_ON_OFF:
            lighting=!lighting;
            break;
        case START_STOP_SELF_SPINNING:
            planet_self_spinning=!planet_self_spinning;
            break;
        case START_STOP_AROUND_SUN_SPINNING:
            planet_sun_spinning=!planet_sun_spinning;
            break;
        case START_STOP_MOVING:
            scene_moving=!scene_moving;
            break;
        default:
        {       /* Nothing */       }
            break;
    }

    glutPostRedisplay();

    return;
}

void Planetary::draw_cube() {
    glPushMatrix();
    glColor3d(1, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    glVertex3d(5, 5, -40);
    glVertex3d(-5, 5, -40);
    glVertex3d(-5, -5, -40);
    glVertex3d(5, -5, -40);
    glVertex3d(5, 5, -40);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3d(5, 5, -10);
    glVertex3d(-5, 5, -10);
    glVertex3d(-5, -5, -10);
    glVertex3d(5, -5, -10);
    glVertex3d(5, 5, -10);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(5, 5, -10);
    glVertex3d(5, 5, -40);
    glVertex3d(-5, 5, -10);
    glVertex3d(-5, 5, -40);
    glVertex3d(-5, -5, -10);
    glVertex3d(-5, -5, -40);
    glVertex3d(5, -5, -10);
    glVertex3d(5, -5, -40);
    glEnd();

    glPopMatrix();
}
