#include<iostream>
#include<string>
using namespace std;
class cnode
{
public:
	int frequency;
	char name[256];
	string encryption;
	cnode *pnext;
	cnode *pleft = NULL;;
	cnode *pright = NULL;
	cnode *pdown = NULL;
};
class clist
{
public:
	cnode *phead;
	cnode *ptail;

	clist()
	{
		phead = NULL;
		ptail = NULL;
	}

	~clist()
	{
		cnode *ptrav = phead;
		while (ptrav != NULL)
		{
			phead = phead->pnext;
			delete ptrav;
			ptrav = phead;
		}
	}

	void Attach(cnode *pnn)
	{
		if (phead == NULL)
		{
			phead = pnn;
			ptail = pnn;
		}
		else
		{
			ptail->pnext = pnn;
			ptail = pnn;
		}
	}

	void sortAttach(cnode *pnn)
	{
		cnode *pB = NULL;
		cnode *ptrav = phead;
		while (ptrav != NULL)
		{
			if (ptrav->frequency > pnn->frequency)
			{
				break;
			}
			pB = ptrav;
			ptrav = ptrav->pnext;
		}
		if (ptrav != NULL)
		{
			if (pB != NULL)
			{
				pB->pnext = pnn;
				pnn->pnext = ptrav;
			}
			else
			{
				pnn->pnext = ptrav;
				phead = pnn;
			}
		}
		else
		{
			pB->pnext = pnn;
			pnn->pnext = NULL;
		}
	}

	void combine(cnode *pnn, cnode *ptrav)
	{
		cnode *pnn2;
		pnn2 = new cnode;
		cnode *tnext;
		cnode *tdown;
		tdown = new cnode;
		tnext = pnn->pnext;
		pnn2->frequency = pnn->frequency + tnext->frequency;
		int k = 0;

		//copy name pnn
		for (int i = 0; i < 256; i++)
		{
			if (pnn->name[i] != ' ')
			{
				pnn2->name[k] = pnn->name[i];
				k++;
			}
			else
			{
				break;
			}

		}

		//copy name pnext
		for (int i = 0; i < 256; i++)
		{
			if (tnext->name[i] != ' ')
			{
				pnn2->name[k] = tnext->name[i];
				k++;
			}
			else
			{
				break;
			}
		}

		//make rest of array null
		for (int i = k; i < 256; i++)
		{
			pnn2->name[i] = ' ';
		}

		//set tdown
		for (int i = 0; i < 256; i++)
		{
			tdown->name[i] = pnn2->name[i];
		}
		tdown->frequency = pnn2->frequency;


		//set tree
			//check pnn
		if (pnn->pdown != NULL)
		{
			tdown->pleft = pnn->pdown;
		}
		else
		{
			tdown->pleft = pnn;
		}

		//check tnext
		if (tnext->pdown != NULL)
		{
			tdown->pright = tnext->pdown;
		}
		else
		{
			tdown->pright = tnext;
		}

		pnn2->pdown = tdown;



		//sortAttach
		cnode *pB = NULL;
		while (ptrav != NULL)
		{
			if (ptrav->frequency > pnn2->frequency)
			{
				break;
			}
			pB = ptrav;
			ptrav = ptrav->pnext;
		}
		if (ptrav != NULL)
		{
			pB->pnext = pnn2;
			pnn2->pnext = ptrav;
		}
		else
		{
			pB->pnext = pnn2;
			pnn2->pnext = ptrav;
		}

	}

