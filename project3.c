/** 
 * Project Name: Component Reliability
 * Description: This program computes and displays expected reliabilities for series and parallel 
 * 				configurations of components (using specified formulas).
 * Last Update Date: 10/27/2021
**/

#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

double GetSeriesReliability(double componentReliability, unsigned componentCount);
double GetParallelReliability(double componentReliability, unsigned componentCount);
bool WasComponentSuccessful(double componentReliability);
double RunSimulationTrials(double componentReliability, unsigned componentCount, unsigned trialCount, bool isSeriesSimulation);

int main ()
{
	srand((unsigned)time(NULL));	//calling srand function to seed the random numbers generator with internal clk time

	double componentReliability;	//individual component reliability
	unsigned int componentCount; //number of components used to be used in each system
	unsigned int trialCount; //number of simulation trials to be performed
	
	//---> USER INPUT FOR CALCULATION <---//
	printf("Component Reliability Calculator\n--------------------------");
	printf("\nEnter the reliability of the individual component : ");
	scanf("%lf", &componentReliability);
	while((componentReliability < 0) || (componentReliability > 1)) {
		printf("Error. Component reliability must be a value between 0 and 1. Please try again.\n");
		printf("Enter the reliability of the individual component : ");
		scanf("%lf", &componentReliability);
	}
	printf("\nEnter the number of components to be used in each system : ");
	scanf("%u", &componentCount);
	while(componentCount < 1) {
		printf("Error. The number of components must be an integer greater than 1. Please try again.\n");
		scanf("Enter the number of components to be used in each system : ");
		scanf("%u", &componentCount);
	}
	printf("\nEnter the number of simulation trials to be performed : ");
	scanf("%u", &trialCount);
	while(trialCount < 1) {
		printf("Error. The number of trials must be an integer greater than 1. Please try again.\n");
		scanf("Enter the number of simulation trials to be performed : ");
		scanf("%u", &trialCount);
	}
	//-------------

	double series_SysReliability;
	double parallel_SysReliability;

	//---> Code Check
	//User input of componentReliability = 0.85 and componentCount = 4 should result in series_r = 52.2% and parallel_r = 99.9%
	series_SysReliability = GetSeriesReliability(componentReliability, componentCount);
	parallel_SysReliability = GetParallelReliability(componentReliability, componentCount);

	printf("\nCalculated series reliability = %.1f %%", series_SysReliability*100);
	printf("\nCalculated parallel reliability = %.1f %%", parallel_SysReliability*100);

	double series_simReliability = RunSimulationTrials(componentReliability, componentCount, trialCount, true);
	double parallel_simReliability = RunSimulationTrials(componentReliability, componentCount, trialCount, false);
	
	printf("\n\nSimulated series reliability = %.1f %%", series_simReliability*100);
	printf("\nSimulated parallel reliability = %.1f %%", parallel_simReliability*100);
	printf("\n--------------------------\n");
	return 0;
} // END main function

double GetSeriesReliability(double componentReliability, unsigned componentCount)
{
	double r;
	r = pow(componentReliability, componentCount);
	return r;
}

double GetParallelReliability(double componentReliability, unsigned componentCount)
{
	double r;
	r = 1 - pow((1 - componentReliability), componentCount);
	return r;
}

bool WasComponentSuccessful(double componentReliability)
{
	if(rand() <= (componentReliability*RAND_MAX)) {
		return true;
	}
	else {
		return false;
	}
}

double RunSimulationTrials(double componentReliability, unsigned componentCount, unsigned trialCount, bool isSeriesSimulation)
{
	if(isSeriesSimulation == true) {
		printf("\n\nRunning series simulation trials...");
	}
	else {
		printf("\nRunning parallel simulation trials...");
	}

	int trialSuccessCount;
	for(int i = 1; i < trialCount; i++) {
		int componentSuccessCount;
		for(int j = 1; j < componentCount; j++) {
			if(WasComponentSuccessful(componentReliability) == true) {
				componentSuccessCount++;
			}
		}
		if((isSeriesSimulation == true) && (componentSuccessCount >= 1)) {
			trialSuccessCount++;
		}
		else if((isSeriesSimulation == false) && (componentSuccessCount >= 1)) {
			trialSuccessCount++;
		}
		else {
			trialSuccessCount = trialSuccessCount;
		}
	}

	double simReliability;
	simReliability = trialSuccessCount/trialCount;
	return simReliability;
}