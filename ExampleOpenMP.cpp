#include <stdio.h>
#include <math.h>
#include <ctime>
#include <chrono>
#include <iostream> 
#include <omp.h>

 
using namespace std; 
using namespace std::chrono; 



//This program is ran in C. It is compiled in min gw 32bit with g++
//The main function calls either trapezoidalRule or SimpsonsRule with an array of inputs values
//The program outputs the result and the error



double trapezoidalRuleP(double n, int numThreads){

	double a = 0.0;
	double b = M_PI;

	double header = ((b-a)/(2.0*n));
	//printf("%f\n", header);
	double body = 0.0;
	double currentIndex = 0.0;
	int newn = (int) n;
	
	omp_set_num_threads(numThreads);
	
	#pragma omp parallel for reduction(+:body)
		for(int i = 0; i <= newn; i++){
			if(i == 0){
				int nProcessors=omp_get_max_threads();
				//cout<<"Max threads="<< nProcessors <<endl;
				cout<<"threads="<<omp_get_num_threads()<<endl;

			}
			//int nProcessors=omp_get_max_threads();
			//cout<<"threads="<<omp_get_num_threads()<<endl;

			double temp = (double) i;
			currentIndex = a + (temp * (b - a)/n);

			
			if(i == 0 || i == n){
				body = body + sin(currentIndex);
			}else{
				body = body + 2.0 * sin(currentIndex);
			}
			//printf("%f\n", body);
		}


	//printf("%f\n", body * header);

	return (body*header);
}


double simpsonsRuleP(double n, int numThreads){
	

	double a = 0.0;
	double b = M_PI;

	//printf("Done with indexes\n");

	double header = ((b-a)/(3.0*n));
	//printf("%f\n", header);
	double body = 0.0;
	double currentIndex = 0.0;
	int newn = (int) n;


	omp_set_num_threads(numThreads);
	
	#pragma omp parallel for reduction(+:body)
		for(int i = 0; i <= newn; i++){
			
			if(i == 0){
				int nProcessors=omp_get_max_threads();
				//cout<<"Max threads="<< nProcessors <<endl;
				cout<<"threads="<<omp_get_num_threads()<<endl;

			}
			double temp = (double) i;
			currentIndex = a + (temp * (b - a)/n);
			
			if(i == 0 || i == n){
				body = body + sin(currentIndex);
			}else if(i % 2 ==1){
				body = body + 4.0 * sin(currentIndex);
			}else{
				body = body + 2.0 * sin(currentIndex);
			}
			//printf("%f\n", body);
		}

	//printf("%f\n", body * header);
	return (body*header);
}

int main(void){



	double segmentarray[] = {1000000.0};
	int numThreadsList[] = {1,2,4,8};

	cout << "OMP example for trapezoid and simpsons rule numerical integration of sin(x) 0 to pi" << endl;
	
	cout << "N is " << 1000000.0 << endl;

	for(int j = 0; j < (sizeof(numThreadsList)/sizeof(*numThreadsList)); j++){
		double sum1 = 0.0;
		double sum2 = 0.0;

		for(int i = 0; i < 1; i++){
			//clock_t begin = clock();
			auto start = high_resolution_clock::now(); 


			double result = trapezoidalRuleP(segmentarray[i], numThreadsList[j]);
			
			//clock_t end = clock();
			//double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			auto stop = high_resolution_clock::now(); 
			auto duration = duration_cast<microseconds>(stop - start); 
			cout << "Trapezoidal Rule Parallel Result " << result << " Time " << duration.count()/1000000.0 << endl;
			sum1 = duration.count()/1000000.0;

		}
		
		for(int i = 0; i < 1; i++){
			auto start = high_resolution_clock::now(); 

			double result2 = simpsonsRuleP(segmentarray[i], numThreadsList[j]);
			auto stop = high_resolution_clock::now(); 
			auto duration = duration_cast<microseconds>(stop - start); 
			cout << "Simpsons Rule Parallel Result " << result2 << " Time " << duration.count()/1000000.0 << endl;
			sum2 = duration.count()/1000000.0;
		}
		//cout << "Combined Time " << sum1 +sum2 << endl;
		
	}
	

}
