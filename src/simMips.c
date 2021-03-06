/**
 * @file simMips.c
 * @author François Cayre, Nicolas Castagné
 * @date Fri Jun 15 18:13:02 2012 puis aout 2013
 * @brief Main pour le début du projet simulateur MIPS.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/* la librairie readline */
#include <readline/readline.h>
#include <readline/history.h>

/* macros de DEBUG_MSG fournies , etc */
#include "notify.h"

/* Inclusion de tous les fichiers de fonction externe */
#include "bp.h"
#include "da.h"
#include "db.h"
#include "dm.h"
#include "dr.h"
#include "er.h"
#include "ex.h"
#include "lm.h"
#include "lp.h"
#include "lr.h"
#include "run.h"
#include "s.h"
#include "si.h"

#include "mips.h"
#include "hash_cmd.h"
#include "initMips.h"
#include "mipself.h"
#include "readELF.h"
#include "list.h"

#include "parseNumber.h"

/* prompt du mode shell interactif */
#define PROMPT_STRING "SimMipsShell : > "

/*************************************************************\
Les commandes du simulateur.

 Dans cette version, deux commandes :
	"testcmd" qui attend un nombre hexa strictement positif et affiche ce nombre +1 dans le terminal
	"exit" qui quitte le simulateur

 Deux fonctions C par commande :
	1/ une qui parse les paramètres "parse_and_execute_cmd_<nomdecommande>(char *)"
	2/ une qui exécute la commande "execute_cmd_<nomdecommande>(...)"
 \*************************************************************/
int execute_cmd_testcmd(int hexValue) {
    if(hexValue <= 0) {
        WARNING_MSG("command %s  - invalid call. The argument should be positive.\n", "test");
        return 2;
    }

    /* ecriture du resultat de la commande dans la sortie standard */
    fprintf(stdout, "CMD TEST RESULT 0x%x\n", hexValue + 1);

    /* Notez que c'est le SEUL fprintf(stdout ...) (donc le seul "printf") de tout le programme ! */

    return CMD_OK_RETURN_VALUE;
}

int parse_and_execute_cmd_testcmd(char * paramsStr) {
    DEBUG_MSG("Parametres : %s", paramsStr);
    /* la commande test attend un argument hexa */
    int hexValue;

    /* ATTENTION : dans cet exemple de code,
     on suppose que le nombre qui suit est bien au format hexa avec le %x.

     Votre simulateur devra etre capable de differencier les
     formats de nombre, eg 0x10 (hexa), 020 (octal), 16 (decimal)...*/

    if(sscanf(paramsStr, "%x", &hexValue) != 1 ) {
        WARNING_MSG("Invalid param : hexadecimal number awaited in '%s'\n", paramsStr);
        return 2;
    }
    return execute_cmd_testcmd(hexValue);
}


/***************/
/*
int execute_cmd_exit() {
    INFO_MSG("Bye bye !");
    return CMD_EXIT_RETURN_VALUE;
}

int parse_and_execute_cmd_exit(char * paramsStr) {
    //on ignore tous les parametres !
    return execute_cmd_exit();
}
*/


/*************************************************************\
 Les deux fonctions principales du simulateur.
	parse_and_execute_cmd_string ( char *) parse la commande et l'execute en appelant la bonne fonction C
	acquire_line( FILE *, char *) : recupere une ligne (donc une "commande") dans le flux
 \*************************************************************/
/**
 * @fn uint  parse_and_execute_cmd_string( char *input )
 *
 * @brief parse la chaine input a la recherche d'une commande, et execute cette commande.
 *
 * @return CMD_OK_RETURN_VALUE si la commande s'est exécutée avec succès (0)
 * @return CMD_EXIT_RETURN_VALUE si c'est la commande exit. Dans ce cas, le programme doit se terminer. (-1)
 * @return CMD_EMPTY_RETURN_VALUE si input n'a aucune commande (chaine vide) ou si commentaire (# qq chose) (-2)
 * @return CMD_UNKOWN_RETURN_VALUE si la commande n'est pas reconnue. (-3)
 * @return tout autre nombre (eg tout nombre positif) si erreur d'execution de la commande
 */

int parse_and_execute_cmd_string(char *input, mips * pMips) {
    DEBUG_MSG("input '%s'", input);
    char cmdStr[MAX_STR];
    int hasher;
    char* adArg; // adress of the first command argument
    memset( cmdStr, '\0', MAX_STR );

    /* gestion des commandes vides, commentaires, etc*/
    if(strlen(input) == 0
            || sscanf(input, "%s", cmdStr) == 0
            || strlen(cmdStr) == 0
            || cmdStr[0] == '#') { /* ligne commence par # => commentaire*/
        return CMD_EMPTY_RETURN_VALUE;
    }

    /* hashage de la commande */
    hasher = hashageCmd(cmdStr);

    adArg = input + strlen(cmdStr);

    /*parsing et execution des commandes !*/
    switch(hasher)
    {
        case HASH_BP :
	    return parseBp(pMips, adArg);
	    break;
	case HASH_DA :
	    return parseDa(pMips, adArg);
	    break;
	case HASH_DB :
	    return parseDb(pMips, adArg);
	    break;
        case HASH_DM :
	    return parseDm(pMips, adArg);
	    break;
	case HASH_DR :
	    return parseDr(pMips, adArg);
	    break;
	case HASH_ER :
	    return parseEr(pMips, adArg);
	    break;
        case HASH_EX :
	    return parseEx(pMips, adArg);
	    break;
	case HASH_LM :
	    return parseLm(pMips, adArg);
	    break;
	case HASH_LP :
	    return parseLp(pMips, adArg);
	    break;
	case HASH_LR :
	    return parseLr(pMips, adArg);
	    break;
	case HASH_RUN :
	    return parseRun(pMips, adArg);
	    break;
	case HASH_S :
	    return parseS(pMips, adArg);
	    break;
	case HASH_SI :
	    return parseSi(pMips, adArg);
	    break;
        default :
	    WARNING_MSG("Unknown Command : '%s'\n", cmdStr);
    }
    return CMD_UNKOWN_RETURN_VALUE;
}


