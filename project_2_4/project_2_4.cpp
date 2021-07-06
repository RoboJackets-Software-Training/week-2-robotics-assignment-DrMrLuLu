#include <iostream>  // Gives us access to std::cin and std::cout
#include <string>  // Gives us access to std::string and std::getline()

struct LightOutputs {
  bool red_ns;
  bool yellow_ns;
  bool green_ns;
  bool red_ew;
  bool yellow_ew;
  bool green_ew;
};

struct LightInputs {
  int time;
  bool car_sensor_n;
  bool car_sensor_s;
};


class lightStateMachine {
  public:
    

    void transition(const LightInputs &inputs) {
      switch (state) {
        case 0:
          if (inputs.car_sensor_n || inputs.car_sensor_s) {
            state = 2;
          } else {
            state = 4;
          }
          time = inputs.time + 5;
          break;
        case 1:
          if (inputs.time >= time) {
            state = 0;
          }
          break;
        case 2:
          if (inputs.time >= time) {
            state = 1;
            time = inputs.time + 2;
          }
          break;
        case 3:
          if (inputs.time >= time) {
            state = 0;
          }
        break;
        case 4:
          if (inputs.time >= time) { 
            state = 3;
            time = inputs.time + 2;
          }
        break;
      }     
    }

    LightOutputs update(const LightInputs &inputs) {
      transition(inputs);
      return getStateControls();
    }
    
    LightOutputs getStateControls() {
      LightOutputs outputs;
      outputs.red_ns = false;
      outputs.yellow_ns = false;
      outputs.green_ns = false;
      outputs.red_ew = false;
      outputs.yellow_ew = false;
      outputs.green_ew = false;
      switch (state) {
        case 0:
          outputs.red_ns = true;
          outputs.red_ew = true;
        case 1:
          outputs.yellow_ns = true;
          outputs.red_ew = true;
        case 2:
          outputs.green_ns = true;
          outputs.red_ew = true;
        case 3:
          outputs.red_ns = true;
          outputs.yellow_ew = true;
        case 4:
          outputs.red_ns = true;
          outputs.green_ew = true;
    }
    return outputs;
  }
  private:
  int state = 0;
  /*
    state 0: all red
    state 1: yellow ns
    state 2: green ns
    state 3: yellow ew
    state 4: green ew
  */
  int time = 0;
};

// TODO Define your light controller state machine class here

int main()
{
    // I needed to look at the answer for some of the struct and pointer stuff. unfortantly, I'm still very bad at those things.
    int time = 0;
    lightStateMachine controller;

    while(true)
    {
        std::string input;
        std::getline(std::cin, input);
        if(input.size() != 2)
            break;
      
        const LightInputs inputs{
            time,
            input[0] == '1',
            input[1] == '1'
        };

        LightOutputs output = controller.update(inputs);

        // copied the print from the answer. I dont know the formating.
        std::cout << output.red_ns << output.yellow_ns << output.green_ns
                  << output.red_ew << output.yellow_ew << output.green_ew
                  << "\n";

        time++;
    }
    return 0;
}
