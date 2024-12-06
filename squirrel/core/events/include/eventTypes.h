#pragma once

#include <cstdint>

namespace Squirrel
{
/*
 * EventType is a bitmask with 64 bits
 * Event Classification
 *     Input:
 *          Key: KeyPress, KeyRelease
 *          Mouse: MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll
 *
 *     Window: WindowClose, WindowResize, WindowFocus, WindowUnfocus, WindowMove
 *
 *     Application: AppTick, AppUpdate, AppRender
 */

enum class EventType : uint64_t
{
  Unknown            = 0x000000000000, // Unknown/unassigned EventType
  WindowClose        = 0x000000000001,
  WindowResize       = 0x000000000002,
  WindowFocus        = 0x000000000004,
  WindowUnfocus      = 0x000000000008,
  WindowMove         = 0x000000000010, // Window events end
  AppTick            = 0x000000010000,
  AppUpdate          = 0x000000020000,
  AppRender          = 0x000000040000, // Application events end
  KeyPress           = 0x000010000000,
  KeyRelease         = 0x000020000000, // Keyboard events end
  MouseButtonPress   = 0x010000000000,
  MouseButtonRelease = 0x020000000000,
  MouseMove          = 0x040000000000,
  MouseScroll        = 0x080000000000 // Mouse events end
};
} // namespace Squirrel
