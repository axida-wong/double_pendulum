#include <stdio.h>
#include <raylib.h>
#include <math.h>

#define WIDTH  1280
#define HEIGHT 720

#define LINE_THICKNESS 4
#define L1 250
#define L2 200

#define MASS_RADIUS 20
#define G 981.0

float l1, m1, phi1, phi1_d, phi1_dd;
float l2, m2, phi2, phi2_d, phi2_dd;


Vector2 get_end(Vector2 start, float l, float phi)
{
    return (Vector2 ){start.x + l * sinf(phi), start.y + l * cosf(phi)};
}

void draw_pendulum(float l, float phi, Vector2 start)
{
    Vector2 end = (Vector2 ){start.x + l * sinf(phi), start.y + l * cosf(phi)};
    DrawLineEx(start, end, LINE_THICKNESS, WHITE);
    DrawCircleV(end, MASS_RADIUS, RED);

}

void draw_double_pendulum(Vector2 start, float phi1, float phi2, float l1, float l2)
{
    Vector2 l1_end = get_end(start, l1, phi1);
    draw_pendulum(l2, phi2, l1_end);
    draw_pendulum(l1, phi1, start);
    // Vector2 l2_end = get_end(l1_end, l2, phi2);
}

void init_solver(void)
{
    l1 = L1;
    m1 = 1;
    phi1 = GetRandomValue(-90,90) * DEG2RAD;
    phi1_d = 0;
    phi1_dd = 0;
    l2 = L2;
    m2 = 1;
    phi2 = GetRandomValue(-90,90) * DEG2RAD;
    phi2_d = 0;
    phi2_dd = 0;
}

void step(float dt)
{
    phi1_dd = -G*(2*m1+m2)*sinf(phi1)-m2*G*sinf(phi1-2*phi2)-
        2*sinf(phi1-phi2)*m2*(phi2_d*phi2_d*l2+phi1_d*phi1_d*l1*cosf(phi1 - phi2));
    phi1_dd /= l1*(2*m1+m2-m2*cosf(2*phi1-2*phi2));

    phi2_dd = 2*sinf(phi1-phi2)*
        (phi1_d*phi1_d*l1*(m1+m2)+G*(m1+m2)*cosf(phi1)+phi2_d*phi2_d*l2*m2*cosf(phi1-phi2));
    phi2_dd /= l2*(2*m1+m2-m2*cosf(2*phi1-2*phi2));
    
    phi1_d += phi1_dd * dt;
    phi2_d += phi2_dd * dt;

    phi1 += phi1_d * dt;
    phi2 += phi2_d * dt;
}

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Double Pendulum");
    
    SetTargetFPS(60);
    init_solver();
    while(!WindowShouldClose())
    {
        step(GetFrameTime());
        

        BeginDrawing();
        ClearBackground(BLACK);
        draw_double_pendulum((Vector2 ){WIDTH / 2, 0}, phi1, phi2, l1, l2);
        EndDrawing();
    }
}