	/*void encrypt(cnode *pnn)
	{
		cnode *ptrav, *ptravd, *cright = NULL;
		ptrav = pnn;
		int c = 0, ctrav = 0, ct = 0;

		//left
		ptrav = ptrav->pleft;
		for (int i = 0; i < 256; i++)
		{
			if (ptrav->name[i] == ' ')
			{
				ptrav->name[i] = ':';
				ptrav->name[i+1] = '0';
				break;
			}
		}
		ptrav = pnn;
		//right
		ptrav = ptrav->pright;
		for (int i = 0; i < 256; i++)
		{
			if (ptrav->name[i] == ' ')
			{
				ptrav->name[i] = ':';
				ptrav->name[i + 1] = '1';
				break;
			}
		}
		ptrav = pnn->pleft;
		

		while (ptrav->pleft != NULL)
		{
			//for left
			ptravd = ptrav->pleft;
			//get pos char left
			for (int i = 0; i < 256; i++)
			{
				if (ptravd->name[i] == ' ')
				{
					ctrav = i;
					break;
				}
			}
			//get pos char
			for (int i = 0; i < 256; i++)
			{
				if (ptrav->name[i] == ':')
				{
					c = i;
					break;
				}
			}
			ct = c;
			//change char left
			for (int i = ctrav; i < 256; i++)
			{
				if (ptrav->name[c + 1] == ' ')
				{
					ptravd->name[i] = ptrav->name[c];
					ptravd->name[i + 1] = '0';
					break;
				}
				else
				{
					ptravd->name[i] = ptrav->name[c];
					c++;
				}
			}
			c = ct;


			//for right
			ptravd = ptrav->pright;
			//get pos char right
			for (int i = 0; i < 256; i++)
			{
				if (ptravd->name[i] == ' ')
				{
					ctrav = i;
					break;
				}
			}
			//change char right
			for (int i = ctrav; i < 256; i++)
			{
				if (ptrav->name[c + 1] == ' ')
				{
					ptravd->name[i] = ptrav->name[c];
					ptravd->name[i + 1] = '1';
					break;
				}
				else
				{
					ptravd->name[i] = ptrav->name[c];
					c++;
				}

			}
			if (ptrav->pleft->pleft != NULL)
			{
				ptrav = ptrav->pleft;
				if (ptrav->pright->pleft != NULL)
				{
					cright = ptrav->pright;
				}
			}
			else
			{
				ptrav = ptrav->pright;
				if (cright == NULL)
				{
					if (ptrav->pright->pleft != NULL)
					{
						cright = ptrav->pright;
					}
				}
			}

		}


		//right
		ptrav = pnn;
		ptrav = ptrav->pright;
		
		while (ptrav->pleft != NULL)
		{
			//for left
			ptravd = ptrav->pleft;
			//get pos char left
			for (int i = 0; i < 256; i++)
			{
				if (ptravd->name[i] == ' ')
				{
					ctrav = i;
					break;
				}
			}
			//get pos char
			for (int i = 0; i < 256; i++)
			{
				if (ptrav->name[i] == ':')
				{
					c = i;
					break;
				}
			}
			ct = c;
			//change char left
			for (int i = ctrav; i < 256; i++)
			{
				if (ptrav->name[c + 1] == ' ')
				{
					ptravd->name[i] = ptrav->name[c];
					ptravd->name[i + 1] = '0';
					break;
				}
				else
				{
					ptravd->name[i] = ptrav->name[c];
					c++;
				}
			}
			c = ct;


			//for right
			ptravd = ptrav->pright;
			//get pos char right
			for (int i = 0; i < 256; i++)
			{
				if (ptravd->name[i] == ' ')
				{
					ctrav = i;
					break;
				}
			}
			//change char right
			for (int i = ctrav; i < 256; i++)
			{
				if (ptrav->name[c + 1] == ' ')
				{
					ptravd->name[i] = ptrav->name[c];
					ptravd->name[i + 1] = '1';
					break;
				}
				else
				{
					ptravd->name[i] = ptrav->name[c];
					c++;
				}
			}
			//go left
			if (ptrav->pleft != NULL)
			{
				ptrav = ptrav->pleft;
			}
			else
			{
				ptrav = ptrav->pright;
			}
			

		}


		if (cright != NULL)
		{
			ptrav = cright;


			while (ptrav->pleft != NULL)
			{
				//for left
				ptravd = ptrav->pleft;
				//get pos char left
				for (int i = 0; i < 256; i++)
				{
					if (ptravd->name[i] == ' ')
					{
						ctrav = i;
						break;
					}
				}
				//get pos char
				for (int i = 0; i < 256; i++)
				{
					if (ptrav->name[i] == ':')
					{
						c = i;
						break;
					}
				}
				ct = c;
				//change char left
				for (int i = ctrav; i < 256; i++)
				{
					if (ptrav->name[c + 1] == ' ')
					{
						ptravd->name[i] = ptrav->name[c];
						ptravd->name[i + 1] = '0';
						break;
					}
					else
					{
						ptravd->name[i] = ptrav->name[c];
						c++;
					}
				}
				c = ct;


				//for right
				ptravd = ptrav->pright;
				//get pos char right
				for (int i = 0; i < 256; i++)
				{
					if (ptravd->name[i] == ' ')
					{
						ctrav = i;
						break;
					}
				}
				//change char right
				for (int i = ctrav; i < 256; i++)
				{
					if (ptrav->name[c + 1] == ' ')
					{
						ptravd->name[i] = ptrav->name[c];
						ptravd->name[i + 1] = '1';
						break;
					}
					else
					{
						ptravd->name[i] = ptrav->name[c];
						c++;
					}

				}
				if (ptrav->pleft->pleft != NULL)
				{
					ptrav = ptrav->pleft;
				}
				else
				{
					ptrav = ptrav->pright;
				}

			}
		}


	}*/

