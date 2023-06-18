#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include"myClass.h"
#include"insert_and_delete.h"
#include"emergency_and_decision.h"
#include"after_each_time_unit.h"
#include"runwayState_and_output.h"
using namespace std;

const int landingMin = 0, landingMax = 4, takeoffMin = 0, takeoffMax = 3, fuelMin = 1, fuelMax = 10;

int greedy(char c, double sizeOfLandingQueue[], double sizeOfTakeoffQueue[], double total_fuel[])
{
	if (c == 'L')
	{
		int min = sizeOfLandingQueue[2] + sizeOfLandingQueue[5] + sizeOfTakeoffQueue[3], index = 2;
		for (int i = 1; i >= 0; i--)
		{
			if (min > (sizeOfLandingQueue[i] + sizeOfLandingQueue[i + 3] + sizeOfTakeoffQueue[i + 1]))
			{
				min = (sizeOfLandingQueue[i] + sizeOfLandingQueue[i + 3] + sizeOfTakeoffQueue[i + 1]);
				index = i;
			}
		}

		if (sizeOfLandingQueue[index + 3] <= sizeOfLandingQueue[index])
		{
			sizeOfLandingQueue[index + 3]++;
			return index + 3;
		}

		else
		{
			sizeOfLandingQueue[index]++;
			return index;
		}
	}

	else // c =='T'
	{
		int min = sizeOfTakeoffQueue[0], index = 0;
		for (int i = 1; i < 4; i++)
		{
			if (min > sizeOfTakeoffQueue[i] + sizeOfLandingQueue[i - 1] + sizeOfLandingQueue[i + 2])
			{
				min = sizeOfTakeoffQueue[i] + sizeOfLandingQueue[i - 1] + sizeOfLandingQueue[i + 2];
				index = i;
			}
		}
		sizeOfTakeoffQueue[index]++;
		return index;
	}
}

