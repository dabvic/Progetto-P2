#include "Game.h"


Game::Game(): spawner(0), scoreManager(new ScoreManager()), usersdb(new UserDB())
{
    // all'avvio del gioco che corisponde alla creazione del oggetto game invoco i metodi Setup necessari
      SetupScene();
      SetupScoreDialog();
      SetupStartButton();
/*
    // background music da implementare
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/bgsound.mp3"));
    music->play();
*/
    show();

    SetupUserForm();
}


void Game::GameOver()
{
   //GameOver invocato da una Bomb nel caso in cui il giocatore non ha piu' vita
   timerGeneral->stop(); //fermo il timer, non necessario dato che non si muovono piu' oggeti

   go= new QGraphicsTextItem("Game Over!");// scritta gameOver
   go->setDefaultTextColor(Qt::red);
   go->setFont(QFont("times",30));
   go->setPos(300,200);
   scene->addItem(go);

   //lo spawner non serve piu'
   delete spawner;


   //controllo se l'utente e' loggato, if cretina ma qt ha deciso di dare problemi
   if(usersdb->currentUser==0)
   {
   }
       else
        scoreManager->AddNew(score->GetScore(), usersdb->currentUser->getNickName());//provo ad aggiungere il punteggio del giocatore nel caso in cui esso sia autenticato

   SetupScoreDialog();//visualizzazione dei punteggi

   scoreDialog->show();

   start->setVisible(true);// visualizzo pulsante start per un nuovo gioco

   delete score;// score non serve piu', verra' reinizializzato nella nuova partita

   delete health; // vita non serve piu', verra' reinizializzato nella nuova partita
}

void Game::StartGame()
{
    start->setVisible(false);// nascondo start
    //avvio timer
    timerGeneral->start(20);// avvio timer per i frame
    scene->clear();//Removes and deletes all items from the scene, but otherwise leaves the state of the scene unchanged.

    //int i=bestScore;

    player = new Player();//nuovo giocatore
    player->setPos(300, 410); // player al centro scena
    player->setFlag(QGraphicsItem::ItemIsFocusable);//focus
    player->setFocus();
    scene->addItem(player);


    //inizializzazione elementi necessari al gioco e aggiunta alla scene
    score= new Score();
    scene->addItem(score);
    health = new Health();
    health->setPos(health->x(),health->y()+50);
    scene->addItem(health);
    spawner=new Spawner(scene);
}

void Game::SetupScene()
{
    //set graffico della scene
    scene= new QGraphicsScene();
    // creo la scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600); // 800x600 invece di infinity
    setBackgroundBrush(QBrush(QImage(":/images/background.png")));

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);
}

void Game::SignIn()
{
    //gestione Gui del SignIn con il collegamento al modulo di database

    if(loginDialog->findChild<QLineEdit*>("usernameInput")->text()=="" || loginDialog->findChild<QLineEdit*>("passwordInput")->text()=="")
        return;
    qDebug(loginDialog->findChild<QLineEdit*>("usernameInput")->text().toLatin1().constData());

    if(usersdb->Login(loginDialog->findChild<QLineEdit*>("usernameInput")->text(), loginDialog->findChild<QLineEdit*>("passwordInput")->text()))
    {

        if(dynamic_cast<const Admin*>(usersdb->currentUser))
        {
           dynamic_cast< Admin*>(const_cast<User*>(usersdb->currentUser))->setScoreManager(scoreManager);
           SetupAdminForm();
        }

        loginDialog->hide();
    }

}

void Game::NewUser()
{
     //gestione Gui della registrazione con il collegamento al modulo di database
    if(signUpDialog->findChild<QLineEdit*>("usernameInput")->text()=="" || signUpDialog->findChild<QLineEdit*>("passwordInput")->text()=="")
        return;

     if(signUpDialog->findChild<QLineEdit*>("passwordInput")->text()== signUpDialog->findChild<QLineEdit*>("confirmPasswordInput")->text())
     {
        if(usersdb->SignUp(signUpDialog->findChild<QLineEdit*>("usernameInput")->text(), signUpDialog->findChild<QLineEdit*>("passwordInput")->text()))
        {
            delete signUpDialog;
        }
     }
}

void Game::GuestUser()
{
    // se l'utente e' guest il modulo graffico del login non serve
    delete loginDialog;
}

void Game::ClearUsers()
{
    //invocazione del clearUsers di Admin
   dynamic_cast<const Admin*>(usersdb->currentUser)->ClearUsers();
}

void Game::ClearScores()
{
    //invocazione del clearScores di Admin
   dynamic_cast<const Admin*>(usersdb->currentUser)->ClearScores();
}

