#include <iostream>
#include <deque>
using namespace std;
int gkey();
void setarea();

deque<uint8_t> cols, rows;
deque<string> text;
uint8_t x = 0, y = 0;
bool delrn = false;

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
		
		else if (key == 17)
		{
			cout << "\e[?25h" << endl;
			return 0;
		}
		
		else if (key == 127 || key == 8 || delrn == true) 
		{
			if (text[(y * size(cols)) + x].length() > 0) text[(y * cols.size()) + x].pop_back();
			uint16_t j = 0;
			for (uint8_t i = 0; i < size(cols); i++) if (uint16_t(text[(i * cols.size()) + x].length()) < uint16_t(cols[x] - 1)) j++;
			j++;
			if (j == size(rows) && cols[x] > 10) cols[x]--;
			delrn = false;
			cout << j;
		}
		
		else  if (key == 5)
		{
			x = 0, y = 0;
			cout << "\e[?25h";
			uint16_t i = 0, h = 0;
			system("clear");
			cout << "Enter new sheet size (x * y) or keep blank: ";
			cin >> h >> i;
				while (!text.empty()) text.pop_back();
				while (!cols.empty()) cols.pop_back();
				while (!rows.empty()) rows.pop_back();
				for (uint16_t f = 0; f < i; f++) cols.push_back(10);
				for (uint16_t f = 0; f < h ; f++) rows.push_back(1);
				for (uint16_t f = 0; f < (h * i); f++) text.push_back("");
				delrn = true;
				cout << "\e[?25l";
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
	cout << endl << "X: " << uint16_t(x) << endl << "Y: " << uint16_t(y) << endl << endl << "CTRL + h  :  get help";
}
