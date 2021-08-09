#pragma once
#include "state.hpp"
#include "color.hpp"
#include <string>
#include <vector>
#include <Windows.h>

class MessageOverlay : public State
{
private:
	std::vector<CHAR_INFO> characterBackup;
	COORD const lineStartPosition;
	SHORT const maxLineLength;
	Color::Color color;

	void RestoreContent();
	void BackupContent();
	void DrawMessage(std::string msg, Color::Color const& color) const;

protected:
	std::string message;

public:
	bool IsOverlay() const override;

	void Focus() override;
	void Destroy() override;

	MessageOverlay(COORD const _lineStartPosition,
		SHORT const _maxLineLength,
		std::string const & message,
		Color::Color const & color);
};

