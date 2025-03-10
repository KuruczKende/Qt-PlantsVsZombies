//
// Created by sun on 8/26/16.
//

#ifndef PLANTS_VS_ZOMBIES_ZOMBIE_H
#define PLANTS_VS_ZOMBIES_ZOMBIE_H


#include <QtCore>
#include <QtWidgets>
#include <QtMultimedia>
#include "Plant.h"

class MoviePixmapItem;
class GameScene;
class PlantInstance;

class Zombie
{
    Q_DECLARE_TR_FUNCTIONS(Zombie)
public:
    Zombie();
    virtual ~Zombie() {}

    QString eName, cName;

    int width, height;

    int hp, level;
    qreal speed;
    int aKind, attack;
    bool canSelect, canDisplay;

    QString cardGif, staticGif, normalGif, attackGif, lostHeadGif,
            lostHeadAttackGif, headGif, dieGif, boomDieGif, standGif;

    int beAttackedPointL, beAttackedPointR;
    int breakPoint, sunNum;
    qreal coolTime;

    virtual bool canPass(int row) const;
    void update();

    GameScene *scene;
};

class Zombie1: public Zombie
{
    Q_DECLARE_TR_FUNCTIONS(Zombie1)
public:
    Zombie1();
};

class Zombie2: public Zombie1
{
    Q_DECLARE_TR_FUNCTIONS(Zombie2)
public:
    Zombie2();
};

class Zombie3: public Zombie1
{
    Q_DECLARE_TR_FUNCTIONS(Zombie3)
public:
    Zombie3();
};

class FlagZombie: public Zombie1
{
    Q_DECLARE_TR_FUNCTIONS(FlagZombie)
public:
    FlagZombie();
};

class ZombieInstance
{
public:
    ZombieInstance(const Zombie *zombie);
    virtual ~ZombieInstance();

    virtual void birth(int row);
    virtual void checkActs();
    virtual void judgeAttack();
    virtual void normalAttack(PlantInstance *plant);
    virtual void crushDie();
    virtual void getPea(int attack, int direction);
    virtual void getSnowPea(int attack, int direction);
    virtual void getFirePea(int attack, int direction);
    virtual void getHit(int attack);
    virtual void autoReduceHp();
    virtual void normalDie();
    virtual void playNormalballAudio();
    virtual void playSlowballAudio();
    virtual void playFireballAudio();
    virtual QPointF getShadowPos();
    virtual QPointF getDieingHeadPos();
    virtual bool getCrushed(PlantInstance *instance);

    QUuid uuid;
    int hp;
    qreal speed, orignSpeed;
    int attack, orignAttack;
    int altitude;
    bool beAttacked, isAttacking, goingDie;

    qreal X, ZX;
    qreal attackedLX, attackedRX;
    int row;
    const Zombie *zombieProtoType;

    QString normalGif, attackGif, lostHeadGif, lostHeadAttackGif;


    QTimer *frozenTimer;
    QGraphicsPixmapItem *shadowPNG;
    MoviePixmapItem *picture;
};

class OrnZombie1: public Zombie1
{
    Q_DECLARE_TR_FUNCTIONS(OrnZombie1)
public:
    int ornHp;
    QString ornLostNormalGif, ornLostAttackGif;
};

class OrnZombieInstance1: public ZombieInstance
{
public:
    OrnZombieInstance1(const Zombie *zombie);
    const OrnZombie1 *getZombieProtoType();
    virtual void getHit(int attack);

    int ornHp;
    bool hasOrnaments;
};

class ConeheadZombie: public OrnZombie1
{
    Q_DECLARE_TR_FUNCTIONS(ConeheadZombie)
public:
    ConeheadZombie();
};

class ConeheadZombieInstance: public OrnZombieInstance1
{
public:
    ConeheadZombieInstance(const Zombie *zombie);
    virtual void playNormalballAudio();

};

class BucketheadZombie: public ConeheadZombie
{
    Q_DECLARE_TR_FUNCTIONS(BucketheadZombie)
public:
    BucketheadZombie();
};

class BucketheadZombieInstance: public OrnZombieInstance1
{
public:
    BucketheadZombieInstance(const Zombie *zombie);
    virtual void playNormalballAudio();

};

class PoleVaultingZombie: public Zombie1
{
    Q_DECLARE_TR_FUNCTIONS(PoleVaultingZombie)
public:
    PoleVaultingZombie();

    QString walkGif, lostHeadWalkGif, jumpGif1, jumpGif2;
};

class PoleVaultingZombieInstance: public ZombieInstance
{
    Q_DECLARE_TR_FUNCTIONS(PoleVaultingZombieInstance)
public:
    PoleVaultingZombieInstance(const Zombie *zombie);
    virtual QPointF getShadowPos();
    virtual QPointF getDieingHeadPos();
    virtual void judgeAttack();
    virtual void normalAttack(PlantInstance *plantInstance);
    const PoleVaultingZombie *getZombieProtoType();
    // TODO: getFreeze
    bool judgeAttackOrig, lostPole, beginCrushed;
    qreal posX; // Just forward message to normalAttack
};


Zombie *ZombieFactory(GameScene *scene, const QString &ename);
ZombieInstance *ZombieInstanceFactory(const Zombie *zombie);

#endif //PLANTS_VS_ZOMBIES_ZOMBIE_H
