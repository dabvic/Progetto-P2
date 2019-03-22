#include <scoremanager.h>


ScoreManager::ScoreEntry::ScoreEntry(int s, QString p, ScoreEntry* pr, ScoreEntry* n):score(s), playerName(p), next(n), prev(pr)
{
}


//distruzione per non lasciare garbage
ScoreManager::ScoreEntry::~ScoreEntry()
{
    qDebug("deleted");
    if(prev)
    {
        prev->next=0;
        prev=0;
    }
    if(next==0)
    {
    }
     else
       delete next;
}


//metodo che serve per mantenere solo gli ultimi 10 record, ammount serve nel caso in cui si vogliano un altro numero di elementi
void ScoreManager::ScoreEntry::PopLast(unsigned int ammount)
{
    ScoreEntry* aux= this;
    while(ammount!=0)
    {
        ammount--;
        if(aux==0)
            return;
        else
            aux=aux->next;
    }

    if(aux==0)
        return;
    else
        delete aux;

}


//metodo che legge dal file xml i punteggi registrati e crea il contenitore necessario a rappresentarli
void ScoreManager::LoadFromDisk()
{
    ScoreEntry* aux= first;
    QXmlStreamReader reader;
    QFile file("Scores.xml");
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        reader.setDevice(&file);

            //reader.readNext();

            reader.readNextStartElement();

            reader.readNextStartElement();

            while (!reader.atEnd())
            {

                QString playerName, stringScore;
                unsigned int score;
                bool openTag=false;

                while(!reader.atEnd())
                {
                    if(reader.isStartElement())
                    {
                        if(reader.name() == "Scores")
                            reader.readNext();
                        else if(reader.name() == "Score")
                        {
                            openTag = true;

                            while(!reader.atEnd())
                            {
                                if(reader.isEndElement())
                                {
                                    if(openTag)
                                    {
                                        if(first==NULL)
                                        {
                                            first= new ScoreEntry(score, playerName);
                                            aux=first;
                                        }
                                        else
                                        {
                                            aux->next= new ScoreEntry(score, playerName, aux);
                                            aux= aux->next;
                                        }
                                        openTag = false;
                                    }
                                    reader.readNext();
                                    break;
                                }
                                else if(reader.isCharacters())
                                    reader.readNext();
                                else if(reader.isStartElement())
                                {
                                    if(reader.name() == "Name")
                                        playerName = reader.readElementText();
                                    if(reader.name() == "score")
                                    {
                                        stringScore = reader.readElementText();
                                        score = stringScore.toInt();
                                    }
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
    first->PopLast();

}


//metodo che salva il contenuto del contenitore su un file xml
void ScoreManager::SaveOnDisk() const
{

    QFile file("Scores.xml");
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    ScoreEntry* aux= first;

    xmlWriter.writeStartElement("Scores");
    first->PopLast();
    while(aux)
    {
        xmlWriter.writeStartElement("Score");
        xmlWriter.writeTextElement("Name", aux->playerName);
        xmlWriter.writeTextElement("score", QString::number(aux->score));
        xmlWriter.writeEndElement();
        aux=aux->next;
    }


    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
}

ScoreManager::ScoreManager(): changed(false), numberOfSaves(10)
{
    LoadFromDisk();//leggo dal db alla creazione del modulo ScoreManager
}

ScoreManager::~ScoreManager()
{

    if(changed)//salvo sul disco all'uscita
        SaveOnDisk();
   delete first;

}


//il metodo aggiunge il nuovo punteggio nel caso in cui rientri tra i primi dieci
void ScoreManager::AddNew(unsigned int x, QString n)
{
    qDebug("added");

    if(first== NULL)
    {
        first= new ScoreEntry(x, n);
        changed=true;
        SaveOnDisk();
        return;
    }
    ScoreEntry* aux=first;
    int i=0;
    while(i<numberOfSaves)
    {
        if(x>aux->score)
        {
            ScoreEntry* newOne= new ScoreEntry(x, n, aux->prev, aux);
            if(aux->prev)
                aux->prev->next=newOne;
            else
                first=newOne;

            aux->prev=newOne;
            SaveOnDisk();// salvataggio automaotico nel momento in cui viene modificato
            return;
        }
        i++;

        if(aux->next)
        {
            aux=aux->next;
        }
        else
        {
            if(i<numberOfSaves)
            {
                aux->next= new ScoreEntry(x, n, aux);
                SaveOnDisk();
                return;
            }
        }
    }
}


//ritorno la posizione del punteggio in classifica
int ScoreManager::CheckScore(unsigned int x) const
{
    ScoreEntry* aux=first;
    int i=0;
    while(aux)
    {
        if(x>aux->score)
            return i;
        else
            i++;
    }
    return i;
}

//ritorna la dimensione della classifica che verra' salvata sul disco
unsigned int ScoreManager::getNumberOfSaves() const
{
    return numberOfSaves;
}

//ritorna una lista di score entri in ordine decrescente, adl piu' altro al piu' basso
list<ScoreManager::ScoreEntry *> ScoreManager::getValues() const
{
    ScoreEntry* aux= first;
    list<ScoreEntry*> ris;
    while(aux)
    {
        ris.push_back(aux);
        aux=aux->next;
    }
    return ris;
}

