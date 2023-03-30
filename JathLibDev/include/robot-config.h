#pragma once
inline vex::brain Brain;
inline vex::controller cont(vex::primary);
inline vex::controller contS(vex::partner);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
