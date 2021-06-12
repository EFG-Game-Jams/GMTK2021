#pragma once
#include "state.hpp"
#include "color.hpp"
#include <string>
#include <vector>
#include <Windows.h>

class MessageState : public State
{
private:
	std::vector<CHAR_INFO> characterBackup;
	COORD const lineStartPosition;
	SHORT const maxLineLength;
	std::string message;
	Color::Color color;

	void RestoreContent();
	void BackupContent();
	void DrawMessage(std::string msg, Color::Color const& color) const;

public:
	bool IsOverlay() const override;

	void Focus() override;
	void Destroy() override;

	MessageState(COORD const _lineStartPosition,
		SHORT const _maxLineLength,
		std::string const & message,
		Color::Color const & color);
};