/**
 * @fn uint  acquire_line( FILE *fp, char *input )
 *
 * @brief extrait la prochaine ligne la flux fp.
 * Si fp ==stdin, utilise la librairie readline pour gestion d'historique de commande.
 *
 * @return 0 si succes.
 * @return un nombre non nul si aucune ligne lue
 */
int  acquire_line(FILE *fp, char * input) {
    memset( input, '\0', MAX_STR );
    if ( stdin == fp ) {
        /* mode shell interactif */
        /* on utilise la librarie libreadline pour disposer d'un historique */
        char *chunk = readline( PROMPT_STRING );
        if (  strlen(chunk) == 0) {
            /* commande vide... */
            return 1;
        }
        /* ajout de la commande a l'historique, librairie readline */
        add_history( chunk );
        strcpy( input, chunk );

        free( chunk ); /* liberation de la mémoire allouée par la fonction readline() de libreadline */
    }
    else {
        /* mode fichier */
        /* acquisition d'une ligne dans le fichier */
        char * ret = fgets( input, MAX_STR, fp );
        if(ret == NULL) {
            return 1;
        }
    if(strlen(ret) >0 && ret[strlen(ret) -1] == '\n') {
 ret[strlen(ret)-1] = '\0';
 }
    }
    DEBUG_MSG("Ligne acquise '%s'", input); /* macro DEBUG_MSG : uniquement si compil en mode DEBUG_MSG */
    return 0;
}


/****************/
void usage_ERROR_MSG( char *command ) {
    fprintf( stderr, "Usage: %s [file.sim]\n   If no file is given, executes in Shell mode.", command );
}


/**
 * Programme principal
 */
int main ( int argc, char *argv[] ) {
    /* exemples d'utilisation des macros du fichier notify.h */
    INFO_MSG("Un message INFO_MSG : Debut du programme %s", argv[0]); /* macro INFO_MSG */
    WARNING_MSG("Un message WARNING_MSG !"); /* macro INFO_MSG */
    DEBUG_MSG("Un message DEBUG_MSG !"); /* macro DEBUG_MSG : uniquement si compil en mode DEBUG_MSG */

    FILE *fp = NULL; /* le flux dans lequel les commande seront lues : stdin (mode shell) ou un fichier */
    mips uP;

    if ( argc > 2 ) {
        usage_ERROR_MSG( argv[0] );
        exit( EXIT_FAILURE );
    }
    if(argc == 2 && strcmp(argv[1], "-h") == 0) {
        usage_ERROR_MSG( argv[0] );
        exit( EXIT_SUCCESS );
    }

    if( initMips( &uP, "bob", "dico.txt" ) )
    {
	ERROR_MSG( "Failed while initializing mips" );
    }

    // Mips initialization
    //uP = initMips( "bob", 1, 2, 3 );
    // Give it a name :)
    //uP.name = (char *) malloc( 4 * sizeof( char ) );
    //uP.name = "bob";

    //uP.regPC = 0;
    //uP.registers[0] = 0;

    // break point list initialization
    //uP.bpList = NULL;

    /*par defaut : mode shell interactif */
    fp = stdin;
    if(argc == 2) {
        /* mode fichier de commandes */
        fp = fopen( argv[1], "r" );
        if ( fp == NULL ) {
            perror( "fopen" );
            exit( EXIT_FAILURE );
        }
    }

    //if(loadDico(&uP))
    //ERROR_MSG("Failed to load dictionnary\n");

    /* boucle principale : lit puis execute une cmd en boucle */
    while ( 1 ) {
        char input[MAX_STR];
        if ( acquire_line( fp,  input )  == 0 ) {
            /* Une nouvelle ligne a ete acquise dans le flux fp*/
            int res = parse_and_execute_cmd_string(input, &uP); /* execution de la commande */
            switch(res) {
            case CMD_OK_RETURN_VALUE: /* tout s'est bien passé */
                break;
            case CMD_EMPTY_RETURN_VALUE: /* commande vide */
                /* rien a faire ! */
                break;
            case CMD_EXIT_RETURN_VALUE:
                /* sortie propre du programme */
                if ( fp != stdin ) {
                    fclose( fp );
                }
                exit(EXIT_SUCCESS);
                break;
            default:
                /* erreur durant l'execution de la commande */
                /* En mode "fichier" toute erreur implique la fin du programme ! */
                if ( fp != stdin ) {
                    fclose( fp );
                    /*macro ERROR_MSG : message d'erreur puis fin de programme ! */
                    ERROR_MSG("ERREUR DETECTEE. Aborts");
                }
                break;
            }
        }
        if( fp != stdin && feof(fp) ) {
            /* mode fichier, fin de fichier => sortie propre du programme */
            DEBUG_MSG("FIN DE FICHIER");
            fclose( fp );
            exit(EXIT_SUCCESS);
        }
    }
    /* tous les cas de sortie du programme sont gérés plus haut*/
    ERROR_MSG("SHOULD NEVER BE HERE\n");
}
