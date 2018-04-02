/*****************************************************************************/
/* util.c                                                                    */
/* 4/01/2018                                                                 */
/* B Wheeless                                                                */
/*                                                                           */
/* Contains code for manual input of monster data, saving of monster data,   */
/* and other miscellaneous data processing routines for monster data.        */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "monster.h"
#include "util.h"

/*****************************************************************************/
/* openDBtoWrite() - accepts filename and returns opened file handle         */
/*****************************************************************************/
FILE* openDBtoWrite( const char* Name ) {
        return fopen( Name, "a" ) ;
}

/*****************************************************************************/
/* WriteMonster() - Accepts filehandle and Pointer to monster object         */
/*                - Writes monster data to text file                         */
/*****************************************************************************/
int WriteMonster( FILE* db, Monster* m ) {
        fprintf( db, "%s|%i|%i|%c|%c|%i|%i|%i|%i|%i|", m->Name, m->AC.Armored,
                       m->AC.UnArmored, m->AC.HitBySilver, m->AC.HitByMagical,
                       m->HitDice.NbrDice, m->HitDice.DieType, m->HitDice.BonusHP,
                       m->HitDice.SpecialAbilityBonus, m->HitDice.AttackBonus ) ;
        for(int i = 0; i < MAX_NBR_ATTACKS; i++)
            fprintf( db, "%i|%s|", m->NbrAttacks[i].Nbr, m->NbrAttacks[i].Type ) ;
        for(int i = 0; i < MAX_NBR_ATTACKS; i++)
            fprintf( db, "%i|%i|", m->Dmg[i].NbrDice, m->Dmg[i].DieType ) ;
        for(int i = 0; i < NBR_MOVE_TYPES; i++)
            fprintf( db, "%s|%i|%i|", m->Movement[i].Type, m->Movement[i].Distance,
                            m->Movement[i].TurningDistance ) ;
        fprintf( db, "%i|", m->morale ) ;
        for(int i = 0; i < NBR_APPEARING_TYPES; i++)
            fprintf( db, "%s|%i|%i|", m->NbrAppearing[i].Type, m->NbrAppearing[i].NbrDice,
                            m->NbrAppearing[i].DieType ) ;
        fprintf( db, "%s|%i|%s|%i\n", m->SaveAs.Class, m->SaveAs.Level, m->TreasureType,
                        m->Exp ) ;

        return 0 ;
}

/*****************************************************************************/
/* closeDB() - Accepts filehandle and closes file it points to.              */
/*****************************************************************************/
int closeDB( FILE* db ) {
        fclose(db) ;
        return 0 ;
}

/*****************************************************************************/
/* init() - Accepts a monster sturcture and populates it with defaults.      */
/*****************************************************************************/
void init(Monster* Mon) {
        Mon->Name = NULL ;
        Mon->AC.Armored = 20 ;
        Mon->AC.UnArmored = 20 ;
        Mon->AC.HitBySilver = 'N' ;
        Mon->AC.HitByMagical = 'N' ;
        Mon->HitDice.NbrDice = 0 ;
        Mon->HitDice.DieType = 0 ;
        Mon->HitDice.BonusHP = 0 ;
        Mon->HitDice.SpecialAbilityBonus = 0 ;
        Mon->HitDice.AttackBonus = 0 ;
        for( int i = 0; i < MAX_NBR_ATTACKS; i++ ) {
            Mon->NbrAttacks[i].Nbr = 0 ;
            Mon->NbrAttacks[i].Type = NULL ;
            Mon->Dmg[i].NbrDice = 0 ;
            Mon->Dmg[i].DieType = 0 ;
        }
        for( int i = 0; i < NBR_MOVE_TYPES; i++ ) {
            Mon->Movement[i].Type = NULL ;
            Mon->Movement[i].Distance = 30 ;
            Mon->Movement[i].TurningDistance = 5 ;
        }
        Mon->morale = 0 ;
        for( int i = 0; i < NBR_APPEARING_TYPES; i++ ) {
            Mon->NbrAppearing[i].Type = NULL ;
            Mon->NbrAppearing[i].NbrDice = 0 ;
            Mon->NbrAppearing[i].DieType = 0 ;
        }
        Mon->SaveAs.Class = NULL ;
        Mon->SaveAs.Level = 0 ;
        Mon->TreasureType = NULL ;
        Mon->Exp = 0 ;
}
