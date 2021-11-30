#pragma once
#include "common.h"
#include <map>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_events.h>
enum class MouseButton
{
  LeftButton,
  RightButton,
  MiddleButton
};
enum class MouseAction
{
  Down,
  Up
};


template<MouseButton buttonType>
struct MouseClickEvent
{
  MouseAction action;
  int x, y;
  float time;
};
template<MouseAction action>
struct MouseClickEventAnyType
{
  MouseButton buttonType;
  int x, y;
  float time;
};
struct MouseClickEventAnyEvent
{
  MouseButton buttonType;
  MouseAction action;
  int x, y;
  float time;
};

struct MouseMoveEvent
{
  int x, y;
  int dx, dy;
  float time;
};
struct MouseWheelEvent
{
  int wheel;
  float time;
};

enum class KeyAction
{
  Down,
  Press,
  Up
};

template<SDL_Keycode Key>
struct KeyDownEvent
{
  float time;
};
template<SDL_Keycode Key>
struct KeyUpEvent
{
  float time;
};
template<SDL_Keycode Key>
struct KeyPressEvent
{
  float time;
};
template<SDL_Keycode Key>
struct KeyEventAnyAction
{
  KeyAction action;
  float time;
};
template<KeyAction Action>
struct KeyEventAnyKey
{
  SDL_Keycode keycode;
  float time;
};

struct KeyEventAnyActionKey
{
  SDL_Keycode keycode;
  KeyAction action;
  float time;
};

struct MousePosition
{
  int x, y;
};

class Input
{
  MousePosition mousePosition;
  map<SDL_Keycode, pair<int, float>> keyMap;
  map<MouseButton, bool> mouseButtonMap;
  struct WheelData
  {
    float lastTime = 0, lastValue = 0, targetValue = 0;
  } wheelData; 

public:
  Input() = default;
  static Input& input();

  void event_process(const SDL_KeyboardEvent& event, float time);
  void event_process(const SDL_MouseButtonEvent& event, float time);
  void event_process(const SDL_MouseMotionEvent& event, float time);
  void event_process(const SDL_MouseWheelEvent& event, float time);
  float get_key_impl(SDL_Keycode keycode, float reaction_time = 0.1f);
  bool get_key_state_impl(SDL_Keycode keycode);
  bool get_mouse_button_state_impl(MouseButton mouseButton);
  float get_key_derivative(SDL_Keycode keycode, float reaction_time = 0.1f);
  float get_wheel_impl();
  static float get_key(SDL_Keycode keycode, float reaction_time = 0.1f);
  static bool get_key_state(SDL_Keycode keycode);
  static bool get_mouse_button_state(MouseButton MouseButton);
  static MousePosition get_mouse_position();
  static float get_wheel();

};