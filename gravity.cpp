#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace sf;

class gravity{
    Vector2f pos;
    float strength;
    CircleShape s;


public:
    gravity(float pos_x, float pos_y,float strength)
    {
        pos.x = pos_x;
        pos.y = pos_y;
        this->strength = strength;

        s.setPosition(pos);
        s.setFillColor(Color::Yellow);
        s.setRadius(10);
    }
    void render(RenderWindow& wind)
    {
        wind.draw(s);
    }
    Vector2f get_pos()
    {
        return pos;
    }
    float get_strength()
    {
        return strength;
    }

};




class particle{
public:
    Vector2f pos;
    Vector2f vel;

    CircleShape s;
    particle(float pos_x, float pos_y,float vel_x,float vel_y, Color color){
        pos.x = pos_x;
        pos.y = pos_y;
        vel.x = vel_x;
        vel.y = vel_y;
        s.setPosition(pos);
        s.setFillColor(color);
        s.setRadius(4);
    }
    void render(RenderWindow& wind)
    {
        s.setPosition(pos);
        wind.draw(s);
    }
    void update_physics(gravity &s)
    {
        float dist_x = s.get_pos().x - pos.x;
        float dist_y = s.get_pos().y - pos.y;
        float dist = sqrt(dist_x*dist_x + dist_y*dist_y);

        float inversedist = 1.f / dist;
        float normalised_x = inversedist *dist_x;
        float normalised_y = inversedist *dist_y;

        float inverse_square_dropoff = inversedist * inversedist;

        float acceleration_x = normalised_x * s.get_strength() * inverse_square_dropoff;
        float acceleration_y = normalised_y * s.get_strength() * inverse_square_dropoff;

        vel.x += acceleration_x;
        vel.y += acceleration_y;

        pos.x += vel.x;
        pos.y += vel.y;
    }
};




int main() {
    RenderWindow window(VideoMode(1600, 800), "SFML Window");
    window.setFramerateLimit(60);

    srand(time(0));
    const int size = 10000;
    int numbers[size];
    particle* particles[size];
    for (int i = 0; i < size; i++) {
        numbers[i] = 300 + rand() % 100;
        Color color(rand()%256,rand()%256,rand()%256);
        particles[i] = new particle(750 + rand()%100,numbers[i]-150,3.2,0,color);
    }
    gravity gravity(800 ,400,1500);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();
        for (int i = 0; i < size; i++) {
            particles[i]->update_physics(gravity);
            particles[i]->render(window);
        }

        gravity.render(window);


        window.display();

    }
    return 0;
}
