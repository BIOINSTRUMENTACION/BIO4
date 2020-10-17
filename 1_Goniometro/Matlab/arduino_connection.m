clc; clear all; close all;
a = arduino;                               % Create Arduino Instance
voltage = readVoltage(a,'A0');             % Obtain analog Voltage
angle = -50.84389624*voltage + 218.4824554 % convert voltage to angle (We obtained this using python)
