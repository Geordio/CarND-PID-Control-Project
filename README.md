# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Intoduction
Implementing the PID code was fairly simple based on the lesson material.
Tuning the PID controller was much more challenging
I was unable to implement a working twiddle function, so I manually tuned the PID controller, essentialy replicating the twiddle function manually, whilst also using references that I found online such as:
https://robotics.stackexchange.com/questions/167/what-are-good-strategies-for-tuning-pid-loops
https://innovativecontrols.com/blog/basics-tuning-pid-loops

In order to aid in the tuning, I wanted to plot some meaningful data.
I populated a csv file with the P,I,D values to the steering command, against the CTE value, so that I could compare the contributions of each to the overal steering command.
I then wrote some python code to parse the csv and plot the PID perfomance and appropriate parts of the track.


## PID Tuning

#### P Gain
I set all gains to 0 except for the P, which I initially set to 1.
This performed porrly, crashing in a short space of time. The Steering command was equal to the CTE, so when the cross track error is greater than 1, the steering request is greater than 1 (but the range should be -1 to +1).

A plot of the Steering output value can be seen below. Note that this actually shows the CTE value, the P value and the steering output, but as Kp = 1, Kd = 0, Ki = 0, all 3 traces are equal, i.e plotted on top of each other.
Note, the keys ae misisng off these plots. The key is. CTE: Black, Steering Output: Red, P: Green, D: Blue, I: Cyan
<img src="https://github.com/Geordio/CarND-PID-Control-Project/blob/master/py/debug_initial_1_0_0.png" alt="PID Plot" width="200" height="200"/>

Hence I reduced the gain over a number of iterations the P gain until it was oscilating, but was able to stay on the road for the initial straight, and keeping the output steering command in the region 0 -1 to +1.
At this point Kp = 0.2.

See plot below
<img src="https://github.com/Geordio/CarND-PID-Control-Project/blob/master/py/debug_initial_1_0_0.png" alt="PID Plot" width="200" height="200"/>
The key is. CTE: Black, Steering Output: Red, P: Green, D: Blue, I: Cyan


#### D Gain

I then modified the D gain. Selecting an appropriate D gain will minimise the overshoots.
Again, I started by setting this to 1.


This time the vehicle was able to get round a large proportion of the track, but the performance was still poor, with excessive oscilation and overshoots, particularly on the bridge.
I analysed the plot of the P,I,D values.

Below is the plot of the start of the drive
<img src="https://github.com/Geordio/CarND-PID-Control-Project/blob/master/py/debug_initial_1_0_0.png" alt="PID Plot" width="200" height="200"/>
The key is. CTE: Black, Steering Output: Red, P: Green, D: Blue, I: Cyan

Note the overshoot is now much more reduced than it was at this point

Below is the plot of around the position of the bridge
<img src="https://github.com/Geordio/CarND-PID-Control-Project/blob/master/py/debug_bridge_0.2_0_1.png" alt="PID Plot" width="200" height="200"/>
The key is. CTE: Black, Steering Output: Red, P: Green, D: Blue, I: Cyan

As you can see the oscilations at this point are very bad (as shown by the black CTE line)

Note that the D (the blue line) is not contributing enough to minimise the overshoots, so I increased this further over a number of increments. When I got to Kd = 2, the vehilce was able to complete a full lap.
Below is the plot of the start of the drive
<img src="https://github.com/Geordio/CarND-PID-Control-Project/blob/master/py/debug_initial_0.2_0_2.png" alt="PID Plot" width="200" height="200"/>

Below is the plot of around the position of the bridge
<img src="https://github.com/Geordio/CarND-PID-Control-Project/blob/master/py/debug_bridge_0.2_0_2.png" alt="PID Plot" width="200" height="200"/>

In both locations the CTE is signifantly reduced. On the bridge the oscilations are now fairly minimal.


#### I Gain

At this point I moved on to the I gain.
Leaving the Kp as 0.2 and Kd as 2, I set Ki to 1.
The vehicle performance was very poor, leaving the track immediately.
I analysed the start plot below. If you look carefully you can see the cyan I value immediately goes off the top of the graph and out of the range.

<img src="https://github.com/Geordio/CarND-PID-Control-Project/blob/master/py/debug_initial_0.2_1_2.png" alt="PID Plot" width="200" height="200"/>

I iteratively reduced the Ki value until I reached 0.001 (I reduced it fairly quickly as I was confident that the vehicle could negogiate a full lap with Ki=0)
A gif of a successful lap completion can be see below.
![lap gif](https://github.com/Geordio/CarND-PID-Control-Project/blob/master/py/PID_0.2_0.001_2_small.gif  "lap gif")

I did not implement a PID on the Throttle control due to time contraints (Christmas!). Instead the value is hardcoded to 0.4.

With the exiting implementation, the vehicle is able to navigate the track successully for many laps without incident, but it still has a tendancy to oscilate signifiantly, so could be tuned further.



# Other

The sections below are from the original README, left in for completeness

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`.

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).
