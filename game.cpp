#include "game.hpp"

using namespace blit;

///////////////////////////////////////////////////////////////////////////
//
// saving progress
//
// write_save/read_save store a struct in a file named after the game's
// title (on the VGC Zero: .blit/<title>/ on its USB drive, kept when the
// game is updated)
//
struct SaveData {
    uint32_t presses = 0;
};

static SaveData save_data;

// called when the player quits the game, from the system menu or by holding
// HOME on the VGC Zero, or by closing the window on desktop
static void save_progress() {
    write_save(save_data);
}

///////////////////////////////////////////////////////////////////////////
//
// init()
//
// setup your game here
//
void init() {
    set_screen_mode(ScreenMode::hires);

    // load the last save, if there is one
    if(!read_save(save_data))
        save_data = SaveData();

    on_quit = save_progress;
}

///////////////////////////////////////////////////////////////////////////
//
// render(time)
//
// This function is called to perform rendering of the game. time is the 
// amount if milliseconds elapsed since the start of your game
//
void render(uint32_t time) {

    // clear the screen -- screen is a reference to the frame buffer and can be used to draw all things with the 32blit
    screen.pen = Pen(0, 0, 0);
    screen.clear();

    // draw some text at the top of the screen
    screen.alpha = 255;
    screen.mask = nullptr;
    screen.pen = Pen(255, 255, 255);
    screen.rectangle(Rect(0, 0, 320, 14));
    screen.pen = Pen(0, 0, 0);
    screen.text("Hello 32blit!", minimal_font, Point(5, 4));

    screen.pen = Pen(255, 255, 255);
    screen.text("A pressed " + std::to_string(save_data.presses) + " times", minimal_font, Point(5, 24));
    screen.text("Saved when you quit", minimal_font, Point(5, 36));
}

///////////////////////////////////////////////////////////////////////////
//
// update(time)
//
// This is called to update your game state. time is the 
// amount if milliseconds elapsed since the start of your game
//
void update(uint32_t time) {
    if(buttons.pressed & Button::A)
        save_data.presses++;
}