	void binsearch(cnode *pnn)
	{
		cnode *ptrav;
		string bin;
		int flag = 0;
		ptrav = pnn;
		cout << "input binary" << endl;
		cin >> bin;
		for (int i = 0; i < bin.length(); i++)
		{
			if (ptrav != NULL)
			{
				if (bin[i] == '0')
				{
					ptrav = ptrav->pleft;
				}
				else
				{
					if (bin[i] == '1')
					{
						ptrav = ptrav->pright;
					}
					else
					{
						flag = 1;
						break;
					}
				}
			}
			else
			{
				break;
			}
		}
		cout << endl << "-------------------------------" << endl;
		if (ptrav != NULL && flag==0)
		{
			for (int i = 0; i < 256; i++)
			{
				if (ptrav->name[i] != ' ')
				{
					cout << ptrav->name[i];
				}
				else
				{
					break;
				}
			}
			cout << " : " << ptrav->frequency << endl;
		}
		else
		{
			cout << "node not found" << endl;
		}

	}

	void searchBin(cnode *pnn)
	{
		cnode *ptrav;
		ptrav = pnn;
		char code[1];
		int flag = 0;
		cin >> code[0];
		while (ptrav->pleft != NULL && ptrav->pright != NULL)
		{
			for (int i = 0; i < 256; i++)
			{
				if (ptrav->pleft->name[i] == code[0])
				{
					ptrav = ptrav->pleft;
					break;
				}
				if (ptrav->pright->name[i] == code[0])
				{
					ptrav = ptrav->pright;
					break;
				}
			}

		}
		pnn = ptrav;
		for (int i = 0; i < 256; i++)
		{
			if (pnn->name[i] != ' ')
			{
				cout << pnn->name[i];
			}
			else
			{
				break;
			}
		}
		cout << " : " << pnn->frequency << endl;
	}

	void searchEnc(cnode *pnn, cnode *pnn2)
	{
		cnode *ptrav;
		ptrav = pnn;
		string encryption;
		char code[1];
		int flag = 0;
		code[0] = pnn2->name[0];
		while (ptrav->pleft != NULL && ptrav->pright != NULL)
		{
			for (int i = 0; i < 256; i++)
			{
				if (ptrav->pleft->name[i] == code[0])
				{
					ptrav = ptrav->pleft;
					encryption += '0';
					break;
				}
				if (ptrav->pright->name[i] == code[0])
				{
					ptrav = ptrav->pright;
					encryption += '1';
					break;
				}
			}
		}
		pnn = ptrav;
		for (int i = 0; i < 256; i++)
		{
			if (pnn->name[i] != ' ')
			{
				cout << pnn->name[i];
			}
			else
			{
				break;
			}
		}
		pnn2->encryption = encryption;
		cout << " : " << pnn2->frequency << " : " << pnn2->encryption << endl;
	}

};

