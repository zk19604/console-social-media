
#include <iostream>
#include <fstream>
using namespace std;
class Helper
{
public:
    static int mylength(char *str)
    {
        int i = 0;
        while (str[i] != '\0')
            i++;
        return i;
    }
    static void copystring(char *&arr, char *str)
    {
        int i;
        for (i = 0; str[i] != '\0'; i++)
        {
            arr[i] = str[i];
        }
        arr[i] = '\0';
    }
    static int mylength(const char *str)
    {
        int i = 0;
        while (str[i] != '\0')
            i++;
        return i;
    }
    static void copystring(char *&arr, const char *str)
    {
        int i;
        for (i = 0; str[i] != '\0'; i++)
        {
            arr[i] = str[i];
        }
        arr[i] = '\0';
    }
    static int mycompare(char *str1, char *str2)
    {
        while (*str1 && *str2 && *str1 == *str2)
        {
            ++str1;
            ++str2;
        }
        return (*str1 - *str2);
    }
    static int mycompare(char *str1, const char str2[])
    {
        while (*str1 && *str2 && *str1 == *str2)
        {
            ++str1;
            ++str2;
        }

        return (*str1 - *str2);
    }
    static void GetStringFromBuffer(char *&str, char *temp)
    {
        int lenstr = Helper::mylength(temp);
        str = new char[lenstr + 1];
        Helper::copystring(str, temp);
    }
    static void GetStringFromBuffer(char *&str, const char *temp)
    {
        int lenstr = Helper::mylength(temp);
        str = new char[lenstr + 1];
        Helper::copystring(str, temp);
    }
};
class Date
{
    int day;
    int month;
    int year;

public:
    Date()
    {
        day = 0;
        month = 0;
        year = 0;
    }
    Date(int d, int m, int y)
    {
        day = d;
        month = m;
        year = y;
    }
    void ReadFromFile(istream &fin)
    {
        fin >> day;
        fin >> month;
        fin >> year;
    }
    void printspecific()
    {
        cout << day << "/" << month << "/" << year << endl;
    }
    int check(Date date)
    {
        int difference;
        difference = date.year - year;
        if (difference == 0)
        {
            difference = date.month - month;
            if (difference == 0)
            {
                difference = date.day - day;
                return difference;
            }
            difference = 30 * difference;
            return difference;
        }
        difference = 365 * difference;
        return difference;
    }
    static bool day2limit(Date current, Date date)
    {
        int difference = date.check(current);
        if (difference <= 2 && difference >= 0)
            return true;
        else
            return false;
    }
    int GetDay()
    {
        return day;
    }
    int GetMonth()
    {
        return month;
    }
    int GetYear()
    {
        return year;
    }
};
class Post;

class Object
{
protected:
    char *ID;
    Post **Timeline;
    int postline = 0;

public:
    Object()
    {
        ID = nullptr;
        Timeline = nullptr;
    }
    virtual void ViewTimeline(Date current, bool memory = false)
    {
        cout << "object timeline with date ";
    }
    virtual void ViewTimeline()
    {
        cout << "object timeline";
    }
    virtual void printspecific()
    {
        cout << "object print specific";
    }
    void SetToTimeline(Post *pagpos)
    {
        if (postline == 0)
        {
            Timeline = new Post *[1];
            Timeline[postline] = pagpos;
        }
        else
        {
            Post **temp = new Post *[postline + 1];
            for (int i = 0; i < postline; i++)
                temp[i] = Timeline[i];
            temp[postline] = pagpos;
            delete[] Timeline;
            Timeline = temp;
        }
        postline++;
    }
    char *GetID()
    {
        return ID;
    }
    virtual char *GETFNAME()
    {
        cout << "object virtual" << endl;
        return 0;
    }
    virtual char *GETLNAME()
    {
        cout << "object virtual" << endl;
        return 0;
    }
    virtual void ViewFriendList()
    {
        cout << "object view friendlist" << endl;
    }
    virtual void ViewLikedPages()
    {
        cout << "object view like pages " << endl;
    }
    virtual void ViewHome(Date current)
    {
        cout << "object view home" << endl;
    }
    virtual void ViewTimelineHome(Date current)
    {
        cout << "object view timeline home" << endl;
    }
    void SeeMemory(Date currentdate);
    ~Object()
    {
        if (ID != nullptr)
        {
            delete[] ID;
        }

        if (Timeline != nullptr)
        {
            delete[] Timeline;
        }
    }
};

