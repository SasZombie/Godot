#include "Mob.hpp"

#include <RandomNumberGenerator.hpp>
#include <SpriteFrames.hpp>

using namespace godot;


void Mob::_register_methods() {
    godot::register_method("_ready", &Mob::_ready);
    godot::register_signal<Mob>("delete", godot::Dictionary());
}


void Mob::_ready()
{
    Ref<RandomNumberGenerator> random = RandomNumberGenerator::_new();
    random->randomize();

    _animated_sprite = get_node<AnimatedSprite>("AnimatedSprite");
    _animated_sprite->set_playing(true);
    PoolStringArray mob_types = _animated_sprite ->get_sprite_frames()->get_animation_names();
    _animated_sprite->set_animation(mob_types[random->randi() % mob_types.size()]);
}

void Mob::_on_VisibilityNotifier2D_screen_exited()
{
    queue_free();
}

