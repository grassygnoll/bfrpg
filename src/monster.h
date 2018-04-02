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
        int SpecialAbilityBonus ;
        int AttackBonus ;
} ;

struct monsterAttacks {
        int Nbr ;
        char* Type ;
} ;

struct monsterDmg {
        int NbrDice ;
        int DieType ;
} ;

struct monsterMove {
        char* Type ;
        int Distance ;
        int TurningDistance ;
} ;

struct monsterNbrAppearing {
        char* Type ;
        int NbrDice ;
        int DieType ;
} ;

struct monsterSaveAs {
        char* Class ;
        int Level ;
} ;

typedef struct monster {
        char* Name ;
        struct monsterAC AC ;
        struct monsterHD HitDice ;
        struct monsterAttacks NbrAttacks[MAX_NBR_ATTACKS] ;
        struct monsterDmg Dmg[MAX_NBR_ATTACKS] ;
        struct monsterMove Movement[NBR_MOVE_TYPES] ;
        int morale ;
        struct monsterNbrAppearing NbrAppearing[NBR_APPEARING_TYPES] ;
        struct monsterSaveAs SaveAs ;
        char* TreasureType ;
        int Exp ;
} Monster ;


// Functions
void init(Monster*) ;

