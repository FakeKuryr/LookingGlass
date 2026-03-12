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

#pragma once

#include <stdbool.h>
#include <stdint.h>

struct WaylandWheelState
{
  double  axis;
  int32_t discrete;
  int32_t value120;
  bool    hasAxis;
  bool    hasDiscrete;
  bool    hasValue120;
  bool    stopped;
};

void waylandWheelReset(struct WaylandWheelState * wheel);
void waylandWheelAxis(struct WaylandWheelState * wheel, double delta);
void waylandWheelDiscrete(struct WaylandWheelState * wheel, int32_t discrete);
void waylandWheelValue120(struct WaylandWheelState * wheel, int32_t value120);
void waylandWheelStop(struct WaylandWheelState * wheel);
int32_t waylandWheelFrame(struct WaylandWheelState * wheel);
