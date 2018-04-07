/*****************************************************************************/
/* monster.h                                                                 */
/* 3/31/2018                                                                 */
/* B Wheeless                                                                */
/*                                                                           */
/* Header file for monster information.                                      */
/*****************************************************************************/

#define MAX_NBR_ATTACKS        3
#define NBR_MOVE_TYPES         3
#define NBR_APPEARING_TYPES    3
#define MAX_LEN                30

struct monsterAC {
        int Armored ;
        int UnArmored ;
        char HitBySilver ;
        char HitByMagical ;
} ;

struct monsterHD {
        int NbrDice ;
        int DieType ;
        int BonusHP ;
        int SpecialAbilityBonus ;   //Possible values of 0,1,2
        int AttackBonus ;
} ;

struct monsterAttacks {
        int Nbr ;
        char Type[MAX_LEN] ;
} ;

struct monsterDmg {
        int NbrDice ;
        int DieType ;
} ;

struct monsterMove {
        char Type[MAX_LEN] ;
        int Distance ;
        int TurningDistance ;
} ;

struct monsterNbrAppearing {
        char Type[MAX_LEN] ;
        int NbrDice ;
        int DieType ;
} ;

struct monsterSaveAs {
        char Class[MAX_LEN] ;
        int Level ;
} ;

typedef struct monster {
        char Name[MAX_LEN] ;
        struct monsterAC AC ;
        struct monsterHD HitDice ;
        struct monsterAttacks NbrAttacks[MAX_NBR_ATTACKS] ;
        struct monsterDmg Dmg[MAX_NBR_ATTACKS] ;
        struct monsterMove Movement[NBR_MOVE_TYPES] ;
        int morale ;
        struct monsterNbrAppearing NbrAppearing[NBR_APPEARING_TYPES] ;
        struct monsterSaveAs SaveAs ;
        char TreasureType[MAX_LEN] ;
        int Exp ;
} Monster ;


// Functions
void init(Monster*) ;
void manualMonsterEntry(Monster*) ;
int WriteMonster( FILE*, Monster* ) ;
void StoreMonster( FILE*, Monster* ) ;
void PrintMonster( Monster* ) ;
