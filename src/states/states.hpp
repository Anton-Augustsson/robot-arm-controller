#ifndef States_HPP
#define States_HPP

#include "../utils/types.hpp"

typedef void (*state_func_t)(void);

typedef struct _state_t {
    uint8_t id;
    state_func_t Enter;
    state_func_t Do;
    state_func_t Exit;
    state_type_t state_type;
    uint32_t delay_ms; // TODO: If < 1 then Do will only be called once
} state_t;

void do_state_calibration(void);
void enter_state_calibration(void);
void exit_state_calibration(void);

const state_t state_cal = {
    0,
    enter_state_calibration,
    do_state_calibration,
    exit_state_calibration,
    event_driven_st,
    300
};

void do_state_manual(void);
void enter_state_manual(void);
void exit_state_manual(void);

const state_t state_man = {
    1,
    enter_state_manual,
    do_state_manual,
    exit_state_manual,
    event_driven_st,
    300
};

void do_state_move_to_start(void);
void enter_state_move_to_start(void);
void exit_state_move_to_start(void);

const state_t state_mts = {
    2,
    enter_state_move_to_start,
    do_state_move_to_start,
    exit_state_move_to_start,
    periodic_st,
    300
};

void do_state_idle(void);
void enter_state_idle(void);
void exit_state_idle(void);

const state_t state_idl = {
    3,
    enter_state_idle,
    do_state_idle,
    exit_state_idle,
    event_driven_st,
    300
};


// TODO: move to main? Buttons and interrupt should be there, right?
const state_t state_table[4][5] = {
    /*  STATE  B1         B2         B3         B4         NO-EVT */
    {/* S0 */  state_cal, state_cal, state_cal, state_man, state_cal}, // Calibrate
    {/* S1 */  state_man, state_man, state_man, state_mts, state_man}, // Manual
    {/* S2 */  state_idl, state_idl, state_idl, state_idl, state_mts}, // Move to start
    {/* S2 */  state_idl, state_man, state_mts, state_cal, state_idl}, // Idle
};

#endif