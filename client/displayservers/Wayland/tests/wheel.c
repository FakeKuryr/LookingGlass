#include "wheel.h"

#include <assert.h>

static void test_precise_scroll_does_not_repeat_on_motion_frame(void)
{
  struct WaylandWheelState wheel = {0};
  waylandWheelReset(&wheel);

  waylandWheelAxis(&wheel, 15.0);
  waylandWheelValue120(&wheel, 120);

  assert(waylandWheelFrame(&wheel) == 1);
  assert(waylandWheelFrame(&wheel) == 0);
}

static void test_value120_replaces_discrete_when_both_are_present(void)
{
  struct WaylandWheelState wheel = {0};
  waylandWheelReset(&wheel);

  waylandWheelAxis(&wheel, 15.0);
  waylandWheelDiscrete(&wheel, 1);
  waylandWheelValue120(&wheel, 120);

  assert(waylandWheelFrame(&wheel) == 1);
}

static void test_axis_stop_discards_fractional_scroll(void)
{
  struct WaylandWheelState wheel = {0};
  waylandWheelReset(&wheel);

  waylandWheelAxis(&wheel, 4.0);
  assert(waylandWheelFrame(&wheel) == 0);

  waylandWheelStop(&wheel);
  assert(waylandWheelFrame(&wheel) == 0);

  waylandWheelAxis(&wheel, 4.0);
  assert(waylandWheelFrame(&wheel) == 0);
}

int main(void)
{
  test_precise_scroll_does_not_repeat_on_motion_frame();
  test_value120_replaces_discrete_when_both_are_present();
  test_axis_stop_discards_fractional_scroll();
  return 0;
}
