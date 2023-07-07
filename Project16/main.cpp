#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
#include<vector>
#include<set>
using namespace std;
typedef long long ll;
void printMenu() {
	cout << "1.Add polynomial" << endl << "2.List" << endl << "3.Exit" << endl << "4.delete"
		<< endl << "5.all delete" << endl << "6.Point value" << endl << "7.Addition of polynomials" <<
		endl << "8.Polynomial multiplication" << endl << "9.Integer roots" << endl << "10.Nth order derivative" << endl;
}
int base_size = 0;
struct sost {
	vector<ll> n;
	vector<set<char>> usl;
};
struct polynomial {
	ll k;
	ll st;
	char var;
	polynomial* next;
};
struct base {
	polynomial* next;
	base* down;
};
void print_polynomial(polynomial*& L) {
	polynomial* qq = L;
	bool fl = 0;
	while (qq != nullptr) {
		if (fl && qq->k >= 0) {
			cout << "+";
		}
		if (qq->st == 0) {
			cout << qq->k;
		}
		else {
			if (qq->st == 1 && qq->k != 1) {
				cout << qq->k << qq->var;
			}
			else {
				if (qq->k == 1) {
					if (qq->st == 1) {
						cout << qq->var;
					}
					else {
						cout << qq->var << "^" << qq->st;
					}
				}
				else {
					cout << qq->k << qq->var << "^" << qq->st;
				}
			}
		}
		qq = qq->next;
		fl = 1;
	}
	cout << endl;
}
void print_list(base*& bas) {
	base* q = bas;
	while (q != nullptr) {
		polynomial* qq = q->next;
		print_polynomial(qq);
		q = q->down;
	}
}
void sort(polynomial*& L) {
	polynomial* q = L;
	ll sch = 0;
	while (q->next != nullptr) {
		if (q->st < q->next->st) {
			ll a = q->k;
			ll b = q->st;
			q->k = q->next->k;
			q->st = q->next->st;
			q->next->k = a;
			q->next->st = b;
		}
		if (q->st == q->next->st) {
			q->k += q->next->k;
			q->next = q->next->next;
			if (q->next == nullptr) break;
		}
		q = q->next;
		sch++;
	}
	for (ll i = 0; i < sch; i++) {
		polynomial* q = L;
		while (q->next != nullptr) {
			if (q->st < q->next->st) {
				ll a = q->k;
				ll b = q->st;
				q->k = q->next->k;
				q->st = q->next->st;
				q->next->k = a;
				q->next->st = b;
			}
			if (q->st == q->next->st) {
				q->k += q->next->k;
				q->next = q->next->next;
				if (q->next == nullptr) break;
			}
			q = q->next;
		}
	}
}
void push(polynomial*& L, ll k, ll st, char var) {
	polynomial* q = new polynomial;
	q->var = var;
	q->k = k;
	q->st = st;
	q->next = L;
	L = q;
}
void push_base(base*& bas, polynomial*& L) {
	base* q = new base;
	q->next = L;
	q->down = bas;
	bas = q;
}
void insert(base*& bas, string str, vector <sost> cond) {
	polynomial* L = nullptr;
	ll a = 0;
	bool flvar = 1, flv = 0, flst = 0;
	ll i = 0;
	char k = 'a';
	ll zn = 0;
	ll st = 0;
	bool flznak = 0;
	for (i = 0; i < str.size(); i++) {
		if (flvar && 'a' <= str[i] && str[i] <= 'z') {
			k = str[i];
			flvar = 0;
		}
		if (k == str[i]) {
			flv = 1;
		}
		if (str[i] == '^') {
			flst = 1;
		}
		if ('0' <= str[i] && str[i] <= '9') {
			while (i < str.size() && '0' <= str[i] && str[i] <= '9' && !flst) {
				zn = zn * 10 + str[i] - '0';
				i++;
			}
			while (i < str.size() && '0' <= str[i] && str[i] <= '9' && flst) {
				st = st * 10 + str[i] - '0';
				i++;
			}
			i--;
		}
		if (str[i] == '+' || str[i] == '-' || i == str.size() - 1) {
			if (flv && st == 0) {
				st = 1;
			}
			if (flv && zn == 0) {
				zn = 1;
			}
			if (zn != 0) {
				if (flznak) {
					push(L, -zn, st, k);
				}
				else {
					push(L, zn, st, k);
				}
			}
			zn = 0;
			st = 0;
			flv = 0, flst = 0;
			if (str[i] == '-') {
				flznak = 1;
			}
			if (str[i] == '+') {
				flznak = 0;
			}
		}
	}
	if (L == nullptr) {
		push(L, 0, 0, 'a');
	}
	sort(L);
	print_polynomial(L);
	push_base(bas, L);
	base_size++;
}
void polynomial_mult(base*& bas, ll nomer1, ll nomer2) {
	nomer1--;
	nomer2--;
	base* q = bas;
	while (nomer1--) {
		q = q->down;
	}
	polynomial* qq1 = q->next;
	q = bas;
	while (nomer2--) {
		q = q->down;
	}
	polynomial* qq2 = q->next;
	if (qq1->var != qq2->var) {
		cout << "different variables" << endl;
		return;
	}
	polynomial* ans = nullptr;
	polynomial* save = qq2;
	while (qq1 != nullptr) {
		while (qq2 != nullptr) {
			push(ans, (qq1->k*qq2->k), (qq1->st + qq2->st), qq1->var);
			qq2 = qq2->next;
		}
		qq1 = qq1->next;
		qq2 = save;
	}
	sort(ans);
	print_polynomial(ans);
	cout << "add polynomial?" << endl;
	cout << "yes/no" << endl;
	string str;
	cin >> str;
	if (str == "yes") {
		push_base(bas, ans);
		base_size++;
	}
}
void addition_polynomials(base*& bas, ll nomer1, ll nomer2) {
	nomer1--;
	nomer2--;
	base* q = bas;
	while (nomer1--) {
		q = q->down;
	}
	polynomial* qq1 = q->next;
	q = bas;
	while (nomer2--) {
		q = q->down;
	}
	polynomial* qq2 = q->next;
	if (qq1->var != qq2->var) {
		cout << "different variables" << endl;
		return;
	}
	polynomial* ans = nullptr;
	while (qq1 != nullptr && qq2 != nullptr) {
		if (qq1->st > qq2->st) {
			push(ans, qq1->k, qq1->st, qq1->var);
			qq1 = qq1->next;
		}
		else {
			if (qq1->st == qq2->st) {
				if (qq1->k + qq2->k != 0) {
					push(ans, (qq1->k + qq2->k), qq1->st, qq1->var);
				}
				qq1 = qq1->next;
				qq2 = qq2->next;
			}
			else {
				push(ans, qq2->k, qq2->st, qq2->var);
				qq2 = qq2->next;
			}
		}
	}
	while (qq1 != nullptr) {
		push(ans, qq1->k, qq1->st, qq1->var);
		qq1 = qq1->next;
	}
	while (qq2 != nullptr) {
		push(ans, qq2->k, qq2->st, qq2->var);
		qq2 = qq2->next;
	}
	sort(ans);
	print_polynomial(ans);
	cout << "add polynomial?" << endl;
	cout << "yes/no" << endl;
	string str;
	cin >> str;
	if (str == "yes") {
		push_base(bas, ans);
		base_size++;
	}
}
double point_Value(base*& bas, ll nomer, ll varx) {
	nomer --;
	base* q = bas;
	while (nomer--) {
		q = q->down;
	}
	polynomial* qq = q->next;
	double ans = 0;
	while (qq != nullptr) {
		ans = ans + (qq->k) * pow(varx, qq->st);
		qq = qq->next;
	}
	return ans;
}
void int_root(base*& bas, ll nomer) {
	nomer--;
	base* q = bas;
	while (nomer--) {
		q = q->down;
	}
	polynomial* qq = q->next;
	while (qq->next != nullptr) {
		qq = qq->next;
	}
	vector<ll> del;
	del.push_back(1);
	ll a = qq->k;
	for (ll i = 1; i <= a; i++) {
		if(a % i == 0) {
			del.push_back(i);
			del.push_back(-i);
		}
	}
	bool fl = 1;
	if (qq->st > 0) {
		cout << "Root: 0 ";
		fl = 0;
	}
	for (ll i = 0; i < del.size(); i++) {
		qq = q->next;
		ll ans = 0;
		while (qq != nullptr) {
			ans = ans + qq->k * pow(del[i], qq->st);
			qq = qq->next;
		}
		if (ans == 0) {
			if (fl) {
				cout << "Root: ";
				fl = 0;
			}
			cout << del[i] << " ";
		}
	}
	if (fl) {
		cout << "No roots";
	}
	cout << endl;
}
void order_der(base*& bas, ll nomer, ll step) {
	nomer--;
	base* q = bas;
	while (nomer--) {
		q = q->down;
	}
	polynomial* qq = q->next;
	polynomial* ans = nullptr;
	bool fl = 0;
	while (qq != nullptr && qq->st >= step) {
		fl = 1;
		ll kof = qq->k, stepen = qq->st;
		for (ll i = 0; i < step; i++) {
			kof *= stepen;
			stepen--;
		}
		push(ans, kof, stepen, qq->var);
		qq = qq->next;
	}
	if (!fl) {
		cout << "0" << endl;
		cout << "add polynomial?" << endl;
		cout << "yes/no" << endl;
		string str;
		cin >> str;
		if (str == "yes") {
			ans->k = 0;
			ans->st = 0;
			ans->var = 'a';
			ans->next = nullptr;
			push_base(bas, ans);
			base_size++;
		}
	}
	else {
		sort(ans);
		print_polynomial(ans);
		cout << "add polynomial?" << endl;
		cout << "yes/no" << endl;
		string str;
		cin >> str;
		if (str == "yes") {
			push_base(bas, ans);
			base_size++;
		}
	}
}
bool kon_avt(string str, vector <sost> cond, char k, set<char>allsym) {
	ll a = 0;
	bool fl = 0, flvar = 1;
	ll i = 0;
	for (i = 0; i < str.size(); i++) {
		fl = 0;
		if (flvar && 'a'<=str[i] && str[i]<='z') {
			k = str[i];
			flvar = 0;
		}
		for (ll y = 0; y < cond[a].usl.size(); y++) {
			if (cond[a].usl[y].count(str[i]) || (cond[a].usl[y].count('a') && 'a' <= str[i] && str[i] <= 'z')) {
				a = cond[a].n[y];
				fl = 1;
				break;
			}
		}
		if (!fl) break;
	}
	if (a == 0 || a == 4 || a == 5) {
		fl = 0;
	}
	if (fl) {
		cout << "Ok" << endl;
		return 1;
	}
	if (!allsym.count(str[i])) {
		cout << "Unknown symbol" << endl;
	}
	else {
		if (i != 0 && str[i - 1] == ' ') {
			cout << "Space separates numbers" << endl;
		}
		else {
			if (a == 0) {
				cout << "Empty line" << endl;
			}
			else {
				if (a == 4) {
					cout << "Degree not entered" << endl;
				}
				else {
					if (a == 5) {
						cout << "no second argument provided" << endl;
					}
					else {
						cout << "No" << endl;
					}
				}
			}
		}
	}
	return 0;
}
void del(base*& bas, ll nomer) {
	if (nomer == 1) {
		bas = bas->down;
		return;
	}
	nomer -= 2;
	base* q = bas;
	while (nomer--) {
		q = q->down;
	}
	q->down = q->down->down;
}
int main() {
	int comand = 0;
	set<char>allsym = { '+', '-', '^', ' ', '\n' };
	set<char> num;
	for (ll i = 0; i < 10; i++) {
		num.insert('0' + i);
		allsym.insert('0' + i);
	}
	for (ll i = 0; i < 27; i++) {
		allsym.insert('a' + i);
	}
	set<char> oper = { '+', '-' };
	char k = 'a';
	set<char> var = { k };
	set<char> deg = {'^'};
	set<char> space = { ' ' };
	set<char> end = {'\n'};
	vector <sost> cond;
	sost a, b, c, d, e, f, g;
	a.n.push_back(0);
	a.n.push_back(1);
	a.n.push_back(2);
	a.usl.push_back(space);
	a.usl.push_back(var);
	a.usl.push_back(num);
	b.n.push_back(1);
	b.n.push_back(3);
	b.n.push_back(4);
	b.usl.push_back(space);
	b.usl.push_back(deg);
	b.usl.push_back(oper);
	c.n.push_back(1);
	c.n.push_back(2);
	c.n.push_back(4);
	c.n.push_back(5);
	c.n.push_back(6);
	c.usl.push_back(var);
	c.usl.push_back(num);
	c.usl.push_back(oper);
	c.usl.push_back(space);
	c.usl.push_back(end);
	d.n.push_back(2);
	d.n.push_back(3);
	d.usl.push_back(num);
	d.usl.push_back(space);
	e.n.push_back(1);
	e.n.push_back(2);
	e.n.push_back(4);
	e.usl.push_back(var);
	e.usl.push_back(num);
	e.usl.push_back(space);
	f.n.push_back(1);
	f.n.push_back(4);
	f.n.push_back(5);
	f.n.push_back(6);
	f.usl.push_back(var);
	f.usl.push_back(oper);
	f.usl.push_back(space);
	f.usl.push_back(end);
	cond.push_back(a);
	cond.push_back(b);
	cond.push_back(c);
	cond.push_back(d);
	cond.push_back(e);
	cond.push_back(f);
	cond.push_back(g);
	base* bas = nullptr;
	ifstream Fin;
	Fin.open("BASE.txt");
	while (!Fin.eof()) {
		string str;
		getline(Fin, str);
		if (str != "") {
			insert(bas, str, cond);
		}
	}
	Fin.close();
	while (comand != 3) {
		printMenu();
		cin >> comand;
		if (comand == 1) {
			cout << "polynomial:" << endl;
			string str;
			getline(cin, str);
			getline(cin, str);
			if (kon_avt(str, cond, k, allsym)) {
				insert(bas, str, cond);
			}
		}
		if (comand == 2) {
			print_list(bas);
		}
		if (comand == 4) {
			cout << "the number of the polynomial to be removed: ";
			ll nomer;
			cin >> nomer;
			if (nomer > base_size || nomer < 1) {
				cout << "no such element" << endl;
			}
			else {
				del(bas, nomer);
				base_size--;
			}
		}
		if (comand == 5) {
			bas = nullptr;
			base_size = 0;
		}
		if (comand == 6) {
			cout << "enter the polynomial number: ";
			ll nomer, varx;
			cin >> nomer;
			if (nomer > base_size || nomer < 1) {
				cout << "no such element" << endl;
			}
			else {
				cout << "X = ";
				cin >> varx;
				cout << "ans: ";
				cout << point_Value(bas, nomer, varx) << endl;
			}
		}
		if (comand == 7) {
			ll nomer1;
			ll nomer2;
			cout << "enter the number of the first polynomial: ";
			cin >> nomer1;
			if (nomer1 > base_size || nomer1 < 1) {
				cout << "no such element" << endl;
			}
			else {
				cout << "enter the number of the second polynomial: ";
				cin >> nomer2;
				if (nomer2 > base_size || nomer2 < 1) {
					cout << "no such element" << endl;
				}
				else {
					addition_polynomials(bas, nomer1, nomer2);
				}
			}
		}
		if (comand == 8) {
			ll nomer1;
			ll nomer2;
			cout << "enter the number of the first polynomial: ";
			cin >> nomer1;
			if (nomer1 > base_size || nomer1 < 1) {
				cout << "no such element" << endl;
			}
			else {
				cout << "enter the number of the second polynomial: ";
				cin >> nomer2;
				if (nomer2 > base_size || nomer2 < 1) {
					cout << "no such element" << endl;
				}
				else {
					polynomial_mult(bas, nomer1, nomer2);
				}
			}
		}
		if (comand == 9) {
			ll nomer;
			cout << "enter the polynomial number: ";
			cin >> nomer;
			if (nomer > base_size || nomer < 1) {
				cout << "no such element" << endl;
			}
			else {
				int_root(bas, nomer);
			}
		}
		if (comand == 10) {
			ll nomer, step;
			cout << "enter the polynomial number: ";
			cin >> nomer;
			if (nomer > base_size || nomer < 1) {
				cout << "no such element" << endl;
			}
			else {
				cout << "count: ";
				cin >> step;
				order_der(bas, nomer, step);
			}
		}
	}
	ofstream Fout;
	Fout.open("BASE.txt");
	base* q = bas;
	while (q != nullptr) {
		polynomial* qq = q->next;
		bool fl = 0;
		while (qq != nullptr) {
			if (fl && qq->k >= 0) {
				Fout << "+";
			}
			if (qq->st == 0) {
				Fout << qq->k;
			}
			else {
				if (qq->st == 1 && qq->k != 1) {
					Fout << qq->k << qq->var;
				}
				else {
					if (qq->k == 1) {
						if (qq->st == 1) {
							Fout << qq->var;
						}
						else {
							Fout << qq->var << "^" << qq->st;
						}
					}
					else {
						Fout << qq->k << qq->var << "^" << qq->st;
					}
				}
			}
			qq = qq->next;
			fl = 1;
		}
		Fout << endl;
		q = q->down;
	}
	Fout.close();
	system("pause");
	return 0;
}