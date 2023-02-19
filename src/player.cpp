#include "player.h"
#include <iostream>

using namespace godot;



void Player::_register_methods() {
    godot::register_method("_ready", &Player::_ready);
    godot::register_method("_process", &Player::_process);
    godot::register_method("_physics_process", &Player::_physics_process);
    godot::register_method("start", &Player::start);
    godot::register_method("_on_Player_body_entered", &Player::_on_Player_body_entered);
    godot::register_property("speed", &Player::speed, (real_t)400.0);
    godot::register_signal<Player>("hit", godot::Dictionary());
    godot::register_property("bullet_scene", &Player::bullet_scene, (godot::Ref<godot::PackedScene>)nullptr);
    godot::register_property("FireRate", &Player::fireRate, 0.2f);

}

void Player::_ready()
{
    _animated_sprite = get_node<godot::AnimatedSprite>("AnimatedSprite");
    _collision_shape = get_node<godot::CollisionShape2D>("CollisionShape2D");
    _input = godot::Input::get_singleton();
    _screen_size = get_viewport_rect().size;
    weapon = get_node<godot::Weapon>("weapon");
}

void godot::Player::_physics_process(const double p_delta)
{
    godot::Vector2 velocity(0,0);
    godot::Vector2 mousePositon = get_global_mouse_position();
    velocity.x = _input->get_action_strength("move_right") - _input->get_action_strength("move_left");
    velocity.y = _input->get_action_strength("move_down") - _input->get_action_strength("move_up");

    bool pressed = _input->get_action_strength("shoot_primary");  
   

    if(_input->get_action_strength("shoot_primary"))
    {
        godot::RigidBody2D *bullet = static_cast<RigidBody2D*>(bullet_scene->instance());
        
        bullet->set_position(weapon->bullet_spawn->get_position());
        bullet->set_rotation(weapon->get_global_rotation());
        bullet->apply_impulse(Vector2(), Vector2(1000, 0.0f).rotated(weapon->get_global_rotation()));
        bullet->call_deferred("add_child", bullet, get_tree()->get_root());
        

    }
   
   weapon->look_at(mousePositon);
    if(pressed)
        weapon->shoot();
    else
       weapon->stopShoot();

    if(velocity.length() > 0)
    {
        
        velocity = velocity.normalized() * speed;
        _animated_sprite->play();
    }
    else
    {
        _animated_sprite->stop();
    }
    godot::Vector2 position = get_position();
    position += velocity * (real_t)p_delta;
    position.x = godot::Math::clamp(position.x, (real_t)0.0f, _screen_size.x);
    position.y = godot::Math::clamp(position.y, (real_t)0.0f, _screen_size.y);
    
    set_position(position);

    
    if(velocity.x != 0)
    {
        _animated_sprite->set_animation("walk");
        _animated_sprite->set_flip_v(false);
   //     weapon->set_flip_h(velocity.x < 0);

        _animated_sprite->set_flip_h(velocity.x < 0);
    }
    else if(velocity.y != 0)
    {
        _animated_sprite->set_animation("up");
        _animated_sprite->set_flip_v(velocity.y > 0);
     
    }

    
}

void Player::_process(const double p_delta)
{


}

void Player::_on_Player_body_entered(godot::Node2D *_body)
{
    if(_body->is_in_group("Bullet"))
        return;
    hide();
    emit_signal("hit");

    _collision_shape->set_deferred("disabled", true);
}

void Player::start(const godot::Vector2 p_position)
{
    set_position(p_position);
    show();
    _collision_shape->set_disabled(false);
}