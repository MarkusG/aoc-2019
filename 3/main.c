#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 64

typedef struct Point {
	int x;
	int y;
} Point;

typedef struct Line {
	Point p1;
	Point p2;
} Line;

typedef struct LinePair {
	Point hori_left;
	Point hori_right;
	Point vert_top;
	Point vert_bottom;
} LinePair;

int intersects(LinePair pair, Point *intersection);
LinePair parse_points(Point p1, Point p2, Point q1, Point q2);
int distance(Point p, Point q);
int next_input(char *direction, int *length);

int main(int argc, char *argv[])
{
	int bufsize = BUFSIZE;
	Point *wire1 = malloc(bufsize * sizeof(Point));
	int n_points = 0;
	const Point origin = { .x = 0, .y = 0 };
	wire1[n_points++] = origin;
	Point current = origin;

	char direction;
	int amount;
	while (next_input(&direction, &amount))
	{
		switch (direction)
		{
			case 'R':
				current.x += amount;
				break;
			case 'L':
				current.x -= amount;
				break;
			case 'U':
				current.y += amount;
				break;
			case 'D':
				current.y -= amount;
				break;
		}
		if (n_points > bufsize)
		{
			bufsize += BUFSIZE;
			wire1 = realloc(wire1, bufsize * sizeof(Point));
		}
		wire1[n_points++] = current;
	}
	current = origin;
	Point prev;
	Point closest_intersection;
	while (next_input(&direction, &amount))
	{
		prev = current;
		switch (direction)
		{
			case 'R':
				current.x += amount;
				break;
			case 'L':
				current.x -= amount;
				break;
			case 'U':
				current.y += amount;
				break;
			case 'D':
				current.y -= amount;
				break;
		}

		for (int i = 0; i < n_points; i++)
		{
			LinePair pair = parse_points(current, prev, wire1[i], wire1[i + 1]);
			Point intersection;
			if (intersects(pair, &intersection))
			{
				if (distance(intersection, origin) < distance(closest_intersection, origin))
					closest_intersection = intersection;
			}
		}
	}
	printf("(%d, %d)\n", closest_intersection.x, closest_intersection.y);
	return 0;

}

int intersects(LinePair pair, Point *intersection)
{
	if (pair.vert_top.x > pair.hori_left.x && pair.vert_top.x < pair.hori_right.x &&
		pair.hori_left.y > pair.vert_bottom.y && pair.hori_left.y < pair.vert_top.y)
	{
		intersection->x = pair.vert_top.x;
		intersection->y = pair.hori_left.y;
		return 1;
	}
	return 0;
}

LinePair parse_points(Point p1, Point p2, Point q1, Point q2)
{
	LinePair result;
	Point hori_left, hori_right;
	Point vert_top, vert_bottom;
	if (p1.y == p2.y) // first line is horizontal
	{
		if (p1.x > p2.x)
		{
			result.hori_left = p2;
			result.hori_right = p1;
		}
		else
		{
			result.hori_left = p1;
			result.hori_right = p2;
		}
		if (q1.y > q2.y)
		{
			result.vert_top = q1;
			result.vert_bottom = q2;
		}
		else
		{
			result.vert_top = q2;
			result.vert_bottom = q1;
		}
	}
	else // first line is vertical
	{
		if (p1.y > p2.y)
		{
			result.vert_top = p1;
			result.vert_bottom = p2;
		}
		else
		{
			result.vert_top = p2;
			result.vert_bottom = p1;
		}
		if (q1.x > q2.x)
		{
			result.hori_left = q2;
			result.hori_right = q1;
		}
		else
		{
			result.hori_left = q1;
			result.hori_right = q2;
		}
	}
	return result;
}

int next_input(char *direction, int *length)
{
	char c;
	if ((c = getchar()) == EOF || c == '\n')
		return 0;
	else
	{
		*direction = c;
		scanf("%d,", length);
	}
	return 1;
}

int distance(Point p, Point q)
{
	return abs(p.x - q.x) + abs(p.y - q.y);
}
