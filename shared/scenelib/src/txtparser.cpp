#include "txtparser.hpp"

#include <mutils/stringutils.hpp>

#include <string>
#include <fstream>

namespace scenelib
{
	unsigned int lineNb = 0;
	const std::string scene("----");
	const char sceneName('@');
	const char choice('*');
	const char goTo('>');


	void logError(const std::string& error)
	{
		throw new std::exception(std::string(
			"Line " + std::to_string(lineNb) + " : " + error
		).data());
	}

	void logUnexpected(const std::string& expectedSymbol, const std::string& line)
	{
		logError("Expected " + expectedSymbol + " symbol, got : " + line);
	}

	void readOneLine(std::ifstream& stream, std::string& line)
	{
		std::string tmp;
		if (std::getline(stream, line))
		{
			line = mutils::trimmed(line);
			++lineNb;
		}
	}

	//! Consumes all empty lines, and return whenever the stream is done or the line isn't empty
	void consumeEmptyLines(std::ifstream& stream, std::string& line)
	{
		readOneLine(stream, line);
		++lineNb;
		while (line.empty())
		{
			readOneLine(stream, line);
		}
	}

	bool isSceneBeginning(const std::string& line)
	{
		//QRegularExpression reSymbol("^/[BE][ACDEMPS]$");
		//return reSymbol.match(line).hasMatch();

		return (line.compare(scene) == 0);
	}

	bool isSymbol(char c)
	{
		return (sceneName == c)
			|| (choice == c)
			|| (goTo == c);
	}

	TxtParser::TxtParser()
	{

	}

	bool loadScene(std::ifstream& stream, Scene& s)
	{
		std::string line;
		readOneLine(stream, line);
		if ((line.size() < 2) || (line[0] != sceneName))
		{
			logError("Expected scene name, got : " + line);
			return false;
		}
		s.name = std::string(line.begin() + 1, line.end());

		consumeEmptyLines(stream, line);

		bool isChoice = false;
		while (!isChoice)
		{
			if (line.empty())
			{
				s.text += "\n";
			}
			else if (line[0] == choice)
			{
				isChoice = true;
			}
			else if (isSymbol(line[0]))
			{
				logError("Expected scene description or choice, got : " + line);
				return false;
			}
			else
			{
				s.text += line + "\n";
			}
		}

		// Choices
		Choice c;
		while (isChoice)
		{
			c.text = mutils::trimmed(std::string(line.begin() + 1, line.end()));
			readOneLine(stream, line);
			if ((line.size() < 2) || (line[0] != goTo))
			{
				logError("Expected goto, got : " + line);
				return false;
			}
			c.nextScene = mutils::trimmed(std::string(line.begin() + 1, line.end()));

			readOneLine(stream, line);
			if (line.empty())
			{
				isChoice = false;
			}
			else if (line[0] != choice)
			{
				logError("Expected choice or empty line, got : " + line);
				return false;
			}
		}
		return true;
	}

	bool TxtParser::loadFromFile(SceneManager& manager, std::string filename)
	{

		std::ifstream file;
		file.open(filename, std::ifstream::in);
		if (!file.is_open())
		{
			MUTILS_ASSERT(false);
			return false;
		}

		std::string line;
		consumeEmptyLines(file, line);
		while (line.compare(scene) == 0)
		{
			Scene s;
			if (!loadScene(file, s))
			{
				return false;
			}
			consumeEmptyLines(file, line);
		}

		return true;
	}
}