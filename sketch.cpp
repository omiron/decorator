/*keeps a generic data member */
class DataMember
{
    public:
        void *data;
        std::string data_type;//keeps the type of data(like "int" or "MyClass")
};

/*the dynamic object. */
class DynObject
{
    //map<name of the member, DataMember
    std::map<std::string, DataMember> members
    public:
        //register a new data member to DynObject
        bool add(void* _data, char* _data_type, char *member_name);
        //return the DataMember corespunding to member_name
        DataMember* call(char *member_name);
};

bool DynObject::add(void* _data, char* _data_type, char *member_name)
{
    //add a new member to the members
    //return true if success else return false
    DataMember new_member;
    new_member.data = _data;
    new_member.data_type = _data_type;
    return members.insert(std::pair<std::string, DataMember>(member_name, new_member));
}


DataMember* DynObject::call(char *_name)
{
    return members.at(_name)
}


int main()
{
    DynObject dyObj;
    int intMember = 1 
    MyClass myclassMember(12, "heigh");

    //register new members in dynObj
    dynObj.add((void *)&intMember, "int", "intMember");
    dynObj.add((void *)&myClassMember, "MyClass", "myClassMember");

    //Now use the data members
    try
    {
        DataMember dm = dynObj.call(dynamic_choose);
        switch(dynamic_choose):
        {
            case "int": &(static_cast<*int>)(dm->data) = 7;
            case "MyClass":&(dynamic_cast<*MyClass>)(dm->data) = MyClass(32, "age"); 
        }
        
    }
    catch(exception &e)
    {
        ......
    }
}
