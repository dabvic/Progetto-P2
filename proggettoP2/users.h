#ifndef USERS_H
#define USERS_H
#include <QString>
#include <list>
#include <QXmlStreamReader>
#include <QFile>
#include <scoremanager.h>


using std::list;

class User{
private:
    QString nickname, password;
public:
    QString getNickName() const;
    QString getPassword() const;
    void setPassword(QString, QString); //old pass, new pass
    User(QString, QString);
    virtual ~User();

};

class UserDB;

class Admin: public User{
private:
    UserDB* usersDB;
    ScoreManager* scoreManager;

public:
    void ClearUsers() const;
    void ClearScores() const;
    void RemoveUser(QString) const;
    void RemoveUser(User*) const;
    void setScoreManager(ScoreManager*);

    Admin(QString, QString, UserDB*);
};

class UserDB{
    friend class Admin;
private:
    list<User> users;
    LoadUsersFromDisk();
    SaveUserOnDisk();
public:
    const User* currentUser;
    bool Login(QString, QString);
    bool SignUp(QString, QString);

    UserDB();

};

#endif // USERS_H
