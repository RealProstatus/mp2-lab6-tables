#pragma once

#include<string>

class Exceptions {
public:
	virtual std::string getMessage() = 0;
};

class InvalidConstructorArgument : public Exceptions {
	std::string getMessage() {
		return "Invalid constructor argument";
	}
};

class OutOfRange : public Exceptions {
	std::string getMessage() {
		return "Idx was out of range";
	}
};

class RecordAlreadyExist : public Exceptions {
	std::string getMessage() {
		return "You tried to rewrite record";
	}
};

class InsertInFullTable : public Exceptions {
	std::string getMessage() {
		return "You tried to insert in full table";
	}
};