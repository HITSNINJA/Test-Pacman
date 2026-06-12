//############################################################
// PAC-SNAKE 3D Perspective Game
// Fitur: Menambah panjang ekor seperti Snake saat makan pebble
// Cocok dijalankan langsung di Dev-C++ Windows
//############################################################

#define GL_SILENCE_DEPRECATION
#include <GL/glut.h>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <ctype.h>
#include <deque>    // WAJIB untuk mekanik Snake
#include <utility>  // WAJIB untuk pair

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
    {0,0,0,0,0,6,0,2,4,0,8,5,0,0,0,0,5,7,0,2,4,0,6,0,0,0,0,0}, // Pintu hantu terbuka (0,0)
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

int pebble_array[31][28];

//############################################################
// GLOBAL VARIABLES
//############################################################

GLuint list[6];
int tp_array[31][28];
int pebbles_left;
double speed1 = 0.15; // Disesuaikan kecepatannya agar luwes meliuk
double angle1 = 90;
bool animate = false;
int lives = 3;
int points = 0;
bool gameover = false;
int num_ghosts = 4;
int start_timer = 3;
unsigned char ckey = 'w';

// TUBUH PAC-SNAKE (Menggunakan Deque dengan spasi > > untuk kompiler lama)
deque<pair<double, double> > pacman_body;
bool food_eaten = false;

//############################################################
// CLASS GHOST
//############################################################
class Ghost {
public:
    bool transporting;
    float color[3];
    double speed;
    bool in_jail;
    int jail_timer;
    double angle;
    double x, y;
    bool isExiting; // Memaksa hantu keluar pintu tengah terlebih dahulu

    Ghost(double tx, double ty) {
        x = tx; y = ty;
        angle = 270; // Hadap ke atas awal mula
        speed = 0.05;
        in_jail = true;
        jail_timer = 500;
        transporting = false;
        isExiting = true;
        color[0] = 1; color[1] = 0; color[2] = 0;
    }
    void Move();
    void Update(void);
    void Chase(double, double, bool*);
    bool Catch(double, double);
    void Reinit(void);
    void Draw(void);
};

Ghost *ghost[4];

void Ghost::Reinit(void) {
    in_jail = true;
    isExiting = true;
    angle = 270;
}

void Ghost::Move() {
    x += speed * cos(M_PI / 180 * angle);
    y += speed * sin(M_PI / 180 * angle);
    if (isExiting && y < 12.5) isExiting = false; // Matikan mode keluar jika sudah di luar
}

void Ghost::Update(void) {
    if ((int)x == 0 && (int)y == 14 && (!transporting)) angle = 180;
    if (x < 0.1 && (int)y == 14) { x = 26.9; transporting = true; }
    if ((int)x == 27 && (int)y == 14 && (!transporting)) angle = 0;
    if (x > 26.9 && (int)y == 14) { x = 0.1; transporting = true; }
    
    if (in_jail && (int)(y + 0.9) == 11) { in_jail = false; angle = 0; }
    if (in_jail && ((int)x == 13 || (int)x == 14)) angle = 270;
    
    if (jail_timer == 0 && in_jail) {
        if (x < 13) angle = 0;
        if (x > 14) angle = 180;
    }
    if (jail_timer > 0) jail_timer--;
}

bool Ghost::Catch(double px, double py) {
    return (px - x < 0.5 && px - x > -0.5 && py - y < 0.5 && py - y > -0.5);
}

void Ghost::Chase(double px, double py, bool *open_move) {
    double targetX = isExiting ? 13.5 : px;
    double targetY = isExiting ? 12.0 : py;

    if (fmod(x + 0.05, 1.0) < 0.2 && fmod(y + 0.05, 1.0) < 0.2) {
        double min_dist = 9999.0;
        double best_angle = angle;
        for (int i = 0; i < 4; i++) {
            double try_a = i * 90;
            if (abs(try_a - angle) == 180) continue;
            if (open_move[i]) {
                double nx = x + cos(M_PI/180 * try_a);
                double ny = y + sin(M_PI/180 * try_a);
                double dist = sqrt(pow(targetX - nx, 2) + pow(targetY - ny, 2));
                if (dist < min_dist) { min_dist = dist; best_angle = try_a; }
            }
        }
        angle = best_angle;
    }
}

