#include "Weapon.hpp"

using namespace godot;


void Weapon::_register_methods()
{
  godot::register_method("_ready", &Weapon::_ready);
  godot::register_method("shoot", &Weapon::shoot);
  godot::register_method("stopShoot", &Weapon::stopShoot);
  godot::register_property("Damage", &Weapon::damage, 10.0f);
  godot::register_property("BulletSpeed", &Weapon::bulletSpeed, 300.0f);
  godot::register_property("bullet_scene", &Weapon::bullet_scene, (godot::Ref<godot::PackedScene>)nullptr);

}

void Weapon::_ready()
{
  weaponLook = get_node<AnimatedSprite>("WeaponLook");
  bullet_spawn = get_node<Node2D>("BulletPoint");
}

void Weapon::shoot()
{
  weaponLook->set_animation("gunShoot"); 
}

void Weapon::stopShoot()
{
  weaponLook->set_animation("idle");
}
