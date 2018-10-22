#ifndef PID_H
#define PID_H

// Struct to contain the temperature state of the controller
typedef struct pid_temps {
    double curr_temp;               // Current temperature
    double set_point;               // Setpoint
} pid_temps;

// Struct to contain coefficients
typedef struct pid_params {
    double Kp;                      // Proportional constant
    double Ki;                      // Integral constant
    double Kd;                      // Derivative constant
    unsigned int tuning_progress;   // Coefficient adjustment timer
    unsigned int tuning_window;     // How long before adjusting coefficients
} pid_params;

// Struct to contain error values for tuning
typedef struct pid_errs {
    double err_sum;                 // Integral of the error term
    double last_err;                // Previous error value
    double cum_err;                 // Average error
} pid_errs;

// Struct to contain all state information
typedef struct pid_args {
    pid_temps temps;                // Contains temperature information
    pid_params coefficients;        // Contains the PID coefficients
    pid_errs errs;                  // Contains errors
    unsigned int time_stamp;        // Time stamp for PID output
} pid_args;

// Controller object for the algorithm
static pid_args controller = (pid_args) {
    (pid_temps) {0, 0},
    (pid_params) {0, 0, 0, 0, 0},
    (pid_errs) {0, 0, 0},
    0
};

// Function to adjust the set point
void set_point(pid_args *state, double set_point);

// Function to change the track the current temperature
void update_temp(pid_args *state, double curr_temp);

// Function to set the coefficients manually
void set_params(pid_args *state, pid_params coefficients);

// Self-tuning PID mechanism
void adjust_params(pid_args *state);

// Function to update error state
void set_errors(pid_args *state, pid_errs errors);

// PID controller function
double control(pid_args *state);
#endif
