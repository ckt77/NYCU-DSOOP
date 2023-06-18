#include<iostream>
using namespace std;

void output(TakeoffQueue& R_queue)
{
	TakeoffQueue* temp = R_queue.next;
	while (temp->id != -1)
	{
		cout << '(' << temp->id << "), ";
		temp = temp->next;
	}
	cout << endl;
}

void output(LandingQueue& R_queue)
{
	LandingQueue* temp = R_queue.next;
	while (temp->id != -1)
	{
		cout << '(' << temp->id << ", " << temp->fuel << "), ";
		temp = temp->next;
	}
	cout << endl;
}

void runwayState(int& R1_id, int& R2_id, int& R3_id, int& R4_id, LandingQueue R2_L1, LandingQueue R3_L1,
	LandingQueue R4_L1, LandingQueue R2_L2, LandingQueue R3_L2, LandingQueue R4_L2, TakeoffQueue R1_T,
	TakeoffQueue R2_T, TakeoffQueue R3_T, TakeoffQueue R4_T)
{
	cout << "Runway1(" << R1_id << ')' << endl;
	cout << "L1:" << endl;
	cout << "L2:" << endl;
	cout << "T: ";
	output(R1_T);
	cout << endl;

	cout << "Runway2(" << R2_id << ')' << endl;
	cout << "L1: ";
	output(R2_L1);
	cout << "L2: ";
	output(R2_L2);
	cout << "T: ";
	output(R2_T);
	cout << endl;

	cout << "Runway3(" << R3_id << ')' << endl;
	cout << "L1: ";
	output(R3_L1);
	cout << "L2: ";
	output(R3_L2);
	cout << "T: ";
	output(R3_T);
	cout << endl;

	cout << "Runway4(" << R4_id << ')' << endl;
	cout << "L1: ";
	output(R4_L1);
	cout << "L2: ";
	output(R4_L2);
	cout << "T: ";
	output(R4_T);
	cout << endl;

	cout << "--------------------------------------------------------------------------------------" << endl;
}