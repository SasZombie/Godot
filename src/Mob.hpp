#ifndef MOB_H
#define MOB_H

#include <AnimatedSprite.hpp>
#include <Godot.hpp>
#include <RigidBody2D.hpp>

namespace godot
{
class Mob : public godot::RigidBody2D
{
private:
    GODOT_CLASS(Mob, godot::RigidBody2D)
    godot::AnimatedSprite *_animated_sprite;
public:
    void _init(){}
    void _ready();
    void _on_VisibilityNotifier2D_screen_exited();

    static void _register_methods();
};

}
#endif