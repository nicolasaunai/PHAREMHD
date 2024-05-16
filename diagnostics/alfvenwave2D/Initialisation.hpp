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
        nx = 100;
        ny = 100;
        Dx = 0.01;
        Dy = 0.01;
        Dt = 0.008;
        FinalTime = 2;
        order = 1;
        nghost = 1;
        rho.resize(ny, std::vector<double>(nx, 1.0));
        vx.resize(ny, std::vector<double>(nx, 0.0));
        vy.resize(ny, std::vector<double>(nx, 0.0));
        vz.resize(ny, std::vector<double>(nx, 0.0));
        Bx.resize(ny, std::vector<double>(nx, 1.0));
        By.resize(ny, std::vector<double>(nx, 0.0));
        Bz.resize(ny, std::vector<double>(nx, 0.0));
        P.resize(ny, std::vector<double>(nx, 0.1));


        double kx = (2*M_PI) * Dx;
        double ky = (2*M_PI) * Dy;

        for(int i=0; i<nx; i++){
            for(int j=0; j<ny; j++){
                vy[j][i] = UserFunction1(-1e-6, kx*i + ky*j);
            }
        }

        for(int i=0; i<nx; i++){
            for(int j=0; j<ny; j++){
                By[j][i] = UserFunction1(1e-6, kx*i + ky*j);
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