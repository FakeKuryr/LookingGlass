/**
 * Looking Glass
 * Copyright © 2017-2026 The Looking Glass Authors
 * https://looking-glass.io
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 59
 * Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "wheel.h"

#include <string.h>

static const double  WL_SCROLL_STEP      = 15.0;
static const double  WL_HALF_SCROLL_STEP = WL_SCROLL_STEP / 2.0;
static const int32_t WL_VALUE120_STEP    = 120;

void waylandWheelReset(struct WaylandWheelState * wheel)
{
  memset(wheel, 0, sizeof(*wheel));
}

void waylandWheelAxis(struct WaylandWheelState * wheel, double delta)
{
  wheel->axis += delta;
  wheel->hasAxis = true;
}

void waylandWheelDiscrete(struct WaylandWheelState * wheel, int32_t discrete)
{
  wheel->discrete += discrete;
  wheel->hasDiscrete = true;
}

void waylandWheelValue120(struct WaylandWheelState * wheel, int32_t value120)
{
  wheel->value120 += value120;
  wheel->hasValue120 = true;
}

void waylandWheelStop(struct WaylandWheelState * wheel)
{
  wheel->stopped = true;
}

int32_t waylandWheelFrame(struct WaylandWheelState * wheel)
{
  int32_t steps = 0;

  if (!wheel->hasAxis && !wheel->hasDiscrete && !wheel->hasValue120 &&
      !wheel->stopped)
    return 0;

  if (wheel->hasValue120)
  {
    steps = wheel->value120 / WL_VALUE120_STEP;
    wheel->value120 %= WL_VALUE120_STEP;
    wheel->axis = 0.0;
  }
  else if (wheel->hasDiscrete)
  {
    steps = wheel->discrete;
    wheel->axis = 0.0;
  }
  else
  {
    while (wheel->axis > WL_HALF_SCROLL_STEP)
    {
      ++steps;
      wheel->axis -= WL_SCROLL_STEP;
    }

    while (wheel->axis < -WL_HALF_SCROLL_STEP)
    {
      --steps;
      wheel->axis += WL_SCROLL_STEP;
    }
  }

  wheel->discrete    = 0;
  wheel->hasAxis     = false;
  wheel->hasDiscrete = false;
  wheel->hasValue120 = false;

  if (wheel->stopped)
  {
    wheel->axis     = 0.0;
    wheel->value120 = 0;
    wheel->stopped  = false;
  }

  return steps;
}
