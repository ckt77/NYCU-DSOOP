#include<iostream>
#include<fstream>
#include<iomanip> // for setw()
#include<string>
#include<vector>
#include<cctype> // for islower()
#include<queue>
using namespace std;

struct HuffmanTree
{
	char name = '0';
	int frequency = 0;
	string str = "";
	int length = 0;
	HuffmanTree* left_child = NULL;
	HuffmanTree* right_child = NULL;
};

int main(int argc, char* argv[])
{
	cout << "DSOO-Program2-Demo: ./tree ";

	HuffmanTree alphabet[52]; // a priority queue
	int alphabet_frequency[52] = { 11,5,2,3,12,3,5,6,8,1,2,4,8,7,2,2,1,9,6,2,4,1,10,10,1,1 };
	string code = "";

	if (argc == 2)
	{
		cout << argv[1];
		string filename = argv[1];
		ifstream cin;
		cin.open(filename);

		for (int i = 0; i < 52; i++)
			alphabet_frequency[i] = 0; // reset

		cout << "\ncharacters : ";
		char next;
		while (cin.get(next) && next != ' ') // initialize
		{
			cout << next;
			if (islower(next))
				alphabet_frequency[next - 97 + 26] += 1;
			else
				alphabet_frequency[next - 65] += 1;
		}

		while (cin.get(next) && next != '\n') // initialize
			code += next;
	}
	cout << endl << endl;

	vector<HuffmanTree> list; // for building a HuffmanTree
	queue<HuffmanTree> q; // for converting HuffmanCode
	string HuffmanCode[52];
	int length_to_root[52] = { 0 };
	int WEPL = 0;
	int counter_1 = 0; // for counting how many numbers which are nonzero in alphabet_frequency[]

	for (int i = 0; i < 52; i++)
	{
		if (alphabet_frequency[i] > 0)
		{
			counter_1++;
			alphabet[i].name = i <= 25 ? char(i + 65) : char(i - 26 + 97);
			alphabet[i].frequency = alphabet_frequency[i];

			// insertion sort
			HuffmanTree temp_1 = alphabet[i];
			int j = i - 1;
			while ((j >= 0) && ((alphabet[j].frequency > temp_1.frequency) || alphabet[j].frequency == 0))
			{
				alphabet[j + 1] = alphabet[j];
				j--;
			}
			alphabet[j + 1] = temp_1;
		}
	}

	list.assign(alphabet, alphabet + counter_1);

	while (list.size() > 1)
	{
		HuffmanTree new_element;
		new_element.left_child = new HuffmanTree;
		new_element.left_child->name = list[0].name;
		new_element.left_child->frequency = list[0].frequency;
		new_element.left_child->left_child = list[0].left_child;
		new_element.left_child->right_child = list[0].right_child;
		list.erase(list.begin());
		new_element.right_child = new HuffmanTree;
		new_element.right_child->name = list[0].name;
		new_element.right_child->frequency = list[0].frequency;
		new_element.right_child->left_child = list[0].left_child;
		new_element.right_child->right_child = list[0].right_child;
		list.erase(list.begin());
		new_element.name = '0';
		new_element.frequency = new_element.left_child->frequency + new_element.right_child->frequency;

		list.push_back(new_element);
		int i = list.size() - 1, j = i - 1;
		HuffmanTree temp_2 = list[i];
		while ((j >= 0) && (list[j].frequency > temp_2.frequency))
		{
			list[j + 1] = list[j];
			j--;
		}
		list[j + 1] = temp_2;
	}

	q.push(list[0]);
	while (!q.empty())
	{
		if (q.front().left_child->name == '0')
		{
			q.front().left_child->str = q.front().str + "0";
			q.front().left_child->length = q.front().length + 1;
			q.push(*q.front().left_child);
		}

		else
		{
			if (islower(q.front().left_child->name))
			{
				HuffmanCode[q.front().left_child->name - 97 + 26] = q.front().str + "0";
				length_to_root[q.front().left_child->name - 97 + 26] = q.front().length + 1;
			}

			else
			{
				HuffmanCode[q.front().left_child->name - 65] = q.front().str + "0";
				length_to_root[q.front().left_child->name - 65] = q.front().length + 1;
			}
		}

		if (q.front().right_child->name == '0')
		{
			q.front().right_child->str = q.front().str + "1";
			q.front().right_child->length = q.front().length + 1;
			q.push(*q.front().right_child);
		}

		else
		{
			if (islower(q.front().right_child->name))
			{
				HuffmanCode[q.front().right_child->name - 97 + 26] = q.front().str + "1";
				length_to_root[q.front().right_child->name - 97 + 26] = q.front().length + 1;
			}

			else
			{
				HuffmanCode[q.front().right_child->name - 65] = q.front().str + "1";
				length_to_root[q.front().right_child->name - 65] = q.front().length + 1;
			}
		}

		q.pop();
	}

	int counter_2 = 0; // for typesetting
	for (int i = 0; i < 52; i++)
	{
		if (alphabet_frequency[i] > 0)
		{
			counter_2++;
			cout << (i <= 25 ? char(i + 65) : char(i - 26 + 97)) << " = " << setw(2) << alphabet_frequency[i] << " | ";
			if (counter_2 % 10 == 0)
				cout << endl;
			WEPL += alphabet_frequency[i] * length_to_root[i];
		}
	}

	cout << endl;
	if (counter_2 % 10 != 0)
		cout << endl;
	for (int i = 0; i < 52; i++)
		if (alphabet_frequency[i] > 0)
			cout << (i <= 25 ? char(i + 65) : char(i - 26 + 97)) << " : " << HuffmanCode[i] << endl;
	cout << endl;

	if (argc == 2)
	{
		cout << "Huffman code : " << code << endl;
		cout << "decode : ";

	here:
		bool ifError = false;
		while (code.length() != 0 && ifError == false)
		{
			string temp_3 = "";
			for (int i = 0; i < code.length(); i++)
			{
				temp_3 += code[i];
				for (int j = 0; j < 52; j++)
				{
					if (temp_3 == HuffmanCode[j])
					{
						cout << (j <= 25 ? char(j + 65) : char(j - 26 + 97));
						code.erase(0, i + 1);
						goto here;
					}
				}

				if (i == code.length() - 1)
				{
					ifError = true;
					cout << " -wrong decode-";
				}
			}
		}
		cout << endl;
	}
	cout << "WEPL : " << WEPL << endl;
	
	system("PAUSE");
	return 0;
}