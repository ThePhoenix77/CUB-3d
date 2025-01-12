# include "cub3d.h"

void calculate_line_steps(int x1, int y1, int x2, int y2, int *dx, int *dy, int *p)
{
    *dx = abs(x2 - x1);
    *dy = abs(y2 - y1);
    *p = 2 * (*dy) - (*dx); // Bresenham algo
}

void draw_horizontal_line(t_img *img, int *x, int *y, int *p, int dx, int dy, int x2, int y2, int color)
{
    while (*x <= x2)
    {
        draw_pixel(img, *x, *y, color);
        if (*p > 0)
        {
            if (y2 > *y)
                *y += 1;
            else
                *y -= 1;
            *p -= 2 * dx;
        }
        *p += 2 * dy;
        (*x)++;
    }
}

void draw_vertical_line(t_img *img, int *x, int *y, int *p, int dx, int dy, int x2, int y2, int color)
{
    while (*y <= y2)
    {
        draw_pixel(img, *x, *y, color);
        if (*p > 0)
        {
            if (x2 > *x)
                *x += 1;
            else
                *x -= 1;
            *p -= 2 * dy;
        }
        *p += 2 * dx;
        (*y)++;
    }
}

void draw_line(t_img *img, int x1, int y1, int x2, int y2, int color)
{
    int dx, dy, p, x, y;

    calculate_line_steps(x1, y1, x2, y2, &dx, &dy, &p);
    x = x1;
    y = y1;

    // Choosing if it s a horizontal or vertical line
    if (dx > dy)
    {
        if (x1 > x2)
            draw_horizontal_line(img, &x, &y, &p, dx, dy, x2, y2, color);
        else
            draw_horizontal_line(img, &x, &y, &p, dx, dy, x2, y2, color);
    }
    else
    {
        if (y1 > y2)
            draw_vertical_line(img, &x, &y, &p, dx, dy, x2, y2, color);
        else
            draw_vertical_line(img, &x, &y, &p, dx, dy, x2, y2, color);
    }
}

/*
 * The functions `draw_horizontal_line` and `draw_vertical_line` implement
 * Bresenham's line-drawing algorithm, a widely-used method for rendering
 * straight lines on a grid (like a pixel-based image). The principle is based
 * on using a decision parameter (`p`) to determine the best approximation of
 * the true geometric line, avoiding floating-point calculations for efficiency.
 *
 * 1. `draw_horizontal_line`: This function handles lines where the slope
 *    (|dy/dx|) is less than or equal to 1, meaning the primary direction
 *    of movement is along the x-axis. For each step along x, the function
 *    uses the decision parameter (`p`) to determine whether to adjust the y
 *    coordinate, ensuring the line stays close to its true path.
 *
 * 2. `draw_vertical_line`: This function deals with lines where the slope
 *    (|dy/dx|) is greater than 1, meaning the primary direction of movement
 *    is along the y-axis. Similarly, for each step along y, the decision
 *    parameter determines if the x coordinate needs to be adjusted to
 *    approximate the geometric line accurately.
 *
 * Both functions use integer arithmetic, making the algorithm efficient
 * and suitable for systems with limited computational power. The decision
 * parameter ensures pixel-perfect accuracy by balancing horizontal and
 * vertical steps, depending on the line's direction and steepness.
 */

/*
 * The `calculate_line_steps` function computes the necessary steps for
 * drawing a line between two points (x1, y1) and (x2, y2) using Bresenham's 
 * line-drawing algorithm. It calculates the absolute differences between 
 * the x and y coordinates (dx and dy), and it computes the decision parameter 
 * `p`, which will be used to determine whether the next pixel should 
 * be placed horizontally or vertically. The formula for the decision parameter 
 * is: p = 2 * dy - dx, which is essential for making the decision at each step.
 * This step ensures that we can choose the best pixel to draw to approximate 
 * the straight line. The result of the function is stored in the pointers 
 * passed as arguments for dx, dy, and p, which are then used in the drawing 
 * functions.
 *
 * The `draw_line` function is responsible for using the steps calculated 
 * by `calculate_line_steps` to draw the line on the image. It checks whether 
 * the line is more horizontal or vertical by comparing the differences between
 * dx and dy. If dx is greater than dy, the line has a shallow slope (horizontal),
 * and the `draw_horizontal_line` function is used. If dy is greater than dx,
 * the line has a steep slope (vertical), and the `draw_vertical_line` function is used.
 * The decision parameter `p` guides whether to move horizontally or vertically 
 * at each step, ensuring the line is drawn with minimal error, maintaining 
 * accuracy in pixel placement.
 */


