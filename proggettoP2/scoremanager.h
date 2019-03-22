#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H
#include <qstring.h>
#include <list>
#include <QXmlStreamReader>
#include <QFile>
#include <QMap>
#include <list>


using std::list;

class ScoreManager{

    friend class Admin;

public:
    class ScoreEntry{
    public:
       ScoreEntry(int, QString, ScoreEntry* =NULL, ScoreEntry* = NULL);
       ~ScoreEntry();
       QString playerName;
       unsigned int score;
       ScoreEntry* prev;
       ScoreEntry* next;
       void PopLast(unsigned int=10);
    };

    ScoreManager();
    ~ScoreManager();
    void AddNew(unsigned int, QString);
    int CheckScore( unsigned int) const;
    unsigned int getNumberOfSaves() const;
    list<ScoreEntry*> getValues() const;



private:
    bool changed;
    unsigned int numberOfSaves;

    ScoreEntry* first;

    void LoadFromDisk();
    void SaveOnDisk() const;

};

#endif // SCOREMANAGER_H
