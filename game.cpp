// A starting point for a chilichip console game. It has a title menu, a play
// screen with a pause menu, and a save file. Replace the play scene with your
// game. The chili game SDK docs: https://game-sdk.chilichip.eu/

#include "game.hpp"

#include "chili/audio.hpp"
#include "chili/fx.hpp"
#include "chili/menu.hpp"
#include "chili/save.hpp"
#include "chili/scene.hpp"

#include <string>

using namespace blit;
namespace audio = chili::audio;
namespace fx = chili::fx;

///////////////////////////////////////////////////////////////////////////
//
// saving progress
//
// Save<T> stores a plain struct in a file named after the game's title (on
// the console: .blit/<title>/ on its USB drive, kept when the game is
// updated). Change the first number to your own four letters, and bump the
// version when you change SaveData: an old file then loads as defaults.
//
struct SaveData {
    uint32_t presses = 0;
    bool sound = true;
};

static chili::Save<SaveData> save(0x454d4147, 1);  // "GAME"

///////////////////////////////////////////////////////////////////////////
//
// sound
//
static const audio::Sfx sfx_blip = {audio::SFX1, Waveform::SQUARE, 0x3000, 0x7fff, 40, 1, {{880, 40}}};

static void ui_sound(chili::UiSound) {
    audio::play_sfx(sfx_blip);
}

///////////////////////////////////////////////////////////////////////////
//
// scenes
//
// Each screen of the game is a Scene. scenes.go() switches between them,
// with a fade if you give it a time in ms.
//
static chili::Scenes scenes;

static Point center() { return Point(screen.bounds.w / 2, screen.bounds.h / 2); }

// scene changes, defined once both scenes exist
static void go_title();
static void go_play();

struct Play;
extern Play play;

struct Title : chili::Scene {
    chili::Menu menu{{
        chili::Menu::action("PLAY", [] { go_play(); }),
        chili::Menu::toggle("SOUND", save.data.sound, [] {
            audio::set_sound(save.data.sound);
            save.store();
        }),
    }};

    void update(uint32_t dt) override { menu.update(scenes.pressed()); }

    void render(uint32_t time) override {
        Point c = center();
        fx::big_text("MY GAME", Point(c.x, c.y - 30), 2, chili::theme.accent);
        menu.render(Rect(c.x - 40, c.y - 10, 80, 20));
        fx::text("A: SELECT", Point(c.x, c.y + 30), chili::theme.dim, TextAlign::top_center);
    }
} title;

struct Play : chili::Scene {
    bool paused = false;
    chili::Menu pause_menu{{
        chili::Menu::action("RESUME", [] { play.paused = false; }),
        chili::Menu::action("QUIT", [] {
            save.store();  // a checkpoint: the console can be switched off at any time
            go_title();
        }),
    }};

    Play() { pause_menu.on_back = [] { play.paused = false; }; }

    void enter() override { paused = false; }

    void update(uint32_t dt) override {
        uint32_t pressed = scenes.pressed();
        if(paused) {
            pause_menu.update(pressed);
            return;
        }
        if(pressed & Button::MENU) {
            paused = true;
            pause_menu.select(0);
            chili::play_ui_sound(chili::UiSound::select);
            return;
        }
        if(pressed & Button::A) {
            save.data.presses++;
            audio::play_sfx(sfx_blip);
        }
    }

    void render(uint32_t time) override {
        Point c = center();
        fx::text("A pressed " + std::to_string(save.data.presses) + " times", Point(c.x, c.y - 8), chili::theme.text, TextAlign::top_center);
        fx::text("MENU: PAUSE", Point(c.x, c.y + 8), chili::theme.dim, TextAlign::top_center);

        if(paused) {
            fx::dim(140);
            fx::panel(Rect(c.x - 46, c.y - 26, 92, 52));
            fx::big_text("PAUSED", Point(c.x, c.y - 12), 2, chili::theme.text);
            pause_menu.render(Rect(c.x - 34, c.y, 68, 20));
        }
    }
} play;

static void go_title() { scenes.go(title, 150); }
static void go_play() { scenes.go(play, 150); }

///////////////////////////////////////////////////////////////////////////
//
// init()
//
// setup your game here
//
void init() {
    set_screen_mode(ScreenMode::hires);

    // load the last save (or defaults), and save again when the player quits
    // to the home screen (from the system menu or by holding HOME)
    save.load();
    save.store_on_quit();

    audio::init();
    audio::set_sound(save.data.sound);
    chili::ui_sound = ui_sound;

    scenes.go(title);
}

///////////////////////////////////////////////////////////////////////////
//
// update(time)
//
// This is called to update your game state. time is the
// amount of milliseconds elapsed since the start of your game
//
void update(uint32_t time) {
    scenes.update(time);
    audio::update(time);
}

///////////////////////////////////////////////////////////////////////////
//
// render(time)
//
// This function is called to perform rendering of the game. time is the
// amount of milliseconds elapsed since the start of your game
//
void render(uint32_t time) {
    screen.alpha = 255;
    screen.mask = nullptr;
    screen.pen = Pen(0, 0, 0);
    screen.clear();

    scenes.render(time);
}