class Comment
{
    Object *commentedby;
    char *text;
    char *ID;

public:
    Comment()
    {
        commentedby = 0;
        text = 0;
        ID = 0;
    }
    void SetValues(char tempid[], Object *tempby, char temptext[])
    {
        Helper::GetStringFromBuffer(ID, tempid);
        Helper::GetStringFromBuffer(text, temptext);
        commentedby = tempby;
    }
    void printspecific()
    {
        commentedby->printspecific();
        cout << "----" << text;
    }
    ~Comment()
    {

        if (text != nullptr)
            delete[] text;

        if (ID != nullptr)
            delete[] ID;
    }
};
class PostContent
{
public:
    virtual void SetValue()
    {
        cout << "post content set value" << endl;
    }
    virtual void ReadContent(ifstream &fin)
    {
        cout << "post content read content" << endl;
    }
    virtual void printspecific(int current, Date date)
    {
        cout << "post content print specific" << endl;
    }
    virtual void MemoryActivity()
    {
        cout << "post content memory activity";
    }
    virtual ~PostContent()
    {
        // cout << "in post content destructor";
    }
};
class Activity : public PostContent
{
    int type;
    char *value;
    char *text;

public:
    Activity()
    {
        value = 0;
        text = 0;
    }
    void SetValue()
    {
        const char *temp;
        if (type == 1)
        {
            temp = "is feeling";
        }
        else if (type == 2)
        {
            temp = "is thinking about";
        }
        else if (type == 3)
        {
            temp = "is making";
        }
        else if (type == 4)
        {
            temp = "is celebrating";
        }
        else
        {
            temp = "shared";
        }
        Helper::GetStringFromBuffer(value, temp);
    }
    void ReadContent(ifstream &fin)
    {
        fin >> type;
        SetValue();
        char temp[80];
        fin.getline(temp, 80);
        Helper::GetStringFromBuffer(text, temp);
    }
    void printspecific(int current, Date user)
    {

        cout << value << " " << text << " ";
        if (current == 0)
            cout << "\t(1h)" << endl;
        else if (current == 1)
            cout << "\t(1d)" << endl;
        else if (current == 2)
            cout << "\t(2d)" << endl;
        else
        {
            cout << "\t";
            user.printspecific();
        }
    }
    void MemoryActivity()
    {
        char arr[] = " a memory";
        Helper::GetStringFromBuffer(text, arr);
        type = 10;
        SetValue();
    }
    ~Activity()
    {
        if (value != nullptr)
            delete[] value;

        if (text != nullptr)
            delete[] text;
    }
};
class Post
{
private:
    char *id;
    Date date;
    char *text;
    Comment **comments;
    int tcom = 0;
    PostContent *content;

public:
    Object *sharedby;
    Object **likedby = new Object *[10];
    int likes = 0;

public:
    Post()
    {
        id = 0;
        text = 0;
        comments = 0;
        content = 0;
        sharedby = 0;
        for (int i = 0; i < 10; i++)
            likedby[i] = 0;
    }
    void ReadFromFile(istream &fin)
    {
        char temp[80];
        fin >> temp;
        Helper::GetStringFromBuffer(id, temp);
        date.ReadFromFile(fin);
        char str[80];
        fin.getline(str, 80);
        Helper::GetStringFromBuffer(text, str);
    }
    void printspecific(Date current)
    {
        int difference;
        sharedby->printspecific();
        difference = date.check(current);
        if (content != 0)
        {
            cout << " ";
            content->printspecific(difference, date);
        }
        else
        {
            if (difference == 0)
                cout << "\t(1h)";
            else if (difference == 1)
                cout << "\t(1d)";
            else if (difference == 2)
                cout << "\t(2d)";
            else
            {
                cout << "\t";
                date.printspecific();
            }
        }
        cout << endl
             << "--------" << text << endl;

        for (int i = 0; i < tcom; i++)
        {
            cout << "\t";
            comments[i]->printspecific();
            cout << endl;
        }
        cout << endl;
    }
    int GetDay()
    {
        return date.GetDay();
    }
    int GetMonth()
    {
        return date.GetMonth();
    }
    int GetYear()
    {
        return date.GetYear();
    }
    char *GetID()
    {
        return id;
    }
    void AddComment(Comment *ptr)
    {
        if (comments == 0)
        {
            comments = new Comment *(ptr);
        }
        else
        {
            Comment **temp = new Comment *[tcom + 1];
            for (int i = 0; i < tcom; i++)
            {
                temp[i] = comments[i];
            }
            temp[tcom] = ptr;
            delete[] comments;
            comments = temp;
        }
        tcom++;
    }
    void AddContent(PostContent *ptr)
    {
        content = ptr;
    }
    void PrintLikes()
    {
        for (int i = 0; i < likes; i++)
        {
            cout << i + 1 << ". ";
            likedby[i]->printspecific();
            cout << endl;
        }
    }
    void LikePost(Object *rhs)
    {
        if (likes == 0)
        {
            likedby = new Object *(rhs);
        }
        else
        {
            Object **temp = new Object *[likes + 1];
            for (int i = 0; i < likes; i++)
            {
                temp[i] = likedby[i];
            }
            temp[likes] = rhs;
            delete[] likedby;
            likedby = temp;
        }
        likes++;
    }
    bool day2limit(Date current)
    {
        return Date::day2limit(current, date);
    }
    void PostComment(char commenttext[])
    {
        Comment *comment = new Comment();
        char tempid[] = "newid";
        comment->SetValues(tempid, sharedby, commenttext);
        AddComment(comment);
    }
    void ShareMemory(Post *&post, Object *&current, Date currentdate, char newtext[])
    {
        this->SetOriginalPost(post);
        sharedby = current;
        date = currentdate;
        char idtext[] = "newmemoryid";
        Helper::GetStringFromBuffer(id, idtext);
        Helper::GetStringFromBuffer(text, newtext);
        current->SetToTimeline(this);
        content = new Activity();
        content->MemoryActivity();
    }
    virtual void SetOriginalPost(Post *&ptr)
    {
        cout << "post original post function" << endl;
    }
    virtual void ViewOriginalPost(Date currentdate)
    {
    }
    virtual ~Post()
    {
        if (id != nullptr)
        {
            delete[] id;
        }
        if (text != nullptr)
        {
            delete[] text;
        }
        if (comments != nullptr)
            for (int i = 0; i < tcom; i++)
            {

                delete comments[i];
            }
        delete[] comments;

        if (content != nullptr)
        {
            delete content;
        }

        if (likedby != nullptr)
        {
            delete[] likedby;
        }
    }
};

