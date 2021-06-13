#include "message.hpp"

unsigned Message::GetPayload() const
{
	return payload;
}

std::chrono::steady_clock::time_point Message::GetCreationTime() const
{
	return creationTime;
}

MessageType Message::GetType() const
{
	return type;
}

Message::Message(MessageType const _type, unsigned const _payload)
	: creationTime(std::chrono::steady_clock::now()),
	type(_type),
	payload(_payload)
{
}
