/*
 *  Copyright (c) 2008 Nick Schermer <nick@xfce.org>
 *  Copyright (C) 2010 Lionel Le Folgoc <lionel@lefolgoc.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <xfconf/xfconf.h>
#include <gdk/gdk.h>
#include <X11/extensions/Xrandr.h>

#ifndef __XFCE_RANDR_H__
#define __XFCE_RANDR_H__

#define XFCE_RANDR_ROTATIONS_MASK             (RR_Rotate_0|RR_Rotate_90|RR_Rotate_180|RR_Rotate_270)
#define XFCE_RANDR_REFLECTIONS_MASK           (RR_Reflect_X|RR_Reflect_Y)

/* check for randr 1.3 or better */
#if RANDR_MAJOR > 1 || (RANDR_MAJOR == 1 && RANDR_MINOR >= 3)
#define HAS_RANDR_ONE_POINT_THREE
#else
#undef HAS_RANDR_ONE_POINT_THREE
#endif

typedef struct _XfceRandr          XfceRandr;
typedef struct _XfceRandrPrivate   XfceRandrPrivate;
typedef struct _XfceRRMode         XfceRRMode;
typedef enum   _XfceOutputStatus   XfceOutputStatus;
typedef enum   _XfceOutputRelation XfceOutputRelation;

enum _XfceOutputStatus
{
    XFCE_OUTPUT_STATUS_PRIMARY,
    XFCE_OUTPUT_STATUS_SECONDARY
};

enum _XfceOutputRelation
{
    XFCE_RANDR_PLACEMENT_MIRROR,
    XFCE_RANDR_PLACEMENT_UP,
    XFCE_RANDR_PLACEMENT_DOWN,
    XFCE_RANDR_PLACEMENT_RIGHT,
    XFCE_RANDR_PLACEMENT_LEFT
};

struct _XfceRRMode
{
    RRMode  id;
    guint   width;
    guint   height;
    gdouble rate;
};

struct _XfceRandr
{
    /* number of connected outputs */
    guint                noutput;

    /* selected settings for all connected outputs */
    RRMode              *mode;
    Rotation            *rotation;
    Rotation            *rotations;
    XfceOutputRelation  *relation;
    guint               *related_to;
    XfceOutputStatus    *status;
    gchar              **friendly_name;

    /* implementation details */
    XfceRandrPrivate    *priv;
};



XfceRandr        *xfce_randr_new             (GdkDisplay      *display,
                                              GError         **error);

void              xfce_randr_free            (XfceRandr        *randr);

void              xfce_randr_reload          (XfceRandr        *randr);

void              xfce_randr_save_output     (XfceRandr        *randr,
                                              const gchar      *scheme,
                                              XfconfChannel    *channel,
                                              guint             output,
                                              gint              rel_changed);

void              xfce_randr_apply           (XfceRandr        *randr,
                                              const gchar      *scheme,
                                              XfconfChannel    *channel);

void              xfce_randr_load            (XfceRandr        *randr,
                                              const gchar      *scheme,
                                              XfconfChannel    *channel);

const XfceRRMode *xfce_randr_find_mode_by_id (XfceRandr        *randr,
                                              guint             output,
                                              RRMode            id);

RRMode            xfce_randr_preferred_mode  (XfceRandr        *randr,
                                              guint             output);

RRMode            xfce_randr_clonable_mode   (XfceRandr        *randr);

const XfceRRMode *xfce_randr_get_modes       (XfceRandr        *randr,
                                              guint             output,
                                              gint             *nmode);

gboolean          xfce_randr_get_positions   (XfceRandr        *randr,
                                              guint             output,
                                              gint             *x,
                                              gint             *y);

guint             xfce_randr_mode_width      (const XfceRRMode *mode,
                                              Rotation          rot);

guint             xfce_randr_mode_height     (const XfceRRMode *mode,
                                              Rotation          rot);

#endif /* !__XFCE_RANDR_H__ */
