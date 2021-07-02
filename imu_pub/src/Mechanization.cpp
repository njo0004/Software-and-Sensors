// ----- Libraries ------ //
#include <iostream>
#include <fstream>
#include <math.h>
#include "Mechanization.h"

using namespace std;

// ----- Constructor ------ //
Mechanization::Mechanization(double* qInput,double dtInput):q(qInput),dt(dtInput){}

// ----- IMU Mechanization Function ------ //
void Mechanization::mechanizeThis(double* gyro, double dt){
        
    double tempq[4] = {q[0],q[1],q[2],q[3]};
    
    // Mechanization Math Block
    q[0] = tempq[0] - 0.5*gyro[0]*dt*tempq[1] - 0.5*gyro[1]*dt*tempq[2] - 0.5*gyro[2]*dt*tempq[3];
    q[1] = 0.5*gyro[0]*dt*tempq[0] + tempq[1] + 0.5*gyro[2]*dt*tempq[2] - 0.5*gyro[1]*dt*tempq[3];
    q[2] = 0.5*gyro[1]*dt*tempq[0] - 0.5*gyro[2]*dt*tempq[1] + tempq[2] + 0.5*gyro[0]*dt*tempq[3];
    q[3] = 0.5*gyro[2]*dt*tempq[0] + 0.5*gyro[1]*dt*tempq[1] - 0.5*gyro[0]*dt*tempq[2] + tempq[3];
        
}

// ------ IMU Normalization Function ----- //
void Mechanization::normalizeThis(double* q){

    double tempq[4] = {q[0],q[1],q[2],q[3]};

    double mag = pow(pow(tempq[0],2)+pow(tempq[1],2)+pow(tempq[2],2)+pow(tempq[3],2),0.5); // calculating magnitude of unnormalized vector; // unnormalized vector magnitude variable 
    q[0] = tempq[0]/(mag); q[1] = tempq[1]/(mag); q[2] = tempq[2]/(mag); q[3] = tempq[3]/(mag);  // Normalization

}

// ----- IMU Update Function (Calls Mechanization and Normalization Functions) ----- //
void Mechanization::update(double* q,double* gyro){

    mechanizeThis(gyro,dt);
    normalizeThis(q);
    
}