void Ghost::Draw(void) {
    glColor3f(color[0], color[1], color[2]);
    glPushMatrix();
    glTranslatef(x, -y, 0.75); // Berada di tengah dinding 3D
    glTranslatef(0.5, 0.6, 0);
    glTranslatef((float)BOARD_X / -2.0f, (float)BOARD_Y / 2.0f, 0);
    glutSolidSphere(.45, 15, 15);
    glPopMatrix();
}

//############################################################
// PAC-SNAKE MECHANIC
//############################################################

bool Open(int col, int row) {
    if (row < 0 || row >= 31 || col < 0 || col >= 28) return false;
    return (board_array[row][col] <= 0 || board_array[row][col] == 11);
}

void MovePacSnake() {
    // Hitung posisi kepala baru berdasarkan arah input
    double nx = pacman_body[0].first + speed1 * cos(M_PI / 180 * angle1);
    double ny = pacman_body[0].second + speed1 * sin(M_PI / 180 * angle1);

    // Deteksi Batas Jalur Labirin
    if (Open((int)(nx + 0.5), (int)(ny + 0.5))) {
        int gx = (int)(nx + 0.5);
        int gy = (int)(ny + 0.5);

        // Jika kepala menyentuh pebble -> MAKAN!
        if (tp_array[gy][gx] == 1) {
            tp_array[gy][gx] = 0;
            pebbles_left--;
            points += 10;
            food_eaten = true; // Set penanda tumbuh
        }

        // push_front untuk meletakkan kepala baru di posisi terdepan ular
        pacman_body.push_front(make_pair(nx, ny));

        if (!food_eaten) {
            pacman_body.pop_back(); // Jika tidak makan, ekor dihapus (jalan biasa)
        } else {
            food_eaten = false;     // Jika makan, jangan pop_back! Tubuh memanjang otomatis
        }
    } else {
        animate = false; // Berhenti jika membentur dinding
    }
}

void DrawPacSnake(void) {
    // Lakukan iterasi sepanjang kontainer deque untuk menggambar kepala & seluruh badan ular
    for (size_t i = 0; i < pacman_body.size(); i++) {
        if (i == 0) {
            glColor3f(1.0, 1.0, 0.0); // Kepala kuning terang
        } else {
            // Gradasi warna badan semakin ke belakang semakin pudar/hijau-kekuningan
            float shift = (float)i / (float)pacman_body.size();
            glColor3f(1.0 - (shift * 0.4), 1.0 - (shift * 0.2), 0.0);
        }

        glPushMatrix();
        glTranslatef(pacman_body[i].first, -pacman_body[i].second, 0.75); // Posisi Z melayang proporsional
        glTranslatef(0.5, 0.6, 0);
        glTranslatef((float)BOARD_X / -2.0f, (float)BOARD_Y / 2.0f, 0);
        glutSolidSphere(i == 0 ? 0.55 : 0.42, 15, 15); // Kepala sedikit lebih besar dibanding segmen badannya
        glPopMatrix();
    }
}

// Cek tabrakan kepala ular dengan tubuhnya sendiri (Aturan Game Snake)
bool CheckSelfCollision() {
    if (pacman_body.size() < 5) return false;
    for (size_t i = 4; i < pacman_body.size(); i++) {
        double dist = sqrt(pow(pacman_body[0].first - pacman_body[i].first, 2) + 
                           pow(pacman_body[0].second - pacman_body[i].second, 2));
        if (dist < 0.2) return true; // Tabrakan terdeteksi
    }
    return false;
}

void tp_restore(void) {
    for (int ISO = 0; ISO < BOARD_X; ISO++) {
        for (int j = 0; j < BOARD_Y; j++) {
            // Mengisi papan pebble_array asli dari board_array kosong
            pebble_array[ISO][j] = (board_array[ISO][j] == 0) ? 1 : 0;
            tp_array[ISO][j] = pebble_array[ISO][j];
        }
    }
    pebbles_left = 244;
}

