#include "render.inl"
//Code-generator production

ecs::QueryDescription gatherSprites_descr("gatherSprites", {
  {ecs::get_type_description<Sprite>("sprite"), false},
  {ecs::get_type_description<Transform2D>("transform"), false},
  {ecs::get_type_description<int>("renderOrder"), true},
  {ecs::get_type_description<vec4>("color"), true}
});

template<typename Callable>
void gatherSprites(Callable lambda)
{
  for (ecs::QueryIterator begin = gatherSprites_descr.begin(), end = gatherSprites_descr.end(); begin != end; ++begin)
  {
    lambda(
      *begin.get_component<Sprite>(0),
      *begin.get_component<Transform2D>(1),
       begin.get_component<int>(2),
       begin.get_component<vec4>(3)
    );
  }
}


ecs::QueryDescription gatherLocalPlayer_descr("getLocalPlayer", {
  {ecs::get_type_description<float>("health"), false},
  {ecs::get_type_description<ecs::Tag>("localPlayer"), false}
});

template<typename Callable>
void getLocalPlayer(Callable lambda)
{
  for (ecs::QueryIterator begin = gatherLocalPlayer_descr.begin(), end = gatherLocalPlayer_descr.end(); begin != end; ++begin)
  {
    lambda(
      *begin.get_component<float>(0)
    );
  }
}


void RenderScene_func();

ecs::SystemDescription RenderScene_descr("RenderScene", {
  {ecs::get_type_description<WorldRenderer>("wr"), false},
  {ecs::get_type_description<Camera>("camera"), false}
}, RenderScene_func, ecs::SystemOrder::RENDER, (uint)(ecs::SystemTag::Game));

void RenderScene_func()
{
  for (ecs::QueryIterator begin = RenderScene_descr.begin(), end = RenderScene_descr.end(); begin != end; ++begin)
  {
    RenderScene(
      *begin.get_component<WorldRenderer>(0),
      *begin.get_component<Camera>(1)
    );
  }
}



