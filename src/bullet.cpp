#include "bullet.hpp"

using namespace godot;

void godot::Bullet::_register_methods()
{
    register_method("_on_VisibilityNotifier2D_screen_exited", &Bullet::_on_VisibilityNotifier2D_screen_exited);
    register_method("_ready", &Bullet::_ready);
    register_property("BulletHp", &Bullet::healhPoints, 1.0f);
}

void godot::Bullet::_ready()
{
    _animated_sprite = get_node<AnimatedSprite>("AnimatedSprite");
    _animated_sprite->set_playing(true);

}

void godot::Bullet::_on_VisibilityNotifier2D_screen_exited()
{
    queue_free();
}
