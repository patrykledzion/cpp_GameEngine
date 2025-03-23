#include "Drawing.h"
#include "Window.h"

void nWindow::Drawing::Begin()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void nWindow::Drawing::DrawRectangle(Vector3* pos, Vector3 *size, Color* color)
{
    Rectangle rect;
    rect.v1.x = pos->x;
    rect.v1.y = pos->y;
    rect.v1.z = 0;


    rect.v2.x = pos->x + size->x;
    rect.v2.y = pos->y;
    rect.v2.z = 0;

    rect.v3.x = pos->x + size->x;
    rect.v3.y = pos->y + size->y;
    rect.v3.z = 0;

    rect.v4.x = pos->x;
    rect.v4.y = pos->y + size->y;
    rect.v4.z = 0;

    Drawing::DrawRectangle(&rect, color);
}

void nWindow::Drawing::DrawRectangle(Vector3* pos, Vector3 *size, Color* color, Texture* texture)
{
    Rectangle rect;
    rect.v1.x = pos->x;
    rect.v1.y = pos->y;
    rect.v1.z = 0;


    rect.v2.x = pos->x + size->x;
    rect.v2.y = pos->y;
    rect.v2.z = 0;

    rect.v3.x = pos->x + size->x;
    rect.v3.y = pos->y + size->y;
    rect.v3.z = 0;

    rect.v4.x = pos->x;
    rect.v4.y = pos->y + size->y;
    rect.v4.z = 0;

    Drawing::DrawRectangle(&rect, color, texture);
}

void nWindow::Drawing::DrawRectangle(Vector3* pos, Vector3 *size, Color* color, Texture* texture, Rectangle chunk)
{
    Rectangle rect;
    rect.v1.x = pos->x;
    rect.v1.y = pos->y;
    rect.v1.z = 0;


    rect.v2.x = pos->x + size->x;
    rect.v2.y = pos->y;
    rect.v2.z = 0;

    rect.v3.x = pos->x + size->x;
    rect.v3.y = pos->y + size->y;
    rect.v3.z = 0;

    rect.v4.x = pos->x;
    rect.v4.y = pos->y + size->y;
    rect.v4.z = 0;

    Drawing::DrawRectangle(&rect, color, texture, chunk);
}

void nWindow::Drawing::DrawRectangle(Rectangle* rectangle, Color* color)
{
    nWindow::Color _color = color == nullptr ? Color{ 1,1,1,1 } : *color;
	glColor4f(_color.r, _color.g, _color.b, _color.a);
	glBegin(GL_QUADS);
	glVertex3f(rectangle->v1.x, rectangle->v1.y, rectangle->v1.z);
	glVertex3f(rectangle->v2.x, rectangle->v2.y, rectangle->v2.z);
	glVertex3f(rectangle->v3.x, rectangle->v3.y, rectangle->v3.z);
	glVertex3f(rectangle->v4.x, rectangle->v4.y, rectangle->v4.z);
	glEnd();
	glColor4f(1, 1, 1, 1);
}

void nWindow::Drawing::DrawRectangle(Rectangle* rectangle, Color* color, Texture* texture)
{
    glBindTexture(GL_TEXTURE_2D, texture->tex);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (texture->tex == 0) return;

    glMatrixMode(GL_TEXTURE); 
    nWindow::Color _color = color == nullptr ? Color{ 1,1,1,1 } : *color;
    glColor4f(_color.r, _color.g, _color.b, _color.a);
    glBegin(GL_QUADS);
    glTexCoord2f(0.f, 1.f); glVertex3f(rectangle->v1.x, rectangle->v1.y, rectangle->v1.z);
    glTexCoord2f(1.f, 1.f); glVertex3f(rectangle->v2.x, rectangle->v2.y, rectangle->v2.z);
    glTexCoord2f(1.f, 0.f); glVertex3f(rectangle->v3.x, rectangle->v3.y, rectangle->v3.z);
    glTexCoord2f(0.f, 0.f); glVertex3f(rectangle->v4.x, rectangle->v4.y, rectangle->v4.z);
    glEnd();
}

void nWindow::Drawing::DrawRectangle(Rectangle* rectangle, Color* color, Texture* texture, Rectangle chunk)
{
    glBindTexture(GL_TEXTURE_2D, texture->tex);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (texture->tex == 0) return;

    glMatrixMode(GL_TEXTURE);
    nWindow::Color _color = color == nullptr ? Color{ 1,1,1,1 } : *color;
    glColor4f(_color.r, _color.g, _color.b, _color.a);
    glBegin(GL_QUADS);
    glTexCoord2f(chunk.v1.x / texture->width, 1.f - chunk.v1.y / texture->height);
    glVertex3f(rectangle->v1.x, rectangle->v1.y, rectangle->v1.z);
    glTexCoord2f(chunk.v2.x / texture->width, 1.f - chunk.v2.y / texture->height);
    glVertex3f(rectangle->v2.x, rectangle->v2.y, rectangle->v2.z);
    glTexCoord2f(chunk.v3.x / texture->width, 1.f - chunk.v3.y / texture->height);
    glVertex3f(rectangle->v3.x, rectangle->v3.y, rectangle->v3.z);
    glTexCoord2f(chunk.v4.x / texture->width, 1.f - chunk.v4.y / texture->height);
    glVertex3f(rectangle->v4.x, rectangle->v4.y, rectangle->v4.z);
    glEnd();
}


nWindow::Texture* nWindow::Drawing::LoadTexture(nWindow::Image* image)
{
    GLuint  tex;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, (GLsizei)image->GetSize().first, (GLsizei)image->GetSize().second, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, image->buffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    nWindow::Texture* texture = new Texture;
    texture->width = image->GetSize().first;
    texture->height = image->GetSize().second;
    texture->tex = tex;

    return texture;
}



void nWindow::Drawing::End(nWindow::Window* window)
{
    SwapBuffers(window->hdc);
}
