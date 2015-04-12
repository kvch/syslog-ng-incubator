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

#include "dummy.h"
#include "driver.h"
#include "logsource.h"


void
dummy_dd_set_path(LogPipe *driver, gchar *path)
{
    DummyDestDriver *self = (DummyDestDriver *) driver;
    self->path = path;
}

void
dummy_dd_set_enable(LogPipe *driver, gboolean enable)
{
    DummyDestDriver *self = (DummyDestDriver *) driver;
    self->enable = enable;
}

void
dummy_dd_set_max(LogPipe *driver, gint max)
{
    DummyDestDriver *self = (DummyDestDriver *) driver;
    self->max = max;
}

static gboolean
dummy_dd_init(LogPipe *driver)
{
    DummyDestDriver *self = (DummyDestDriver *) driver;

    if (!log_dest_driver_init_method(driver))
        return FALSE;

    msg_info("Initialize dummy destination driver",
             evt_tag_str("driver", self->super.super.id),
             NULL);

    return TRUE;
}

static gboolean
dummy_dd_deinit(LogPipe *driver)
{
    DummyDestDriver *self = (DummyDestDriver *) driver;

    g_free(self->path);
    if (!log_dest_driver_deinit_method(driver))
        return FALSE;

    msg_info("Deinitialize dummy destination driver",
             evt_tag_str("driver", self->super.super.id),
             NULL);

    return TRUE;
}

void
dummy_dd_free(LogPipe *driver)
{
    DummyDestDriver *self = (DummyDestDriver *) driver;

    log_dest_driver_free(driver);
}

LogDriver *
dummy_dd_new(GlobalConfig *cfg)
{
    DummyDestDriver *self = g_new0(DummyDestDriver, 1);
    log_dest_driver_init_instance(&self->super, cfg);

    self->super.super.super.init = dummy_dd_init;
    self->super.super.super.deinit = dummy_dd_deinit;
    self->super.super.super.free_fn = dummy_dd_free;

    msg_info("New dummy destination driver", NULL, NULL);

    return (LogDriver *) self;
}


static gboolean
dummy_source_init(LogPipe *source)
{
    DummySource *self = (DummySource *) source;

    if (!log_source_init(source))
    {
        msg_error("Failed to initialize source", NULL);
        return FALSE;
    }

    msg_info("Initialize dummy source", NULL, NULL);

    return TRUE;
}

static gboolean
dummy_source_deinit(LogPipe *source)
{
    DummySource *self = (DummySource *) source;

    if (!log_source_deinit(source))
    {
        msg_error("Failed to deinitialize source", NULL);
        return FALSE;
    }

    msg_info("Deinitialize dummy source", NULL, NULL);
    
    return TRUE;
}


static LogSource *
dummy_source_new(DummySourceDriver *owner, LogSourceOptions *options, GlobalConfig *cfg)
{
    DummySource *self = g_new0(DummySource, 1);
  
    log_source_init_instance(&self->super, cfg);
    log_source_set_options(&self->super, options, 0, 0,
                           owner->super.super.id, NULL, FALSE, FALSE);
  
    self->super.super.init = dummy_source_init;
    self->super.super.deinit = dummy_source_deinit;
  
    return &self->super;
}


void
dummy_sd_set_name(LogPipe *driver, gchar *name)
{
    DummySourceDriver *self = (DummySourceDriver *) driver;
    self->name_of_creator = name;
}

void
dummy_sd_set_min(LogPipe *driver, gint min)
{
    DummySourceDriver *self = (DummySourceDriver *) driver;
    self->min = min;
}

static gboolean
dummy_sd_init(LogPipe *driver)
{
    DummySourceDriver *self = (DummySourceDriver *) driver;
    GlobalConfig *cfg = log_pipe_get_config(driver);

    if (!log_src_driver_init_method(driver))
    {
        msg_error("Failed to initialize source driver", NULL);
        return FALSE;
    }

    log_source_options_init(&self->options, cfg, self->super.super.group);
    self->source = dummy_source_new(self, &self->options, cfg);

    log_pipe_append(&self->source->super, driver);
    log_pipe_init(&self->source->super);

    msg_info("Initialize dummy source driver",
             evt_tag_str("driver", self->super.super.id),
             NULL);

    return TRUE;
}

static gboolean
dummy_sd_deinit(LogPipe *driver)
{
    DummySourceDriver *self = (DummySourceDriver *) driver;

    if (self->source)
    {
        log_pipe_deinit(&self->source->super);
        log_pipe_unref(&self->source->super);
        self->source = NULL;
    }

    g_free(self->name_of_creator);
    msg_info("Deinitialize dummy source driver",
             evt_tag_str("driver", self->super.super.id),
             NULL);
    
    return log_src_driver_deinit_method(driver);
}

void
dummy_sd_free(LogPipe *driver)
{
    DummySourceDriver *self = (DummySourceDriver *) driver;

    log_src_driver_free(driver);
}

LogDriver *
dummy_sd_new(GlobalConfig *cfg)
{
    DummySourceDriver *self = g_new0(DummySourceDriver, 1);
    log_src_driver_init_instance(&self->super, cfg);

    self->super.super.super.init = dummy_sd_init;
    self->super.super.super.deinit = dummy_sd_deinit;
    self->super.super.super.free_fn = dummy_sd_free;

    msg_info("New dummy source driver", NULL, NULL);

    return (LogDriver *) self;
}
