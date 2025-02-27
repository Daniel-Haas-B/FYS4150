#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>
#include <armadillo>
#include "./include/Particle.hpp"
#include "./include/PenningTrap.hpp"

void prettyprint(arma::vec armavec, std::string title, std::vector<std::string> labels);
void RK4_data(int n_particles,int n_timesteps,double total_time, std::string inter);
void Euler_data(int n_particles,int n_timesteps,double total_time);

///////// MAKING A PENNING TRAP AND MAKING IT GLOBALLY ACCESSIBLE /////////

//define your physical system's variables here:
//use atomic mass units, micrometers, microseconds and element.charge e 
double B0 = 9.65 * pow(10,1);
double V0 = 2.41 * pow(10, 6);  
double d = 500; //micrometers
double q = 1;//.602 * pow(10,-19); //double check with the A-team
double m = 40.078; //calcium ion's atomic mass in atomic mass units



PenningTrap PT = PenningTrap(B0, V0, d);

// main function takes input arguments from the command line: Method, n_timesteps, total_time
int main(int argc, char*argv[] )
{   

    //If the user doesn't input the correct number of arguments, print an error message and exit
    if (argc != 5)
    {
        std::cout << "Error: Incorrect number of arguments. Please input the method, number of timesteps, and total time. got:" << argc <<std::endl;
        return 1;
    }
    //define your positions and velocities 
    arma::vec r1 = arma::vec(std::vector<double> { 20, 0, 20 }); //micrometers 
    arma::vec v1 = arma::vec(std::vector<double> { 0, 25, 0 }); //micrometers per microsec
    arma::vec r2 = arma::vec(std::vector<double> { 25, 25, 0 }); //micrometers 
    arma::vec v2 = arma::vec(std::vector<double> { 0, 40, 5 }); //micrometers per microsec

    //Option to turn interactions on and off
    std::string inter=argv[4];
    std::cout << inter <<"|" << "Type: " << typeid(inter).name() << std::endl;
    if (inter == "on")
    {
        PT.toggle_interaction(true);
    }
    else if (inter == "off")
    {
        PT.toggle_interaction(false);
    }
    else
    {
        std::cout << "Error: Please input 'on' or 'off' for particle-particle interaction." << std::endl;
        return 1;
    }
    //remember to define correct elementary charge value here!!
    //here, I create object of type "Particle" using our class, which I call "particle1", and assign attributes to it such as 
    //charge, mass, position and velocity!
    Particle particle1 = Particle(q, m, r1, v1);
    //I do the same thing here, just for the second particle 
    Particle particle2 = Particle(q, m, r2, v2);
    // Adding particles to the trap
    PT.add_particle(particle1);
    PT.add_particle(particle2);
    




    // Define time step and number of time steps
    double total_time= atoi(argv[3]);
    int N = atoi(argv[2]);
    double dt = total_time/N;
    int n_particles = PT.particles.size();
    // If methis is Rk4, call RK4_data
    if (std::string(argv[1]) == "RK4")
    {
        RK4_data(n_particles,N,total_time,inter);
    }
    // If method is Euler, call Euler_data
    else if (std::string(argv[1]) == "Euler")
    {
        Euler_data(n_particles,N,total_time);
    }
    // If method is not Euler or RK4, print error message
    else
    {
        std::cout << "Error: Method must be either Euler or RK4" << std::endl;
    }




    return 0;
}

//Function for producing data with RK4

void RK4_data(int n_particles,int n_timesteps,double total_time,std::string inter)
{
    // Define time step and number of time steps
    double dt = total_time/n_timesteps;
    
    // Use rk4 to evolve and write to file

    // Format parameters
    std::ofstream outfile;
	int width = 25;
	int prec = 15;
    // make path to output file with the method, number of timesteps, and total time
    std::string path_str = "./Data/RK4_"+std::to_string(n_particles)+"_" + std::to_string(n_timesteps) + inter + ".txt";

    //const char *path=path_str;
    outfile.open(path_str);

    for (int i = 0; i < n_timesteps +1; i++) 
    {   
            PT.evolve_RK4(dt);
            
        for (int j = 0; j < n_particles; j++)
                    {
                PT.particles.at(j).time+=dt;
                //std::cout << "particle " << j << " has position " << PT.particles.at(j).r << " and velocity " << PT.particles.at(j).v << "at time : t="<<PT.particles.at(j).time<< std::endl;
                
                    outfile << 
                    std::setw(width) << std::setprecision(prec) <<PT.particles.at(j).r.at(0) << 
                    std::setw(width) << std::setprecision(prec) << PT.particles.at(j).r.at(1) << 
                    std::setw(width) << std::setprecision(prec)<< PT.particles.at(j).r.at(2) <<  
                    
                    std::setw(width) << std::setprecision(prec) << PT.particles.at(j).v.at(0) << 
                    std::setw(width) << std::setprecision(prec) << PT.particles.at(j).v.at(1) << 
                    std::setw(width) << std::setprecision(prec) << PT.particles.at(j).v.at(2) <<
                    std::setw(width) << std::setprecision(prec) << j << std::endl;
                    }
            }
    outfile.close();



        

}

//Function for producing data with Euler

void Euler_data(int n_particles,int n_timesteps,double total_time)
{
    // Define time step and number of time steps
    double dt = total_time/n_timesteps;
    
    // Use rk4 to evolve and write to file

    // Format parameters
    std::ofstream outfile;
    int width = 25;
    int prec = 15;

        // make path to output file with the method, number of timesteps, and total time
    std::string path_str = "./Data/Euler_" +std::to_string(n_particles)+"_"+ std::to_string(n_timesteps) + ".txt";
    outfile.open(path_str);

    for (int i = 0; i < n_timesteps +1; i++) 
    {   
            PT.evolve_RK4(dt);
            
        for (int j = 0; j < n_particles; j++)
        {
            
                outfile << 
                std::setw(width) << std::setprecision(prec) <<PT.particles.at(j).r.at(0) << 
                std::setw(width) << std::setprecision(prec) << PT.particles.at(j).r.at(1) << 
                std::setw(width) << std::setprecision(prec)<< PT.particles.at(j).r.at(2) <<  
                
                std::setw(width) << std::setprecision(prec) << PT.particles.at(j).v.at(0) << 
                std::setw(width) << std::setprecision(prec) << PT.particles.at(j).v.at(1) << 
                std::setw(width) << std::setprecision(prec) << PT.particles.at(j).v.at(2) <<  
                std::endl;
                
            
            }
    }
    outfile.close();


}

//nice function to print stuff out : enables print of xyz position and velocity
void prettyprint(arma::vec armavec, std::string title, std::vector<std::string> labels)
{
    if (labels.size() != armavec.n_elem)
    {
        std::cout << "Size mismatch." << std::endl;
        return;
    }

    std::cout << title << std::endl;

    for (int i = 0; i < labels.size(); ++i)
        std::cout << "  " << labels.at(i) << ": " << armavec.at(i) << std::endl;
}
