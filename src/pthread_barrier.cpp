/*
 * pthread_barrier.c - Barrier handling for pthreads.
 *
 * This file is part of the Portable.NET C library.
 * Copyright (C) 2004  Southern Storm Software, Pty Ltd.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "pthread_barrier.h"
#include <errno.h>

int pthread_barrier_init (pthread_barrier_t *barrier, unsigned int count)
{
	if (count == 0)
	{
		errno = EINVAL;
		return -1;
	}
	if (pthread_mutex_init (&(barrier->mutex), 0) < 0)
		return -1;
	if (pthread_cond_init (&(barrier->condition), 0) < 0)
	{
		pthread_mutex_destroy (&(barrier->mutex));
		return -1;
	}
	barrier->desired_count = count;
	barrier->current_count = 0;
	return 0;
}

int pthread_barrier_destroy (pthread_barrier_t *barrier)
{
	pthread_cond_destroy (&(barrier->condition));
	pthread_mutex_destroy (&(barrier->mutex));
	return 0;
}

int pthread_barrier_wait (pthread_barrier_t *barrier)
{
	pthread_mutex_lock (&(barrier->mutex));
	++(barrier->current_count);
	if (barrier->current_count >= barrier->desired_count)
	{
		barrier->current_count = 0;
		pthread_cond_broadcast (&(barrier->condition));
		pthread_mutex_unlock (&(barrier->mutex));
		return 1;
	} else {
		pthread_cond_wait (&(barrier->condition), &(barrier->mutex));
		pthread_mutex_unlock (&(barrier->mutex));
		return 0;
	}
}