class Memory : public Post
{
    Post *originalpost;

public:
    Memory()
    {
        originalpost = 0;
    }
    void SetOriginalPost(Post *&ptr)
    {
        originalpost = ptr;
    }
    void ViewOriginalPost(Date currentdate)
    {
        int difference;
        if (originalpost->GetDay() == currentdate.GetDay())
        {
            if (originalpost->GetMonth() == currentdate.GetMonth())
            {
                if (originalpost->GetYear() == currentdate.GetYear())
                {

                    cout << endl
                         << "\t----------"
                         << "Today"
                         << "----------" << endl;
                }
                else
                {
                    cout << endl
                         << "\t----------"
                         << currentdate.GetYear() - originalpost->GetYear() << " years ago"
                                                                               "----------"
                         << endl;
                }
            }
            else
            {
                difference = currentdate.GetMonth() - originalpost->GetMonth();
                if (difference < 0)
                    difference = 12 + difference;
                cout << endl
                     << "\t----------"
                     << difference << " months ago"
                     << "----------" << endl;
            }
            cout << endl;
            originalpost->printspecific(currentdate);
        }
    }
    ~Memory()
    {}
};
class Page : public Object
{

    char *Title;

public:
    Page()
    {
        Title = 0;
    }
    void ReadDataFromFile(ifstream &fin)
    {
        char tempname[50];
        fin >> tempname;
        Helper::GetStringFromBuffer(ID, tempname);
        fin.ignore();
        fin.getline(tempname, 50);
        Helper::GetStringFromBuffer(Title, tempname);
    }
    char *GETID()
    {
        return ID;
    }
    char *GETTITLE()
    {
        return Title;
    }
    void printspecific()
    {
        cout << Title;
    }
    void ViewTimeline(Date current, bool memory = false)
    {

        // if (postline == 0)
        //     cout << Title<<" has no Posts Shared " << endl;
        // else
        for (int i = 0; i < postline; i++)
        {

            cout << endl;
            Timeline[i]->printspecific(current);
        }
    }
    void ViewTimelineHome(Date current)
    {

        // if (postline == 0)
        //     cout << Fname<<" "<<Lname<<" has no Posts Shared " << endl;
        // else
        for (int i = 0; i < postline; i++)
        {
            if (Timeline[i]->day2limit(current))
            {
                cout << endl;
                Timeline[i]->printspecific(current);
            }
        }
    }
    char *GETFNAME()
    {
        return Title;
    }
    ~Page()
    {
        if (Title != nullptr)
            delete[] Title;
    }
};
class User : public Object
{
    char *Fname;
    char *Lname;
    User **FriendList; // null or 10 pointers max
    Page **LikedPages; // null or 10 pointers max
    int friendnum = 0;
    int pagenum = 0;

public:
    User()

