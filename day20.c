#include <mem.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Particle {
    int px;
    int py;
    int pz;
    int vx;
    int vy;
    int vz;
    int ax;
    int ay;
    int az;
    int collided;
} Particle;

int main() {
    Particle particles[2000];
    int particle_count = 0;

    char buf[100] = {};
    int line_count = 0;
    while (strlen(fgets(buf, 100, stdin)) > 1) {
        buf[strlen(buf) - 1] = '\0';

        Particle p;
        p.collided = 0;
        sscanf(buf, "p=<%d,%d,%d>, v=<%d,%d,%d>, a=<%d,%d,%d>", &p.px, &p.py, &p.pz, &p.vx, &p.vy, &p.vz, &p.ax, &p.ay,
               &p.az);
        particles[particle_count++] = p;
    }

    int closest_idx;
    int closest_acc = 999999999;
    int closest_vel = 999999999;
    int closest_pos = 999999999;
    for (int i = 0; i < particle_count; i++) {
        Particle *p = &particles[i];
        int pos = abs(p->px) + abs(p->py) + abs(p->pz);
        int vel = abs(p->vx) + abs(p->vy) + abs(p->vz);
        int acc = abs(p->ax) + abs(p->ay) + abs(p->az);
        if (acc < closest_acc || (acc == closest_acc && vel < closest_vel) || (acc == closest_acc && vel == closest_vel && pos < closest_pos)) {
            closest_acc = acc;
            closest_vel = vel;
            closest_pos = pos;
            closest_idx = i;
        }
    }

    int not_collided = 0;
    for (int i = 0; i < 1000; i++) {
        not_collided = 0;
        for (int j = 0; j < particle_count; j++) {
            Particle *p = &particles[j];
            p->vx += p->ax;
            p->vy += p->ay;
            p->vz += p->az;
            p->px += p->vx;
            p->py += p->vy;
            p->pz += p->vz;

            if (!p->collided) not_collided++;
        }

        for (int j = 0; j < particle_count; j++) {
            Particle *p = &particles[j];
            for (int k = 0; k < particle_count; k++) {
                if (j == k) continue;
                Particle *q = &particles[k];

                if (p->px == q->px && p->py == q->py && p->pz == q->pz && (!p->collided || q->collided)) {
                    p->collided = 1;
                    q->collided = 1;

                    i = 0;
                }
            }
        }
    }

    printf("%d\n", closest_idx);
    printf("%d\n", not_collided);
}