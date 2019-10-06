#include <iostream>
#include <string>
using namespace std;

enum CallType {
	VOICE, TEXT
};

class Medium
{
public:
	Medium(string id) { m_id = id; }
	virtual ~Medium() {}
	virtual string connect() const = 0;
	virtual string transmit(string msg) const { return "text: " + msg; };
	string id() const { return m_id; }
private:
	string m_id;
};


class TwitterAccount : public Medium
{
public:
	TwitterAccount(string id):Medium(id) {}
	virtual string connect() const { return "Tweet"; }
	virtual ~TwitterAccount() { cout << "Destroying the Twitter account " << Medium::id() << "." << endl; }
};

class Phone : public Medium
{
public:
	Phone(string num, CallType type) :Medium(num) { if (type == VOICE) m_type = "voice: "; else m_type = "text: "; }

	virtual string connect() const { return "Call"; }
	virtual string transmit(string msg) const { return m_type + msg;}
	virtual ~Phone() { cout << "Destroying the phone " << Medium::id() << "." << endl; }
private:
	string m_type;
};


class EmailAccount : public Medium
{
public:
	EmailAccount(string id):Medium(id){}
	virtual string connect() const { return "Email"; }
	virtual ~EmailAccount() { cout << "Destroying the email account " << Medium::id() << "." << endl; }
};


void send(const Medium* m, string msg)
{
	cout << m->connect() << " using id " << m->id()
		<< ", sending " << m->transmit(msg) << endl;
}

