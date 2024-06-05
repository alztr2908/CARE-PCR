#include "ThermocyclerOperation.h"
#include <Arduino.h>
#include "../GlobalDeclarations.h"
// #include "PID_v1.h"

// ADS1115 ADS(0x48); // address of the ADC
// double Kp = 40;
// double Ki = 1.1;
// double Kd = 10;
// double current_temp;
// double actual_temp;
// bool maintain = false;
// float maintain_start;
// const int num_cycles = 6; // TO DO: CHANGE THIS TO A CYCLE = 3 STEPS SYSTEM
// float cycle_duration[num_cycles] = {60.0, 60.0, 60.0, 60.0, 60.0, 60.0};
// float setpoints_array[num_cycles] = {50.0, 68.0, 75.0, 50.0, 68.0, 75.0};
// int setpoint_idx = 0;

// setpoint is the temp we want
// input is where the pin that reads the thermistor will be
// output is where the pwm will come from
// double Setpoint, Input, Output;

// PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

// float TimeNow_1;
// float TimeNow_2;
// float UpdateInterval = 1000;

// given some temp, and the globally set <Setpoint>, compute <Output> PWM based on PID G(s)
void PCR_PID(double temp, double setPoint)
{
  /* Peltier Explanation */
  //[InA,InB] = (9,10)[0,1] such that [OutA, OutB] = [-,+], peltier is connected [red, black]
  // [red,black] = (9,10)[0,1] is heating
  // [red, black] = (9,10)[1,0] is cooling

  // HEATING MODE
  if (temp < setPoint + 1)
  {
    pageManager.blockPWMInput = temp;
    pageManager.currentTargetSetpoint = setPoint;

    pageManager.PIDCompute(); // "return" output.. modify output inside the function

    // heat mode if we need to go higher
    // assert bit for peltier's heating mode in a PWM manner
    analogWrite(9, 0); // reset bit for cooling mode
    analogWrite(10, pageManager.blockPWMOutput);

    // send same PWM to heater
    analogWrite(11, pageManager.blockPWMOutput);

    // Serial.println("Heating Mode");
  }

  // COOLING MODE
  else
  {
    // else, if we need cooling, put the pwm on the port meant for the peltier

    // Reflect the input about the setPoint axis
    pageManager.blockPWMInput = temp * (-1.0);
    pageManager.currentTargetSetpoint = setPoint * (-1.0);
    // setPoint *= (-1.0);

    pageManager.PIDCompute(); // "return" output.. modify output inside the function
    analogWrite(9, pageManager.blockPWMOutput);
    analogWrite(10, 0);
    analogWrite(11, 0); // turn off the heater
    // Serial.println("Cooling Mode");
  }
}

// use the long temp array for resolution
float ConvertToTemp(float r_ntc)
{
  float resistance_table[200] = {310.764, 303.08805, 295.4121, 288.16025, 280.9084, 274.0549, 267.2014, 260.72209999999995, 254.2428, 248.11525, 241.9877, 236.19085, 230.394, 224.90820000000002, 219.4224, 214.22925, 209.0361, 204.1184, 199.2007, 194.5424, 189.8841, 185.47, 181.0559, 176.872, 172.6881, 168.72105, 164.754, 160.9915, 157.229, 153.6594, 150.0898, 146.7021, 143.3144, 140.09845, 136.8825, 133.8287, 130.7749, 127.87415, 124.9734, 122.2173, 119.4612, 116.84175, 114.2223, 111.732, 109.2417, 106.8735, 104.5053, 102.25265, 100, 97.8566, 95.7132, 93.67325, 91.6333, 89.69125, 87.7492, 85.89985, 84.0505, 82.28895, 80.5274, 78.84905, 77.1707, 75.5712, 73.9717, 72.44695, 70.9222, 69.4683, 68.0144, 66.62774999999999, 65.2411, 63.91825, 62.5954, 61.33305, 60.0707, 58.86585, 57.661, 56.5107, 55.3604, 54.26195, 53.1635, 52.1143, 51.0651, 50.062650000000005, 49.0602, 48.10225, 47.1443, 46.22865, 45.313, 44.43755, 43.5621, 42.72495, 41.8878, 41.087, 40.2862, 39.52005, 38.7539, 38.02075, 37.2876, 36.585899999999995, 35.8842, 35.21235, 34.5405, 33.897149999999996, 33.2538, 32.6376, 32.0214, 31.4311, 30.8408, 30.275199999999998, 29.7096, 29.16745, 28.6253, 28.105649999999997, 27.586, 27.08775, 26.5895, 26.11165, 25.6338, 25.175449999999998, 24.7171, 24.27735, 23.8376, 23.41565, 22.9937, 22.58835, 22.183, 21.79455, 21.4061, 21.03275, 20.6594, 20.3009, 19.9424, 19.59805, 19.2537, 18.922849999999997, 18.592, 18.274099999999997, 17.9562, 17.6507, 17.3452, 17.051499999999997, 16.7578, 16.4754, 16.193, 15.92145, 15.6499, 15.38875, 15.1276, 14.876349999999999, 14.6251, 14.3834, 14.1417, 13.90905, 13.6764, 13.4525, 13.2286, 13.0131, 12.7976, 12.59005, 12.3825, 12.182649999999999, 11.9828, 11.790299999999998, 11.5978, 11.4124, 11.227, 11.04835, 10.8697, 10.69755, 10.5254, 10.359449999999999, 10.1935, 10.03355, 9.8736, 9.7194, 9.5652, 9.4165, 9.2678, 9.12435, 8.9809, 8.84255, 8.7042, 8.57075, 8.4373, 8.3085, 8.1797, 8.05545, 7.9312, 7.8111999999999995, 7.6912, 7.5754, 7.4596, 7.347799999999999, 7.236, 7.12805, 7.0201, 6.9158, 6.8115, 6.7108, 6.6101};

  // Binary Search solution
  int low = 0;
  int high = 200;

  while (low <= high)
  {
    int mid = (low + high) / 2;

    if (r_ntc == resistance_table[mid])
    {
      return mid / 2.0;
    }
    else if (r_ntc < resistance_table[mid])
    {
      low = mid + 1;
    }
    else
    {
      high = mid - 1;
    }
  }

  // If no exact match is found, check the surrounding values
  if (low > 0 && r_ntc < resistance_table[low - 1] && r_ntc >= resistance_table[low])
  {
    return (low - 1) / 2.0;
  }

  if (high < 200 && r_ntc < resistance_table[high] && r_ntc >= resistance_table[high + 1])
  {
    return high / 2.0;
  }

  // Return a default value or error indicator if no match found
  return -1; // or some other error value appropriate for your application
}

