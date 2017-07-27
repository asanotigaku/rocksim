#include <iostream>
#include <fstream>
#include <map>
#include <sksat/math/vector.hpp>

double t = 0.;
const double dt= 0.001;
const double t_limit = 100.0;

double r = 0.;
double m = 0.04;
const double g = 9.8;

std::map<double, double> e_data;

void load_engine_data(){
	std::ifstream ifs;
	ifs.open("data/A8-3.dat");
	double e_time, e_thrust;
	while(ifs){
		ifs>> e_time >> e_thrust;
//		std::cout<<"time:"<<e_time<<" thrust:"<<e_thrust<<std::endl;
		e_data[e_time] = e_thrust;
	}
}

double engine(double time){
	static double before_thrust = 0.;
	if(e_data.find(time) != e_data.end())
		before_thrust = e_data[time];
	return before_thrust;
}

template<typename T>
const sksat::math::vector<T> func(sksat::math::vector<T> x){
	return sksat::math::vector<T>{
		x.get_y(),
		(r * x.get_y() + engine(t))/m - g,
	};
}

int main(int argc, char **argv){
	load_engine_data();

	sksat::math::vector<> x(0., 0.);

	bool liftoff_flg = false;

	for(auto i=0; t<=t_limit; ++i){
		std::cout
			<< t
			<< " "
			<< x.get_x()
//			<< engine(t)
			<< std::endl;

		x = x + dt * func(x);

		double tmp = x.get_x();
		if(tmp > 0 && liftoff_flg == false)
			liftoff_flg = true;
		if(liftoff_flg && tmp < 0)
			break;

		t = i * dt;
	}

	return 0;
}
