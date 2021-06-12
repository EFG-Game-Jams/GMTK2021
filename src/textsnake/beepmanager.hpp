#pragma once

#include <vector>
#include <thread>
#include <concurrent_queue.h>

class BeepManager
{
public:
	static BeepManager instance;

	BeepManager();
	~BeepManager();

	struct Note
	{
		unsigned long frequency;
		unsigned long duration;

		Note(unsigned long frequency, unsigned long duration)
			: frequency(frequency), duration(duration)
		{}
	};

	void Play(std::vector<Note> notes);
	void Play(Note note);

private:
	typedef std::chrono::steady_clock::time_point TimePoint;
	struct Sequence
	{
		std::vector<Note> notes;
		size_t noteIndex;
		long noteTimeElapsed;
		TimePoint startTime;

		Sequence();
		Sequence(std::vector<Note> notes);

		long getElapsedTime() const;
		bool isFinished() const;
		bool advance(Note& note);
	};

	typedef concurrency::concurrent_queue<Sequence> SequenceQueue;
	SequenceQueue sequenceQueue;

	bool keepRunning;
	std::thread workerThread;

	static void workerThreadFunc(SequenceQueue *queue, bool *keepRunning);
};