int main()
{
	LandingQueue R2_L1, R3_L1, R4_L1, R2_L2, R3_L2, R4_L2;
	TakeoffQueue R1_T, R2_T, R3_T, R4_T;
	double timeUnit, total_landingTime = 0, total_takeoffTime = 0, total_fuel_saved = 0,
		total_takeoffs = 0, total_landings = 0;
	int emergency = 0, crash = 0;
	int landing_rv, takeoff_rv, fuel_rv;
	int landing_id = 1, takeoff_id = 0, emergency_id, emergency_waitingTime;
	bool R1 = false, R2 = false, R3 = false, R4 = false;
	double sizeOfLandingQueue[6] = { 0 }, sizeOfTakeoffQueue[4] = { 0 };
	int R1_id = -1, R2_id = -1, R3_id = -1, R4_id = -1;
	double total_fuel[6] = { 0 }, counter = 0;

	srand(time(NULL));
	cout << "Please input the total time units you want to simulate: ";
	cin >> timeUnit;
	cout << endl << "--------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < timeUnit; i++)
	{
		landing_rv = rand() % (landingMax - landingMin + 1) + landingMin;
		takeoff_rv = rand() % (takeoffMax - takeoffMin + 1) + takeoffMin;
		cout << "Simulation Time: " << i + 1 << endl << endl; //***
		runwayState(R1_id, R2_id, R3_id, R4_id, R2_L1, R3_L1, R4_L1, R2_L2, R3_L2, R4_L2, R1_T, R2_T, R3_T, R4_T); //***
		cout << "Step 1:" << endl; //***
		cout << "landing plane:"; //***

		for (int j = 0; j < landing_rv; j++) // check for inserting landingQueue
		{
			fuel_rv = rand() % (fuelMax - fuelMin + 1) + fuelMin;
			cout << '(' << landing_id << ", " << fuel_rv << "), "; //***

			switch (greedy('L', sizeOfLandingQueue, sizeOfTakeoffQueue, total_fuel))
			{
			case 0:
				insertToLandingQueue(R2_L1, landing_id, fuel_rv);
				break;

			case 1:
				insertToLandingQueue(R3_L1, landing_id, fuel_rv);
				break;

			case 2:
				insertToLandingQueue(R4_L1, landing_id, fuel_rv);
				break;

			case 3:
				insertToLandingQueue(R2_L2, landing_id, fuel_rv);
				break;

			case 4:
				insertToLandingQueue(R3_L2, landing_id, fuel_rv);
				break;

			case 5:
				insertToLandingQueue(R4_L2, landing_id, fuel_rv);
				break;
			}
		}

		cout << endl << endl; //***
		runwayState(R1_id, R2_id, R3_id, R4_id, R2_L1, R3_L1, R4_L1, R2_L2, R3_L2, R4_L2, R1_T, R2_T, R3_T, R4_T); //***
		cout << "Step 2:" << endl; //***
		cout << "takeoff plane: "; //***

		for (int k = 0; k < takeoff_rv; k++) // check for inserting takeoffQueue
		{
			cout << '(' << takeoff_id << "), "; //***
			switch (greedy('T', sizeOfLandingQueue, sizeOfTakeoffQueue, total_fuel))
			{
			case 0:
				insertToTakeoffQueue(R1_T, takeoff_id);
				break;

			case 1:
				insertToTakeoffQueue(R2_T, takeoff_id);
				break;

			case 2:
				insertToTakeoffQueue(R3_T, takeoff_id);
				break;

			case 3:
				insertToTakeoffQueue(R4_T, takeoff_id);
				break;
			}
		}

		cout << endl << endl; //***
		runwayState(R1_id, R2_id, R3_id, R4_id, R2_L1, R3_L1, R4_L1, R2_L2, R3_L2, R4_L2, R1_T, R2_T, R3_T, R4_T); //***
		cout << "Step 3: " << endl; //***
		cout << "emergency plane: "; //***

		for (int m = 0; m < 6; m++) // check for emergency
		{
			LandingQueue* head = new LandingQueue;
			switch (m)
			{
			case 0:
				head = &R2_L1;
				break;

			case 1:
				head = &R3_L1;
				break;

			case 2:
				head = &R4_L1;
				break;

			case 3:
				head = &R2_L2;
				break;

			case 4:
				head = &R3_L2;
				break;

			case 5:
				head = &R4_L2;
				break;
			}

			LandingQueue* current = head->next;
			while (current->id != -1)
			{
				counter += current->fuel;
				if (current->fuel == 0)
				{
					cout << '(' << current->id << "), "; //***
					sizeOfLandingQueue[m]--;
					emergency += 1;
					emergency_id = current->id;
					emergency_waitingTime = current->waitingTime;
					current->prev->next = current->next;
					current->next->prev = current->prev;

					if (R1 == false)
					{
						emergency_landing(R1_id, emergency_id, emergency_waitingTime, total_landingTime, total_landings);
						R1 = true;
					}

					else if (R2 == false)
					{
						emergency_landing(R2_id, emergency_id, emergency_waitingTime, total_landingTime, total_landings);
						R2 = true;
					}

					else if (R3 == false)
					{
						emergency_landing(R3_id, emergency_id, emergency_waitingTime, total_landingTime, total_landings);
						R3 = true;
					}

					else if (R4 == false)
					{
						emergency_landing(R4_id, emergency_id, emergency_waitingTime, total_landingTime, total_landings);
						R4 = true;
					}

					else
						crash += 1;
				}
				current = current->next;
			}

			total_fuel[m] = counter;
			counter = 0;
		}

		cout << endl << endl; //***
		runwayState(R1_id, R2_id, R3_id, R4_id, R2_L1, R3_L1, R4_L1, R2_L2, R3_L2, R4_L2, R1_T, R2_T, R3_T, R4_T); //***
		cout << "Step 4:" << endl << endl; //***

		landOrTakeoff(R1, sizeOfTakeoffQueue, sizeOfLandingQueue, 0, R1_id,
			total_takeoffTime, total_landingTime, total_fuel_saved, R1_T, R2_L1,
			R2_L2, total_takeoffs, total_landings, total_fuel);

		landOrTakeoff(R2, sizeOfTakeoffQueue, sizeOfLandingQueue, 1, R2_id,
			total_takeoffTime, total_landingTime, total_fuel_saved, R2_T, R2_L1,
			R2_L2, total_takeoffs, total_landings, total_fuel);

		landOrTakeoff(R3, sizeOfTakeoffQueue, sizeOfLandingQueue, 2, R3_id,
			total_takeoffTime, total_landingTime, total_fuel_saved, R3_T, R3_L1,
			R3_L2, total_takeoffs, total_landings, total_fuel);

		landOrTakeoff(R4, sizeOfTakeoffQueue, sizeOfLandingQueue, 3, R4_id,
			total_takeoffTime, total_landingTime, total_fuel_saved, R4_T, R4_L1,
			R4_L2, total_takeoffs, total_landings, total_fuel);

		runwayState(R1_id, R2_id, R3_id, R4_id, R2_L1, R3_L1, R4_L1, R2_L2, R3_L2, R4_L2, R1_T, R2_T, R3_T, R4_T); //***

		landingQueue_after(R2_L1);
		landingQueue_after(R3_L1);
		landingQueue_after(R4_L1);
		landingQueue_after(R2_L2);
		landingQueue_after(R3_L2);
		landingQueue_after(R4_L2);
		takeoffQueue_after(R1_T);
		takeoffQueue_after(R2_T);
		takeoffQueue_after(R3_T);
		takeoffQueue_after(R4_T);
		R1 = false, R2 = false, R3 = false, R4 = false;
		R1_id = -1, R2_id = -1, R3_id = -1, R4_id = -1;
	}

	cout << "How Many Time Unit You Want to Simulate: " << timeUnit << endl;
	cout << "average landing waiting time: " << fixed << setprecision(3) << total_landingTime / total_landings << "(s)" << endl;
	cout << "average takeoff waiting time: " << fixed << setprecision(3) << total_takeoffTime / total_takeoffs << "(s)" << endl;
	cout << "average fuel saved: " << fixed << setprecision(3) << total_fuel_saved / total_landings << "(units)" << endl;
	cout << "total plane in emergency: " << emergency << endl;
	cout << "total plane crashed: " << crash << endl << endl;
	
	system("PAUSE");
	return 0;
}