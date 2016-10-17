/*
 * display.c
 *
 *  Created on: Sep 27, 2016
 *      Author: lidq
 */

#include <display.h>

int r = 0;
int st = 0;
pthread_t pthd;
s_engine *e = NULL;
s_params *p = NULL;

int __init(s_engine *engine, s_params *params)
{
	e = engine;
	p = params;

	st = 1;
	r = 1;
	pthread_create(&pthd, (const pthread_attr_t*) NULL, (void* (*)(void*)) &run, NULL);

	printf("[ OK ] Display Init.\n");

	return 0;
}

int __destory(s_engine *e, s_params *p)
{
	r = 0;

	return 0;
}

int __status()
{
	return st;
}

void run()
{
	usleep(1000);

	while (r)
	{
		printf("[%s]", e->lock == 1 ? "LOCKED" : "UNLOCK");

#ifdef __DISPLAY_MODE_MORE__
		printf("[v: %4.0f][h: %4.2f][xyz: %+7.3f %+7.3f %+7.3f][g: %+7.3f %+7.3f %+7.3f][x:%+8.3f y:%+8.3f z:%+8.3f xv:%+8.3f yv:%+8.3f]", e->v, e->height, e->x + e->dx + e->mx, e->y + e->dy + e->my, e->z + e->dz, e->gx + e->dgx, e->gy + e->dgy, e->gz + e->dgz, e->x_devi, e->y_devi, e->z_devi, e->xv_devi, e->yv_devi);
#endif

		if (p->ctl_type == 0)
		{
			printf("[pid: %+5.2f %+5.2f %+5.2f]", p->kp, p->ki, p->kd);
		}
		else if (p->ctl_type == 1)
		{
			printf("[pidv: %+5.2f %+5.2f %+5.2f]", p->kp_v, p->ki_v, p->kd_v);
		}
		else if (p->ctl_type == 2)
		{
			printf("[cxy: %+5.2f %+5.2f]", p->cx, p->cy);
		}
		else if (p->ctl_type == 3)
		{
			printf("[ctl zero: %4d %4d %4d]", p->ctl_fb_zero, p->ctl_lr_zero, p->ctl_pw_zero);
		}

#ifndef __DISPLAY_MODE_MORE__
		else if (p->ctl_type == 4)
		{
			printf("[xyz: %+7.3f %+7.3f %+7.3f]", e->x + e->dx + e->mx, e->y + e->dy + e->my, e->z + e->dz);
		}
		else if (p->ctl_type == 5)
		{
			printf("[g: %+7.3f %+7.3f %+7.3f]", e->gx + e->dgx, e->gy + e->dgy, e->gz + e->dgz);
		}
		else if (p->ctl_type == 6)
		{
			printf("[x:%+8.3f y:%+8.3f z:%+8.3f xv:%+8.3f yv:%+8.3f]", e->x_devi, e->y_devi, e->z_devi, e->xv_devi, e->yv_devi);
		}
#endif

		printf("\n");

		usleep(DISPLAY_SPEED * 1000);
	}

	st = 0;
}
