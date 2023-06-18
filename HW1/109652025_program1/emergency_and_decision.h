void emergency_landing(int& R_id, int emergency_id, int emergency_waitingTime, double& total_landingTime, double& total_landings)
{
	R_id = emergency_id;
	total_landingTime += emergency_waitingTime;
	total_landings += 1;
}

void landOrTakeoff(bool name, double sizeOfTakeoffQueue[], double sizeOfLandingQueue[], int runway_n, int& R_id,
	double& total_takeoffTime, double& total_landingTime, double& total_fuel_saved, TakeoffQueue& R_T, LandingQueue& R_L1,
	LandingQueue& R_L2, double& total_takeoffs, double& total_landings, double total_fuel[])
{
	if (name == false)
	{
		if (runway_n != 0)
		{
			if ((sizeOfLandingQueue[runway_n + 2] + sizeOfLandingQueue[runway_n - 1]) > 0 &&
				((total_fuel[runway_n + 2] + total_fuel[runway_n - 1]) /
					(sizeOfLandingQueue[runway_n + 2] + sizeOfLandingQueue[runway_n - 1])) < 5)
			{
				if (total_fuel[runway_n + 2] == 0)
				{
					R_id = R_L1.prev->id;
					landing(R_L1, total_landingTime, total_fuel_saved, total_landings);
					sizeOfLandingQueue[runway_n - 1]--;
				}

				else if (total_fuel[runway_n - 1] == 0)
				{
					R_id = R_L2.prev->id;
					landing(R_L2, total_landingTime, total_fuel_saved, total_landings);
					sizeOfLandingQueue[runway_n + 2]--;
				}

				else if (total_fuel[runway_n + 2] / sizeOfLandingQueue[runway_n + 2] <=
					total_fuel[runway_n - 1] / sizeOfLandingQueue[runway_n - 1])
				{
					R_id = R_L2.prev->id;
					landing(R_L2, total_landingTime, total_fuel_saved, total_landings);
					sizeOfLandingQueue[runway_n + 2]--;
				}

				else
				{
					R_id = R_L1.prev->id;
					landing(R_L1, total_landingTime, total_fuel_saved, total_landings);
					sizeOfLandingQueue[runway_n - 1]--;
				}
			}

			else if (sizeOfTakeoffQueue[runway_n] > 0)
			{
				R_id = R_T.prev->id;
				takeoff(R_T, total_takeoffTime, total_takeoffs);
				sizeOfTakeoffQueue[runway_n]--;
			}

			else if ((sizeOfLandingQueue[runway_n + 2] + sizeOfLandingQueue[runway_n - 1]) > 0)
			{
				if (total_fuel[runway_n + 2] == 0)
				{
					R_id = R_L1.prev->id;
					landing(R_L1, total_landingTime, total_fuel_saved, total_landings);
					sizeOfLandingQueue[runway_n - 1]--;
				}

				else if (total_fuel[runway_n - 1] == 0)
				{
					R_id = R_L2.prev->id;
					landing(R_L2, total_landingTime, total_fuel_saved, total_landings);
					sizeOfLandingQueue[runway_n + 2]--;
				}

				else if (total_fuel[runway_n + 2] / sizeOfLandingQueue[runway_n + 2] <=
					total_fuel[runway_n - 1] / sizeOfLandingQueue[runway_n - 1])
				{
					R_id = R_L2.prev->id;
					landing(R_L2, total_landingTime, total_fuel_saved, total_landings);
					sizeOfLandingQueue[runway_n + 2]--;
				}

				else
				{
					R_id = R_L1.prev->id;
					landing(R_L1, total_landingTime, total_fuel_saved, total_landings);
					sizeOfLandingQueue[runway_n - 1]--;
				}
			}
		}

		else
		{
			if (sizeOfTakeoffQueue[runway_n] > 0)
			{
				R_id = R_T.prev->id;
				takeoff(R_T, total_takeoffTime, total_takeoffs);
				sizeOfTakeoffQueue[runway_n]--;
			}
		}
	}
}