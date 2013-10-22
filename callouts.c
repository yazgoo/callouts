#include <cairo/cairo.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
void draw_filled_circle(cairo_t* cr, int width, int height)
{
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_move_to(cr, width/2, height/2);
    cairo_arc(cr, width/2, height/2, width/2, 0, 2.1 * M_PI);
    cairo_fill(cr);
}
void draw_text(cairo_t* cr, int width, int height, const char* text)
{
    cairo_text_extents_t extents;
    cairo_select_font_face(cr, "arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 0.7 * width * (strlen(text) == 1 ? 1.5 : 1));
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_text_extents(cr, text, &extents);
    cairo_move_to(cr, width/2-(extents.width/2 + extents.x_bearing),
            height/2-(extents.height/2 + extents.y_bearing));
    cairo_show_text(cr, text);
}
void create_callout(int width, int height, const char* text)
{
    cairo_surface_t *surface =
        cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cairo_t *cr =
        cairo_create(surface);
    char* file_name = calloc(sizeof(char), strlen(text) + 5);
    strcpy(file_name, text);
    strcat(file_name, ".png");
    draw_filled_circle(cr, width, height);
    draw_text(cr, width, height, text);
    cairo_destroy(cr);
    cairo_surface_write_to_png(surface, file_name);
    free(file_name);
    cairo_surface_destroy(surface);
}
int main(int argc, char** argv)
{
    int width, height;
    int i;
    if(argc < 4)
    {
        printf("Create callouts with number\n");
        printf("Usage: %s width height text1 [text2 [text3...]]\n", *argv);
        return 1;
    }
    width = atoi(argv[1]);
    height = atoi(argv[1]);
    for(i = 1; i < argc; i++) create_callout(width, height, argv[i]);
    return 0;
}
