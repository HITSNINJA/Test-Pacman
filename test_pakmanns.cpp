#include <GL/glut.h>
#include <iostream>
#include <deque>
#include <cmath>
#include <stdlib.h>

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//############################################################
// DATA LABIRIN
//############################################################

const int BOARD_X = 31;
const int BOARD_Y = 28;

int board_array[31][28] = {
    {8,5,5,5,5,5,5,5,5,5,5,5,5,1,1,5,5,5,5,5,5,5,5,5,5,5,5,7},
    {6,0,0,0,0,0,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0,0,0,0,0,6},
    {6,0,8,1,1,7,0,8,1,1,1,7,0,2,4,0,8,1,1,1,7,0,8,1,1,7,0,6},
    {6,0,2,11,11,4,0,2,11,11,11,4,0,2,4,0,2,11,11,11,4,0,2,11,11,4,0,6},
    {6,0,9,3,3,10,0,9,3,3,3,10,0,9,10,0,9,3,3,3,10,0,9,3,3,10,0,6},
    {6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
    {6,0,8,1,1,7,0,8,7,0,8,1,1,1,1,1,1,7,0,8,7,0,8,1,1,7,0,6},
    {6,0,9,3,3,10,0,2,4,0,9,3,3,11,11,3,3,10,0,2,4,0,9,3,3,10,0,6},
    {6,0,0,0,0,0,0,2,4,0,0,0,0,2,4,0,0,0,0,2,4,0,0,0,0,0,0,6},
    {9,5,5,5,5,7,0,2,11,1,1,7,0,2,4,0,8,1,1,11,4,0,8,5,5,5,5,10},
    {0,0,0,0,0,6,0,2,11,3,3,10,0,9,10,0,9,3,3,11,4,0,6,0,0,0,0,0},
    {0,0,0,0,0,6,0,2,4,0,0,0,0,0,0,0,0,0,0,2,4,0,6,0,0,0,0,0},
    {0,0,0,0,0,6,0,2,4,0,8,5,0,0,0,0,5,7,0,2,4,0,6,0,0,0,0,0}, // Pintu dibuka (0,0)
    {5,5,5,5,5,10,0,9,10,0,6,0,0,0,0,0,0,6,0,9,10,0,9,5,5,5,5,5},
    {0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0},
    {5,5,5,5,5,7,0,8,7,0,6,0,0,0,0,0,0,6,0,8,7,0,8,5,5,5,5,5},
    {0,0,0,0,0,6,0,2,4,0,9,5,5,5,5,5,5,10,0,2,4,0,6,0,0,0,0,0},
    {0,0,0,0,0,6,0,2,4,0,0,0,0,0,0,0,0,0,0,2,4,0,6,0,0,0,0,0},
    {0,0,0,0,0,6,0,2,4,0,8,1,1,1,1,1,1,7,0,2,4,0,6,0,0,0,0,0},
    {8,5,5,5,5,10,0,9,10,0,9,3,3,11,11,3,3,10,0,9,10,0,9,5,5,5,5,7},
    {6,0,0,0,0,0,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,0,0,0,0,0,0,6},
    {6,0,8,1,1,7,0,8,1,1,1,7,0,2,4,0,8,1,1,1,7,0,8,1,1,7,0,6},
    {6,0,9,3,11,4,0,9,3,3,3,10,0,9,10,0,9,3,3,3,10,0,2,11,3,10,0,6},
    {6,0,0,0,2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,4,0,0,0,6},
    {2,1,7,0,2,4,0,8,7,0,8,1,1,1,1,1,1,7,0,8,7,0,2,4,0,8,1,4},
    {2,3,10,0,9,10,0,2,4,0,9,3,3,11,11,3,3,10,0,2,4,0,9,10,0,9,3,4},
    {6,0,0,0,0,0,0,2,4,0,0,0,0,2,4,0,0,0,0,2,4,0,0,0,0,0,0,6},
    {6,0,8,1,1,1,1,11,11,1,1,7,0,2,4,0,8,1,1,11,11,1,1,1,1,7,0,6},
    {6,0,9,3,3,3,3,3,3,3,3,10,0,9,10,0,9,3,3,3,3,3,3,3,3,10,0,6},
    {6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
    {9,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,10}
};

//############################################################
// GLOBAL VARIABLES
//############################################################

int tp_array[31][28];
deque<pair<double, double> > snake_body; 
double speed_val = 0.12; 
double angle_val = 0;
bool is_animate = false;
int player_lives = 3;
int player_points = 0;
bool is_game_over = false;

//############################################################
// HELPER FUNCTIONS
//############################################################

bool IsOpen(int x, int y) {
    if (x < 0 || x >= 28 || y < 0 || y >= 31) return false;
    return (board_array[y][x] == 0 || board_array[y][x] == 11);
}

//############################################################
// GHOST CLASS
//############################################################

class Ghost {
public:
    double x, y, speed, angle;
    float color[3];
    bool isExiting; // Flag baru untuk memaksa keluar kotak

    Ghost(double tx, double ty) {
        x = tx; y = ty;
        angle = 270; // Arahkan ke atas saat mulai
        speed = 0.05; 
        isExiting = true; // Mulai dengan mode keluar
        color[0] = 1.0f; color[1] = 0.0f; color[2] = 0.0f;
    }

    void Draw() {
        glColor3f(color[0], color[1], color[2]);
        glPushMatrix();
        glTranslatef(x - 13.5, 14.5 - y, 0.5);
        glutSolidSphere(0.45, 10, 10);
        glPopMatrix();
    }

    bool canMove(double next_angle) {
        double nx = x + 0.4 * cos(M_PI / 180 * next_angle);
        double ny = y + 0.4 * sin(M_PI / 180 * next_angle);
        return IsOpen((int)(nx + 0.5), (int)(ny + 0.5));
    }

    void Move() {
        if (canMove(angle)) {
            x += speed * cos(M_PI / 180 * angle);
            y += speed * sin(M_PI / 180 * angle);
        } else {
            // Jika mentok saat keluar, coba arah acak tapi prioritaskan atas
            angle = (rand() % 4) * 90;
        }

        // Jika sudah di luar kotak tengah (y < 12), matikan mode exiting
        if (isExiting && y < 12.5) {
            isExiting = false;
        }
    }

    void Chase(double px, double py) {
        // Jika masih di dalam kotak, paksa cari jalan ke koordinat pintu (13.5, 12.0)
        double targetX = isExiting ? 13.5 : px;
        double targetY = isExiting ? 12.0 : py;

        // Logika belok hanya di tengah grid agar tidak memantul liar
        if (fmod(x + 0.05, 1.0) < 0.2 && fmod(y + 0.05, 1.0) < 0.2) {
            double min_dist = 9999.0;
            double best_angle = angle;

            for (int i = 0; i < 4; i++) {
                double try_a = i * 90;
                
                // Jangan putar balik 180 derajat kecuali mentok
                if (abs(try_a - angle) == 180) continue;

                if (canMove(try_a)) {
                    double nextX = x + cos(M_PI/180 * try_a);
                    double nextY = y + sin(M_PI/180 * try_a);
                    double dist = sqrt(pow(targetX - nextX, 2) + pow(targetY - nextY, 2));

                    if (dist < min_dist) {
                        min_dist = dist;
                        best_angle = try_a;
                    }
                }
            }
            angle = best_angle;
        }
    }
};

Ghost* ghosts[4];

//############################################################
// LOGIKA PERMAINAN
//############################################################

void resetGame() {
    snake_body.clear();
    // Gunakan make_pair dan koordinat tepat di jalur (13.5, 23.0)
    snake_body.push_front(make_pair(13.5, 23.0));
    angle_val = 0;
    is_animate = false;
}

void moveSnake() {
    double nx = snake_body[0].first + speed_val * cos(M_PI / 180 * angle_val);
    double ny = snake_body[0].second + speed_val * sin(M_PI / 180 * angle_val);

    // Tunneling (Tembus samping)
    if (nx > 27.5) nx = 0.5;
    if (nx < 0.5) nx = 27.5;

    if (IsOpen((int)(nx + 0.5), (int)(ny + 0.5))) {
        int gx = (int)(nx + 0.5);
        int gy = (int)(ny + 0.5);
        bool eat = false;

        if (tp_array[gy][gx] == 1) {
            tp_array[gy][gx] = 0;
            player_points += 10;
            eat = true;
        }

        snake_body.push_front(make_pair(nx, ny));
        if (!eat) {
            snake_body.pop_back();
        }
    } else {
        is_animate = false; // Berhenti jika tabrak tembok
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, 38, 0, 0, 0, 0, 1, 0);

    if (!is_game_over) {
        if (is_animate) moveSnake();

        // Draw Maze & Dots
        for (int i = 0; i < 31; i++) {
            for (int j = 0; j < 28; j++) {
                if (board_array[i][j] > 0 && board_array[i][j] != 11) {
                    glColor3f(0.1, 0.1, 0.8);
                    glPushMatrix();
                    glTranslatef(j - 13.5, 14.5 - i, 0);
                    glutSolidCube(1.0);
                    glPopMatrix();
                }
                if (tp_array[i][j] == 1) {
                    glColor3f(1.0, 1.0, 1.0);
                    glPushMatrix();
                    glTranslatef(j - 13.5, 14.5 - i, 0.5);
                    glutSolidSphere(0.1, 8, 8);
                    glPopMatrix();
                }
            }
        }

        // Draw Pac-Snake
        for (size_t i = 0; i < snake_body.size(); i++) {
            glColor3f(1.0, 1.0, (i == 0 ? 0 : 0.5));
            glPushMatrix();
            glTranslatef(snake_body[i].first - 13.5, 14.5 - snake_body[i].second, 0.5);
            glutSolidSphere(i == 0 ? 0.55 : 0.45, 12, 12);
            glPopMatrix();
        }

        // Ghost Logic
        for (int i = 0; i < 4; i++) {
            ghosts[i]->Chase(snake_body[0].first, snake_body[0].second);
            ghosts[i]->Move();
            ghosts[i]->Draw();
            
            double d = sqrt(pow(ghosts[i]->x - snake_body[0].first, 2) + pow(ghosts[i]->y - snake_body[0].second, 2));
            if (d < 0.6) {
                player_lives--;
                resetGame();
                if (player_lives <= 0) is_game_over = true;
            }
        }
    } else {
        // Tampilkan Game Over sederhana di layar
        glColor3f(1, 0, 0);
        glRasterPos2f(-3, 0);
        string go = "GAME OVER";
        for(int i=0; i<go.length(); i++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, go[i]);
    }
    
    glutSwapBuffers();
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    is_animate = true;
    switch (key) {
        case GLUT_KEY_UP:    angle_val = 270; break;
        case GLUT_KEY_DOWN:  angle_val = 90;  break;
        case GLUT_KEY_LEFT:  angle_val = 180; break;
        case GLUT_KEY_RIGHT: angle_val = 0;   break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 700);
    glutCreateWindow("Pac-Snake Hybrid Fix");

    glEnable(GL_DEPTH_TEST);
    for(int i=0; i<31; i++)
        for(int j=0; j<28; j++)
            tp_array[i][j] = (board_array[i][j] == 0);

    resetGame();
    
    // Inisialisasi Ghost di dalam kotak tengah
    ghosts[0] = new Ghost(13, 14);
    ghosts[1] = new Ghost(14, 14);
    ghosts[2] = new Ghost(13, 15);
    ghosts[3] = new Ghost(14, 15);
    ghosts[3]->color[2] = 1.0f; // Beda warna

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1.33, 1, 100);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}
