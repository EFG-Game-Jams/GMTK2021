#pragma once
#include "messagetype.hpp"
#include <chrono>

struct Message
{
private:
	std::chrono::steady_clock::time_point creationTime;
	MessageType type;
	unsigned payload;

public:
	unsigned GetPayload() const;
	std::chrono::steady_clock::time_point GetCreationTime() const;
	MessageType GetType() const;

	Message(MessageType const type, unsigned const payload);
	virtual ~Message() = default;
};