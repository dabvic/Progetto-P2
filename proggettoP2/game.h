#ifndef GAME_H
#define GAME_H

#include <QtWidgets>
#include <QWidget>
#include <QGraphicsScene>

#include <QPushButton>
#include "Player.h"
#include "Score.h"
#include "Health.h"
#include "Spawner.h"
#include <scoremanager.h>
#include <users.h>

#include <fstream>

#include <QInputDialog>

#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QMediaPlayer>
#include <QBrush>
#include <QImage>

class Spawner;
class Game: public QGraphicsView{
    Q_OBJECT// macro per utilizzare gli slot
public:
    Game();
    Player * player;
    Score * score;
    Health * health;
    Spawner *spawner;
    ScoreManager* scoreManager;
    UserDB* usersdb;


    static QTimer* timerGeneral;
    QGraphicsScene * scene;
    QPushButton *start;
    QGraphicsTextItem* go;
    void GameOver();
private slots:
    void StartGame();
    void SignIn();
    void GuestUser();
    void SignUp();
    void NewUser();
    void ClearUsers();
    void ClearScores();


private:
   unsigned int bestScore;
   std:: string user;

   void SetupScene();
   void SetupScoreDialog();
   void SetupStartButton();
   void SetupUserForm();
   void SetupAdminForm();

   bool logged;

   QDialog* scoreDialog;
   QDialog* loginDialog;
   QDialog* signUpDialog;
   QDialog* adminDialog;

};

#endif // GAME_H

