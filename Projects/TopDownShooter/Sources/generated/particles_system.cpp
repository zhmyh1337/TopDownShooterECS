#include "particles_system.inl"
//Code-generator production

void UpdateParticles_func();

ecs::SystemDescription UpdateParticles_descr("UpdateParticles", {
  {ecs::get_type_description<ecs::EntityId>("eid"), false},
  {ecs::get_type_description<float>("lifeCycleState"), false},
  {ecs::get_type_description<float>("lifeTime"), false},
  {ecs::get_type_description<ecs::Tag>("particle"), false}
}, UpdateParticles_func, ecs::SystemOrder::LOGIC, (uint)(ecs::SystemTag::Game));

void UpdateParticles_func()
{
  for (ecs::QueryIterator begin = UpdateParticles_descr.begin(), end = UpdateParticles_descr.end(); begin != end; ++begin)
  {
    UpdateParticles(
      *begin.get_component<ecs::EntityId>(0),
      *begin.get_component<float>(1),
      *begin.get_component<float>(2)
    );
  }
}


void UpdateBloodParticles_func();

ecs::SystemDescription UpdateBloodParticles_descr("UpdateBloodParticles", {
  {ecs::get_type_description<float>("lifeCycleState"), false},
  {ecs::get_type_description<vec4>("color"), false},
  {ecs::get_type_description<vec2>("velocity"), false},
  {ecs::get_type_description<vec2>("acceleration"), false},
  {ecs::get_type_description<Sprite>("sprite"), false},
  {ecs::get_type_description<SpriteSheetsPool>("ssp"), false},
  {ecs::get_type_description<ecs::Tag>("particle"), false},
  {ecs::get_type_description<ecs::Tag>("blood"), false}
}, UpdateBloodParticles_func, ecs::SystemOrder::LOGIC + 1, (uint)(ecs::SystemTag::Game));

void UpdateBloodParticles_func()
{
  for (ecs::QueryIterator begin = UpdateBloodParticles_descr.begin(), end = UpdateBloodParticles_descr.end(); begin != end; ++begin)
  {
    UpdateBloodParticles(
      *begin.get_component<float>(0),
      *begin.get_component<vec4>(1),
      *begin.get_component<vec2>(2),
      *begin.get_component<vec2>(3),
      *begin.get_component<Sprite>(4),
      *begin.get_component<SpriteSheetsPool>(5)
    );
  }
}


void EntityEmitBlood_handler(const EntityEmitBloodEvent &event);

ecs::EventDescription<EntityEmitBloodEvent> EntityEmitBlood_descr("EntityEmitBlood", {
  {ecs::get_type_description<Transform2D>("transform"), false}
}, EntityEmitBlood_handler, (uint)(ecs::SystemTag::Game));

void EntityEmitBlood_handler(const EntityEmitBloodEvent &event)
{
  for (ecs::QueryIterator begin = EntityEmitBlood_descr.begin(), end = EntityEmitBlood_descr.end(); begin != end; ++begin)
  {
    EntityEmitBlood(
      event,
      *begin.get_component<Transform2D>(0)
    );
  }
}


void EntityEmitBlood_singl_handler(const EntityEmitBloodEvent &event, ecs::QueryIterator &begin);

ecs::SingleEventDescription<EntityEmitBloodEvent> EntityEmitBlood_singl_descr("EntityEmitBlood", {
  {ecs::get_type_description<Transform2D>("transform"), false}
}, EntityEmitBlood_singl_handler, (uint)(ecs::SystemTag::Game));

void EntityEmitBlood_singl_handler(const EntityEmitBloodEvent &event, ecs::QueryIterator &begin)
{
  EntityEmitBlood(
    event,
      *begin.get_component<Transform2D>(0)
  );
}



