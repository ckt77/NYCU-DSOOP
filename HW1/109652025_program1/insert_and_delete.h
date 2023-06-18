void insertToLandingQueue(LandingQueue& head, int& landing_id, int fuel_rv)
{
	LandingQueue* temp = head.next;
	LandingQueue* new_item = new LandingQueue;
	new_item->id = landing_id;
	new_item->fuel = fuel_rv;
	new_item->waitingTime = 0;
	new_item->next = temp;
	new_item->prev = &head;
	temp->prev = new_item;
	head.next = new_item;
	landing_id += 2;
}

int landing(LandingQueue& head, double& total_landingTime, double& total_fuel_saved, double& total_landings)
{
	LandingQueue* temp = head.prev;
	int R_id = temp->id;
	total_landingTime += temp->waitingTime;
	total_fuel_saved += temp->fuel;
	total_landings++;
	temp->prev->next = &head;
	head.prev = temp->prev;
	return R_id;
}

void insertToTakeoffQueue(TakeoffQueue& head, int& takeoff_id)
{
	TakeoffQueue* temp = head.next;
	TakeoffQueue* new_item = new TakeoffQueue;
	new_item->id = takeoff_id;
	new_item->waitingTime = 0;
	new_item->next = temp;
	new_item->prev = &head;
	temp->prev = new_item;
	head.next = new_item;
	takeoff_id += 2;
}

int takeoff(TakeoffQueue& head, double& total_takeoffTime, double& total_takeoffs)
{
	TakeoffQueue* temp = head.prev;
	int R_id = temp->id;
	total_takeoffTime += temp->waitingTime;
	total_takeoffs++;
	temp->prev->next = &head;
	head.prev = temp->prev;
	return R_id;
}