int main()
{
	cnode *pnn;
	cnode *t, *t2;
	clist l, lcopy;
	int c = 0, flag = 0, n;
	string p;

	//start check values
	/*pnn = new cnode;
	pnn->frequency = 100;
	pnn->name[0] = 'A';
	for (int i = 1; i < 256; i++)
	{
		pnn->name[i] = ' ';
	}
	pnn->pnext = NULL;
	l.Attach(pnn);
	pnn = new cnode;
	pnn->frequency = 120;
	pnn->name[0] = 'K';
	for (int i = 1; i < 256; i++)
	{
		pnn->name[i] = ' ';
	}
	pnn->pnext = NULL;
	l.Attach(pnn);
	pnn = new cnode;
	pnn->frequency = 160;
	pnn->name[0] = 'M';
	for (int i = 1; i < 256; i++)
	{
		pnn->name[i] = ' ';
	}
	pnn->pnext = NULL;
	l.Attach(pnn);
	pnn = new cnode;
	pnn->frequency = 180;
	pnn->name[0] = 'F';
	for (int i = 1; i < 256; i++)
	{
		pnn->name[i] = ' ';
	}
	pnn->pnext = NULL;
	l.Attach(pnn);
	pnn = new cnode;
	pnn->frequency = 310;
	pnn->name[0] = 'W';
	for (int i = 1; i < 256; i++)
	{
		pnn->name[i] = ' ';
	}
	pnn->pnext = NULL;
	l.Attach(pnn);
	pnn = new cnode;
	pnn->frequency = 350;
	pnn->name[0] = 'Q';
	for (int i = 1; i < 256; i++)
	{
		pnn->name[i] = ' ';
	}
	pnn->pnext = NULL;
	l.Attach(pnn);
	pnn = new cnode;
	pnn->frequency = 600;
	pnn->name[0] = 'B';
	for (int i = 1; i < 256; i++)
	{
		pnn->name[i] = ' ';
	}
	pnn->pnext = NULL;
	l.Attach(pnn);
	pnn = new cnode;
	pnn->frequency = 700;
	pnn->name[0] = 'Z';
	for (int i = 1; i < 256; i++)
	{
		pnn->name[i] = ' ';
	}
	pnn->pnext = NULL;
	l.Attach(pnn);*/
	//end check values

	//if cin needed
	/*cout << "How many nodes?" << endl;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		pnn = new cnode;
		cout << "Input Character: ";
		cin >> pnn->name[0];
		for (int i = 1; i < 256; i++)
		{
			pnn->name[i] = ' ';
		}
		cout << "Input frequency: ";
		cin >> pnn->frequency;
		pnn->pnext = NULL;
		l.Attach(pnn);
	}*/


	//if text
	cin >> p;

	pnn = new cnode;
	pnn->name[0] = p[0];
	for (int i = 1; i < 256; i++)
	{
		pnn->name[i] = ' ';
	}
	pnn->frequency = 1;
	for (int i = 1; i < p.length(); i++)
	{
		if (p[i] == pnn->name[0])
		{
			pnn->frequency++;
		}
	}
	l.Attach(pnn);
	c++;

	for (int i = c; i < p.length(); i++)
	{
		t = l.phead;
		while (t != NULL)
		{
			if (p[c] == t->name[0])
			{
				flag = 1;
				break;
			}
			t = t->pnext;
		}
		if (flag != 1)
		{
			pnn = new cnode;
			pnn->name[0] = p[c];
			for (int i = 1; i < 256; i++)
			{
				pnn->name[i] = ' ';
			}
			pnn->frequency = 0;
			for (int i = c; i < p.length(); i++)
			{
				if (p[i] == pnn->name[0])
				{
					pnn->frequency++;
				}
			}
			l.sortAttach(pnn);
		}
		flag = 0;
		c++;

	}

	t = l.phead;
	while (t != NULL)
	{
		cout << t->name[0] << " : " << t->frequency << endl;
		t = t->pnext;
	}



	//show nodes
	cout << endl << "-------------------------------" << endl;
	t = l.phead;
	while (t != NULL)
	{
		for (int i = 0; i < 256; i++)
		{
			if (t->name[i] != ' ')
			{
				cout << t->name[i];
			}
			else
			{
				break;
			}
		}
		cout << " : " << t->frequency << endl;
		t = t->pnext;
	}


	t = l.phead;
	while (t->pnext != NULL)
	{
		t2 = l.phead;
		l.combine(t, t2);
		t = t->pnext;
		t = t->pnext;
		l.phead = t;
	}

	//cout debug
	/*t = l.phead->pdown;
	t = t->pleft;
	t = t->pright;
	t = t->pright;
	t = t->pright;
	cout << "left: ";
	for (int i = 0; i < 256; i++)
	{
		if (t->pleft->name[i] != ' ')
		{
			cout << t->pleft->name[i];
		}
		else
		{
			break;
		}
	}
	cout << " : " << t->pleft->frequency << endl;
	cout << "right: ";
	for (int i = 0; i < 256; i++)
	{
		if (t->pright->name[i] != ' ')
		{
			cout << t->pright->name[i];
		}
		else
		{
			break;
		}
	}
	cout << " : " << t->pright->frequency << endl;
*/

	//show first root
	t = l.phead;
	cout << endl << "-------------------------------" << endl << "First root : ";
	for (int i = 0; i < 256; i++)
	{
		if (t->name[i] != ' ')
		{
			cout << t->name[i];
		}
		else
		{
			break;
		}
	}
	cout << " : " << t->frequency << endl;

	//functions
	cout << endl << "-------------------------------" << endl;
	t = l.phead->pdown;
	//l.encrypt(t);


	c = 0;
	pnn = new cnode;
	pnn->name[0] = p[0];
	for (int i = 1; i < 256; i++)
	{
		pnn->name[i] = ' ';
	}
	pnn->frequency = 1;
	for (int i = 1; i < p.length(); i++)
	{
		if (p[i] == pnn->name[0])
		{
			pnn->frequency++;
		}
	}
	lcopy.Attach(pnn);
	c++;
	for (int i = c; i < p.length(); i++)
	{
		t = lcopy.phead;
		while (t != NULL)
		{
			if (p[c] == t->name[0])
			{
				flag = 1;
				break;
			}
			t = t->pnext;
		}
		if (flag != 1)
		{
			pnn = new cnode;
			pnn->name[0] = p[c];
			for (int i = 1; i < 256; i++)
			{
				pnn->name[i] = ' ';
			}
			pnn->frequency = 0;
			for (int i = c; i < p.length(); i++)
			{
				if (p[i] == pnn->name[0])
				{
					pnn->frequency++;
				}
			}
			lcopy.sortAttach(pnn);
		}
		flag = 0;
		c++;

	}


	t2 = lcopy.phead;
	while (t2 != NULL)
	{
		t = l.phead->pdown;
		l.searchEnc(t, t2);
		t2 = t2->pnext;
	}

	clist lencypt;
	char m, stemp = 0, comp[256];
	int iBit = 7;
	c = 0;
	for (int i = 0; i < p.length(); i++)
	{
		t = lcopy.phead;
		while (t->name[0] != p[i])
		{
			t = t->pnext;
		}
		for (int k = 0; k < t->encryption.length(); k++)
		{
			if (iBit == -1)
			{
				comp[c] = stemp;
				c++;
				iBit = 7;
				stemp = 0;
			}
			if (t->encryption[k] == '0')
			{
				m = 0;
			}
			else
			{
				m = 1;
			}
			stemp = stemp | (m << iBit);
			iBit--;
		}
		if ((i + 1) == p.length())
		{
			comp[c] = stemp;
			comp[c + 1] = '\0';
			c++;
		}
	}

	cout << endl << "-------------------------------" << endl;
	for (int i = 0; i!=-1; i++)
	{
		cout << comp[i];
		if (comp[i] == '\0')
		{
			break;
		}
	}
	cout << endl << endl;

	clist lcomp;
	char res, decomp[500];
	string check, null;
	c = 0;
	for (int i = 0; comp[i] != '\0'; i++)
	{

		stemp = comp[i];
		iBit = 7;
		while (iBit != -1)
		{
			char res = stemp & (1 << iBit);
			if (res != 0)
			{
				pnn = new cnode;
				pnn->name[0] = '1';
				pnn->pnext = NULL;
				lcomp.Attach(pnn);
			}
			else
			{
				pnn = new cnode;
				pnn->name[0] = '0';
				pnn->pnext = NULL;
				lcomp.Attach(pnn);
			}
			t = lcopy.phead;
			t2 = lcomp.phead;
			check = null;
			while (t2 != NULL)
			{
				check += t2->name[0];
				t2 = t2->pnext;
			}

			//check encry
			while (t != NULL)
			{
				if (check == t->encryption)
				{
					decomp[c] = t->name[0];
					c++;
					lcomp.phead = NULL;
					break;
				}
				t = t->pnext;
			}
			iBit--;
		}
	}
	decomp[c] = '\0';
	cout << endl << "-------------------------------" << endl;
	for (int i = 0; i != -1; i++)
	{
		cout << decomp[i];
		if (decomp[i] == '\0')
		{
			break;
		}
	}
	cout << endl << endl;


	system("pause");
	return 0;
}
