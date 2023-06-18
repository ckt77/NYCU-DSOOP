class LandingQueue
{
public:
	LandingQueue();
	int id;
	int fuel;
	int waitingTime;
	class LandingQueue* next;
	class LandingQueue* prev;
};
LandingQueue::LandingQueue() :id(-1), fuel(0), waitingTime(0), next(this), prev(this) {}

class TakeoffQueue
{
public:
	TakeoffQueue();
	int id;
	int waitingTime;
	class TakeoffQueue* next;
	class TakeoffQueue* prev;
};
TakeoffQueue::TakeoffQueue() : id(-1), waitingTime(0), next(this), prev(this) {}