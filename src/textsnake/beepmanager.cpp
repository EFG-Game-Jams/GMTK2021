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
	/*
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

	for (size_t i = 0; i < notes.size(); ++i)
		notes[i].duration /= 2;
	/*/
	notes.push_back(Note(233, 247)); notes.push_back(Note(261, 250)); notes.push_back(Note(277, 125)); notes.push_back(Note(0, 127)); notes.push_back(Note(277, 247)); notes.push_back(Note(311, 250)); notes.push_back(Note(261, 375)); notes.push_back(Note(233, 131)); notes.push_back(Note(207, 1071)); notes.push_back(Note(0, 928)); notes.push_back(Note(233, 140)); notes.push_back(Note(0, 109)); notes.push_back(Note(233, 207)); notes.push_back(Note(261, 327)); notes.push_back(Note(277, 259)); notes.push_back(Note(233, 273)); notes.push_back(Note(0, 226)); notes.push_back(Note(207, 276)); notes.push_back(Note(415, 211)); notes.push_back(Note(0, 288)); notes.push_back(Note(415, 247)); notes.push_back(Note(311, 919)); notes.push_back(Note(0, 582)); notes.push_back(Note(233, 170)); notes.push_back(Note(233, 301)); notes.push_back(Note(261, 256)); notes.push_back(Note(277, 198)); notes.push_back(Note(233, 337)); notes.push_back(Note(277, 300)); notes.push_back(Note(311, 206)); notes.push_back(Note(0, 293)); notes.push_back(Note(261, 182)); notes.push_back(Note(233, 175)); notes.push_back(Note(0, 142)); notes.push_back(Note(233, 248)); notes.push_back(Note(207, 759)); notes.push_back(Note(0, 491)); notes.push_back(Note(233, 135)); notes.push_back(Note(0, 114)); notes.push_back(Note(233, 244)); notes.push_back(Note(261, 265)); notes.push_back(Note(277, 191)); notes.push_back(Note(233, 218)); notes.push_back(Note(207, 255)); notes.push_back(Note(207, 207)); notes.push_back(Note(0, 127)); notes.push_back(Note(311, 170)); notes.push_back(Note(311, 225)); notes.push_back(Note(0, 104)); notes.push_back(Note(311, 240)); notes.push_back(Note(349, 252)); notes.push_back(Note(311, 720)); notes.push_back(Note(0, 286)); notes.push_back(Note(277, 1197)); notes.push_back(Note(311, 321)); notes.push_back(Note(349, 271)); notes.push_back(Note(277, 285)); notes.push_back(Note(311, 160)); notes.push_back(Note(311, 251)); notes.push_back(Note(311, 313)); notes.push_back(Note(349, 305)); notes.push_back(Note(311, 247)); notes.push_back(Note(207, 203)); notes.push_back(Note(207, 631)); notes.push_back(Note(0, 917)); notes.push_back(Note(233, 239)); notes.push_back(Note(261, 308)); notes.push_back(Note(277, 268)); notes.push_back(Note(233, 187)); notes.push_back(Note(0, 312)); notes.push_back(Note(311, 271)); notes.push_back(Note(349, 225)); notes.push_back(Note(311, 580)); notes.push_back(Note(0, 194)); notes.push_back(Note(207, 135)); notes.push_back(Note(233, 143)); notes.push_back(Note(277, 139)); notes.push_back(Note(233, 133)); notes.push_back(Note(349, 207)); notes.push_back(Note(0, 167)); notes.push_back(Note(349, 347)); notes.push_back(Note(311, 698)); notes.push_back(Note(207, 219)); notes.push_back(Note(233, 115)); notes.push_back(Note(261, 173)); notes.push_back(Note(233, 109)); notes.push_back(Note(311, 244)); notes.push_back(Note(0, 145)); notes.push_back(Note(311, 433)); notes.push_back(Note(277, 359)); notes.push_back(Note(261, 135)); notes.push_back(Note(233, 264)); notes.push_back(Note(207, 131)); notes.push_back(Note(233, 117)); notes.push_back(Note(277, 167)); notes.push_back(Note(233, 113)); notes.push_back(Note(277, 536)); notes.push_back(Note(311, 238)); notes.push_back(Note(261, 267)); notes.push_back(Note(233, 244)); notes.push_back(Note(207, 253)); notes.push_back(Note(0, 252)); notes.push_back(Note(207, 256)); notes.push_back(Note(311, 497)); notes.push_back(Note(277, 804)); notes.push_back(Note(0, 197)); notes.push_back(Note(207, 135)); notes.push_back(Note(233, 143)); notes.push_back(Note(277, 139)); notes.push_back(Note(233, 133)); notes.push_back(Note(349, 207)); notes.push_back(Note(0, 167)); notes.push_back(Note(349, 347)); notes.push_back(Note(311, 698)); notes.push_back(Note(207, 219)); notes.push_back(Note(233, 115)); notes.push_back(Note(261, 173)); notes.push_back(Note(233, 109)); notes.push_back(Note(415, 513)); notes.push_back(Note(261, 250)); notes.push_back(Note(277, 361)); notes.push_back(Note(261, 135)); notes.push_back(Note(233, 264)); notes.push_back(Note(207, 131)); notes.push_back(Note(233, 117)); notes.push_back(Note(277, 167)); notes.push_back(Note(233, 113)); notes.push_back(Note(277, 536)); notes.push_back(Note(311, 238)); notes.push_back(Note(261, 384)); notes.push_back(Note(233, 125)); notes.push_back(Note(207, 250)); notes.push_back(Note(0, 252)); notes.push_back(Note(207, 256)); notes.push_back(Note(311, 247)); notes.push_back(Note(277, 125)); notes.push_back(Note(0, 127)); notes.push_back(Note(277, 802)); notes.push_back(Note(0, 947)); notes.push_back(Note(277, 128)); notes.push_back(Note(0, 121)); notes.push_back(Note(277, 247)); notes.push_back(Note(233, 128)); notes.push_back(Note(0, 123)); notes.push_back(Note(277, 287)); notes.push_back(Note(311, 468)); notes.push_back(Note(0, 531)); notes.push_back(Note(261, 245)); notes.push_back(Note(233, 90)); notes.push_back(Note(0, 163)); notes.push_back(Note(233, 268)); notes.push_back(Note(207, 997)); notes.push_back(Note(0, 252)); notes.push_back(Note(233, 160)); notes.push_back(Note(233, 322)); notes.push_back(Note(261, 302)); notes.push_back(Note(277, 261)); notes.push_back(Note(233, 258)); notes.push_back(Note(207, 268)); notes.push_back(Note(0, 481)); notes.push_back(Note(415, 109)); notes.push_back(Note(0, 140)); notes.push_back(Note(415, 221)); notes.push_back(Note(311, 536)); notes.push_back(Note(349, 268)); notes.push_back(Note(311, 251)); notes.push_back(Note(277, 191)); notes.push_back(Note(0, 308)); notes.push_back(Note(277, 170)); notes.push_back(Note(277, 301)); notes.push_back(Note(233, 256)); notes.push_back(Note(277, 198)); notes.push_back(Note(233, 337)); notes.push_back(Note(277, 300)); notes.push_back(Note(311, 206)); notes.push_back(Note(0, 293)); notes.push_back(Note(261, 182)); notes.push_back(Note(233, 175)); notes.push_back(Note(0, 142)); notes.push_back(Note(233, 248)); notes.push_back(Note(207, 759)); notes.push_back(Note(0, 491)); notes.push_back(Note(233, 135)); notes.push_back(Note(0, 114)); notes.push_back(Note(233, 244)); notes.push_back(Note(261, 265)); notes.push_back(Note(277, 191)); notes.push_back(Note(233, 218)); notes.push_back(Note(207, 255)); notes.push_back(Note(0, 584)); notes.push_back(Note(311, 248)); notes.push_back(Note(349, 125)); notes.push_back(Note(0, 126)); notes.push_back(Note(349, 541)); notes.push_back(Note(311, 602)); notes.push_back(Note(0, 147)); notes.push_back(Note(277, 1197)); notes.push_back(Note(311, 321)); notes.push_back(Note(349, 271)); notes.push_back(Note(311, 372)); notes.push_back(Note(0, 127)); notes.push_back(Note(311, 161)); notes.push_back(Note(311, 313)); notes.push_back(Note(349, 305)); notes.push_back(Note(311, 247)); notes.push_back(Note(207, 203)); notes.push_back(Note(207, 631)); notes.push_back(Note(0, 667)); notes.push_back(Note(207, 247)); notes.push_back(Note(233, 241)); notes.push_back(Note(261, 308)); notes.push_back(Note(277, 268)); notes.push_back(Note(233, 187)); notes.push_back(Note(0, 312)); notes.push_back(Note(311, 271)); notes.push_back(Note(349, 225)); notes.push_back(Note(311, 580)); notes.push_back(Note(0, 194)); notes.push_back(Note(207, 135)); notes.push_back(Note(233, 143)); notes.push_back(Note(277, 139)); notes.push_back(Note(233, 133)); notes.push_back(Note(349, 207)); notes.push_back(Note(0, 167)); notes.push_back(Note(349, 347)); notes.push_back(Note(311, 698)); notes.push_back(Note(207, 219)); notes.push_back(Note(233, 115)); notes.push_back(Note(261, 173)); notes.push_back(Note(233, 109)); notes.push_back(Note(311, 244)); notes.push_back(Note(0, 145)); notes.push_back(Note(311, 433)); notes.push_back(Note(277, 359)); notes.push_back(Note(261, 135)); notes.push_back(Note(233, 264)); notes.push_back(Note(207, 131)); notes.push_back(Note(233, 117)); notes.push_back(Note(277, 167)); notes.push_back(Note(233, 113)); notes.push_back(Note(277, 536)); notes.push_back(Note(311, 238)); notes.push_back(Note(261, 267)); notes.push_back(Note(233, 244)); notes.push_back(Note(207, 253)); notes.push_back(Note(0, 252)); notes.push_back(Note(207, 256)); notes.push_back(Note(311, 497)); notes.push_back(Note(277, 804)); notes.push_back(Note(0, 197)); notes.push_back(Note(207, 135)); notes.push_back(Note(233, 143)); notes.push_back(Note(277, 139)); notes.push_back(Note(233, 133)); notes.push_back(Note(349, 207)); notes.push_back(Note(0, 167)); notes.push_back(Note(349, 347)); notes.push_back(Note(311, 698)); notes.push_back(Note(207, 219)); notes.push_back(Note(233, 115)); notes.push_back(Note(261, 173)); notes.push_back(Note(233, 109)); notes.push_back(Note(415, 513)); notes.push_back(Note(261, 250)); notes.push_back(Note(277, 361)); notes.push_back(Note(261, 135)); notes.push_back(Note(233, 264)); notes.push_back(Note(207, 131)); notes.push_back(Note(233, 117)); notes.push_back(Note(277, 167)); notes.push_back(Note(233, 113)); notes.push_back(Note(277, 536)); notes.push_back(Note(311, 238)); notes.push_back(Note(261, 384)); notes.push_back(Note(233, 125)); notes.push_back(Note(207, 250)); notes.push_back(Note(0, 252)); notes.push_back(Note(207, 256)); notes.push_back(Note(311, 247)); notes.push_back(Note(277, 125)); notes.push_back(Note(0, 127)); notes.push_back(Note(277, 802)); notes.push_back(Note(0, 197)); notes.push_back(Note(207, 135)); notes.push_back(Note(233, 143)); notes.push_back(Note(277, 139)); notes.push_back(Note(233, 133)); notes.push_back(Note(349, 207)); notes.push_back(Note(0, 167)); notes.push_back(Note(349, 347)); notes.push_back(Note(311, 698)); notes.push_back(Note(207, 219)); notes.push_back(Note(233, 115)); notes.push_back(Note(261, 173)); notes.push_back(Note(233, 109)); notes.push_back(Note(311, 244)); notes.push_back(Note(0, 145)); notes.push_back(Note(311, 433)); notes.push_back(Note(277, 359)); notes.push_back(Note(261, 135)); notes.push_back(Note(233, 264)); notes.push_back(Note(207, 131)); notes.push_back(Note(233, 117)); notes.push_back(Note(277, 167)); notes.push_back(Note(233, 113)); notes.push_back(Note(277, 536)); notes.push_back(Note(311, 238)); notes.push_back(Note(261, 267)); notes.push_back(Note(233, 244)); notes.push_back(Note(207, 253)); notes.push_back(Note(0, 252)); notes.push_back(Note(207, 256)); notes.push_back(Note(311, 497)); notes.push_back(Note(277, 804)); notes.push_back(Note(0, 197)); notes.push_back(Note(207, 135)); notes.push_back(Note(233, 143)); notes.push_back(Note(277, 139)); notes.push_back(Note(233, 133)); notes.push_back(Note(349, 207)); notes.push_back(Note(0, 167)); notes.push_back(Note(349, 347)); notes.push_back(Note(311, 698)); notes.push_back(Note(207, 219)); notes.push_back(Note(233, 115)); notes.push_back(Note(261, 173)); notes.push_back(Note(233, 109)); notes.push_back(Note(415, 513)); notes.push_back(Note(261, 250)); notes.push_back(Note(277, 361)); notes.push_back(Note(261, 135)); notes.push_back(Note(233, 264)); notes.push_back(Note(207, 131)); notes.push_back(Note(233, 117)); notes.push_back(Note(277, 167)); notes.push_back(Note(233, 113)); notes.push_back(Note(277, 536)); notes.push_back(Note(311, 238)); notes.push_back(Note(261, 384)); notes.push_back(Note(233, 125)); notes.push_back(Note(207, 250)); notes.push_back(Note(0, 252)); notes.push_back(Note(207, 256)); notes.push_back(Note(311, 247)); notes.push_back(Note(277, 125)); notes.push_back(Note(0, 127)); notes.push_back(Note(277, 802)); notes.push_back(Note(0, 2697)); notes.push_back(Note(349, 198)); notes.push_back(Note(0, 176)); notes.push_back(Note(349, 357)); notes.push_back(Note(311, 286)); notes.push_back(Note(0, 2981)); notes.push_back(Note(349, 198)); notes.push_back(Note(0, 176)); notes.push_back(Note(349, 357)); notes.push_back(Note(311, 286)); notes.push_back(Note(0, 1231)); notes.push_back(Note(207, 120)); notes.push_back(Note(233, 111)); notes.push_back(Note(277, 143)); notes.push_back(Note(233, 128)); notes.push_back(Note(349, 170)); notes.push_back(Note(207, 191)); notes.push_back(Note(233, 116)); notes.push_back(Note(277, 154)); notes.push_back(Note(233, 146)); notes.push_back(Note(349, 264)); notes.push_back(Note(0, 235)); notes.push_back(Note(349, 198)); notes.push_back(Note(0, 176)); notes.push_back(Note(349, 357)); notes.push_back(Note(311, 286)); notes.push_back(Note(0, 1231)); notes.push_back(Note(207, 120)); notes.push_back(Note(233, 111)); notes.push_back(Note(277, 143)); notes.push_back(Note(233, 128)); notes.push_back(Note(349, 170)); notes.push_back(Note(207, 191)); notes.push_back(Note(233, 116)); notes.push_back(Note(277, 154)); notes.push_back(Note(233, 146)); notes.push_back(Note(349, 264)); notes.push_back(Note(0, 235)); notes.push_back(Note(349, 198)); notes.push_back(Note(0, 176)); notes.push_back(Note(349, 357)); notes.push_back(Note(311, 286)); notes.push_back(Note(0, 1231)); notes.push_back(Note(277, 128)); notes.push_back(Note(0, 121)); notes.push_back(Note(277, 247)); notes.push_back(Note(233, 128)); notes.push_back(Note(0, 123)); notes.push_back(Note(277, 287)); notes.push_back(Note(311, 468)); notes.push_back(Note(0, 531)); notes.push_back(Note(261, 245)); notes.push_back(Note(233, 90)); notes.push_back(Note(0, 163)); notes.push_back(Note(233, 268)); notes.push_back(Note(207, 997)); notes.push_back(Note(0, 252)); notes.push_back(Note(233, 160)); notes.push_back(Note(233, 322)); notes.push_back(Note(261, 302)); notes.push_back(Note(277, 261)); notes.push_back(Note(233, 258)); notes.push_back(Note(207, 268)); notes.push_back(Note(0, 481)); notes.push_back(Note(415, 109)); notes.push_back(Note(0, 140)); notes.push_back(Note(415, 221)); notes.push_back(Note(311, 536)); notes.push_back(Note(349, 268)); notes.push_back(Note(311, 251)); notes.push_back(Note(277, 191)); notes.push_back(Note(0, 308)); notes.push_back(Note(277, 170)); notes.push_back(Note(277, 301)); notes.push_back(Note(233, 256)); notes.push_back(Note(277, 198)); notes.push_back(Note(233, 337)); notes.push_back(Note(277, 300)); notes.push_back(Note(311, 206)); notes.push_back(Note(0, 293)); notes.push_back(Note(261, 182)); notes.push_back(Note(233, 175)); notes.push_back(Note(0, 142)); notes.push_back(Note(233, 248)); notes.push_back(Note(207, 759)); notes.push_back(Note(0, 491)); notes.push_back(Note(233, 135)); notes.push_back(Note(0, 114)); notes.push_back(Note(233, 244)); notes.push_back(Note(261, 265)); notes.push_back(Note(277, 191)); notes.push_back(Note(233, 218)); notes.push_back(Note(207, 255)); notes.push_back(Note(0, 584)); notes.push_back(Note(311, 248)); notes.push_back(Note(349, 125)); notes.push_back(Note(0, 126)); notes.push_back(Note(349, 541)); notes.push_back(Note(311, 602)); notes.push_back(Note(0, 147)); notes.push_back(Note(277, 1197)); notes.push_back(Note(311, 321)); notes.push_back(Note(349, 271)); notes.push_back(Note(277, 285)); notes.push_back(Note(311, 160)); notes.push_back(Note(311, 251)); notes.push_back(Note(311, 313)); notes.push_back(Note(349, 305)); notes.push_back(Note(311, 247)); notes.push_back(Note(207, 203)); notes.push_back(Note(207, 631)); notes.push_back(Note(0, 917)); notes.push_back(Note(233, 239)); notes.push_back(Note(261, 308)); notes.push_back(Note(277, 268)); notes.push_back(Note(233, 187)); notes.push_back(Note(0, 312)); notes.push_back(Note(311, 271)); notes.push_back(Note(349, 225)); notes.push_back(Note(311, 580)); notes.push_back(Note(0, 194)); notes.push_back(Note(207, 135)); notes.push_back(Note(233, 143)); notes.push_back(Note(277, 139)); notes.push_back(Note(233, 133)); notes.push_back(Note(349, 207)); notes.push_back(Note(0, 167)); notes.push_back(Note(349, 347)); notes.push_back(Note(311, 698)); notes.push_back(Note(207, 219)); notes.push_back(Note(233, 115)); notes.push_back(Note(261, 173)); notes.push_back(Note(233, 109)); notes.push_back(Note(311, 244)); notes.push_back(Note(0, 145)); notes.push_back(Note(311, 433)); notes.push_back(Note(277, 359)); notes.push_back(Note(261, 135)); notes.push_back(Note(233, 264)); notes.push_back(Note(207, 131)); notes.push_back(Note(233, 117)); notes.push_back(Note(277, 167)); notes.push_back(Note(233, 113)); notes.push_back(Note(277, 536)); notes.push_back(Note(311, 238)); notes.push_back(Note(261, 267)); notes.push_back(Note(233, 244)); notes.push_back(Note(207, 253)); notes.push_back(Note(0, 252)); notes.push_back(Note(207, 256)); notes.push_back(Note(311, 497)); notes.push_back(Note(277, 804)); notes.push_back(Note(0, 197)); notes.push_back(Note(207, 135)); notes.push_back(Note(233, 143)); notes.push_back(Note(277, 139)); notes.push_back(Note(233, 133)); notes.push_back(Note(349, 207)); notes.push_back(Note(0, 167)); notes.push_back(Note(349, 347)); notes.push_back(Note(311, 698)); notes.push_back(Note(207, 219)); notes.push_back(Note(233, 115)); notes.push_back(Note(261, 173)); notes.push_back(Note(233, 109)); notes.push_back(Note(415, 513)); notes.push_back(Note(261, 250)); notes.push_back(Note(277, 361)); notes.push_back(Note(261, 135)); notes.push_back(Note(233, 264)); notes.push_back(Note(207, 131)); notes.push_back(Note(233, 117)); notes.push_back(Note(277, 167)); notes.push_back(Note(233, 113)); notes.push_back(Note(277, 536)); notes.push_back(Note(311, 238)); notes.push_back(Note(261, 384)); notes.push_back(Note(233, 125)); notes.push_back(Note(207, 250)); notes.push_back(Note(0, 252)); notes.push_back(Note(207, 256)); notes.push_back(Note(311, 247)); notes.push_back(Note(277, 125)); notes.push_back(Note(0, 127)); notes.push_back(Note(277, 802)); notes.push_back(Note(0, 197)); notes.push_back(Note(207, 135)); notes.push_back(Note(233, 143)); notes.push_back(Note(277, 139)); notes.push_back(Note(233, 133)); notes.push_back(Note(349, 207)); notes.push_back(Note(0, 167)); notes.push_back(Note(349, 347)); notes.push_back(Note(311, 698)); notes.push_back(Note(207, 219)); notes.push_back(Note(233, 115)); notes.push_back(Note(261, 173)); notes.push_back(Note(233, 109)); notes.push_back(Note(311, 244)); notes.push_back(Note(0, 145)); notes.push_back(Note(311, 433)); notes.push_back(Note(277, 359)); notes.push_back(Note(261, 135)); notes.push_back(Note(233, 264)); notes.push_back(Note(207, 131)); notes.push_back(Note(233, 117)); notes.push_back(Note(277, 167)); notes.push_back(Note(233, 113)); notes.push_back(Note(277, 536)); notes.push_back(Note(311, 238)); notes.push_back(Note(261, 267)); notes.push_back(Note(233, 244)); notes.push_back(Note(207, 253)); notes.push_back(Note(0, 252)); notes.push_back(Note(207, 256)); notes.push_back(Note(311, 497)); notes.push_back(Note(277, 804)); notes.push_back(Note(0, 197)); notes.push_back(Note(207, 135)); notes.push_back(Note(233, 143)); notes.push_back(Note(277, 139)); notes.push_back(Note(233, 133)); notes.push_back(Note(349, 207)); notes.push_back(Note(0, 167)); notes.push_back(Note(349, 347)); notes.push_back(Note(311, 698)); notes.push_back(Note(207, 219)); notes.push_back(Note(233, 115)); notes.push_back(Note(261, 173)); notes.push_back(Note(233, 109)); notes.push_back(Note(415, 513)); notes.push_back(Note(261, 250)); notes.push_back(Note(277, 361)); notes.push_back(Note(261, 135)); notes.push_back(Note(233, 264)); notes.push_back(Note(207, 131)); notes.push_back(Note(233, 117)); notes.push_back(Note(277, 167)); notes.push_back(Note(233, 113)); notes.push_back(Note(277, 536)); notes.push_back(Note(311, 238)); notes.push_back(Note(261, 384)); notes.push_back(Note(233, 125)); notes.push_back(Note(207, 250)); notes.push_back(Note(0, 252)); notes.push_back(Note(207, 256)); notes.push_back(Note(311, 247)); notes.push_back(Note(277, 125)); notes.push_back(Note(0, 127)); notes.push_back(Note(277, 802)); notes.push_back(Note(0, 197)); notes.push_back(Note(207, 135)); notes.push_back(Note(233, 143)); notes.push_back(Note(277, 139)); notes.push_back(Note(233, 133)); notes.push_back(Note(349, 207)); notes.push_back(Note(0, 167)); notes.push_back(Note(349, 347)); notes.push_back(Note(311, 698)); notes.push_back(Note(207, 219)); notes.push_back(Note(233, 115)); notes.push_back(Note(261, 173)); notes.push_back(Note(233, 109)); notes.push_back(Note(311, 244)); notes.push_back(Note(0, 145)); notes.push_back(Note(311, 433)); notes.push_back(Note(277, 359)); notes.push_back(Note(261, 135)); notes.push_back(Note(233, 264)); notes.push_back(Note(207, 131)); notes.push_back(Note(233, 117)); notes.push_back(Note(277, 167)); notes.push_back(Note(233, 113)); notes.push_back(Note(277, 536)); notes.push_back(Note(311, 238)); notes.push_back(Note(261, 267)); notes.push_back(Note(233, 244)); notes.push_back(Note(207, 253)); notes.push_back(Note(0, 252)); notes.push_back(Note(207, 256)); notes.push_back(Note(311, 497)); notes.push_back(Note(277, 804)); notes.push_back(Note(0, 197)); notes.push_back(Note(207, 135)); notes.push_back(Note(233, 143)); notes.push_back(Note(277, 139)); notes.push_back(Note(233, 133)); notes.push_back(Note(349, 207)); notes.push_back(Note(0, 167)); notes.push_back(Note(349, 347)); notes.push_back(Note(311, 698)); notes.push_back(Note(207, 219)); notes.push_back(Note(233, 115)); notes.push_back(Note(261, 173)); notes.push_back(Note(233, 109)); notes.push_back(Note(415, 513)); notes.push_back(Note(261, 250)); notes.push_back(Note(277, 361)); notes.push_back(Note(261, 135)); notes.push_back(Note(233, 264)); notes.push_back(Note(207, 131)); notes.push_back(Note(233, 117)); notes.push_back(Note(277, 167)); notes.push_back(Note(233, 113)); notes.push_back(Note(277, 536)); notes.push_back(Note(311, 238)); notes.push_back(Note(261, 384)); notes.push_back(Note(233, 125)); notes.push_back(Note(207, 250)); notes.push_back(Note(0, 252)); notes.push_back(Note(207, 256)); notes.push_back(Note(311, 247)); notes.push_back(Note(277, 125)); notes.push_back(Note(0, 127)); notes.push_back(Note(277, 802));
	//*/
	
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
	return; // BE QUIET!
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
	while (noteEnd < elapsed && noteIndex < notes.size() - 1)
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
