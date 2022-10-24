#include <iostream>
#include <deque>
using namespace std;
int gkey();
void setarea();

deque<uint8_t> cols, rows;
deque<string> text;
uint8_t x = 0, y = 0;

int main(int argc, char** argv)
{
	cout << "\e[?25l";
	for (uint8_t i {0}; i < 5; i++) cols.push_back(10);
	for (uint8_t i = 0; i < 6; i++) rows.push_back(1);
	for (uint8_t i = 0; i < cols.size() * rows.size(); i++) text.push_back("");
	system("clear");
	char key;
	
	while (true)
	{
		system("clear");
		setarea();
		key = gkey();
		
		if (key == '\033') 
		{
			gkey();
			switch (gkey()) 
			{
				case 'A': if (y != 0) y--; break;
				case 'B': if (y < rows.size() - 1) y++; break;
				case 'C': if (x < cols.size() - 1) x++; break;
				case 'D': if (x != 0) x--; break;
			}
		}
		
		else if (key == 'q')
		{
			cout << "\e[?25h" << endl;
			return 0;
		}
		
		else if (key == 127 && text[(y * cols.size()) + x].length() > 0) text[(y * cols.size()) + x].pop_back();
		
		else  if (key == 5)
		{
			system("clear");
			cout << "Enter new sheet size (x * y) or keep blank: ";
			
		}
		
		else 
		{
			if (text[(y * cols.size()) + x].length() + 1 == cols[x]) cols[x]++;
			text[(y * cols.size()) + x] += key;	
		}
	}
}

int gkey()
{
	system("/bin/stty raw");
	int c;
	system("/bin/stty -echo");
	c = getc(stdin);
	system("/bin/stty echo");
	system("/bin/stty cooked");
	return c;
}

void setarea()
{
	cout << "IRRADIX TERMSHEETS - ";
	if (rows.size() < 10) cout << "0";
	cout << rows.size() << " rows x ";
	if (cols.size() < 10) cout << "0";
	cout << uint16_t(cols.size()) << " columns" << endl;
	for (uint8_t i = 0; i < cols.size(); i++) for (uint8_t j = 0; j < cols[i]; j++) cout << "_";
	cout << endl;
	
	for (uint8_t i = 0; i < rows.size(); i++)
	{
		for (uint8_t j = 0; j < cols.size(); j++)
		{
			if (!text[(i * cols.size()) + j].size()) for (uint8_t f = 0; f < cols[j] - 1; f++) cout << "_";
			
			else if (text[(i * cols.size()) + j].size() && uint16_t(text[(i * cols.size()) + j].size()) < cols[j] - 1) 
			{
				cout << text[(i * cols.size()) + j];
				for (uint8_t g = 0; g < cols[j] - text[(i * cols.size()) + j].size() - 1; g++) cout << "_";
			}
			
			else cout << text[(i * cols.size()) + j];
			
			if ((y * cols.size()) + x - 1 == (i * cols.size()) + j - 1)  cout << ".";
			
			else cout << "|";
			
		}
		cout << endl;
	}
	cout << endl;
}
