/**
 * Copyright (C) 2012 Liu Bin
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* write by Liu Bin, the idea is from checkinstall/installwatch */

#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>

static FILE *(*real_fopen)(const char *path, const char *mode);
static FILE *(*real_fdopen)(int fd, const char *mode);
static FILE *(*real_freopen)(const char *path, const char *mode, FILE *stream);

static void (*real_setbuf)(FILE *stream, char *buf);
static void (*real_setbuffer)(FILE *stream, char *buf, size_t size);
static void (*real_setlinebuf)(FILE *stream);
static int (*real_setvbuf)(FILE *stream, char *buf, int mode, size_t size);

static void *libc_handle = NULL;

__attribute__((constructor))
static void initialize(void) {
	if (libc_handle)
		return;

	libc_handle = RTLD_NEXT;

	real_fopen      = dlsym(libc_handle, "fopen");
	real_fdopen     = dlsym(libc_handle, "fdopen");
	real_freopen    = dlsym(libc_handle, "freopen");
	real_setbuf     = dlsym(libc_handle, "setbuf");
	real_setbuffer  = dlsym(libc_handle, "setbuffer");
	real_setlinebuf = dlsym(libc_handle, "setlinebuf");
	real_setvbuf    = dlsym(libc_handle, "setvbuf");

	if (stdout)
		real_setvbuf(stdout, NULL, _IONBF, 0);
	if (stderr)
		real_setvbuf(stderr, NULL, _IONBF, 0);
}

void _init(void) { initialize(); }

FILE *fopen(const char *path, const char *mode) {
	if (!libc_handle)
		initialize();
	FILE *fp = real_fopen(path, mode);
	if (fp)
		real_setvbuf(fp, NULL, _IONBF, 0);
	return fp;
}

FILE *fdopen(int fd, const char *mode) {
	if (!libc_handle)
		initialize();
	FILE *fp = real_fdopen(fd, mode);
	if (fp)
		real_setvbuf(fp, NULL, _IONBF, 0);
	return fp;
}

FILE *freopen(const char *path, const char *mode, FILE *stream) {
	if (!libc_handle)
		initialize();
	FILE *fp = real_freopen(path, mode, stream);
	if (fp)
		real_setvbuf(fp, NULL, _IONBF, 0);
	return fp;
}

void setbuf(FILE *stream, char *buf) {if (!libc_handle) initialize();}
void setbuffer(FILE *stream, char *buf, size_t size) {if (!libc_handle) initialize();}
void setlinebuf(FILE *stream) {if (!libc_handle) initialize();}
int setvbuf(FILE *stream, char *buf, int mode, size_t size) {
	if (!libc_handle)
		initialize();
	int rc = real_setvbuf(stream, buf, mode, size);
	if (rc)
		return rc;
	real_setvbuf(stream, NULL, _IONBF, 0);
	return 0;
}

