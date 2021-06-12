#pragma once
#include "gamestate.hpp"
#include "color.hpp"
#include <string>
#include <vector>
#include <Windows.h>

class MessageState : public GameState
{
private:
	std::vector<CHAR_INFO> characterBackup;
	COORD const lineStartPosition;
	SHORT const maxLineLength;

	void RestoreContent();
	void BackupContent();
	void DrawMessage(std::string msg, Color::Color const& color) const;

public:
	void Awake() override;

	MessageState(COORD const _lineStartPosition,
		SHORT const _maxLineLength,
		std::string const & message,
		Color::Color const & color);
	~MessageState();
};

