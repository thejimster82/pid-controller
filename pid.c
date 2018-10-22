#include "pid.h"

// Function to adjust the set point
void set_point(pid_args *state, double set_point) {
    // Change the set point to input
    state->temps.set_point = set_point;
}

// Function to change the track the current temperature
void update_temp(pid_args *state, double curr_temp) {
    // Change the current temperature to input
    state->temps.curr_temp = curr_temp;
}

// Function to set the coefficients manually
void set_params(pid_args *state, pid_params coefficients) {
    // Change all PID coefficients
    state->coefficients = coefficients;
}

// Self-tuning PID mechanism
void adjust_params(pid_args *state) {
    // Extract the state information
    pid_temps temps = state->temps;
    pid_params curr_coefficients = state->coefficients;
    pid_errs curr_errs = state->errs;

    // Apply the correction formula
    double correction = (curr_errs.cum_err / (curr_coefficients.tuning_window * temps.set_point))

    // Reset the tuning iterator and correct the parameters
    pid_params new_coefficients = (pid_params) {
        curr_coefficients.Kp - correction,
        curr_coefficients.Ki - correction,
        curr_coefficients.Kd - correction,
        0,
        curr_coefficients.tuning_window
    };

    // Push the changes to the controller
    set_params(state, new_coefficients);
}

// Function to update error state
void set_errors(pid_args *state, pid_errs errors) {
    // Change all error values
    state->errs = errors;
}

// PID controller function
double control(pid_args *state) {
    // Extract all state information
    pid_temps temps = state->temps;
    pid_params coefficients = state->coefficients;
    pid_errs errs = state->errs;

    // Extract PID coefficients
    double Kp = coefficients.Kp;
    double Ki = coefficients.Ki;
    double Kd = coefficients.Kd;    

    // WIP
    // Measure the elapsed time
    unsigned int now = millis();
    unsigned int last = state->time_stamp;
    double dt = now - last;

    // Measure the current error
    double error = temps.set_point - temps.curr_temp;

    // Recalculate the integral of the error using previous and current values
    double i_err = errs.err_sum + (error * dt);
    
    // Recalculate the derivative of the error
    double d_err = (error - errs.last_err) / dt;

    // Generate the PID control output
    double out = Kp * error + Kd * d_err + Ki * i_err;
    
    // Update the timestamp
    state->time_stamp = now;

    // Update errors
    set_errors(state, (pid_errs) {
        i_err,
        error,
        state->errs.cum_err + fabs(error)
    });

    // Tune PID coefficients as needed
    if (coefficients.tuning_progress == coefficients.tuning_window) {
        adjust_params(state);
    }

    // Return the change in duty cycle
    return out;
}