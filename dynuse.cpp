#include <string>
#include <map>
#include <iostream>
#include <exception>
#include <typeinfo>

//g++ -o a.out dynuse.cpp
//
using namespace std;

class Member
{
    public:
        void *vptrMember;//can be data member or function member
        string strMemberType;//keeps the type of member
        Member();
        Member(void *, string);
};

Member::Member()
{
    vptrMember = NULL;
};

Member::Member(void *new_member, string member_type)
{
    vptrMember = new_member;
    strMemberType = member_type;
};

/*the dynamic object. */
class DynObject
{
    map<string, Member> members;
    public:
        //registering a new member to DynObject
        void registering_member(void* new_member, string member_type, string member_name);
        //return the Member corespunding to member_name
        Member getting_member(string member_name);
};

void DynObject::registering_member(void* new_member, string member_type, string member_name)
{
    members[member_name] = Member(new_member, member_type); 
};

Member DynObject::getting_member(string member_name)
{
    return members.at(member_name);
};

void print_data_member(Member member)
{
    /*
     One if for each type supported
     TODO:should test on Windows/Mac/... because I'm not sure that types are 
     named the same for all OS
    */
    if (member.strMemberType == "i")
        cout << *(int *) member.vptrMember << endl;
    else if (member.strMemberType == "Ss")
        cout << *(string *) member.vptrMember << endl;
    else
        throw -1;
};

int suma(int first, int second)
{
    return first + second;
};

int main()
{
    DynObject dynObj;
    int age = 7;
    string first_name = "John"; 
    //Playing with data members
    cout << "Registering new int member named \'age\', type: "<< typeid(age).name() << endl;
    dynObj.registering_member((void *)(&age), typeid(age).name(), "age");
    cout << "Registering new string member named \'first_name\', type: "<< typeid(first_name).name() << endl;
    dynObj.registering_member((void *)(&first_name), typeid(first_name).name(), "first_name");
    cout << "Acces data members" << endl;
    try 
    {
        Member dm = dynObj.getting_member("age");
        cout << "getting age ";
        print_data_member(dm);
        dm = dynObj.getting_member("first_name");
        cout << "getting first_name ";
        print_data_member(dm);
    }
    catch(exception &e)
    {
        cout << "Received exception "<< e.what() << endl;
        return -1;
    }
    //Playing with function member
    dynObj.registering_member((void *)(&suma), typeid(&suma).name(), "suma");
    try
    {
        Member member = dynObj.getting_member("suma");
        cout << "use suma ";
        cout << ((int (* )(int, int))member.vptrMember)(32, 3) << endl; 
    }
    catch(exception &e)
    {
        cout << "Received exception "<< e.what() << endl;
        return -1;
    };
    
    return 0; 
}

