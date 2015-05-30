//
// Created by root on 25.04.15.
//

#ifndef GRAPH_LAB4_PLANETARY_H
#define GRAPH_LAB4_PLANETARY_H


#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <map>
#include <math.h>
enum MENU_OPTIONS{
    LIGHT_ON_OFF,
    START_STOP_SELF_SPINNING,
    START_STOP_AROUND_SUN_SPINNING,
    START_STOP_MOVING

};

const GLfloat LIGHT_AMBIENCE[]  = { 0.23, 0.34, 0.45, 1.0 };
const GLfloat LIGHT_DIFFUSION[] = { 0.11, 0.81, 0.81, 1.0 };
const GLfloat LIGHT_POSITION []   { 0, 0, 0, 1};
const GLfloat LIGHT_SPECULAR[]   = {1.0, 1.0, 1.0, 1.0};


class Planetary {
public:


    bool is_lighting() const {
        return lighting;
    }

    void set_lighting(bool lighting) {
        Planetary::lighting = lighting;
    }

    bool is_planet_self_spinning() const {
        return planet_self_spinning;
    }

    bool is_planet_sun_spinning() const{
        return planet_sun_spinning;
    }


    void add_planet_self_angle(float angle){
        planet_self_angle+=angle;
    }
    void reduce_planet_sun_angle(float angle){
        planet_sun_angle-=angle;
    }
    void reduce_planet_self_angle(float angle){
        planet_self_angle-=angle;
    }
    void add_planet_sun_angle(float angle){
        planet_sun_angle+=angle;
    }

    float get_sun_radius() const {
        return sun_radius;
    }

    void set_sun_radius(float sun_radius) {
        Planetary::sun_radius = sun_radius;
    }

    float get_planet_radius() const {
        return planet_radius;
    }

    void set_planet_radius(float planet_radius) {
        Planetary::planet_radius = planet_radius;
    }

    bool is_scene_moving() const {
        return scene_moving;
    }

    void set_scene_moving(bool scene_moving) {
        Planetary::scene_moving = scene_moving;
    }

    void init_rendering();
    void on_window_resize(int w,int h);
    void on_scene_render();
    void on_idle();

    void on_keyboard( unsigned char key,int x,int y);

    void on_special_keyboard(int key, int i1, int i2);
    void menu(int m);

private:
    /**
     * поля відповідальні за обертання планети навколо осі, і сонця
     */
    bool planet_self_spinning=true;
    bool planet_sun_spinning=true;
    bool scene_moving=true;
    bool info_drawing=false;
    bool lighting=true;
    float planet_radius=0.1;
    float sun_radius=0.3;

    float x=0,y=0,z=-4.0f;
    float dx = 0.01, dy = 0.04, dz = 0.08;

    float planet_self_angle = 0.0f;
    float planet_sun_angle=0.0f;

    GLuint * textures = new GLuint[2];
    GLUquadric ** quadrics = new GLUquadric * [2];


    void draw_cube();
    void draw_planet();
    void draw_sun();
    void draw_info();


};




#endif //GRAPH_LAB4_PLANETARY_H
