void landingQueue_after(LandingQueue& head)
{
	LandingQueue* current = head.next;
	while (current->id != -1)
	{
		current->waitingTime += 1;
		current->fuel -= 1;
		current = current->next;
	}
}

void takeoffQueue_after(TakeoffQueue& head)
{
	TakeoffQueue* current = head.next;
	while (current->id != -1)
	{
		current->waitingTime += 1;
		current = current->next;
	}
}