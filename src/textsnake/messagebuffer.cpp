#include "messagebuffer.hpp"

std::vector<std::shared_ptr<Message>> buffer;

void MessageBuffer::RemoveStaleMessages(long long const maximumAgeInMilliseconds)
{
	std::vector<std::shared_ptr<Message>> filteredBuffer;
	auto const now = std::chrono::steady_clock::now();
	for (auto& message : buffer)
	{
		auto const ageInMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - message->GetCreationTime()).count();
		if (ageInMs <= maximumAgeInMilliseconds)
		{
			filteredBuffer.push_back(message);
		}
	}

	std::swap(buffer, filteredBuffer);
}

void MessageBuffer::Publish(MessageType const type, unsigned const payload)
{
	Publish(std::make_shared<Message>(type, payload));
}

void MessageBuffer::Publish(std::shared_ptr<Message> message)
{
	buffer.push_back(message);
}

std::vector<std::shared_ptr<Message>> MessageBuffer::Consume(
	std::chrono::steady_clock::time_point const after,
	MessageType const ofType)
{
	std::vector<std::shared_ptr<Message>> filteredBuffer;
	for (auto& message : buffer)
	{
		if (message->GetCreationTime() > after &&
			(ofType == MessageType::All || message->GetType() == ofType))
		{
			filteredBuffer.push_back(message);
		}
	}

	return filteredBuffer;
}
