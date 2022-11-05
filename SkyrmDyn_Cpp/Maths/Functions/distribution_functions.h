#ifndef DISTRIBUTION_FUNCTIONS_H
#define DISTRIBUTION_FUNCTIONS_H

double gaussian( double x, double mean, double sigma );
double lorentzian( double x, double mean, double sigma );
double exponential( double x, double lambda );
int delta( double i, double j );

#endif // DISTRIBUTION_FUNCTIONS_H
