#include "beepmanager.hpp"
#include <stack>
#include <iostream>
#include <Windows.h>
#undef min
#undef max

BeepManager BeepManager::instance;

BeepManager::BeepManager()
	: sequenceQueue(), keepRunning(true), workerThread(workerThreadFunc, &sequenceQueue, &keepRunning)
{
	std::vector<Note> notes;
	for (int i = 0; i < 5; ++i)
	{
		notes.push_back(Note(264, 500));
		notes.push_back(Note(0, 250));
		notes.push_back(Note(264, 250));
		notes.push_back(Note(0, 250));
		notes.push_back(Note(297, 1000));
		notes.push_back(Note(0, 250));
		notes.push_back(Note(264, 1000));
		notes.push_back(Note(0, 250));
		notes.push_back(Note(352, 1000));
		notes.push_back(Note(0, 250));
		notes.push_back(Note(330, 2000));
		notes.push_back(Note(0, 500));

		notes.push_back(Note(264, 500));
		notes.push_back(Note(0, 250));
		notes.push_back(Note(264, 250));
		notes.push_back(Note(0, 250));
		notes.push_back(Note(297, 1000));
		notes.push_back(Note(0, 250));
		notes.push_back(Note(264, 1000));
		notes.push_back(Note(0, 250));
		notes.push_back(Note(396, 1000));
		notes.push_back(Note(0, 250));
		notes.push_back(Note(352, 2000));
		notes.push_back(Note(0, 500));
	}

	for (size_t i = 0; i < notes.size(); ++i)
		notes[i].duration /= 2;

	Play(notes);
}

BeepManager::~BeepManager()
{
	keepRunning = false;
	workerThread.join();
}

void BeepManager::Play(std::vector<Note> notes)
{
	Sequence sequence(notes);
	sequenceQueue.push(sequence);
}
void BeepManager::Play(Note note)
{
	Sequence sequence;
	sequence.notes.push_back(note);
	sequenceQueue.push(sequence);
}

void BeepManager::workerThreadFunc(SequenceQueue *queue, bool *keepRunning)
{
	std::stack<Sequence> sequenceStack;

	Sequence tempSequence;
	Note tempNote(0, 0);

	while (*keepRunning)
	{
		// start any pending sequences
		while (queue->try_pop(tempSequence))
		{
			tempSequence.startTime = std::chrono::steady_clock::now();
			sequenceStack.push(tempSequence);
		}

		// play the next note in the current sequence
		while (!sequenceStack.empty())
		{
			Sequence &sequence = sequenceStack.top();

			while (*keepRunning && sequence.advance(tempNote)) {
				//std::cout << "Note " << tempNote.frequency << "Hz " << tempNote.duration << "ms\n";
				//if (tempNote.frequency)
					Beep(tempNote.frequency, tempNote.duration);
				//else
				//	std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(tempNote.duration));
			}

			if (sequence.isFinished())
			{
				sequenceStack.pop();
				continue;
			}
		}

		std::this_thread::yield();
	}
	//Beep(beepDescriptor.frequency, beepDescriptor.duration);
}

BeepManager::Sequence::Sequence()
	: noteIndex(0), noteTimeElapsed(0)
{}
BeepManager::Sequence::Sequence(std::vector<Note> notes)
	: notes(notes), noteIndex(0), noteTimeElapsed(0)
{}
long BeepManager::Sequence::getElapsedTime() const
{
	TimePoint now = std::chrono::steady_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();
	return static_cast<long>(elapsed);
}
bool BeepManager::Sequence::isFinished() const
{
	return noteIndex >= notes.size();
}
bool BeepManager::Sequence::advance(Note & note)
{
	if (isFinished())
		return false;

	long elapsed = getElapsedTime();
	if (elapsed < noteTimeElapsed)
		return false; // still playing previous note

	// advance to currently playing note
	long noteEnd = noteTimeElapsed + static_cast<long>(notes[noteIndex].duration);
	while (noteEnd < elapsed && noteIndex < notes.size())
	{
		noteTimeElapsed += notes[noteIndex].duration;
		++noteIndex;
		noteEnd = noteTimeElapsed + static_cast<long>(notes[noteIndex].duration);
	}

	// we might have gone past the end of the sequence
	if (isFinished())
		return false;

	// adjust note duration to end at the right time
	long latency = elapsed - noteTimeElapsed;
	note = notes[noteIndex];
	note.duration = static_cast<unsigned long>(std::max(0l, static_cast<long>(note.duration) - latency));
	return true;
}