void ResetPacman() {
    pacman_body.clear();
    pacman_body.push_front(make_pair(13.5, 23.0)); // Mulai kembali dengan kepala saja
    angle1 = 0;
    animate = false;
}

void G_Reinit(void) {
    start_timer = 3;
    int start_x[4] = {11, 12, 15, 16};
    float ghost_colors[4][3] = {{255,0,0},{120,240,120},{255,200,200},{255,125,0}};
    for (int i = 0; i < num_ghosts; i++) {
        ghost[i]->Reinit();
        ghost[i]->x = start_x[i]; ghost[i]->y = 14;
        ghost[i]->jail_timer = i * 33 + 66; ghost[i]->speed = 0.05; 
        for (int j = 0; j < 3; j++) ghost[i]->color[j] = ghost_colors[i][j] / 255.0f;
    }
}

void Write(char *string) {
    while (*string) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
}

void DrawMaze(void) {
    for (int ISO = 0; ISO < BOARD_X; ISO++) {
        for (int j = 0; j < BOARD_Y; j++) {
            int call_this = 0;
            glPushMatrix();
            glTranslatef(-(float)BOARD_X / 2.0f, -(float)BOARD_Y / 2.0f, 0);
            glTranslatef(j, BOARD_Y - ISO, 0);
            glPushMatrix();
            glTranslatef(0.5, 0.5, 0);
            switch (board_array[ISO][j]) {
                case 4:  glRotatef(90.0, 0, 0, 1);
                case 3:  glRotatef(90.0, 0, 0, 1);
                case 2:  glRotatef(90.0, 0, 0, 1);
                case 1:  call_this = 1; break;
                case 6:  glRotatef(90.0, 0, 0, 1);
                case 5:  call_this = 2; break;
                case 10: glRotatef(90.0, 0, 0, 1);
                case 9:  glRotatef(90.0, 0, 0, 1);
                case 8:  glRotatef(90.0, 0, 0, 1);
                case 7:  call_this = 3; break;
            }
            glScalef(1, 1, 1.5); // Dinding 3D menjulang tinggi
            glTranslatef(-0.5, -0.5, 0);
            glCallList(list[call_this]);
            glPopMatrix();
            if (call_this != 0 || board_array[ISO][j] == 11) {
                glTranslatef(0, 0, -0.5);
                glCallList(list[4]);
            }
            glPopMatrix();
            
            // Gambar makanan melayang di atas lantai labirin
            if (tp_array[ISO][j] == 1) {
                glColor3f(1.0, 1.0, 1.0);
                glPushMatrix();
                glTranslatef(-(float)BOARD_X / 2.0f, -(float)BOARD_Y / 2.0f, 0.5);
                glTranslatef(j, BOARD_Y - ISO, 0);
                glTranslatef(0.5, 0.5, 0.2);
                glutSolidSphere(0.15, 8, 8);
                glPopMatrix();
            }
        }
    }
    DrawPacSnake();
}

void RenderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Tunneling samping kiri-kanan
    if ((int)pacman_body[0].first == 27 && (int)pacman_body[0].second == 14 && angle1 == 0) {
        pacman_body[0].first = 0; animate = true;
    } else if ((int)(pacman_body[0].first + 0.9) == 0 && (int)pacman_body[0].second == 14 && angle1 == 180) {
        pacman_body[0].first = 27; animate = true;
    }
    
    if (animate) {
        MovePacSnake();
        // Cek jika menabrak diri sendiri
        if (CheckSelfCollision()) {
            lives--;
            ResetPacman();
            if (lives <= 0) gameover = true;
        }
    }
    
    if (!(Open((int)(pacman_body[0].first + 0.5 * cos(M_PI / 180 * angle1)), (int)(pacman_body[0].second + 0.5 * sin(M_PI / 180 * angle1))))) 
        animate = false;
        
    if (pebbles_left == 0) { G_Reinit(); ResetPacman(); tp_restore(); points = 0; lives = 3; }
    
    if (!gameover) DrawMaze();
    
    // Pemrosesan pergerakan Hantu mengejar Pacman
    for (int d = 0; d < num_ghosts; d++) {
        if (!gameover && start_timer == 0) ghost[d]->Update();
        if (!ghost[d]->in_jail && ghost[d]->x - (int)ghost[d]->x < 0.1 && ghost[d]->y - (int)ghost[d]->y < 0.1) {
            bool open_m[4];
            for (int ang = 0; ang < 4; ang++)
                open_m[ang] = Open((int)(ghost[d]->x + cos(M_PI / 180 * ang * 90)), (int)(ghost[d]->y + sin(M_PI / 180 * ang * 90)));
            ghost[d]->Chase(pacman_body[0].first, pacman_body[0].second, open_m);
        }
        if (!gameover && start_timer == 0) ghost[d]->Move();
        ghost[d]->Draw();
        
        // Deteksi hantu menangkap KEPALA Pacman
        if (ghost[d]->Catch(pacman_body[0].first, pacman_body[0].second)) {
            lives--;
            if (lives == 0) gameover = true;
            ResetPacman();
            break;
        }
    }
    
    // HUD overlay 2D tetap datar di depan layar perspektif
    glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity(); gluOrtho2D(0, 100, 0, 100);
    glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();
    char tmp_str[50];
    if (gameover) { glColor3f(1, 0, 0); glRasterPos2f(45, 50); sprintf(tmp_str, "GAME OVER"); Write(tmp_str); }
    glColor3f(1, 1, 0); glRasterPos2f(72, 95); sprintf(tmp_str, "Points: %d | Size: %d", points, (int)pacman_body.size()); Write(tmp_str);
    glColor3f(1, 0, 1); glRasterPos2f(42, 95); sprintf(tmp_str, "PAC-SNAKE 3D"); Write(tmp_str);
    glColor3f(1, 1, 0); glRasterPos2f(5, 95);  sprintf(tmp_str, "Lives: %d", lives); Write(tmp_str);
    glMatrixMode(GL_PROJECTION); glPopMatrix(); glMatrixMode(GL_MODELVIEW); glPopMatrix();
    
    glutSwapBuffers();
    glutPostRedisplay();
}

void create_list_lib() {
    for (int i = 1; i <= 3; i++) {
        list[i] = glGenLists(1);
        glNewList(list[i], GL_COMPILE);
        glColor3f(0.12, 0.25, 0.85); // Dinding biru neon kokoh
        glutSolidCube(1.0);
        glEndList();
    }
    list[4] = glGenLists(1); glNewList(list[4], GL_COMPILE); glColor3f(0.1, 0.1, 0.2); glutSolidCube(1.0); glEndList();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluPerspective(60, 1.5, 0.1, 100);
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    // Kamera dimiringkan serong (isometris) demi efek kedalaman lorong 3D nyata
    gluLookAt(0.0, -14.5, 27.5,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
}

void mykey(unsigned char key, int x, int y) { if (start_timer > 0) start_timer--; }

void specialDown(int key, int x, int y) {
    if (start_timer > 0) start_timer--;
    ckey = key;
    if (key == GLUT_KEY_UP && Open((int)pacman_body[0].first, (int)(pacman_body[0].second - 1)))    { animate = true; angle1 = 270; }
    else if (key == GLUT_KEY_DOWN && Open((int)pacman_body[0].first, (int)(pacman_body[0].second + 1))) { animate = true; angle1 = 90; }
    else if (key == GLUT_KEY_LEFT && Open((int)(pacman_body[0].first - 1), (int)pacman_body[0].second)) { animate = true; angle1 = 180; }
    else if (key == GLUT_KEY_RIGHT && Open((int)(pacman_body[0].first + 1), (int)pacman_body[0].second)){ animate = true; angle1 = 0; }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1200, 780);
    glutCreateWindow("Pac-Snake 3D Edition - Dev-C++");
    init();
    create_list_lib();
    glutKeyboardFunc(mykey);
    glutSpecialFunc(specialDown);
    glutDisplayFunc(RenderScene);
    
    int start_x[4] = {11, 12, 15, 16};
    for (int ISO = 0; ISO < num_ghosts; ISO++) ghost[ISO] = new Ghost(start_x[ISO], 14);
    G_Reinit();
    
    tp_restore();
    ResetPacman();
    
    glutMainLoop();
    return 0;
}
