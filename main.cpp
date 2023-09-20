#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

float barraX1, barraY1, barraX2, barraY2; 
float corR = 0.0f, corG = 0.0f, corB = 0.0f;
float raqueteX = 0.0f;
float raqueteX2 = 0.0f;
float pi = 3.14159265358979323846;

float bolaX = 0.0f;
float bolaY = 0.0f;
float velocidadeX = 0.01f;
float velocidadeY = 0.01f;

int pontuacaoRaquete1 = 0;
int pontuacaoRaquete2 = 0;


void Raquete() {
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
    glVertex2f(-0.15f + raqueteX, -0.85f);
    glVertex2f(0.15f + raqueteX, -0.85f);
    glVertex2f(0.15f + raqueteX, -0.86f);
    glVertex2f(-0.15f + raqueteX, -0.86f);
    glEnd();
}

void Raquete2() {
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
    glVertex2f(-0.15f + raqueteX2, 0.85f);
    glVertex2f(0.15f + raqueteX2, 0.85f);
    glVertex2f(0.15f + raqueteX2, 0.86f);
    glVertex2f(-0.15f + raqueteX2, 0.86f);
    glEnd();
}

void Bola() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i += 10) {
        float angulo = i * pi / 180.0;
        float x = bolaX + 0.02f * cos(angulo);
        float y = bolaY + 0.02f * sin(angulo);
        glVertex2f(x, y);
    }
    glEnd();
}

void Linhas() {
     glColor3f(1.0f, 1.0f, 1.0f);
    
    glBegin(GL_QUADS);
    glVertex2f(-0.95f, 0.0f);
    glVertex2f(0.95f, 0.0f);
    glVertex2f(0.95f, 0.01f);
    glVertex2f(-0.95f, 0.01f);
    glEnd();
}


void Teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            raqueteX -= 0.1f;
            break;
        case 'd':
            raqueteX += 0.1f;
            break;
        case 'j':
             raqueteX2 -= 0.1f;
             break;
        case 'l':
             raqueteX2 += 0.1f;
             break;
    }
    glutPostRedisplay();
}

bool ColisaoBolaRaquete(float bolaX, float bolaY, float raqueteX, float raqueteY) {
    if (bolaX >= raqueteX - 0.15f && bolaX <= raqueteX + 0.15f) {
        if (bolaY <= raqueteY + 0.02f && bolaY >= raqueteY - 0.02f) {
            return true;
        }
    }
    return false;
}


void AtualizarBola() {
    bolaX += velocidadeX;
    bolaY += velocidadeY;
    
    
    if (bolaX + 0.02f > 1.0f || bolaX - 0.02f < -1.0f) {
        velocidadeX = -velocidadeX;
    }
    if (bolaY + 0.02f > 1.0f || bolaY - 0.02f < -1.0f) {
        velocidadeY = -velocidadeY;
    }

    // Verificar colisão com a raquete inferior
    if (ColisaoBolaRaquete(bolaX, bolaY, raqueteX, -0.85f)) {
        velocidadeY = -velocidadeY;
    }

    // Verificar colisão com a raquete superior
    if (ColisaoBolaRaquete(bolaX, bolaY, raqueteX2, 0.85f)) {
        velocidadeY = -velocidadeY;
    }

    // Verificar se a bola atingiu a borda superior
    if (bolaY + 0.02f > 1.0f) {
        pontuacaoRaquete1++;
        bolaX = 0.0f;
        bolaY = 0.0f;

        velocidadeX = 0.01f;
        velocidadeY = -0.01f;
    }

    // Verificar se a bola atingiu a borda inferior
    if (bolaY - 0.02f < -1.0f) {
        pontuacaoRaquete2++;
        bolaX = 0.0f;
        bolaY = 0.0f;

        velocidadeX = 0.01f;
        velocidadeY = 0.01f;
    }
}

void DesenharPontuacao() {
    glColor3f(1.0f, 1.0f, 1.0f);
    
    char pontuacaoStr[50];
    
    snprintf(pontuacaoStr, sizeof(pontuacaoStr), "Raquete 1: %d", pontuacaoRaquete1);
    
    glRasterPos2f(-0.9f, 0.9f);
    for (int i = 0; pontuacaoStr[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, pontuacaoStr[i]);
    }

    snprintf(pontuacaoStr, sizeof(pontuacaoStr), "Raquete 2: %d", pontuacaoRaquete2);
    
    glRasterPos2f(0.6f, 0.9f);
    for (int i = 0; pontuacaoStr[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, pontuacaoStr[i]);
    }
}




void Timer(int value) {
    AtualizarBola();
    glutPostRedisplay();
    glutTimerFunc(16, Timer, 0);
}


void Cenario() {
   glClearColor(corR, corG, corB, 0.0f);
   glClear(GL_COLOR_BUFFER_BIT);

   Linhas();
   Raquete();
   Raquete2();
   Bola();
   DesenharPontuacao();

   glFlush();
   glutSwapBuffers();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Trabalho ICG - Vinicius Siess");
    glutDisplayFunc(Cenario);
    
    glutKeyboardFunc(Teclado);
    glutTimerFunc(0, Timer, 0);
    glutMainLoop();
    return 0;
}
