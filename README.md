# DS3231_Light Arduino Library
Minimal functionality requirements library for DS3231 RTC IC

* This library is only intended for 2000-2099 year use
* This library is intended for use in projects where **alarm functionalities are not required**.
  * It has getter and setter functions for both **time** and **date**
  * It has an **automatic day of the week calculator**, triggered after every day, month or year modification
    * The calculator only works for gregorian calendar 
  * It has a get and set full time string
  * It has a get and set full date string
  * All functions have their purpose in the .h file
