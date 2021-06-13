#pragma once
#include <vector>
#include <memory>
#include "message.hpp"

namespace MessageBuffer
{
	void RemoveStaleMessages(long long const maximumAgeInMilliseconds);

	void Publish(MessageType const type, unsigned const payload = 0);
	void Publish(std::shared_ptr<Message> message);

	std::vector<std::shared_ptr<Message>> Consume(
		std::chrono::steady_clock::time_point const after,
		MessageType const ofType = MessageType::All);
}

