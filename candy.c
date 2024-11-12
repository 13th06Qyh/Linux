#include <GL/glut.h>
#include <math.h>

// Các tham số điều khiển góc nhìn và vị trí
float theta = 0.0f;                          // Góc xoay quanh trục Y
float phi = 0.0f;                            // Góc xoay quanh trục X
float zoom = 1.0f;                           // Hệ số phóng to/thu nhỏ
float eyeX = 0.0f, eyeY = 0.0f, eyeZ = 5.0f; // Vị trí quan sát ban đầu

int projectionMode = 0; // 0 = song song, 1 = phối cảnh

// Hàm khởi tạo
void init()
{
    glClearColor(0.1, 0.1, 0.1, 1.0); // Màu nền
    glEnable(GL_DEPTH_TEST);          // Kích hoạt kiểm tra độ sâu
}

// Hàm thiết lập chế độ chiếu
void setProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (projectionMode == 0)
    {
        // Chiếu song song
        glOrtho(-5 * zoom, 5 * zoom, -5 * zoom, 5 * zoom, 1, 100);
    }
    else
    {
        // Chiếu phối cảnh
        gluPerspective(45 * zoom, 1.0, 1, 100);
    }
    glMatrixMode(GL_MODELVIEW);
}

// Hàm vẽ khung dây của một hình lập phương
void drawWireCube()
{
    glutWireCube(2.0); // Sử dụng hàm GLUT để vẽ hình lập phương dạng khung dây
}

// Hàm xử lý vẽ
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Xóa bộ đệm

    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Cài đặt điểm nhìn

    // Xoay theo góc theta và phi
    glRotatef(theta, 0.0, 1.0, 0.0); // Xoay quanh trục Y
    glRotatef(phi, 1.0, 0.0, 0.0);   // Xoay quanh trục X

    drawWireCube(); // Vẽ đối tượng

    glutSwapBuffers(); // Hoán đổi bộ đệm
}

// Hàm xử lý thay đổi kích thước cửa sổ
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); // Cập nhật viewport
    setProjection();                          // Cập nhật chế độ chiếu
}

// Hàm xử lý bàn phím để thay đổi góc xoay và chế độ chiếu
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'p': // Chuyển đổi giữa chiếu song song và phối cảnh
        projectionMode = 1 - projectionMode;
        setProjection();
        break;
    case '+': // Phóng to
        zoom *= 0.9f;
        setProjection();
        break;
    case '-': // Thu nhỏ
        zoom *= 1.1f;
        setProjection();
        break;
    case 'w': // Xoay lên
        phi += 5;
        break;
    case 's': // Xoay xuống
        phi -= 5;
        break;
    case 'a': // Xoay trái
        theta -= 5;
        break;
    case 'd': // Xoay phải
        theta += 5;
        break;
    case 27: // Phím ESC thoát
        exit(0);
        break;
    }
    glutPostRedisplay(); // Cập nhật hình ảnh
}

// Hàm xử lý phím mũi tên để thay đổi vị trí quan sát
void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        eyeY += 0.1f;
        break;
    case GLUT_KEY_DOWN:
        eyeY -= 0.1f;
        break;
    case GLUT_KEY_LEFT:
        eyeX -= 0.1f;
        break;
    case GLUT_KEY_RIGHT:
        eyeX += 0.1f;
        break;
    }
    glutPostRedisplay();
}

// Hàm main
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("3D Object Viewer");

    init();
    setProjection();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glutMainLoop();
    return 0;
}

