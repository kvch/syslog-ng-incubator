/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * As an additional exemption you are allowed to compile & link against the
 * OpenSSL libraries as published by the OpenSSL project. See the file
 * COPYING for details.
 *
 */

#ifndef _DUMMY_H
#define _DUMMY_H

#include "driver.h"
#include "logsource.h"


typedef struct _DummyDestDriver
{
  LogDestDriver super;
  gchar *path;
  gboolean enable;
  gint max;
} DummyDestDriver;

typedef struct
{
  LogSource super;
} DummySource;

typedef struct _DummySourceDriver
{
  LogSrcDriver super;
  LogSource *source;
  LogSourceOptions options;

  gchar *name_of_creator;
  gint min;
} DummySourceDriver;

void dummy_dd_set_path(LogPipe *driver, gchar* path);
void dummy_dd_set_enable(LogPipe *driver, gboolean enable);
void dummy_dd_set_max(LogPipe *driver, gint max);
LogDriver *dummy_dd_new(GlobalConfig *cfg);

void dummy_sd_set_min(LogPipe *driver, gint min);
void dummy_sd_set_name(LogPipe *driver, gchar *name);
LogDriver *dummy_sd_new(GlobalConfig *cfg);

#endif
