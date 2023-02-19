#include "main.hpp"

#include <SceneTree.hpp>
#include "Mob.hpp"

using namespace godot;

void Main::_register_methods() {
    godot::register_method("_ready", &Main::_ready);
    godot::register_method("game_over", &Main::game_over);
    godot::register_method("new_game", &Main::new_game);
    godot::register_method("_on_MobTimer_timeout", &Main::_on_MobTimer_timeout);
    godot::register_method("_on_ScoreTimer_timeout", &Main::_on_ScoreTimer_timeout);
    godot::register_method("_on_StartTimer_timeout", &Main::_on_StartTimer_timeout);
    godot::register_property("mob_scene", &Main::mob_scene, (godot::Ref<godot::PackedScene>)nullptr);
}


void Main::_ready()
{
    _hud = get_node<Hud>("Hud");
    _player = get_node<Player>("Player");
    _start_position = get_node<godot::Node2D>("StartPosition");
    _mob_spawn_location = get_node<godot::PathFollow2D>("MobPath/MobSpawnLocation");
    _mob_timer = get_node<godot::Timer>("MobTimer");
    _score_timer = get_node<godot::Timer>("ScoreTimer");
    _start_timer = get_node<godot::Timer>("StartTimer");
    _random = (godot::Ref<godot::RandomNumberGenerator>)godot::RandomNumberGenerator::_new();
    _random->randomize();


}

void Main::_on_ScoreTimer_timeout()
{
    score += 1;
}

void Main::_on_StartTimer_timeout() 
{
    _mob_timer->start();
    _score_timer->start();
    _hud->update_score(score);
}

void Main::game_over() 
{
    _score_timer->stop();
    _mob_timer->stop();
    _hud->show_game_over();
    _score_timer->stop();
    _start_timer->stop();
}

void Main::new_game() 
{
    score = 0;
    _player->start(_start_position->get_position());
    _start_timer->start();
   _hud->update_score(score);
   _hud->show_get_ready();
    get_tree()->call_group("mobs", "queue_free");

}

void Main::_on_MobTimer_timeout() {
    // Create a new instance of the Mob scene.
    godot::Node *mob = mob_scene->instance();

    // Choose a random location on Path2D.
    _mob_spawn_location->set_offset((real_t)_random->randi());

    // Set the mob's direction perpendicular to the path direction.
    real_t direction = _mob_spawn_location->get_rotation() + (real_t)Math_PI / 2;

    // Set the mob's position to a random location.
    mob->set("position", _mob_spawn_location->get_position());

    // Add some randomness to the direction.
    direction += _random->randf_range((real_t)-Math_PI / 4, (real_t)Math_PI / 4);
    mob->set("rotation", direction);

    // Choose the velocity for the mob.
    godot::Vector2 velocity = godot::Vector2(_random->randf_range(250.0, 400.0), 0.0);
    mob->set("linear_velocity", velocity.rotated(direction));

    // Spawn the mob by adding it to the Main scene.
    add_child(mob);
}

