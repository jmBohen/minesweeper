#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

// ALL DEFINITIONS ARE FROM GAME DESCRIPTION LINKED IN README.md

//small board | easy mode
#define SMALL_SYMBOL 'E' //easy
#define SMALL_BOARD 9
#define SMALL_TIME_MINUTES 10
#define SMALL_NUMBER_OF_MINES 10

//medium board | medium mode
#define MEDIUM_SYMBOL 'M' 
#define MEDIUM_BOARD 16
#define MEIDUM_TIME_MINUTES 20
#define MEIDUM_NUMBER_OF_MINES 40

//large board | difficult mode
#define LARGE_SYMBOL 'D' //difficult
#define LARGE_BOARD_R 30
#define LARGE_BOARD_C 16
#define LARGE_TIME_MINUTES 40
#define LARGE_NUMBER_OF_MINES 99

//constants for setting up custom board 
#define CUSTOM_SYMBOL 'C' //custom
#define MINIMUM_SIZE 5
#define MAXIMUM_SIZE_R 24
#define MAXIMUM_SIZE_C 30
#define CUSTOM_TIME_MINUTES(a,b) ((a+b)*0.75)
#define CUSTOM_NUMBER_OF_MINES(a,b) ((a-4)*(b-4))

//basic queries used to ask user for input
#define SETTINGS_QUERY "Please choose the dificulty of your game:\n'e' - easy (9x9)\n'm' - medium (16x16)\n'd' - diffiuclt (30x16)\n'c' - custom\n-> "
#define CUSTOM_SETTINGS_QUERY_R "Enter number of rows (5 - 24): "
#define CUSTOM_SETTINGS_QUERY_C "Enter number of columns (5 - 30): "

//chars for board printing
#define UNREVEALED_CHAR (char)'#'
#define FLAG_CHAR (char)'F'
#define REVEALED_CLEAR_CHAR (char)' '
#define MINE_CHAR (char)'*'

#endif