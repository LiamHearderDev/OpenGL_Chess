#ifndef INPUT_DATA_H
#define INPUT_DATA_H

/** Data that's passed to mouse click input events. */
struct mouse_click_data {
    int button;
    int action;
    int mods;
    double cursor_pos_x;
    double cursor_pos_y;
};

#endif // INPUT_DATA_H