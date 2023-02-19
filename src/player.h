#ifndef PLAYER_H
#define PLAYER_H 

#include <AnimatedSprite.hpp>
#include <Area2D.hpp>
#include <CollisionShape2D.hpp>
#include <Godot.hpp>
#include <Input.hpp>
#include "Weapon.hpp"
#include "bullet.hpp"

namespace godot
{
    

class Player : public godot::Area2D
{
private:
    GODOT_CLASS(Player, godot::Area2D)
    godot::AnimatedSprite * _animated_sprite;
    godot::CollisionShape2D *_collision_shape;
    godot::Input *_input;
    godot::Vector2 _screen_size;
    godot::Weapon *weapon;
    float speed, fireRate;
public:
    Player() = default;
    godot::Ref<godot::PackedScene> bullet_scene;

    void _init(){}
    void _ready();
    void _physics_process(const double delta);
    void _process(const double p_delta);
    void start(const godot::Vector2 p_position);
    void _on_Player_body_entered(godot::Node2D * _body);

    static void _register_methods();
    ~Player() = default;
};
}

#endif