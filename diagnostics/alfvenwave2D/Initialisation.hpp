#ifndef INITIALISATION_HPP_
#define INITIALISATION_HPP_

#include <vector>
#include <cmath>

class Initialisation{
public:
    int nx;
    int ny;
    double Dx;
    double Dy;
    double Dt;
    double FinalTime;
    int order;
    int nghost;

    std::vector<std::vector<double>> rho;
    std::vector<std::vector<double>> vx;
    std::vector<std::vector<double>> vy;
    std::vector<std::vector<double>> vz;
    std::vector<std::vector<double>> Bx;
    std::vector<std::vector<double>> By;
    std::vector<std::vector<double>> Bz;
    std::vector<std::vector<double>> P;


    Initialisation() {
        nx = 200;
        ny = 100;
        Dx = 0.01;
        Dy = 0.01;
        Dt = 0.0;
        FinalTime = 1;
        order = 1;
        nghost = 1;

        double kx = (2.0*M_PI);
        double ky = (2.0*M_PI);
        double cosalpha = 1;//std::sqrt(2.0) / 2.0;
        double sinalpha = 1;//std::sqrt(2.0) / 2.0;

        rho.resize(ny, std::vector<double>(nx, 1.0));
        vx.resize(ny, std::vector<double>(nx, 0.0));
        vy.resize(ny, std::vector<double>(nx, 1.0));
        vz.resize(ny, std::vector<double>(nx, 0.0));
        Bx.resize(ny, std::vector<double>(nx, 1.0 / 2.0 * sinalpha));
        By.resize(ny, std::vector<double>(nx, 1.0 / 2.0 * cosalpha));
        Bz.resize(ny, std::vector<double>(nx, 0.0));
        P.resize(ny, std::vector<double>(nx, 0.1));

        for(int i=0; i<nx; i++){
            for(int j=0; j<ny; j++){
                vx[j][i] = UserFunction1(0.1, kx * (i+0.5) * Dx * cosalpha + ky * (j+0.5) * Dy * sinalpha) / 2.0 * sinalpha;
                vy[j][i] = UserFunction1(-0.1, kx * (i+0.5) * Dx * cosalpha + ky * (j+0.5) * Dy * sinalpha) / 2.0 * cosalpha;
            }
        }

        for(int i=0; i<nx; i++){
            for(int j=0; j<ny; j++){
                Bx[j][i] -= UserFunction1(0.1, kx * (i+0.5) * Dx * cosalpha + ky * (j+0.5) * Dy * sinalpha) / 2.0 * sinalpha;
                By[j][i] += UserFunction1(0.1, kx * (i+0.5) * Dx * cosalpha + ky * (j+0.5) * Dy * sinalpha) / 2.0 * cosalpha;
            }
        }
    }
    ~Initialisation() = default;
private:
    double UserFunction1(double ampl, double kx){
        return ampl*cos(kx);
    }
};


#endif //INITIALISATION_HPP_