    {
        Fname = 0;
        Lname = 0;
        FriendList = new User *[10];
        for (int i = 0; i < 10; i++)
            FriendList[i] = 0;
        LikedPages = new Page *[10];
        for (int i = 0; i < 10; i++)
            LikedPages[i] = 0;
    }
    char *GETID()
    {
        return ID;
    }
    char *GETFNAME()
    {
        return Fname;
    }
    char *GETLNAME()
    {
        return Lname;
    }
    int GetFriendNum()
    {
        return friendnum;
    }
    void AddFriend(User *&rhs)
    {
        User **temp;
        temp = new User *[friendnum + 1];
        for (int i = 0; i < friendnum; i++)
        {
            temp[i] = FriendList[i];
        }
        temp[friendnum] = rhs;
        delete[] FriendList;
        FriendList = temp;
        friendnum++;
    }
    void ReadDataFromFile(ifstream &fin)
    {
        char tempname[20];
        fin >> tempname;
        Helper::GetStringFromBuffer(ID, tempname);
        fin.ignore();
        fin >> tempname;
        Helper::GetStringFromBuffer(Fname, tempname);
        fin.ignore();
        fin >> tempname;
        Helper::GetStringFromBuffer(Lname, tempname);
    }
    void LikePage(Page *&rhs)
    {
        Page **temp;
        temp = new Page *[pagenum + 1];
        for (int i = 0; i < pagenum; i++)
        {
            temp[i] = LikedPages[i];
        }
        temp[pagenum] = rhs;
        delete[] LikedPages;
        LikedPages = temp;
        pagenum++;
    }
    void ViewFriendList()
    {
        cout << "Friend List : " << endl;
        if (friendnum != 0)
            for (int i = 0; i < friendnum; i++)
            {
                cout << i + 1 << ". ";
                FriendList[i]->printspecific();
                cout << endl;
            }
        else
            cout << "NO FRIENDS " << endl;
    }
    void ViewLikedPages()
    {
        cout << "Page List : " << endl;
        if (pagenum != 0)
            for (int i = 0; i < pagenum; i++)
            {
                cout << i + 1 << ". ";
                LikedPages[i]->printspecific();
                cout << endl;
            }

        else
            cout << "NO LIKED PAGES " << endl;
    }
    void printspecific()
    {
        cout << Fname << " " << Lname;
    }
    void ViewTimelineHome(Date current)
    {
        for (int i = 0; i < postline; i++)
        {
            if (Timeline[i]->day2limit(current))
            {
                cout << endl;
                Timeline[i]->printspecific(current);
            }
        }
    }
    void ViewHome(Date current)
    {
        ViewTimelineHome(current);
        for (int i = 0; i < friendnum; i++)
        {
            FriendList[i]->ViewTimelineHome(current);
        }
        for (int i = 0; i < pagenum; i++)
        {
            LikedPages[i]->ViewTimelineHome(current);
        }
    }
    void ViewTimeline(Date current, bool memory = false)
    {

        if (postline == 0)
            cout << Fname << " " << Lname << " has no Posts Shared " << endl;
        else
            for (int i = 0; i < postline; i++)
            {

                cout << endl;
                if (!memory)
                    Timeline[i]->printspecific(current);
                else
                {
                    Timeline[i]->printspecific(current);
                    Timeline[i]->ViewOriginalPost(current);
                }
            }
    }
    ~User()
    {
        if (Fname != nullptr)
            delete[] Fname;
        if (Fname != nullptr)
            delete[] Lname;

        if (FriendList != nullptr)
            delete[] FriendList;

        if (LikedPages != nullptr)
            delete[] LikedPages;
    }
};

