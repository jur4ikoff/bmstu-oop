#ifndef RENDER_HPP__
#define RENDER_HPP__

#include <QPixmap>

typedef struct _render_type
{
    QPixmap *scene;
    int width, height;
}render_t;


#endif // RENDER_HPP__