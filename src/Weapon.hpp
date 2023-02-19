#ifndef WEAPON_H
#define WEAPON_H

#include <AnimatedSprite.hpp>
#include <Godot.hpp>
#include <Input.hpp>
#include <PackedScene.hpp>
#include <PathFollow2D.hpp>
#include <RigidBody2D.hpp>
#include <SceneTree.hpp>
#include <Position2D.hpp>

namespace godot
{
class Weapon : public godot::Node2D
{
private:
    GODOT_CLASS(Weapon, godot::Node2D)
    godot::Input *mouse_click;
    godot::AnimatedSprite *weaponLook;
    godot::PathFollow2D *_mob_spawn_location;
    float damage, bulletSpeed;

public:
    void _init(){}
    void _ready();
    void shoot();
    void stopShoot();
    godot::Node2D *bullet_spawn;

    godot::Ref<godot::PackedScene> bullet_scene;

    static void _register_methods();

};
}


#endif