// Return a default value or error indicator if no match found
// return r_ntc; // or some other error value appropriate for your application
// }

// function to read voltage value from A0
float ReadTemp()
{

  // ADC stuff, replace analogRead with this after testing
  // ADS.setGain(0);
  // int16_t val_0 = ADS.readADC(0);
  // float f = ADS.toVoltage(2);  // voltage factor

  float Vout = (analogRead(A0) * (5.0 / 1024.0));
  // Serial.println("Vout: ");
  // Serial.println(Vout);
  float R_NTC = (Vout * 51000) / (3.3 - Vout);
  // Serial.println("RNTC: ");
  // Serial.println(R_NTC);
  float Temp_C = ConvertToTemp((R_NTC / 1000.0));
  // Serial.println("Temp in C: ");
  // Serial.println(Temp_C);

  return Temp_C;
  // return resistance_table[0];
  // return R_NTC;
}

// void setup()
// {
// put your setup code here, to run once:
// pinMode(A0, INPUT);
// pinMode(5, OUTPUT);  // INA, peltier
// pinMode(6, OUTPUT);  // INB, peltier
// pinMode(10, OUTPUT); // heater
// // digitalWrite(10, 255);
// digitalWrite(5, 0);
// digitalWrite(6, 0);
// digitalWrite(10, 0);

// digitalWrite(5, HIGH); digitalWrite(6, LOW); //[InA, InB] = [1,0]
// digitalWrite(5, LOW); digitalWrite(6, HIGH); //[InA, InB] = [0,1]

// Input = analogRead(A0);
// Setpoint = setpoints_array[0];

// myPID.SetMode(AUTOMATIC);

// TimeNow_1 = millis();
// Serial.begin(9600);

// adc nonsense
// Serial.println(__FILE__);
// Serial.print("ADS1X15_LIB_VERSION: ");
// Serial.println(ADS1X15_LIB_VERSION);
// ADS.begin();
// }

// void loop()
// {
//   // put your main code here, to run repeatedly:
//   TimeNow_2 = millis();
//   if ((TimeNow_2 - TimeNow_1) > UpdateInterval)
//   {
//     actual_temp = ReadTemp();
//     PCR_PID(actual_temp);
//     TimeNow_1 = TimeNow_2;
//     Serial.println(actual_temp);
//   }

/*
When the system detects that we are at the desired temperature (Setpoint)
Start a timer that counts towards the desired duration to be at a given temp
For this test system, keep it at 30s for each cycle that demands temperature
T_setpoint, stored in setpoints_array

*/

//   //  ERamp mode
//   if (!maintain)
//   {
//     // if we arent maintaining yet, check for the moment when the temperature hits the required setpoint

//     if ((actual_temp == Setpoint) || (actual_temp == Setpoint - 1))
//     {
//       maintain = true;
//       maintain_start = millis(); // record the instance when we hit the required temperature
//     }
//   }

//   // ERunning mode
//   if (maintain)
//   {

//     // if we are maintaining rn, constantly check for if the proper amount of time has elapsed.
//     if (((millis() - maintain_start) >= (cycle_duration[setpoint_idx] * 1000)))
//     {
//       /*
//       when we've already been maintaining for the required amount of time
//       we are done with that temperature step, and now lets move on to the next step:
//       change the setpoint to the next one in the array:
//       */
//       maintain = false; // we are no longer in the maintain mode
//       setpoint_idx++;

//       Setpoint = setpoints_array[setpoint_idx]; // go to the next setpoint

//       // add some logic to repeat in terms of cycles
//     }
//   }
// }
