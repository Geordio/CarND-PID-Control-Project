#ifndef PID_H
#define PID_H
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;


class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;
  double prev_cte;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  string debugFilename_;
  ofstream debugFile_;
  int count;

  /*
   * twiddle parameters
   */
  std::vector<double> p;
  std::vector<double> dp;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();


  /*
  * Calculate Steering control command.
  */
  double Steering();

  /*
  * Twiddle function
  */
  double Twiddle();

  /*
  * Sets up a csv file for debug information
  */
  void SetupCsv();
};

#endif /* PID_H */
