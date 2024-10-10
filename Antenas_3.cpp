// Strategy: it takes the point with the least density in the neighborhood of the previous one and sets up an antenna at the densest point containing it.

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <random>
#include <array>
#include <ctime>

using namespace std;

#define R 6378100

// -----------------------------------------------------------------------

class Point {

public:
    void init(int i, double x, double y);
    array<double, 2> get_coord( );
    double dist_to(Point *p);

    bool covered = false, center = false;

private:
    int i;
    double x, y;
};

void Point::init(int i, double x, double y) {
    this->i = i;
    this->x = x;
    this->y = y;
}

array<double, 2> Point::get_coord( ) {
    return {this->x, this->y};
}

double Point::dist_to(Point *p) {
    array<double, 2> coord = p->get_coord( );

    return sqrt(pow(this->x - coord[0], 2) + pow(this->y - coord[1], 2));
}

// -----------------------------------------------------------------------

int get_num_uncov(int N, Point *points) {
    int n = 0;

    for(int i = 0; i < N && !points[i].covered; i++)
        n++;

    return n;
}

int get_point_cov(int N, int r, Point *points, int p) {
    int q = 0;

    for(int i = 0; i < N; i++)
        if(!points[i].covered && points[p].dist_to(&points[i]) <= r)
            q++;

    return q;
}

int set_random_point(int N, Point *points) {
    int n = get_num_uncov(N, points);
    int r = 1 + rand( )%n;

    for(int i = 0; i < N; i++)
        if(!points[i].covered) {
            r--;

            if(r == 0)
                return i;
        }
    
    return -1;
}

int get_denser(int N, double r, Point *points, int p) {
    int max_cov = 0;
    int best_point = -1;

    int cov;

    for(int i = 0; i < N; i++)
        if(!points[i].covered && points[p].dist_to(&points[i]) <= r) {
            cov = get_point_cov(N, r, points, i);

            if(cov > max_cov) {
                max_cov = cov;
                best_point = i;
            }
        }

    return best_point;
}

int set_next(int N, double r, Point *points, int prev_c) {
    double d, min_dist = numeric_limits<double>::infinity( );

    for(int i = 0; i < N; i++)
        if(!points[i].covered) {
            d = points[prev_c].dist_to(&points[i]);

            if(d < min_dist)
                min_dist = d;
        }

    int cov, min_cov = numeric_limits<int>::max( );
    int best_point = -1;

    for(int i = 0; i < N; i++)
        if(!points[i].covered) {
            d = points[prev_c].dist_to(&points[i]);

            if(min_dist <= d && d <= r + min_dist) {
                cov = get_point_cov(N, r, points, i);
                
                if(cov < min_cov) {
                    min_cov = cov;
                    best_point = i;
                }
            }
        }
    
    if(best_point == -1)
        return get_denser(N, r, points, set_random_point(N, points));
    
    return get_denser(N, r, points, best_point);
}

double set_antena(int N, int r, Point *points, int c) {
    points[c].center = true;

    int q = 0;

    for(int i = 0; i < N; i++)
        if(!points[i].covered && points[c].dist_to(&points[i]) <= r) {
            points[i].covered = true;
            q++;
        }

    cout << c << " " << "\n";

    return double(q)/N;
}

void read_file(int &N, double &r, Point *&points) {
    FILE *file = fopen("C:\\Users\\Gustavo\\OneDrive\\Documentos\\GitHub\\Antenas\\NewYork.txt", "rt");

    while (!isdigit (fgetc (file)));
    fseek (file, -1, SEEK_CUR);
    fscanf (file, "%d", &N);

    while (!isdigit (fgetc (file)));
    fseek (file, -1, SEEK_CUR);
    fscanf (file, "%lf", &r);

    while (!isdigit (fgetc (file)));
    fseek (file, -1, SEEK_CUR);

    points = new Point[N];

    for(int i = 0; i < N; i++) {
        double lat, lon;

        fscanf(file, "%lf", &lat);
        fscanf(file, "%lf", &lon);

        points[i].init(i, R*lat*M_PI/180, R*lon*M_PI/180);
    }

    fclose (file);
}

// -----------------------------------------------------------------------

int main( ) {

    srand(time(NULL));

    int N, n = 0;
    double r;
    double cx = 0;
    Point *points;

    read_file(N, r, points);

    int c = set_random_point(N, points);
    n++;
    cx += set_antena(N, r, points, c);

    while (cx < 1 && c != -1) {
        c = set_next(N, r, points, c);
        n++;
        cx += set_antena(N, r, points, c);
    }

    delete[] points;

    return 0;
}