class Controller
{

    User **AllUsers;
    Page **AllPages;
    static int totaluser;
    static int totalpages;
    static int totalposts;
    Post **AllPosts;

public:
    Controller()
    {
        AllUsers = nullptr;
        AllPages = nullptr;
        AllPosts = nullptr;
    }
    User *SearchUserByID(char *id)
    {
        for (int j = 0; j < totaluser; j++)
        {
            if (Helper::mycompare(id, AllUsers[j]->GETID()) == 0)
            {
                return (AllUsers[j]);
            }
        }
        return nullptr;
    }
    Page *SearchPageByID(char *id)
    {
        for (int j = 0; j < totalpages; j++)
        {
            if (Helper::mycompare(id, AllPages[j]->GETID()) == 0)
            {
                return (AllPages[j]);
            }
        }
        return nullptr;
    }
    void LoadAllUser()
    {
        ifstream fin("users.txt");
        if (!fin.is_open())
        {
            cout << "Error opening file!" << endl;
            return;
        }
        fin >> totaluser;
        AllUsers = new User *[totaluser];
        for (int i = 0; i < totaluser; i++)
        {

            AllUsers[i] = new User();
            AllUsers[i]->ReadDataFromFile(fin);
        }
    }
    void LoadAllPages()
    {
        ifstream fin("pages.txt");
        if (!fin.is_open())
        {
            cout << "Error opening file!" << endl;
            return;
        }
        fin >> totalpages;
        AllPages = new Page *[totalpages];
        for (int i = 0; i < totalpages; i++)
        {

            AllPages[i] = new Page();
            AllPages[i]->ReadDataFromFile(fin);
        }
    }
    void LinkUsersAndPages()
    {
        ifstream fin("friends.txt");
        if (!fin.is_open())
        {
            cout << "Error opening file!" << endl;
            return;
        }
        char userid[5];
        while (fin >> userid)
        {
            if (Helper::mycompare(userid, "-1") == 0)
            {
                break;
            }
            for (int i = 0; i < totaluser; i++)
            {
                if (Helper::mycompare(userid, AllUsers[i]->GETID()) == 0)
                {
                    char temp[5];

                    while (fin >> temp)
                    {
                        if (Helper::mycompare(temp, "-1") == 0)
                        {
                            break;
                        }
                        User *temppp = SearchUserByID(temp);
                        if (temppp)
                            AllUsers[i]->AddFriend(temppp);
                    }
                    while (fin >> temp)
                    {
                        if (Helper::mycompare(temp, "-1") == 0)
                        {
                            break; // Exit loop if sentinel value is encountered
                        }
                        Page *temppp = SearchPageByID(temp);
                        if (temppp)
                            AllUsers[i]->LikePage(temppp);
                    }
                    // cout << "User : ";
                    // AllUsers[i]->printspecific();
                    // AllUsers[i]->ViewFriendList();
                    // AllUsers[i]->ViewLikedPages();
                    // cout << endl;
                    break;
                }
            }
            fin.ignore();
        }
    }
    void LoadData()
    {
        LoadAllUser(); // Keep it easily configurable
        LoadAllPages();
        LinkUsersAndPages();
        LoadAllPosts();
        ReadAllComments();
        ReadPostContent();
    }
    void PrintAll()
    {
        cout << "ALL USERS : " << endl;
        for (int i = 0; i < totaluser; i++)
        {
            AllUsers[i]->printspecific();
        }
        cout << "ALL PAGES : " << endl;
        for (int i = 0; i < totalpages; i++)
        {
            AllPages[i]->printspecific();
        }
    }
    void LoadAllPosts()
    {
        ifstream fin("post.txt");
        if (!fin.is_open())
        {
            cout << "Error opening file!" << endl;
            return;
        }
        fin >> totalposts;
        AllPosts = new Post *[totalposts];
        int totallikes = 0;
        for (int i = 0; i < totalposts; i++)
        {
            AllPosts[i] = new Post();
            AllPosts[i]->ReadFromFile(fin);
            char temp[5];
            fin >> temp;
            if (temp[0] == 'u')
            {
                AllPosts[i]->sharedby = new User();
                User *tempp = SearchUserByID(temp);
                AllPosts[i]->sharedby = tempp;
            }
            else
            {
                AllPosts[i]->sharedby = new Page();
                Page *tempp = SearchPageByID(temp);
                AllPosts[i]->sharedby = tempp;
            }
            AllPosts[i]->sharedby->SetToTimeline(AllPosts[i]);
            totallikes = 0;
            while (fin >> temp, Helper::mycompare(temp, "-1") != 0)
            {

                if (totallikes == 0)
                {
                    if (temp[0] = 'u')
                    {

                        User *tempp = SearchUserByID(temp);
                        AllPosts[i]->likedby[0] = new User();
                        AllPosts[i]->likedby[0] = tempp;
                    }
                    else
                    {
                        AllPosts[i]->likedby[0] = new Page();
                        Page *tempp = SearchPageByID(temp);
                        AllPosts[i]->likedby[0] = tempp;
                    }
                }
                else
                {
                    Object **temppp = new Object *[totallikes + 1];
                    for (int j = 0; j < totallikes; j++)
                    {
                        temppp[j] = AllPosts[i]->likedby[j];
                    }
                    if (temp[0] = 'u')
                    {
                        temppp[totallikes] = new User();
                        temppp[totallikes] = SearchUserByID(temp);
                    }
                    else
                    {
                        temppp[totallikes] = new Page();
                        temppp[totallikes] = SearchPageByID(temp);
                    }
                    delete[] AllPosts[i]->likedby;
                    AllPosts[i]->likedby = temppp;
                }
                totallikes++;
            }
            AllPosts[i]->likes = totallikes;
        }
    }
    Post *SearchPostbyID(char *tempid)
    {
        for (int i = 0; i < totalposts; i++)
        {
            if (Helper::mycompare(AllPosts[i]->GetID(), tempid) == 0)
            {
                return AllPosts[i];
            }
        }
        return nullptr;
    }
    void ReadAllComments()
    {
        ifstream fin("comments.txt");
        if (!fin.is_open())
        {
            cout << "Error opening file!" << endl;
            return;
        }
        int totalcomments = 0;
        fin >> totalcomments;
        for (int i = 0; i < totalcomments; i++)
        {
            Comment *ptr = new Comment;
            char comid[20];
            fin >> comid;
            char tempid[20];
            fin >> tempid;
            Post *pptr = SearchPostbyID(tempid);
            fin >> tempid;
            char temptext[80];
            fin.getline(temptext, 80);
            Object *tempptr;

            tempptr = SearchUserByID(tempid);
            if (tempptr == 0)
                tempptr = SearchPageByID(tempid);
            ptr->SetValues(comid, tempptr, temptext);
            if (pptr != nullptr)
            {
                pptr->AddComment(ptr);
            }
        }
    }
    void ReadPostContent()
    {
        ifstream fin("activity.txt");
        if (!fin.is_open())
        {
            cout << "Error opening file!" << endl;
            return;
        }
        int totalcontent = 0;
        fin >> totalcontent;
        for (int i = 0; i < totalcontent; i++)
        {
            char temp[20];
            fin >> temp;
            PostContent *tempptr = new Activity;
            Post *ptr = SearchPostbyID(temp);
            if (ptr != nullptr)
            {
                ptr->AddContent(tempptr);
            }
            tempptr->ReadContent(fin);
        }
    }
    void ViewTimeline(char *name)
    {
        Object *temp = SearchUserByID(name);
        if (temp == 0)
            temp = SearchPageByID(name);
        temp->ViewTimeline();
    }
    void RunPractice(Date &currentdate, char *runuser)
    {
        cout << endl
             << "--------------------------------------------------------------------------" << endl
             << endl;
        cout << "System Date : ";
        currentdate.printspecific();
        cout << endl
             << "--------------------------------------------------------------------------" << endl
             << endl;
        Object *currentuser = SearchUserByID(runuser);
        if (currentuser == nullptr)
        {
            cout << "User not found\nCant proceed" << endl;
            return;
        }
        currentuser->printspecific();
        cout << " successfully set as current user" << endl;
        cout << endl
             << "--------------------------------------------------------------------------" << endl
             << endl;
        cout << "Command = View Friend List" << endl;
        cout << endl
             << "--------------------------------------------------------------------------" << endl
             << endl;
        currentuser->printspecific();
        cout << " - Friend List" << endl
             << endl;
        currentuser->ViewFriendList();
        cout << endl
             << "--------------------------------------------------------------------------" << endl
             << endl;
        cout << "Command = View Liked Pages" << endl;
        cout << endl
             << "--------------------------------------------------------------------------" << endl
             << endl;
        currentuser->printspecific();
        cout << " - Liked Pages " << endl
             << endl;
        currentuser->ViewLikedPages();
        cout << endl
             << "--------------------------------------------------------------------------" << endl
             << endl;
        cout << "Command = View Timeline" << endl;
        cout << endl
             << "--------------------------------------------------------------------------" << endl
             << endl;
        currentuser->printspecific();
        cout << " - Timeline " << endl;
        currentuser->ViewTimeline(currentdate);
        cout << endl
             << "--------------------------------------------------------------------------" << endl
             << endl;
        cout << "Command = View Likes of Post 5" << endl;
        cout << endl
             << "--------------------------------------------------------------------------" << endl
             << endl;
        cout << "Likes of Post 5 " << endl
             << endl;
        char currentpost[] = "post5";
        Post *temppost = SearchPostbyID(currentpost);
        temppost->PrintLikes();
        cout << endl
             << "--------------------------------------------------------------------------" << endl
             << endl;
        cout << "Command = Like of Post 5" << endl;
        cout << endl
             << "--------------------------------------------------------------------------" << endl
             << endl;
        cout << "Likes of Post 5 " << endl
             << endl;
        temppost->LikePost(currentuser);
        temppost->PrintLikes();
        cout << endl
             << "--------------------------------------------------------------------------" << endl
             << endl;
        cout << "Command = View Page 1" << endl;
        cout << endl
             << "--------------------------------------------------------------------------" << endl
             << endl;
        cout << "Page 1 : " << endl;
        char currentpage[] = "p1";
        Page *temppage = SearchPageByID(currentpage);
        temppage->ViewTimeline(currentdate);
        cout << endl
             << "--------------------------------------------------------------------------" << endl
             << endl;
        cout << "Command = View Home " << endl;
        cout << endl
             << "--------------------------------------------------------------------------" << endl
             << endl;
        currentuser->printspecific();
        cout << " - Home " << endl
             << endl;
        currentuser->ViewHome(currentdate);
        char commenttext[] = "Thanks for the wishes";
        cout << endl
             << "--------------------------------------------------------------------------" << endl
             << endl;
        cout << "Command = Post a comment on post 8  " << commenttext << endl;
        cout << endl
             << "--------------------------------------------------------------------------" << endl
             << endl;
        cout << "View Comments on post 8 " << endl
             << endl;
        char commentpost[] = "post8";
        Post *postcomment = SearchPostbyID(commentpost);
        postcomment->PostComment(commenttext);
        postcomment->printspecific(currentdate);
        cout << endl
             << "--------------------------------------------------------------------------" << endl
             << endl;
        cout << "Command = View Memories  " << endl;
        cout << endl
             << "--------------------------------------------------------------------------" << endl
             << endl;
        currentuser->printspecific();
        cout << " - See your memories ";
        currentdate.printspecific();
        cout << endl
             << endl;
        currentuser->SeeMemory(currentdate);
        cout << endl
             << "--------------------------------------------------------------------------" << endl
             << endl;
        cout << "Command = Share a memory - Post 10 - Never thought I will be a specialist in this field...  " << endl;
        cout << endl
             << "--------------------------------------------------------------------------" << endl
             << endl;
        Memory *memory = new Memory();
        char memorypost[] = "post10";
        char memorytext[] = "Never thought I will be a specialist in this field...";
        Post *post = SearchPostbyID(memorypost);
        memory->ShareMemory(post, currentuser, currentdate, memorytext);
        cout << "Command = View Timeline (with new memory) " << endl;
        cout << endl
             << "--------------------------------------------------------------------------" << endl
             << endl;
        currentuser->printspecific();
        cout << " - Timeline " << endl
             << endl;
        AddMemorytoAllPosts(memory);
        currentuser->ViewTimeline(currentdate, 1);
    }
    void AddMemorytoAllPosts(Memory *&memory)
    {
        Post **temp;
        temp = new Post *[totalposts + 1];
        for (int i = 0; i < totalposts; i++)
        {
            temp[i] = AllPosts[i];
        }
        temp[totalposts] = memory;
        delete[] AllPosts;
        AllPosts = temp;
        totalposts++;
    }
    ~Controller()
    {
        if (AllUsers != nullptr)
        {

            for (int i = 0; i < totaluser; i++)
                delete AllUsers[i];
            delete[] AllUsers;
        }
        if (AllPages != nullptr)
        {
            for (int i = 0; i < totalpages; i++)
                delete AllPages[i];
            delete[] AllPages;
        }
        if (AllPosts != nullptr)
        {
            for (int i = 0; i < totalposts; i++)
                delete AllPosts[i];
            delete[] AllPosts;
        }
    }
};

