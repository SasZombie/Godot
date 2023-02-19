#include "hud.hpp"
using namespace godot;


void Hud::_ready() {
    _score_label = get_node<godot::Label>("ScoreLabel");
    _message_label = get_node<godot::Label>("Massage");
    _start_message_timer = get_node<godot::Timer>("StartMessageTimer");
    _get_ready_message_timer = get_node<godot::Timer>("GetReadyMessageTimer");
    _start_button = get_node<godot::Button>("Start");
    _start_button_timer = get_node<godot::Timer>("MassageTimer");
}

void Hud::_register_methods() {
    godot::register_method("_ready", &Hud::_ready);
    godot::register_method("show_get_ready", &Hud::show_get_ready);
    godot::register_method("show_game_over", &Hud::show_game_over);
    godot::register_method("update_score", &Hud::update_score);
    godot::register_method("_on_StartButton_pressed", &Hud::_on_StartButton_pressed);
    godot::register_method("_on_StartMessageTimer_timeout", &Hud::_on_StartMessageTimer_timeout);
    godot::register_method("_on_GetReadyMessageTimer_timeout", &Hud::_on_GetReadyMessageTimer_timeout);
    godot::register_signal<Hud>("start_game", godot::Dictionary());
}

void Hud::show_get_ready() {
    _message_label->set_text("Get Ready");
    _message_label->show();
    _get_ready_message_timer->start();
}

void Hud::show_game_over()
{
    _message_label->set_text("Game Over");
    _message_label->show();
    _start_button->show();
    _start_message_timer->start();
}

void Hud::update_score(const int p_score)
{
    _score_label->set_text(godot::Variant(p_score));
}

void Hud::_on_StartButton_pressed() {
    _start_button_timer->stop();
    _start_button->hide();
    emit_signal("start_game");
}

void Hud::_on_StartMessageTimer_timeout() {
    _message_label->set_text("Dodge the\n Niggas");
    _message_label->show();
}

void Hud::_on_GetReadyMessageTimer_timeout() {
    _message_label->hide();
}