// MECHANIZATION CLASS HEADER //

#ifndef MECHANIZATION_H
#define MECHANIZATION_H

class Mechanization{
    public:

        double* q;
        double dt;
        double* gyro;

        Mechanization(double* qInput,double dtInput); // Constructor Prototype

        void mechanizeThis(double* gyro, double dt); // Mechanization Prototype
        void normalizeThis(double* q); // Normalization Prototype
        void update(double* q, double* gyro); // Update Prototype

};

#endif