int Controller::totaluser = 0;
int Controller::totalpages = 0;
int Controller::totalposts = 0;

int main()
{
    {
        Controller mainApp;
        cout << "\033[1;34m";
        mainApp.LoadData();
        Date currentdate(17, 4, 2024);
        char currentuser[] = "u7";
        mainApp.RunPractice(currentdate, currentuser);
    }
}
void Object::SeeMemory(Date currentdate)
{
    cout << "We hope you enjoy looking back and sharing your memories, from the most recent to those long ago." << endl;
    cout << endl;
    cout << "On this day - ";
    currentdate.printspecific();
    int difference;
    for (int i = 0; i < postline; i++)
    {
        if (Timeline[i]->GetDay() == currentdate.GetDay())
        {
            if (Timeline[i]->GetMonth() == currentdate.GetMonth())
            {
                if (Timeline[i]->GetYear() == currentdate.GetYear())
                {

                    cout << endl
                         << "\t----------"
                         << "Today"
                         << "----------" << endl;
                }
                else
                {
                    cout << endl
                         << "\t----------"
                         << currentdate.GetYear() - Timeline[i]->GetYear() << " years ago"
                         << "----------" << endl;
                }
            }
            else
            {
                difference = currentdate.GetMonth() - Timeline[i]->GetMonth();
                if (difference < 0)
                    difference = 12 + difference;
                cout << endl
                     << "\t----------"
                     << difference << " months ago"
                     << "----------" << endl;
            }
            cout << endl;
            Timeline[i]->printspecific(currentdate);
        }
    }
}