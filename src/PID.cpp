#include "PID.h"
#include <iostream>
#include <numeric>


#include <random>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <math.h>
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>

using namespace std;


/*
 * TODO: Complete the PID class.
 */

PID::PID() {}

PID::~PID() {}


/*
 * Initialize PID.
 */
void PID::Init(double Kp, double Ki, double Kd) {

  cout << "Init" << endl;

  p_error = 0;
  i_error = 0;
  d_error = 0;
  prev_cte = 0;

  PID::Kp = Kp;
  PID::Ki = Ki;
  PID::Kd = Kd;

  count = 0;
  debugFilename_ = "../py/debug.csv";
  SetupCsv();
}


/*
 * Update the PID error variables given cross track error.
 */
void PID::UpdateError(double cte) {
  cout << "UpdateError" << endl;
  cout << "CTE: " << cte << endl;

  // set the individual errors
  d_error = cte - prev_cte;
  p_error = cte;
  i_error += cte;

  prev_cte = cte;

  // write to the terminal
  cout << "count: " << count << "\tp_error: " << p_error  << "\td_error: " << d_error << "\ti_error: " << i_error;
  // increment the counter variable used for debug
  count++;
}


/*
 * Calculate the total PID error. Not sure what this was intended for, not used.
 */
double PID::TotalError() {
  cout << "TotalError" << endl;
  return 0;
}


/*
 * Calculate Steering control command.
 */
double PID::Steering() {

  // calculate the contributions from the p_error and gain, d_error and gain, and i_error and gain.
  // these are allocated to variables so that the can be written to a debug file.
  double p_part = Kp * p_error;
  double d_part = Kd * d_error;
  double i_part = Ki * i_error;

  // calculate the steering output.
  double steering_output = (-p_part - d_part - i_part);
//  double steering_output = (- Kp * p_error - Kd * d_error - Ki * i_error);
  cout << "p_part: " << p_part << "\td_part: " << d_part << "\ti_part: " << i_part << endl;

  // write to the debug file. Note that the -ve steering angle is written to make it easier to compare to the other elements
  debugFile_ << count<< ","<< prev_cte << "," <<  p_part << "," << d_part << "," << i_part <<"," << -steering_output << endl;
  //  cin.get();
  return steering_output;
}



/**
 * Opens and sets up a csv file to store debug information to interpret
 *
 */
void PID::SetupCsv() {
// open the debug file
  debugFile_.open(debugFilename_, ios::out);

  // write the column headers
  debugFile_ << "Index" << "," << "CTE" << "," << "p_error" << "," << "d_error" << "," << "i_error"<< "," << "steering_output" << endl;

}
