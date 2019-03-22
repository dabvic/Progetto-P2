#include <users.h>
QString User::getNickName() const
{
    return nickname;
}

QString User::getPassword() const
{
    return password;
}

void User::setPassword(QString o, QString n)
{
    if(password==o)
        password=n;
}

User::User(QString n, QString p):nickname(n), password(p)
{}

User::~User()
{

}
//svuota il DB degli utenti
void Admin::ClearUsers() const
{

   usersDB->users.clear();
   usersDB->SaveUserOnDisk();
}

//svuota il DB delle ScoreEntry
void Admin::ClearScores() const
{
    qDebug("enter");
    if(scoreManager->first!=0)
    {
            qDebug("not empty");
        delete scoreManager->first;
            scoreManager->first=0;
            scoreManager->SaveOnDisk();
    }
       qDebug("empty");


}


//rimuove l'utente di nome s
void Admin::RemoveUser(QString s) const
{
    if(usersDB== NULL)
        return;
    else
    {
        for(std::list<User>::iterator it = usersDB->users.begin() ; it != usersDB->users.end(); ++it)
        {
            if(it->getNickName()== s)
            {
                usersDB->users.erase(it);
                --it;
            }
        }
    }
}


//aggiunge lo score manager da gestire al modulo admin
void Admin::setScoreManager(ScoreManager * sm)
{
    scoreManager= sm;
}

Admin::Admin(QString n, QString p, UserDB * db):User(n, p), usersDB(db)
{

}

//legge dal disco al momento della creazione
UserDB::UserDB()
{
    LoadUsersFromDisk();
}


//ritorna true se l'utente esiste e la password p corrisponde a quella registrata nel DB
bool UserDB::Login(QString n, QString p)
{

    if(n=="admin" && p=="admin")
    {
        currentUser= new Admin(n, p, this);
        return true;
    }

    for(std::list<User>::const_iterator it = users.begin() ; it != users.end(); ++it)
    {

        if(it->getNickName()== n && it->getPassword()==p)
        {
            currentUser=&(*it);
            qDebug("loged");
            return true;
        }
    }
    return false;
}


//ritorna false se un utente con l'username n e' gia' registrato nel sistema, altrimenti registra un nuovo utete di nome n e password p e ritorna true
bool UserDB::SignUp(QString n, QString p)
{


    for(std::list<User>::const_iterator it = users.begin() ; it != users.end(); ++it)
    {
        if(it->getNickName()== n)
        {
            return false;
        }
    }
    users.push_back(User(n, p));
    SaveUserOnDisk();//salvataggio automatico nel momento in cui il db viene modificato
    return true;
}


//metodo che legge il file XML e aggiunge al contenitore del DB gli utenti creati
UserDB::LoadUsersFromDisk()
{
    QXmlStreamReader reader;
    QFile file("Users.xml");
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        reader.setDevice(&file);

            //reader.readNext();

            reader.readNextStartElement();

            reader.readNextStartElement();

            while (!reader.atEnd())
            {
                QString playerName, password;
                bool openTag=false;

                while(!reader.atEnd())
                {
                    if(reader.isStartElement())
                    {
                        if(reader.name() == "Users")
                            reader.readNext();
                        else if(reader.name() == "User")
                        {
                            openTag = true;

                            while(!reader.atEnd())
                            {
                                if(reader.isEndElement())
                                {
                                    if(openTag)
                                    {
                                        users.push_back(User(playerName, password));
                                        openTag = false;
                                    }
                                    reader.readNext();
                                    break;
                                }
                                else if(reader.isCharacters())
                                    reader.readNext();
                                else if(reader.isStartElement())
                                {
                                    if(reader.name() == "username")
                                        playerName = reader.readElementText();
                                    if(reader.name() == "password")
                                        password = reader.readElementText();
                                    reader.readNext();
                                }
                                else
                                    reader.readNext();
                            }
                        }
                    }
                    else
                        reader.readNext();
                }
            }
        }
    file.close();
}
//salva sul file XMl gli utenti e le loro relative password
UserDB::SaveUserOnDisk()
{
    QFile file("Users.xml");
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("Users");

    for(list<User>::const_iterator it= users.begin(); it!=users.end(); ++it)
    {
        xmlWriter.writeStartElement("User");
        xmlWriter.writeTextElement("username", it->getNickName());
        xmlWriter.writeTextElement("password", it->getPassword());
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
}
