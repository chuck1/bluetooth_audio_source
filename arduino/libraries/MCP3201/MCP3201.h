#ifndef MCP3201_H
#define MCP3201_H

class MCP3201
{
	public:
		MCP3201(int pin_CS);
		void setup();
		unsigned int read();
	private:
		int _pin_CS;
};

#endif