//modulo graffico per la registrazione
void Game::SignUp()
{
    signUpDialog = new QDialog();

    QGridLayout* layout= new QGridLayout();
    signUpDialog->setLayout(layout);
    signUpDialog->setModal(true);
    signUpDialog->setWindowTitle("SignUp");

    QLabel* username= new QLabel("username", signUpDialog);
    QLabel* password= new QLabel("password",signUpDialog);
    QLabel* confirmPassword= new QLabel("Confirm Password",signUpDialog);

    QLineEdit* usernameInput= new QLineEdit(signUpDialog);
    usernameInput->setObjectName("usernameInput");
    QLineEdit* passwordInput= new QLineEdit(signUpDialog);
    passwordInput->setObjectName("passwordInput");
    QLineEdit* confirmPasswordInput= new QLineEdit(signUpDialog);
    confirmPasswordInput->setObjectName("confirmPasswordInput");

    QPushButton* signup= new QPushButton();
    signup->setText("Sign Up");

    layout->addWidget(username, 1, 1);
    layout->addWidget(usernameInput, 1, 2);
    layout->addWidget(password, 2, 1);
    layout->addWidget(passwordInput, 2, 2);
    layout->addWidget(confirmPassword, 3, 1);
    layout->addWidget(confirmPasswordInput, 3, 2);

    layout->addWidget(signup, 4, 1);

    connect(signup, SIGNAL (released()), this, SLOT (NewUser()));
    signUpDialog->show();

}


//modulo graffico che rappresenta i punteggi dei giocatori
void Game::SetupScoreDialog()
{

    scoreDialog= new QDialog();
    QGridLayout* layout= new QGridLayout();
    scoreDialog->setLayout(layout);
    scoreDialog->setModal(true);


    list<ScoreManager::ScoreEntry*> ls= scoreManager->getValues();

    int row=0;
    for(std::list<ScoreManager::ScoreEntry*>::iterator it=ls.begin(); it != ls.end(); ++it)
    {
        qDebug("row");
        layout->addWidget(new QLabel(QString::number(row+1), scoreDialog), row, 0);
        layout->addWidget(new QLabel((*it)->playerName, scoreDialog), row, 1);
        layout->addWidget(new QLabel(QString::number((*it)->score), scoreDialog), row, 2);
        row++;
    }
    //nascondo se non ho punteggi
    if(row=0)
        scoreDialog->hide();

}

void Game::SetupStartButton()
{
    start=new QPushButton("start", this);

    // set size and location of the button
      start->setGeometry(350 ,400, 100, 50),
      //QSize(600, 50)));
    connect(start, SIGNAL (released()), this, SLOT (StartGame()));
}

//creo un timer per tutto il gioco
QTimer* Game::timerGeneral = new QTimer();


//modulo graffico per il form iniziale di azioni utente
void Game::SetupUserForm()
{
   loginDialog = new QDialog();

   QGridLayout* layout= new QGridLayout();
   loginDialog->setLayout(layout);
   loginDialog->setModal(true);
   loginDialog->setWindowTitle("Login");

   QLabel* username= new QLabel("username", loginDialog);
   QLabel* password= new QLabel("password",loginDialog);

   QLineEdit* usernameInput= new QLineEdit(loginDialog);
   usernameInput->setObjectName("usernameInput");
   QLineEdit* passwordInput= new QLineEdit(loginDialog);
   passwordInput->setObjectName("passwordInput");

   QPushButton* login= new QPushButton();
   login->setText("Sign In");

   QPushButton* guest= new QPushButton();
   guest->setText("Guest");

   QPushButton* signup= new QPushButton();
   signup->setText("Sign Up");

   layout->addWidget(username, 1, 1);
   layout->addWidget(usernameInput, 1, 2);
   layout->addWidget(password, 2, 1);
   layout->addWidget(passwordInput, 2, 2);

   layout->addWidget(guest, 3, 1);
   layout->addWidget(login, 3, 2);
   layout->addWidget(signup, 4, 1);

   connect(guest, SIGNAL (released()), this, SLOT (GuestUser()));
   connect(login, SIGNAL (released()), this, SLOT (SignIn()));
   connect(signup, SIGNAL (released()), this, SLOT (SignUp()));

   loginDialog->show();

}
//modulo graffico per il form di admin
void Game::SetupAdminForm()
{
   adminDialog = new QDialog();

   QGridLayout* layout= new QGridLayout();
   adminDialog->setLayout(layout);
   adminDialog->setModal(false);
   adminDialog->setWindowTitle("Admin Pannel");

   QPushButton* clearUsers= new QPushButton();
   clearUsers->setText("Clear Users");
   layout->addWidget(clearUsers, 1, 1);

   connect(clearUsers, SIGNAL (released()), this, SLOT (ClearUsers()));


   QPushButton* clearScores= new QPushButton();
   clearScores->setText("Clear Scores");
   layout->addWidget(clearScores, 2, 1);

   connect(clearScores, SIGNAL (released()), this, SLOT (ClearScores()));

   adminDialog->show();

}

