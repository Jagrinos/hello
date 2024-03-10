#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;

class kol_rep
{
public:
	void set(string _elem, unsigned int _kol_repeat) {
		elem = _elem;
		kol_repeat = _kol_repeat;
	}
	void get() {
		cout << elem << ": " << kol_repeat << endl;
	}
private:
	string elem;
	unsigned int kol_repeat;
	friend void print_baze(kol_rep*, int);
	friend void print_baze_without_sort(kol_rep*, int);
};

void print_baze_without_sort(kol_rep* full, int kol_words) {
	for (int i = 0; i < kol_words; i++)
	{
		if ((*(full + i)).elem == "") continue;
		(*(full + i)).get();
	}
}


void print_baze(kol_rep * full, int kol_words) {
	/*for (int i = 0; i < kol_words; i++)
	{
		if ((*(full + i)).elem == "") continue;
		(*(full + i)).get();
	}*/

	int* mass_kol = new int[kol_words];
	int kol_mass_kol = 0;
	
	//form
	for (int i = 0; i < kol_words; i++) {
		if ((*(full + i)).elem == "") continue;
		*(mass_kol + kol_mass_kol) = (*(full + i)).kol_repeat;
		kol_mass_kol++;
	}

	//sort
	for (int i = 0; i < kol_mass_kol; i++) {
		int max = i;

		for (int j = i + 1; j < kol_mass_kol; j++) {
			max = (*(mass_kol + j) > *(mass_kol + max)) ? j : max;
		}
		
		if (i != max) {
			int buf = *(mass_kol + i);
			*(mass_kol + i) = *(mass_kol + max);
			*(mass_kol + max) = buf;
		}
	}

	for (int i = 0; i < kol_mass_kol; i++) {
		
		for (int j = 0; j < kol_words; j++)
		{
			if ((*(full + j)).elem == "") continue;
			if ((*(full + j)).kol_repeat == *(mass_kol + i))
			{
				(*(full + j)).get();
				(*(full + j)).elem = "";
				break;
			}
		}
	}
}



int main() {
	setlocale(LC_ALL, "rus");
	ifstream file("ghost.txt");

	string line;
	
	unsigned int kol_words = 0;


	while (getline(file, line)) {
		/*string line_without_tchk = "";

		for (int i = 0; i < line.length(); i++) {
			if (line[i] != '.' && line[i] != ',' && line[i] != '!' && line[i] != '?') {
				line_without_tchk += line[i];
			}
		}*/

		istringstream ist(line);

		for (string word; ist >> word;) {
			kol_words++;
		}
	}
	file.close();

	string* words = new string[kol_words];

	file.open("ghost.txt");
	int i = 0;

	while (getline(file, line)) {
		

		string line_without_tchk = "";

		for (int i = 0; i < line.length(); i++) {
			if (line[i] != '.' && line[i] != ',' && line[i] != '!' && line[i] != '?') {
				line_without_tchk += tolower(line[i]);
			}
		}
		istringstream ist(line_without_tchk);
		
		for (string word; ist >> word; i++) {
			*(words + i) = word;
		}
	}
	

	kol_rep* full = new kol_rep[kol_words];

	for (int i = 0; i < kol_words; i++) {

		if (*(words + i) == "") continue;
		
		unsigned int kol_repeat = 1;
		string elem = *(words + i);
		*(words + i) = "";

		for (int j = i; j < kol_words; j++) {
			if (*(words + j) == elem) {
				kol_repeat++;
				*(words + j) = "";
			}
		}

		(*(full + i)).set(elem, kol_repeat);
	}

	print_baze(full, kol_words);

	return 1488;
}