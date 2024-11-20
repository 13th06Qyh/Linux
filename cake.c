#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 10
#define HEIGHT 10

int screen[HEIGHT][WIDTH]; // Giả lập màn hình

// Hàm tô màu theo đường biên sử dụng đệ quy
void boundaryFill(int x, int y, int fillColor, int boundaryColor)
{
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    if (screen[y][x] != boundaryColor && screen[y][x] != fillColor)
    {
        screen[y][x] = fillColor;
        boundaryFill(x + 1, y, fillColor, boundaryColor);
        boundaryFill(x - 1, y, fillColor, boundaryColor);
        boundaryFill(x, y + 1, fillColor, boundaryColor);
        boundaryFill(x, y - 1, fillColor, boundaryColor);
    }
}

// Hàm để vẽ hình vuông
void drawSquare(int x, int y, int color)
{
    if (color == 0)
    {
        glColor3f(0.68f, 0.85f, 0.9f); // Màu xanh lam nhạt cho nền
    }
    else if (color == 1)
    {
        glColor3f(1.0f, 0.75f, 0.8f); // Màu hồng nhạt cho hình vuông
    }

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + 1, y);
    glVertex2f(x + 1, y + 1);
    glVertex2f(x, y + 1);
    glEnd();
}

// Hàm hiển thị
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            drawSquare(j, i, screen[i][j]);
        }
    }
    glFlush();
}

// Hàm khởi tạo
void init()
{
    // Khởi tạo màn hình với một đường biên màu 1
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
                screen[i][j] = 0; // Đường biên màu 0 (màu nền)
            else
                screen[i][j] = 1; // Màu 1 cho hình vuông
        }
    }

    // Tô màu và hiển thị
    boundaryFill(1, 1, 2, 1); // Tô màu khu vực bên trong hình vuông với màu 2
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("ToMauDungDeQuy");

    // Thiết lập màu nền xanh lam nhạt
    glClearColor(0.68f, 0.85f, 0.9f, 1.0f);

    // Thiết lập hệ tọa độ
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, 0, HEIGHT, -1, 1); // Thiết lập không gian vẽ

    init();

    glutDisplayFunc(display);
   // glutMainLoop();
    return 0;
}

